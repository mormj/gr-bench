#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.9.0.0-git

from gnuradio import gr, blocks, fft, filter, dtv, analog
from gnuradio.filter import firdes
import pmt
import sys
import signal
from argparse import ArgumentParser
import time
from gnuradio.fft import window


class file_atsc_tx(gr.top_block):

    def __init__(self, args):
        gr.top_block.__init__(self, "File Atsc Rx", catch_exceptions=True)

        ##################################################
        # Variables
        ##################################################
        self.symbol_rate = symbol_rate = 4500000.0 / 286 * 684
        self.sps = sps = 1.1
        self.atsc_sym_rate = atsc_sym_rate = 4.5e6/286*684
        self.sample_rate = sample_rate = atsc_sym_rate*sps
        self.pilot_freq = pilot_freq = (6000000.0 - (symbol_rate / 2)) / 2
        self.oversampled_rate = oversampled_rate = atsc_sym_rate*sps
        self.center_freq = center_freq = 429e6
        self.capt_sample_rate = capt_sample_rate = 20e6

        ##################################################
        # Blocks
        ##################################################
        self.filter_fft_rrc_filter_0 = filter.fft_filter_ccc(1, firdes.root_raised_cosine(1, sample_rate, atsc_sym_rate/2.0, 0.1152, 50), 1)
        self.dtv_atsc_viterbi_decoder_0 = dtv.atsc_viterbi_decoder()
        # self.dtv_atsc_viterbi_decoder_0.set_processor_affinity([2])
        self.dtv_atsc_sync_0 = dtv.atsc_sync(oversampled_rate)
        self.dtv_atsc_rs_decoder_0 = dtv.atsc_rs_decoder()
        self.dtv_atsc_fs_checker_0 = dtv.atsc_fs_checker()
        self.dtv_atsc_fpll_0 = dtv.atsc_fpll(oversampled_rate)
        # self.dtv_atsc_fpll_0.set_processor_affinity([0])
        self.dtv_atsc_equalizer_0 = dtv.atsc_equalizer()
        self.dtv_atsc_derandomizer_0 = dtv.atsc_derandomizer()
        self.dtv_atsc_depad_0 = dtv.atsc_depad()
        self.dtv_atsc_deinterleaver_0 = dtv.atsc_deinterleaver()
        self.dc_blocker_xx_0 = filter.dc_blocker_ff(4096, True)
        # self.dc_blocker_xx_0.set_processor_affinity([1])
        self.blocks_interleaved_short_to_complex_0_0 = blocks.interleaved_short_to_complex(False, False,32768)
        self.blocks_file_source_0_0 = blocks.file_source(gr.sizeof_short*1, args.infile, False, 0, 0)
        self.blocks_file_source_0_0.set_begin_tag(pmt.PMT_NIL)
        self.blocks_file_sink_0_0 = blocks.file_sink(gr.sizeof_char*1, args.outfile, False)
        self.blocks_file_sink_0_0.set_unbuffered(False)
        self.agc = analog.agc_ff(1e-5, 4.0, 1.0)
        self.agc.set_max_gain(65536)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.agc, 0), (self.dtv_atsc_sync_0, 0))
        self.connect((self.blocks_file_source_0_0, 0), (self.blocks_interleaved_short_to_complex_0_0, 0))
        self.connect((self.blocks_interleaved_short_to_complex_0_0, 0), (self.filter_fft_rrc_filter_0, 0))
        self.connect((self.dc_blocker_xx_0, 0), (self.agc, 0))
        self.connect((self.dtv_atsc_deinterleaver_0, 0), (self.dtv_atsc_rs_decoder_0, 0))
        self.connect((self.dtv_atsc_depad_0, 0), (self.blocks_file_sink_0_0, 0))
        self.connect((self.dtv_atsc_derandomizer_0, 0), (self.dtv_atsc_depad_0, 0))
        self.connect((self.dtv_atsc_equalizer_0, 0), (self.dtv_atsc_viterbi_decoder_0, 0))
        self.connect((self.dtv_atsc_fpll_0, 0), (self.dc_blocker_xx_0, 0))
        self.connect((self.dtv_atsc_fs_checker_0, 0), (self.dtv_atsc_equalizer_0, 0))
        self.connect((self.dtv_atsc_rs_decoder_0, 0), (self.dtv_atsc_derandomizer_0, 0))
        self.connect((self.dtv_atsc_sync_0, 0), (self.dtv_atsc_fs_checker_0, 0))
        self.connect((self.dtv_atsc_viterbi_decoder_0, 0), (self.dtv_atsc_deinterleaver_0, 0))
        self.connect((self.filter_fft_rrc_filter_0, 0), (self.dtv_atsc_fpll_0, 0))



def main(top_block_cls=file_atsc_tx, options=None):

    parser = ArgumentParser(description='Run a flowgraph iterating over parameters for benchmarking')
    parser.add_argument('--rt_prio', help='enable realtime scheduling', action='store_true')
    parser.add_argument('--samples', type=int, default=200000000)
    parser.add_argument('--infile')
    parser.add_argument('--outfile')

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
