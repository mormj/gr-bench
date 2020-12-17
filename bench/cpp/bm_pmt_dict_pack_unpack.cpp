#include <chrono>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <gnuradio/blocks/null_sink.h>
#include <gnuradio/realtime.h>
#include <gnuradio/top_block.h>
#include <bench/nop.h>
#include <bench/nop_head.h>
#include <bench/nop_source.h>

using namespace gr;
using namespace pmt;

bool run_test(const int times, uint64_t nitems)
{
    bool valid = true;
    for (int i = 0; i < times; i++) {

        auto d = pmt::make_dict();
        for (int k = 0; k < nitems; k++) {
            auto keypmt = pmt::intern("key" + std::to_string(k));
            auto value = pmt::from_long(k);
            d = dict_add(d, keypmt, value);
        }

        #if 0
        for (int k = 0; k < nitems; k++) {
            auto ref = pmt::dict_ref(d, pmt::intern("key" + std::to_string(k)), PMT_NIL);

            if (pmt::to_long(ref) != k)
                valid = false;
        }
        #endif
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
        "index", po::value<uint64_t>(&index)->default_value(0), "Index for lookup");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    {

        auto t1 = std::chrono::steady_clock::now();

        auto valid = run_test(samples, items);

        auto t2 = std::chrono::steady_clock::now();
        auto time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1e9;

        std::cout << "[PROFILE_TIME]" << time << "[PROFILE_TIME]" << std::endl;
        std::cout << "[PROFILE_VALID]" << valid << "[PROFILE_VALID]" << std::endl;
    }
}
