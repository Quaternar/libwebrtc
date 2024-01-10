#ifndef LIB_WEBRTC_VIDEO_PRODUCER_IMPL_HXX
#define LIB_WEBRTC_VIDEO_PRODUCER_IMPL_HXX

#include "rtc_video_producer.h"
#include "api/video/video_source_interface.h"
#include "api/video/video_frame.h"
#include "media/base/video_broadcaster.h"

namespace libwebrtc {

class RTCVideoProducerImpl : public RTCVideoProducer {
 public:
  RTCVideoProducerImpl();
  virtual ~RTCVideoProducerImpl();

  virtual void OnFrame(scoped_refptr<RTCVideoFrame> frame) override;

  std::shared_ptr<rtc::VideoSourceInterface<webrtc::VideoFrame>> VideoSource()
      const;

 private:
  std::shared_ptr<rtc::VideoBroadcaster> broadcaster_;
};
}  // namespace libwebrtc

#endif  // LIB_WEBRTC_VIDEO_PRODUCER_IMPL_HXX
