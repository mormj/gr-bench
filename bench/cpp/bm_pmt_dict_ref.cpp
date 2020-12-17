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
using namespace pmt;

bool run_test(const int times, pmt_t d, uint64_t index)
{
    std::stringbuf sb; // fake channel

    auto key = pmt::intern("key"+std::to_string(index));

    bool valid = true;
    for (int i=0; i< times; i++)
    {
        auto ref = pmt::dict_ref(d, key, PMT_NIL);

        // if (pmt::equal(ref,PMT_NIL))
        //    valid = false;

        if (pmt::to_long(ref) != index)
           valid = false;
    }
    return valid;
}

int main(int argc, char* argv[])
{
    uint64_t samples;
    uint64_t items;
    uint64_t index;
    int nblocks;
    int nthreads;
    size_t veclen;
    int buffer_type;
    bool rt_prio = false;

    po::options_description desc("Basic Test Flow Graph");
    desc.add_options()("help,h", "display help")(
        "samples",
        po::value<uint64_t>(&samples)->default_value(10000),
        "Number of times to perform lookup")(
        "items",
        po::value<uint64_t>(&items)->default_value(100),
        "Number of items in dict")(
        "index",
        po::value<uint64_t>(&index)->default_value(0),
        "Index for lookup");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    {
        // Create the dictionary

        auto d = pmt::make_dict();
        for (int k = 0; k < items; k++)
        {
            auto keypmt = pmt::intern("key"+std::to_string(k));
            auto value = pmt::from_long(k);
            d = dict_add(d, keypmt, value);
        }

        auto t1 = std::chrono::steady_clock::now();

        auto valid = run_test(samples, d, index);

        auto t2 = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

        std::cout << "[PROFILE_TIME]" << time << "[PROFILE_TIME]" << std::endl;
        std::cout << "[PROFILE_VALID]" << valid << "[PROFILE_VALID]" << std::endl;
    }
}
