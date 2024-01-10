#pragma once
/*
 *  Copyright (c) 2013 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#ifndef INTERNAL_VIDEO_CAPTURER_WRAPPER_H_
#define INTERNAL_VIDEO_CAPTURER_WRAPPER_H_

#include <stddef.h>

#include <memory>
#include <atomic>

#include "api/video/video_frame.h"
#include "api/video/video_source_interface.h"
#include "media/base/video_adapter.h"
#include "media/base/video_broadcaster.h"
#include "modules/video_capture/video_capture.h"
#include "modules/video_capture/video_capture_factory.h"
#include "pc/video_track_source.h"
#include "rtc_video_processor.h"

namespace webrtc {
namespace internal {

class VideoCapturerWrapper : public rtc::VideoSourceInterface<VideoFrame>,
                             public rtc::VideoSinkInterface<VideoFrame> {
 public:
  VideoCapturerWrapper(
      libwebrtc::scoped_refptr<libwebrtc::RTCVideoProcessor> processor,
      std::shared_ptr<rtc::VideoSourceInterface<VideoFrame>> source);

  virtual ~VideoCapturerWrapper();

  virtual void AddOrUpdateSink(rtc::VideoSinkInterface<VideoFrame>* sink,
                               const rtc::VideoSinkWants& wants) override;
  virtual void RemoveSink(rtc::VideoSinkInterface<VideoFrame>* sink) override;

  virtual void OnFrame(const VideoFrame& frame) override;

  virtual void OnConstraintsChanged(
      const webrtc::VideoTrackSourceConstraints& constraints) override;

 protected:
  rtc::VideoBroadcaster broadcaster_;
  libwebrtc::scoped_refptr<libwebrtc::RTCVideoProcessor> processor_;
  std::shared_ptr<rtc::VideoSourceInterface<VideoFrame>> source_;
  std::atomic<int> sink_count_;
};
}  // namespace internal
}  // namespace webrtc

#endif  // INTERNAL_VIDEO_CAPTURER_WRAPPER_H_
