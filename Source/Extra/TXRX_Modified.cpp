////
//// Copyright 2010-2012,2014-2015 Ettus Research LLC
//// Copyright 2018 Ettus Research, a National Instruments Company
////
//// SPDX-License-Identifier: GPL-3.0-or-later
////
//
//#include "wavetable.hpp"
//#include <uhd/exception.hpp>
//#include <uhd/types/tune_request.hpp>
//#include <uhd/usrp/multi_usrp.hpp>
//#include <uhd/utils/safe_main.hpp>
//#include <uhd/utils/static.hpp>
//#include <uhd/utils/thread.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/format.hpp>
//#include <boost/math/special_functions/round.hpp>
//#include <boost/program_options.hpp>
//#include <boost/thread/thread.hpp>
//#include <csignal>
//#include <fstream>
//#include <functional>
//#include <iostream>
//#include "../External/Misc/ConsoleColor.h"
//#include <numbers>
//#include <stdio.h>
//
//namespace po = boost::program_options;
//
///***********************************************************************
// * Signal handlers
// **********************************************************************/
//
//static bool stop_signal_called = false;
//void sig_int_handler(int)
//{
//    stop_signal_called = true;
//}
//
//
///***********************************************************************
// * transmit_worker function
// * A function to be used as a boost::thread_group thread for transmitting
// **********************************************************************/
//
//void transmit_worker(std::vector<std::complex<float>> buff,
//    wave_table_class wave_table,
//    uhd::tx_streamer::sptr tx_streamer,
//    uhd::tx_metadata_t metadata,
//    size_t step,
//    size_t index,
//    int num_channels)
//{
//    std::vector<std::complex<float>*> buffs(num_channels, &buff.front());
//
//    // send data until the signal handler gets called
//    while (not stop_signal_called) {
//        // fill the buffer with the waveform
//        for (size_t n = 0; n < buff.size(); n++) {
//            buff[n] = wave_table(index += step);
//        }
//
//        // send the entire contents of the buffer
//        tx_streamer->send(buffs, buff.size(), metadata);
//
//        metadata.start_of_burst = false;
//        metadata.has_time_spec = false;
//    }
//
//    // send a mini EOB packet
//    metadata.end_of_burst = true;
//    tx_streamer->send("", 0, metadata);
//}
//
//
///***********************************************************************
// * recv_to_file function
// **********************************************************************/
//
//template <typename samp_type>
//void recv_to_file(uhd::usrp::multi_usrp::sptr usrp,
//    const std::string& cpu_format,
//    const std::string& wire_format,
//    const std::string& file,
//    size_t samps_per_buff,
//    int num_requested_samples,
//    double settling_time,
//    std::vector<size_t> rx_channel_nums)
//{
//    int num_total_samps = 0;
//    // create a receive streamer
//    uhd::stream_args_t stream_args(cpu_format, wire_format);
//    stream_args.channels = rx_channel_nums;
//    uhd::rx_streamer::sptr rx_stream = usrp->get_rx_stream(stream_args);
//
//    // Prepare buffers for received samples and metadata
//    uhd::rx_metadata_t md;
//    std::vector<std::vector<samp_type>> buffs(
//        rx_channel_nums.size(), std::vector<samp_type>(samps_per_buff));
//    // create a vector of pointers to point to each of the channel buffers
//    std::vector<samp_type*> buff_ptrs;
//    for (size_t i = 0; i < buffs.size(); i++) {
//        buff_ptrs.push_back(&buffs[i].front());
//    }
//
//    // Create one ofstream object per channel
//    // (use shared_ptr because ofstream is non-copyable)
//    std::vector<std::shared_ptr<std::ofstream>> outfiles;
//    for (size_t i = 0; i < buffs.size(); i++) {
//        const std::string this_filename = generate_out_filename(file, buffs.size(), i);
//        outfiles.push_back(std::shared_ptr<std::ofstream>(
//            new std::ofstream(this_filename.c_str(), std::ofstream::binary)));
//    }
//    UHD_ASSERT_THROW(outfiles.size() == buffs.size());
//    UHD_ASSERT_THROW(buffs.size() == rx_channel_nums.size());
//    bool overflow_message = true;
//    double timeout =
//        settling_time + 0.1f; // expected settling time + padding for first recv
//
//    // setup streaming
//    uhd::stream_cmd_t stream_cmd((num_requested_samples == 0)
//        ? uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS
//        : uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
//    stream_cmd.num_samps = num_requested_samples;
//    stream_cmd.stream_now = false;
//    stream_cmd.time_spec = uhd::time_spec_t(settling_time);
//    rx_stream->issue_stream_cmd(stream_cmd);
//
//    while (not stop_signal_called
//        and (num_requested_samples > num_total_samps or num_requested_samples == 0)) {
//        size_t num_rx_samps = rx_stream->recv(buff_ptrs, samps_per_buff, md, timeout);
//        timeout = 0.1f; // small timeout for subsequent recv
//
//        if (md.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) {
//            std::cout << boost::format("Timeout while streaming") << std::endl;
//            break;
//        }
//        if (md.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) {
//            if (overflow_message) {
//                overflow_message = false;
//                std::cerr
//                    << boost::format(
//                        "Got an overflow indication. Please consider the following:\n"
//                        "  Your write medium must sustain a rate of %fMB/s.\n"
//                        "  Dropped samples will not be written to the file.\n"
//                        "  Please modify this example for your purposes.\n"
//                        "  This message will not appear again.\n")
//                    % (usrp->get_rx_rate() * sizeof(samp_type) / 1e6);
//            }
//            continue;
//        }
//        if (md.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
//            throw std::runtime_error(
//                str(boost::format("Receiver error %s") % md.strerror()));
//        }
//
//        num_total_samps += num_rx_samps;
//
//        for (size_t i = 0; i < outfiles.size(); i++) {
//            outfiles[i]->write(
//                (const char*)buff_ptrs[i], num_rx_samps * sizeof(samp_type));
//        }
//    }
//
//    // Shut down receiver
//    stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
//    rx_stream->issue_stream_cmd(stream_cmd);
//
//    // Close files
//    for (size_t i = 0; i < outfiles.size(); i++) {
//        outfiles[i]->close();
//    }
//}
