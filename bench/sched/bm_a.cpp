/*

Scheduler benchmarking script A - blocks with varying nproduce

*/

#include <chrono>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>
#include <bench/head_null_sink.h>
#include <bench/nop.h>
#include <bench/copy.h>
#include <bench/nop_source.h>

using namespace gr;


int main(int argc, char* argv[])
{
    uint64_t samples, itemsize;
    bool rt_prio = false;
    uint64_t N1, N2, N3;
    bool use_memcpy = true;

    // clang-format off
    po::options_description desc("Basic Test Flow Graph");
    desc.add_options()("help,h", "display help")
       ("samples", po::value<uint64_t>(&samples)->default_value(1000000000),"Number of samples")
       ("itemsize", po::value<uint64_t>(&itemsize)->default_value(sizeof(float)),"itemsize")
       ("N1", po::value<uint64_t>(&N1)->default_value(8192),"N1")
       ("N2", po::value<uint64_t>(&N2)->default_value(8192),"N2")
       ("N3", po::value<uint64_t>(&N3)->default_value(8192),"N3")
       ("rt_prio", "Enable Real-time priority")
       ("no_memcpy", "don't use memcpy");
    // clang-format on

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

    if (vm.count("no_memcpy")) {
        use_memcpy = false;
    }

    if (rt_prio && gr::enable_realtime_scheduling() != RT_OK) {
        std::cout << "Error: failed to enable real-time scheduling." << std::endl;
    }

    {
        auto src = bench::nop_source::make(itemsize, N1);
        auto snk = bench::head_null_sink::make(itemsize, samples);

        auto b1 = bench::copy::make(itemsize, use_memcpy, N2);
        auto b2 = bench::copy::make(itemsize, use_memcpy, N1);
        auto b3 = bench::copy::make(itemsize, use_memcpy, N3);

        // src->set_max_output_buffer(0, 4096);
        // b1->set_max_output_buffer(0, 4096);
        // b2->set_max_output_buffer(0, 4096);
        // b3->set_max_output_buffer(0, 4096);

        auto fg = make_top_block("nop_flowgraph");

        fg->connect(src, 0, b1, 0);
        fg->connect(b1, 0, b2, 0);
        fg->connect(b2, 0, b3, 0);
        fg->connect(b3, 0, snk, 0);

        auto t1 = std::chrono::steady_clock::now();

        fg->start();
        fg->wait();

        auto t2 = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

        std::cout << "[PROFILE_TIME]" << time << "[PROFILE_TIME]" << std::endl;
        // for (int i = 0; i < nblocks; i++) {
        //     std::cout << "nout_avg: " << copy_blks[i]->pc_noutput_items_avg() <<
        //     std::endl;
        // }
    }
}
