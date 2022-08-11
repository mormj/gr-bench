#include <chrono>
#include <iostream>
#include <thread>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>
#include <bench/pdu_process.h>
#include <bench/msg_forward.h>


using namespace gr;


int main(int argc, char* argv[])
{
    uint64_t pdus;
    uint64_t pdu_size;
    int nblocks;
    std::string data_type;
    bool rt_prio = false;

    po::options_description desc("Basic Test Flow Graph");
    desc.add_options()("help,h", "display help")(
        "pdus",
        po::value<uint64_t>(&pdus)->default_value(10000),
        "Number of bursts")(
        "pdu_size",
        po::value<uint64_t>(&pdu_size)->default_value(1024),
        "Size of packet")(
        "nblocks", po::value<int>(&nblocks)->default_value(4), "Number of pdu blocks")
        (
        "data_type", po::value<std::string>(&data_type)->default_value("rf32"), "Data type of pdu vector")(
        "rt_prio", "Enable Real-time priority");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("rt_prio")) {
        rt_prio = true;
    }


    if (rt_prio && gr::enable_realtime_scheduling() != RT_OK) {
        std::cout << "Error: failed to enable real-time scheduling." << std::endl;
    }

    {

        std::vector<basic_block_sptr> msg_blks(nblocks);
        // std::vector<bench::pdu_process<float>::sptr> msg_blks(nblocks);
        for (int i = 0; i < nblocks; i++) {
            // brute force do the type mappings here:
            if (data_type == "cf32")
                msg_blks[i] = bench::pdu_process<gr_complex>::make()->to_basic_block();
            else if (data_type == "rf32")
                msg_blks[i] = bench::pdu_process<float>::make()->to_basic_block();
            else if (data_type == "ri32")
                msg_blks[i] = bench::pdu_process<int32_t>::make()->to_basic_block();
            else if (data_type == "ri16")
                msg_blks[i] = bench::pdu_process<int16_t>::make()->to_basic_block();
            else if (data_type == "ru8")
                msg_blks[i] = bench::pdu_process<uint8_t>::make()->to_basic_block();
            else
                throw std::runtime_error("unsupported data type");

            // msg_blks[i] = bench::msg_forward::make();
        }
        auto fg = make_top_block("msg_flowgraph");

        for (int i = 1; i < nblocks; i++) {
            fg->msg_connect(msg_blks[i-1], "out", msg_blks[i], "in");
        }


        for(int p = 0; p < pdus; p++) {
            // brute force do the type mappings here:
            pmt::pmt_t msg;
            auto d = pmt::make_dict();
            d = pmt::dict_add(d, pmt::intern("field1"), pmt::intern("value1"));
            d = pmt::dict_add(d, pmt::intern("field2"), pmt::intern("value2"));
            if (data_type == "cf32")
                msg = pmt::cons(pmt::PMT_NIL, pmt::make_c32vector(pdu_size, gr_complex(123.456, -765.543)));
            else if (data_type == "rf32")
                msg = pmt::cons(pmt::PMT_NIL, pmt::make_f32vector(pdu_size, 123.456));
            else if (data_type == "ri32")
                msg = pmt::cons(pmt::PMT_NIL, pmt::make_s32vector(pdu_size, 0xABABCDCD));
            else if (data_type == "ri16")
                msg = pmt::cons(pmt::PMT_NIL, pmt::make_s16vector(pdu_size, 0x5A5A));
            else if (data_type == "ru8")
                msg = pmt::cons(pmt::PMT_NIL, pmt::make_u8vector(pdu_size, 0x42));
            else
                throw std::runtime_error("unsupported data type");
            
            msg_blks[0]->post(pmt::mp("in"), msg);
        }

        pmt::pmt_t msg = pmt::cons(pmt::intern("done"), pmt::from_long(1));
        msg_blks[0]->post(pmt::mp("system"), msg);

        auto t1 = std::chrono::steady_clock::now();

        fg->start();
        fg->wait();

        auto t2 = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

        std::cout << "[PROFILE_TIME]" << time << "[PROFILE_TIME]" << std::endl;
        
    }
}
