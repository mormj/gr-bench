/*

Scheduler benchmarking script B - sequential Math operations

*/

#include <chrono>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <bench/head_null_sink.h>
#include <bench/nop_source.h>
#include <gnuradio/blocks/add_const_ff.h>
#include <gnuradio/blocks/multiply_const.h>
#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>

using namespace gr;


int main(int argc, char* argv[])
{
    uint64_t samples; 
    uint64_t itemsize = 4; // use floats for this benchmark
    bool rt_prio = false;
    uint64_t stages = 1;

    // clang-format off
    po::options_description desc("Basic Test Flow Graph");
    desc.add_options()("help,h", "display help")
       ("samples", po::value<uint64_t>(&samples)->default_value(1000000000),"Number of samples")
       ("stages", po::value<uint64_t>(&stages)->default_value(1),"stages")
       ("rt_prio", "Enable Real-time priority");
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


    if (rt_prio && gr::enable_realtime_scheduling() != RT_OK) {
        std::cout << "Error: failed to enable real-time scheduling." << std::endl;
    }

    {
        auto src = bench::nop_source::make(itemsize);
        auto snk = bench::head_null_sink::make(itemsize, samples );

        auto fg = make_top_block("nop_flowgraph");

        

        basic_block_sptr last_block = src->to_basic_block();
        basic_block_sptr first_block = nullptr;
        for (size_t ii = 0; ii < stages; ii++) {
            auto b1 = blocks::add_const_ff::make(1.0);
            if (!first_block) {
                first_block = b1;
            }
            auto b2 = blocks::multiply_const_ff::make(2.0);
            auto b3 = blocks::multiply_const_ff::make(0.5);
            auto b4 = blocks::add_const_ff::make(-1.0);
            
            fg->connect(last_block, 0, b1, 0);
            fg->connect(b1, 0, b2, 0);
            fg->connect(b2, 0, b3, 0);
            fg->connect(b3, 0, b4, 0);

            last_block = b4->to_basic_block();
        }

        fg->connect(last_block, 0, snk, 0);

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
