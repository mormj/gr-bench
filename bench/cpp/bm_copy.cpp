#include <chrono>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>
#include <gnuradio/blocks/null_source.h>
#include <gnuradio/blocks/null_sink.h>
#include <gnuradio/blocks/copy.h>
#include <gnuradio/blocks/head.h>

using namespace gr;


int main(int argc, char* argv[])
{
    uint64_t samples;
    int nblocks;
    int nthreads;
    int veclen;
    int buffer_type;
    bool rt_prio = false;

    po::options_description desc("Basic Test Flow Graph");
    desc.add_options()("help,h", "display help")(
        "samples",
        po::value<uint64_t>(&samples)->default_value(15000000),
        "Number of samples")(
        "veclen", po::value<int>(&veclen)->default_value(1), "Vector Length")(
        "nblocks", po::value<int>(&nblocks)->default_value(1), "Number of nop blocks")(
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
        auto src = blocks::null_source::make(sizeof(gr_complex) * veclen);
        auto head = blocks::head::make(sizeof(gr_complex) * veclen, samples / veclen);
        auto snk = blocks::null_sink::make(sizeof(gr_complex) * veclen);
        std::vector<blocks::copy::sptr> copy_blks(nblocks);
        for (int i = 0; i < nblocks; i++) {
            copy_blks[i] = blocks::copy::make(sizeof(gr_complex) * veclen);
        }
        
        auto fg = make_top_block("nop_flowgraph");

        fg->connect(src, 0, head, 0);
        fg->connect(head, 0, copy_blks[0], 0);
        for (int i = 0; i < nblocks - 1; i++) {
            fg->connect(copy_blks[i], 0, copy_blks[i + 1], 0);
        }
        fg->connect(copy_blks[nblocks - 1], 0, snk, 0);

        auto t1 = std::chrono::steady_clock::now();

        fg->start();
        fg->wait();

        auto t2 = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

        std::cout << "[PROFILE_TIME]" << time << "[PROFILE_TIME]" << std::endl;
        // for (int i = 0; i < nblocks; i++) {
        //     std::cout << "nout_avg: " << copy_blks[i]->pc_noutput_items_avg() << std::endl;
        // }
        
    }
}
