#include "MediaSourceExampleSource.h"
#include "AK/AkWwiseSDKVersion.h"
#include "../MediaSourceExampleConfig.h"

AK::IAkPlugin* CreateMediaSourceExampleSource(AK::IAkPluginMemAlloc* in_pAllocator)
{
	return AK_PLUGIN_NEW(in_pAllocator, MediaSourceExampleSource());
}

AK::IAkPluginParam* CreateMediaSourceExampleSourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
	return AK_PLUGIN_NEW(in_pAllocator, MediaSourceExampleSourceParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(MediaSourceExampleSource, AkPluginTypeSource, MediaSourceExampleConfig::CompanyID, MediaSourceExampleConfig::PluginID)

// --------------------------------------------------------------------------------

AKRESULT MediaSourceExampleSource::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
	m_pParams = (MediaSourceExampleSourceParams*)in_pParams;
	m_pAllocator = in_pAllocator;
	m_pContext = in_pContext;
	m_durationHandler.Setup(m_pParams->RTPC.fDuration, in_pContext->GetNumLoops(), in_rFormat.uSampleRate);

	uint8_t* pMediaData = nullptr;
	uint32_t uDataSize = 0;
	in_pContext->GetPluginMedia(MediaSourceExampleConfig::ExampleMediaIndex, pMediaData, uDataSize);
	if (pMediaData && uDataSize > 0)
	{
		in_pContext->PostMonitorMessage("Plugin media is valid", AK::Monitor::ErrorLevel::ErrorLevel_Message);
		return AK_Success;
	}
	else
	{
		in_pContext->PostMonitorMessage("Plugin media is NULL", AK::Monitor::ErrorLevel::ErrorLevel_Error);
		return AK_Fail;
	}
}

AKRESULT MediaSourceExampleSource::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
	AK_PLUGIN_DELETE(in_pAllocator, this);
	return AK_Success;
}

AKRESULT MediaSourceExampleSource::Reset()
{
	return AK_Success;
}

AKRESULT MediaSourceExampleSource::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
	out_rPluginInfo.eType = AkPluginTypeSource;
	out_rPluginInfo.bIsInPlace = true;
	out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
	return AK_Success;
}

void MediaSourceExampleSource::Execute(AkAudioBuffer* out_pBuffer)
{
	m_durationHandler.SetDuration(m_pParams->RTPC.fDuration);
	m_durationHandler.ProduceBuffer(out_pBuffer);

	const AkUInt32 uNumChannels = out_pBuffer->NumChannels();

	AkUInt16 uFramesProduced;
	for (AkUInt32 i = 0; i < uNumChannels; ++i)
	{
		AkReal32* AK_RESTRICT pBuf = (AkReal32 * AK_RESTRICT)out_pBuffer->GetChannel(i);

		uFramesProduced = 0;
		while (uFramesProduced < out_pBuffer->uValidFrames)
		{
			// Generate output here
			*pBuf++ = 0.0f;
			++uFramesProduced;
		}
	}
}

AkReal32 MediaSourceExampleSource::GetDuration() const
{
	return m_durationHandler.GetDuration() * 1000.0f;
}
