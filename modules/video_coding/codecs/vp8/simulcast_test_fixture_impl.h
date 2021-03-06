/*
 *  Copyright (c) 2018 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MODULES_VIDEO_CODING_CODECS_VP8_SIMULCAST_TEST_FIXTURE_IMPL_H_
#define MODULES_VIDEO_CODING_CODECS_VP8_SIMULCAST_TEST_FIXTURE_IMPL_H_

#include <memory>
#include <vector>

#include "api/test/simulcast_test_fixture.h"
#include "api/video/i420_buffer.h"
#include "api/video/video_frame.h"
#include "api/video_codecs/video_decoder_factory.h"
#include "api/video_codecs/video_encoder_factory.h"
#include "common_types.h"  // NOLINT(build/include)
#include "modules/video_coding/codecs/vp8/simulcast_rate_allocator.h"
#include "modules/video_coding/include/mock/mock_video_codec_interface.h"

namespace webrtc {
namespace test {

class SimulcastTestFixtureImpl final : public SimulcastTestFixture {
 public:
  SimulcastTestFixtureImpl(
      std::unique_ptr<VideoEncoderFactory> encoder_factory,
      std::unique_ptr<VideoDecoderFactory> decoder_factory);
  ~SimulcastTestFixtureImpl() final;

  // Implements SimulcastTestFixture.
  void TestKeyFrameRequestsOnAllStreams() override;
  void TestPaddingAllStreams() override;
  void TestPaddingTwoStreams() override;
  void TestPaddingTwoStreamsOneMaxedOut() override;
  void TestPaddingOneStream() override;
  void TestPaddingOneStreamTwoMaxedOut() override;
  void TestSendAllStreams() override;
  void TestDisablingStreams() override;
  void TestActiveStreams() override;
  void TestSwitchingToOneStream() override;
  void TestSwitchingToOneOddStream() override;
  void TestSwitchingToOneSmallStream() override;
  void TestSpatioTemporalLayers333PatternEncoder() override;
  void TestSpatioTemporalLayers321PatternEncoder() override;
  void TestStrideEncodeDecode() override;

  static void DefaultSettings(VideoCodec* settings,
                              const int* temporal_layer_profile);

 private:
  class Vp8TestEncodedImageCallback;
  class Vp8TestDecodedImageCallback;

  void SetUpCodec(const int* temporal_layer_profile);
  void SetUpRateAllocator();
  void SetRates(uint32_t bitrate_kbps, uint32_t fps);
  void RunActiveStreamsTest(const std::vector<bool> active_streams);
  void UpdateActiveStreams(const std::vector<bool> active_streams);
  void ExpectStreams(FrameType frame_type,
                     const std::vector<bool> expected_streams_active);
  void ExpectStreams(FrameType frame_type, int expected_video_streams);
  void VerifyTemporalIdxAndSyncForAllSpatialLayers(
      Vp8TestEncodedImageCallback* encoder_callback,
      const int* expected_temporal_idx,
      const bool* expected_layer_sync,
      int num_spatial_layers);
  void SwitchingToOneStream(int width, int height);

  std::unique_ptr<VideoEncoder> encoder_;
  MockEncodedImageCallback encoder_callback_;
  std::unique_ptr<VideoDecoder> decoder_;
  MockDecodedImageCallback decoder_callback_;
  VideoCodec settings_;
  rtc::scoped_refptr<I420Buffer> input_buffer_;
  std::unique_ptr<VideoFrame> input_frame_;
  std::unique_ptr<SimulcastRateAllocator> rate_allocator_;
};

}  // namespace test
}  // namespace webrtc

#endif  // MODULES_VIDEO_CODING_CODECS_VP8_SIMULCAST_TEST_FIXTURE_IMPL_H_
