#include "mp_sdk_audio.h"

using namespace gmpi;

class DBStereoToMono final : public MpBase2
{
	AudioInPin pinInLeft;
	AudioInPin pinInRight;
	AudioOutPin pinOutLeft;
	AudioOutPin pinOutRight;

public:
	DBStereoToMono()
	{
		initializePin(pinInLeft);
		initializePin(pinInRight);
		initializePin(pinOutLeft);
		initializePin(pinOutRight);
	}

	void subProcess(int sampleFrames)
	{
		// get pointers to in/output buffers.
		auto InLeft = getBuffer(pinInLeft);
		auto InRight = getBuffer(pinInRight);
		auto OutLeft = getBuffer(pinOutLeft);
		auto OutRight = getBuffer(pinOutRight);

		for (int s = sampleFrames; s > 0; --s)
		{
			// TODO: Signal processing goes here.
			const float mono = ((*InLeft) + (*InRight)) * 0.5f;
			*OutLeft = mono;
			*OutRight = mono;

			// Increment buffer pointers.
			++InLeft;
			++InRight;
			++OutLeft;
			++OutRight;
		}
	}

	void onSetPins() override
	{
		// Check which pins are updated.
		if (pinInLeft.isStreaming())
		{
		}
		if (pinInRight.isStreaming())
		{
		}

		// Set state of output audio pins.
		pinOutLeft.setStreaming(true);
		pinOutRight.setStreaming(true);

		// Set processing method.
		setSubProcess(&DBStereoToMono::subProcess);
	}
};

namespace
{
	auto r = Register<DBStereoToMono>::withId(L"My DB Stereo To Mono");
}
