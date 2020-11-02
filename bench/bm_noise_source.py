#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.9.0.0-git

from gnuradio import gr, blocks, analog
from gnuradio.filter import firdes
import sys
import signal
from argparse import ArgumentParser
import time

class benchmark_noise_source(gr.top_block):

    def __init__(self, args):
        gr.top_block.__init__(self, "Not titled yet", catch_exceptions=True)

        ##################################################
        # Variables
        ##################################################
        nsamples = args.samples
        veclen = args.veclen
        actual_samples = int(nsamples / veclen)
        ntype = args.ntype if args.ntype else analog.GR_GAUSSIAN

        ##################################################
        # Blocks
        ##################################################

        src = analog.noise_source_c(ntype, 10.0, 0)
        snk = blocks.null_sink(
            gr.sizeof_gr_complex*veclen)
        head_blk = blocks.head(
            gr.sizeof_gr_complex*veclen, actual_samples)

        ##################################################
        # Connections
        ##################################################
        self.connect((head_blk, 0), (snk, 0))
        self.connect((src, 0), (head_blk, 0))


def main(top_block_cls=benchmark_noise_source, options=None):

    parser = ArgumentParser(
        description='Run a flowgraph iterating over parameters for benchmarking')
    parser.add_argument(
        '--rt_prio', help='enable realtime scheduling', action='store_true')
    parser.add_argument('--samples', type=int, default=1e9)
    parser.add_argument('--veclen', type=int, default=1)
    parser.add_argument('--ntype', type=int)

    args = parser.parse_args()
    print(args)

    if args.rt_prio and gr.enable_realtime_scheduling() != gr.RT_OK:
        print("Error: failed to enable real-time scheduling.")

    tb = top_block_cls(args)

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()
        sys.exit(0)

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    print("starting ...")
    startt = time.time()
    tb.start()

    tb.wait()
    endt = time.time()

    print(f'[PROFILE_TIME]{endt-startt}[PROFILE_TIME]')


if __name__ == '__main__':
    main()
