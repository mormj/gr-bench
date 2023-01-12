/*

Scheduler benchmarking script B - sequential Math operations

*/

#include <chrono>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <gnuradio/blocks/add_const_ff.h>
#include <gnuradio/blocks/multiply_const.h>
#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>
#include <bench/head_nop_latency_sink.h>
#include <bench/nop_latency_source.h>
#include <bench/nop_source.h>


#include <fstream>
#include <iostream>
#include <numeric>

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
        auto src = bench::nop_latency_source::make(itemsize, "/tmp/src.txt", 100000, 500);
        auto snk = bench::head_nop_latency_sink::make(
            itemsize, samples, "/tmp/snk.txt", 100000, 500);

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


        std::ifstream in1("/tmp/src.txt");
        std::ifstream in2("/tmp/snk.txt");

        std::string line1, line2;

        std::vector<double> meas_latency_vec;
        while (getline(in1, line1)) {
            if (getline(in2, line2)) {

                double i1 = double(std::stoll(line1));
                double i2 = double(std::stoll(line2));

                if (i2 < i1) {

                    std::cout << i2 << " " << i1 << std::endl;
                }

                double latency = i2 - i1;
                std::cout << latency << std::endl;

                meas_latency_vec.push_back(double(latency));
            }
        }

        double mean_latency =
            std::accumulate(meas_latency_vec.begin(), meas_latency_vec.end(), 0) /
            double(meas_latency_vec.size());
        std::cout << "[PROFILE_LATENCY_MEAN]" << mean_latency << "[PROFILE_LATENCY_MEAN]"
                  << std::endl;
    }
}
