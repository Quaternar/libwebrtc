#ifndef LIB_WEBRTC_RTC_VIDEO_PRODUCER_HXX
#define LIB_WEBRTC_RTC_VIDEO_PRODUCER_HXX

#include "rtc_types.h"
#include "rtc_video_frame.h"
#include "base/scoped_ref_ptr.h"

namespace libwebrtc {

class RTCVideoProducer : public RefCountInterface {
 public:
  ~RTCVideoProducer() {}
  virtual void OnFrame(scoped_refptr<RTCVideoFrame> frame) = 0;
};

}  // namespace libwebrtc

#endif  // LIB_WEBRTC_RTC_VIDEO_PRODUCER_HXX
