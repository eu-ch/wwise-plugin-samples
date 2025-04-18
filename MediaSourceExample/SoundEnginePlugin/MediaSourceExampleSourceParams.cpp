#include "MediaSourceExampleSourceParams.h"
#include <AK/Tools/Common/AkBankReadHelpers.h>

MediaSourceExampleSourceParams::MediaSourceExampleSourceParams(const MediaSourceExampleSourceParams& in_rParams)
{
	RTPC = in_rParams.RTPC;
	NonRTPC = in_rParams.NonRTPC;
	m_paramChangeHandler.SetAllParamChanges();
}

AK::IAkPluginParam* MediaSourceExampleSourceParams::Clone(AK::IAkPluginMemAlloc* in_pAllocator)
{
	return AK_PLUGIN_NEW(in_pAllocator, MediaSourceExampleSourceParams(*this));
}

AKRESULT MediaSourceExampleSourceParams::Init(AK::IAkPluginMemAlloc* in_pAllocator, const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
	if (in_ulBlockSize == 0)
	{
		RTPC.fDuration = 0.0f;
		m_paramChangeHandler.SetAllParamChanges();
		return AK_Success;
	}

	return SetParamsBlock(in_pParamsBlock, in_ulBlockSize);
}

AKRESULT MediaSourceExampleSourceParams::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
	AK_PLUGIN_DELETE(in_pAllocator, this);
	return AK_Success;
}

AKRESULT MediaSourceExampleSourceParams::SetParamsBlock(const void* in_pParamsBlock, AkUInt32 in_ulBlockSize)
{
	AKRESULT eResult = AK_Success;
	AkUInt8* pParamsBlock = (AkUInt8*)in_pParamsBlock;

	RTPC.fDuration = READBANKDATA(AkReal32, pParamsBlock, in_ulBlockSize);
	CHECKBANKDATASIZE(in_ulBlockSize, eResult);
	m_paramChangeHandler.SetAllParamChanges();

	return eResult;
}

AKRESULT MediaSourceExampleSourceParams::SetParam(AkPluginParamID in_paramID, const void* in_pValue, AkUInt32 in_ulParamSize)
{
	AKRESULT eResult = AK_Success;

	switch (in_paramID)
	{
	case PARAM_DURATION_ID:
		RTPC.fDuration = *((AkReal32*)in_pValue);
		m_paramChangeHandler.SetParamChange(PARAM_DURATION_ID);
		break;
	default:
		eResult = AK_InvalidParameter;
		break;
	}

	return eResult;
}
