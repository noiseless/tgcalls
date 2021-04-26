#ifndef TGCALLS_VIDEO_CAPTURER_INTERFACE_IMPL_H
#define TGCALLS_VIDEO_CAPTURER_INTERFACE_IMPL_H

#include "VideoCapturerInterface.h"

#include "api/media_stream_interface.h"

namespace tgcalls {

class DesktopCaptureSourceHelper;
class VideoCameraCapturer;

class VideoCapturerInterfaceImpl final : public VideoCapturerInterface {
public:
	VideoCapturerInterfaceImpl(
		rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> source,
		std::string deviceId,
		std::function<void(VideoState)> stateUpdated,
		std::pair<int, int> &outResolution);
	~VideoCapturerInterfaceImpl() override;

	void setState(VideoState state) override;
	void setPreferredCaptureAspectRatio(float aspectRatio) override;
	void setUncroppedOutput(std::shared_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> sink) override;
	int getRotation() override {
		return 0;
	}

private:
	rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> _source;
	std::shared_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> _sink;
	std::unique_ptr<DesktopCaptureSourceHelper> _desktopCapturer;
	std::unique_ptr<VideoCameraCapturer> _cameraCapturer;
	std::shared_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> _uncroppedSink;
	std::function<void(VideoState)> _stateUpdated;

};

} // namespace tgcalls

#endif
