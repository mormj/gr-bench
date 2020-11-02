#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.9.0.0-git

from gnuradio import blocks
from gnuradio import gr
from gnuradio.filter import firdes
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio.fft import window
import time
import trt
import json
import datetime
import itertools


class benchmark_fft(gr.top_block):

    def __init__(self, args):
        gr.top_block.__init__(self, "Not titled yet", catch_exceptions=True)

        ##################################################
        # Variables
        ##################################################
        nsamples = args.samples
        veclen = args.veclen
        self.actual_samples = actual_samples = int(nsamples / veclen)
        num_blocks = args.nblocks

        ##################################################
        # Blocks
        ##################################################
        blks = []
        for i in range(num_blocks):
            blks.append(
                blocks.multiply_const_cc(1.0, veclen)
            )

        self.blocks_null_source_0 = blocks.null_source(
            gr.sizeof_gr_complex*veclen)
        self.blocks_null_sink_0 = blocks.null_sink(
            gr.sizeof_gr_complex*veclen)
        self.blocks_head_0 = blocks.head(
            gr.sizeof_gr_complex*veclen, actual_samples)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_head_0, 0), (blks[0], 0))
        self.connect((self.blocks_null_source_0, 0), (self.blocks_head_0, 0))

        for i in range(1, num_blocks):
            self.connect((blks[i-1], 0), (blks[i], 0))

        self.connect((blks[num_blocks-1], 0),
                     (self.blocks_null_sink_0, 0))


def main(top_block_cls=benchmark_fft, options=None):

    parser = ArgumentParser(
        description='Run a flowgraph iterating over parameters for benchmarking')
    parser.add_argument(
        '--rt_prio', help='enable realtime scheduling', action='store_true')
    parser.add_argument('--samples', type=int, default=1e9)
    parser.add_argument('--veclen', type=int, default=1)
    parser.add_argument('--nblocks', type=int, default=1)

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
