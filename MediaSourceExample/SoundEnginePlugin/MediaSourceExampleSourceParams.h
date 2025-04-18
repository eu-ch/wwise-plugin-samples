#pragma once

#include <AK/SoundEngine/Common/IAkPlugin.h>
#include <AK/Plugin/PluginServices/AkFXParameterChangeHandler.h>

static const AkPluginParamID PARAM_DURATION_ID = 0;
static const AkUInt32 NUM_PARAMS = 1;

struct MediaSourceExampleRTPCParams
{
	AkReal32 fDuration;
};

struct MediaSourceExampleNonRTPCParams
{
};

struct MediaSourceExampleSourceParams : public AK::IAkPluginParam
{
	MediaSourceExampleSourceParams() = default;
	MediaSourceExampleSourceParams(const MediaSourceExampleSourceParams& in_rParams);
	~MediaSourceExampleSourceParams() = default;

	IAkPluginParam* Clone(AK::IAkPluginMemAlloc* in_pAllocator) override;
	AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;
	AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;
	AKRESULT SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;
	AKRESULT SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize) override;

	AK::AkFXParameterChangeHandler<NUM_PARAMS> m_paramChangeHandler;
	MediaSourceExampleRTPCParams RTPC;
	MediaSourceExampleNonRTPCParams NonRTPC;
};

