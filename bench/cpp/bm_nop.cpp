#include <chrono>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>
#include <bench/nop_source.h>
#include <gnuradio/blocks/null_sink.h>
#include <bench/nop.h>
#include <bench/nop_head.h>

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
        auto src = bench::nop_source::make(sizeof(gr_complex) * veclen);
        auto head = bench::nop_head::make(sizeof(gr_complex) * veclen, samples / veclen);
        auto snk = blocks::null_sink::make(sizeof(gr_complex) * veclen);
        std::vector<bench::nop::sptr> nop_blks(nblocks);
        for (int i = 0; i < nblocks; i++) {
            nop_blks[i] = bench::nop::make(sizeof(gr_complex) * veclen);
        }
        
        auto fg = make_top_block("nop_flowgraph");

        fg->connect(src, 0, head, 0);
        fg->connect(head, 0, nop_blks[0], 0);
        for (int i = 0; i < nblocks - 1; i++) {
            fg->connect(nop_blks[i], 0, nop_blks[i + 1], 0);
        }
        fg->connect(nop_blks[nblocks - 1], 0, snk, 0);

        auto t1 = std::chrono::steady_clock::now();

        fg->start();
        fg->wait();

        auto t2 = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

        std::cout << "[PROFILE_TIME]" << time << "[PROFILE_TIME]" << std::endl;
    }
}
