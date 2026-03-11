#include "MyAudioInputSource.h"
#include "../MyAudioInputConfig.h"

#include <AK/AkWwiseSDKVersion.h>
#include "MyAudioInputTypes.h"

AK::IAkPlugin* CreateMyAudioInputSource(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, MyAudioInputSource());
}

AK::IAkPluginParam* CreateMyAudioInputSourceParams(AK::IAkPluginMemAlloc* in_pAllocator)
{
    return AK_PLUGIN_NEW(in_pAllocator, MyAudioInputSourceParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY(MyAudioInputSource, AkPluginTypeSource, MyAudioInputConfig::CompanyID, MyAudioInputConfig::PluginID)

MyAudioInputSource::MyAudioInputSource() : m_pContext(nullptr)
{
}

MyAudioInputSource::~MyAudioInputSource()
{
}

AKRESULT MyAudioInputSource::Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat)
{
    m_pContext = in_pContext;
    if (const MyAudioInput_Cookie* pCookie = reinterpret_cast<MyAudioInput_Cookie*>(m_pContext->GetCookie()))
    {
        if (pCookie->m_uMagicNumber != MYAUDIOINPUT_MAGIC_NUMBER)
        {
			if (m_pContext->CanPostMonitorData())
			{
				m_pContext->PostMonitorMessage("Unexpected value of magic number, probably an incorrect cookie was provided.", AK::Monitor::ErrorLevel_Error);
			}
		    return AK_Fail;
        }
        else if (!(pCookie->m_pfnExecuteFn && pCookie->m_pfnSetFormatFn && pCookie->m_pUserPayload))
        {
			if (m_pContext->CanPostMonitorData())
			{
				m_pContext->PostMonitorMessage("User-provided cookie doesn't have all pointers set up.", AK::Monitor::ErrorLevel_Error);
			}
		    return AK_Fail;
        }
        else
        {
			pCookie->m_pfnSetFormatFn(pCookie->m_pUserPayload, &in_rFormat);
		    return AK_Success;
        }
    }
    else
    {
        if (m_pContext->CanPostMonitorData())
        {
            m_pContext->PostMonitorMessage("No cookie associated with the event. MyAudioInput plugin requires a pointer to type MyAudioInputCookie to be provided as a cookie.", AK::Monitor::ErrorLevel_Error);
        }
		return AK_Fail;
    }
}

AKRESULT MyAudioInputSource::Term(AK::IAkPluginMemAlloc* in_pAllocator)
{
    AK_PLUGIN_DELETE(in_pAllocator, this);
    return AK_Success;
}

AKRESULT MyAudioInputSource::Reset()
{
    return AK_Success;
}

AKRESULT MyAudioInputSource::GetPluginInfo(AkPluginInfo& out_rPluginInfo)
{
    out_rPluginInfo.eType = AkPluginTypeSource;
    out_rPluginInfo.bIsInPlace = true;
    out_rPluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

void MyAudioInputSource::Execute(AkAudioBuffer* out_pBuffer)
{
    if (const MyAudioInput_Cookie* pCookie = reinterpret_cast<MyAudioInput_Cookie*>(m_pContext->GetCookie()))
    {
        pCookie->m_pfnExecuteFn(pCookie->m_pUserPayload, out_pBuffer);
    }
    else
    {
        if (m_pContext->CanPostMonitorData())
        {
            m_pContext->PostMonitorMessage("No Cookie found in when Execute method was called; this shouldn've happened.", AK::Monitor::ErrorLevel_Error);
        }
        out_pBuffer->eState = AK_NoMoreData;
    }
}

AkReal32 MyAudioInputSource::GetDuration() const
{
    return -1.f;
}
