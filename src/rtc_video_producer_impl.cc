#include "rtc_video_producer_impl.h"

#include "rtc_video_frame_impl.h"

namespace libwebrtc {
RTCVideoProducerImpl::RTCVideoProducerImpl()
    : broadcaster_(std::make_shared<rtc::VideoBroadcaster>()) {}

RTCVideoProducerImpl ::~RTCVideoProducerImpl() {}

void RTCVideoProducerImpl::OnFrame(scoped_refptr<RTCVideoFrame> frame) {
  libwebrtc::VideoFrameBufferImpl* mod_frame_impl =
      static_cast<libwebrtc::VideoFrameBufferImpl*>(frame.get());

  broadcaster_->OnFrame(webrtc::VideoFrame::Builder()
                            .set_video_frame_buffer(mod_frame_impl->buffer())
                            .set_rotation(mod_frame_impl->rotationRTC())
                            //.set_timestamp_us(mod_frame_impl->timestamp_us())
                            .set_timestamp_rtp(static_cast<uint32_t>(
                                mod_frame_impl->timestamp_us()))
                            //.set_timestamp_ms(mod_frame_impl->timestamp_us())
                            //.set_id(frame.id())
                            .build());
}

std::shared_ptr<rtc::VideoSourceInterface<webrtc::VideoFrame>>
RTCVideoProducerImpl::VideoSource() const {
  return broadcaster_;
}

}  // namespace libwebrtc