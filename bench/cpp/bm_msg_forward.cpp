#include <chrono>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>
#include <bench/msg_forward.h>

using namespace gr;


int main(int argc, char* argv[])
{
    uint64_t samples;
    int nblocks;
    uint64_t pdu_size;
    bool rt_prio = false;

    po::options_description desc("Basic Test Flow Graph");
    desc.add_options()("help,h", "display help")(
        "samples",
        po::value<uint64_t>(&samples)->default_value(1000),
        "Number of bursts")(
        "pdu_size",
        po::value<uint64_t>(&pdu_size)->default_value(5000),
        "Size of packet")(
        "nblocks", po::value<int>(&nblocks)->default_value(50), "Number of nop blocks")(
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

        std::vector<bench::msg_forward::sptr> msg_blks(nblocks);
        for (int i = 0; i < nblocks; i++) {
            msg_blks[i] = bench::msg_forward::make();
        }
        
        auto fg = make_top_block("msg_flowgraph");

        for (int i = 1; i < nblocks; i++) {
            fg->msg_connect(msg_blks[i-1], "out", msg_blks[i], "in");
        }


        for(int p = 0; p < samples; p++) {
            pmt::pmt_t msg = pmt::cons(pmt::PMT_NIL, pmt::make_u8vector(pdu_size, 0x42));
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
        // for (int i = 0; i < nblocks; i++) {
        //     std::cout << "nout_avg: " << msg_blks[i]->pc_noutput_items_avg() << std::endl;
        // }

        // for (auto& b : msg_blks)
        // {
        //     std::cout << b->message_count() << ", ";
        // }
        // std::cout << std::endl;
        
    }
}
