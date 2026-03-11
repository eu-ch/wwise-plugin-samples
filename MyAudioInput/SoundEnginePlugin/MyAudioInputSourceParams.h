#pragma once

#include <AK/SoundEngine/Common/IAkPlugin.h>
#include <AK/Plugin/PluginServices/AkFXParameterChangeHandler.h>

static const AkUInt32 NUM_PARAMS = 0;

struct MyAudioInputRTPCParams
{
};

struct MyAudioInputNonRTPCParams
{
};

struct MyAudioInputSourceParams
    : public AK::IAkPluginParam
{
    MyAudioInputSourceParams() = default;
    MyAudioInputSourceParams(const MyAudioInputSourceParams& in_rParams);
    ~MyAudioInputSourceParams() = default;

    IAkPluginParam* Clone(AK::IAkPluginMemAlloc* in_pAllocator) override;
    AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;
    AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;
    AKRESULT SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize) override;
    AKRESULT SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize) override;

    MyAudioInputRTPCParams RTPC;
    MyAudioInputNonRTPCParams NonRTPC;
};

