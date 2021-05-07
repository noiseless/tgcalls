#ifndef TGCALLS_VIDEO_CAPTURER_INTERFACE_IMPL_H
#define TGCALLS_VIDEO_CAPTURER_INTERFACE_IMPL_H

#include "VideoCapturerInterface.h"

#ifdef TGCALLS_UWP_DESKTOP_CAPTURE
#include "platform/uwp/UwpPlatformContext.h"
#include "platform/uwp/UwpScreenCapturer.h"
#endif // TGCALLS_UWP_DESKTOP_CAPTURE

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
		std::shared_ptr<PlatformContext> platformContext,
		std::pair<int, int> &outResolution);
	~VideoCapturerInterfaceImpl() override;

	void setState(VideoState state) override;
	void setPreferredCaptureAspectRatio(float aspectRatio) override;
	void setUncroppedOutput(std::shared_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> sink) override;
	int getRotation() override {
		return 0;
	}
	void setOnFatalError(std::function<void()> error) override {
	}

private:
	rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> _source;
	std::shared_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> _sink;
#ifdef TGCALLS_UWP_DESKTOP_CAPTURE
	std::unique_ptr<UwpScreenCapturer> _screenCapturer;
#else
	std::unique_ptr<DesktopCaptureSourceHelper> _desktopCapturer;
#endif // TGCALLS_UWP_DESKTOP_CAPTURE
	std::unique_ptr<VideoCameraCapturer> _cameraCapturer;
	std::shared_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> _uncroppedSink;
	std::function<void(VideoState)> _stateUpdated;

};

} // namespace tgcalls

#endif
