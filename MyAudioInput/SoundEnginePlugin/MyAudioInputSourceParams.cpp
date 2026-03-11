#include "MyAudioInputSourceParams.h"

#include <AK/Tools/Common/AkBankReadHelpers.h>

MyAudioInputSourceParams::MyAudioInputSourceParams(const MyAudioInputSourceParams& in_rParams)
{
    RTPC = in_rParams.RTPC;
    NonRTPC = in_rParams.NonRTPC;
}

AK::IAkPluginParam* MyAudioInputSourceParams::Clone(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, MyAudioInputSourceParams(*this));
}

AKRESULT MyAudioInputSourceParams::Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
    if (in_ulBlockSize == 0)
    {
        return AK_Success;
    }
    return SetParamsBlock(in_pParamsBlock, in_ulBlockSize);
}

AKRESULT MyAudioInputSourceParams::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT MyAudioInputSourceParams::SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
    AKRESULT eResult = AK_Success;
    return eResult;
}

AKRESULT MyAudioInputSourceParams::SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize)
{
    AKRESULT eResult = AK_Success;
    return eResult;
}
