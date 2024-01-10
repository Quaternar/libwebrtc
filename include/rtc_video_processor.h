#ifndef LIB_WEBRTC_RTC_VIDEO_PROCESSOR_HXX
#define LIB_WEBRTC_RTC_VIDEO_PROCESSOR_HXX

#include "rtc_types.h"
#include "rtc_video_frame.h"
namespace libwebrtc {

class RTCVideoProcessor : public RefCountInterface {
 public:
  virtual scoped_refptr<RTCVideoFrame> Process(
      const scoped_refptr<RTCVideoFrame>& frame) = 0;

  ~RTCVideoProcessor() {}
};

}  // namespace libwebrtc

#endif  // LIB_WEBRTC_RTC_VIDEO_PROCESSOR_HXX
