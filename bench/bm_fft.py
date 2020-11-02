#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.9.0.0-git

from gnuradio import gr, blocks, fft
import sys
import signal
from argparse import ArgumentParser
import time
from gnuradio.fft import window


class benchmark_fft(gr.top_block):

    def __init__(self, args):
        gr.top_block.__init__(self, "Benchmark FFT", catch_exceptions=True)

        ##################################################
        # Variables
        ##################################################
        nsamples = args.samples
        fft_size = args.fftsize
        actual_samples = int(nsamples /  fft_size)
        num_blocks = args.nblocks
        win = args.window if hasattr(args,'window') and args.window else ''

        # Apply window equal to FFT Size
        fftwin = []
        if win.lower() == 'blackmanharris':
            fftwin = window.blackman_harris(fft_size)
        elif win.lower().startswith('rect'):
            fftwin = window.rectangular(fft_size)
        elif win.lower() == 'hamming':
            fftwin = window.hamming(fft_size)

        ##################################################
        # Blocks
        ##################################################
        blks = []
        for i in range(num_blocks):
            blks.append(
                fft.fft_vcc(
                    fft_size, True, fftwin)
            )

        self.blocks_null_source_0 = blocks.null_source(
            gr.sizeof_gr_complex*fft_size)
        self.blocks_null_sink_0 = blocks.null_sink(
            gr.sizeof_gr_complex*fft_size)
        self.blocks_head_0 = blocks.head(
            gr.sizeof_gr_complex*fft_size, actual_samples)

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

    parser = ArgumentParser(description='Run a flowgraph iterating over parameters for benchmarking')
    parser.add_argument('--rt_prio', help='enable realtime scheduling', action='store_true')
    parser.add_argument('--samples', type=int, default=2e8)
    parser.add_argument('--fftsize', type=int, default=1)
    parser.add_argument('--window', type=int)
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
