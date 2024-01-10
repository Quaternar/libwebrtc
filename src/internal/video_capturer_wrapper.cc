/*
 *  Copyright (c) 2017 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "src/internal/video_capturer_wrapper.h"

#include <algorithm>

#include "api/scoped_refptr.h"
#include "api/video/i420_buffer.h"
#include "api/video/video_frame_buffer.h"
#include "api/video/video_rotation.h"
#include "rtc_video_frame.h"
#include "src/rtc_video_frame_impl.h"

namespace webrtc {
namespace internal {
VideoCapturerWrapper::VideoCapturerWrapper(
    libwebrtc::scoped_refptr<libwebrtc::RTCVideoProcessor> processor,
    std::shared_ptr<rtc::VideoSourceInterface<VideoFrame>> source)
    : processor_(processor), source_(source), sink_count_(0) {}
VideoCapturerWrapper::~VideoCapturerWrapper() = default;

void VideoCapturerWrapper::AddOrUpdateSink(
    rtc::VideoSinkInterface<VideoFrame>* sink,
    const rtc::VideoSinkWants& wants) {
  broadcaster_.AddOrUpdateSink(sink, wants);
  source_->AddOrUpdateSink(this, wants);
  sink_count_++;
}

void VideoCapturerWrapper::RemoveSink(
    rtc::VideoSinkInterface<VideoFrame>* sink) {
  broadcaster_.RemoveSink(this);
  sink_count_--;
  if (sink_count_ == 0) {
    source_->RemoveSink(this);
  }
}

void VideoCapturerWrapper::OnFrame(const VideoFrame& frame) {
  rtc::scoped_refptr<VideoFrameBuffer> buffer = frame.video_frame_buffer();
  libwebrtc::scoped_refptr<libwebrtc::RTCVideoFrame> video_frame =
      libwebrtc::VideoFrameBufferImpl::Create(buffer);

  libwebrtc::scoped_refptr<libwebrtc::RTCVideoFrame> mod_frame =
      processor_->Process(video_frame);

  libwebrtc::VideoFrameBufferImpl* mod_frame_impl =
      static_cast<libwebrtc::VideoFrameBufferImpl*>(mod_frame.get());
  mod_frame_impl->buffer();
  broadcaster_.OnFrame(VideoFrame::Builder()
                           .set_video_frame_buffer(mod_frame_impl->buffer())
                           .set_rotation(mod_frame_impl->rotationRTC())
                           //.set_timestamp_us(mod_frame_impl->timestamp_us())
                           .set_timestamp_rtp(static_cast<uint32_t>(
                               mod_frame_impl->timestamp_us()))
                           //.set_timestamp_ms(mod_frame_impl->timestamp_us())
                           .set_id(frame.id())
                           .build());
}

void VideoCapturerWrapper::OnConstraintsChanged(
    const webrtc::VideoTrackSourceConstraints& constraints) {}

}  // namespace internal
}  // namespace webrtc
