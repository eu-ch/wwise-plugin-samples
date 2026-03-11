#pragma once

#include "MyAudioInputSourceParams.h"

#include <AK/Plugin/PluginServices/AkFXDurationHandler.h>

class MyAudioInputSource : public AK::IAkSourcePlugin
{
public:
    MyAudioInputSource();
    ~MyAudioInputSource();

    AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat) override;
    AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;
    AKRESULT Reset() override;
    AKRESULT GetPluginInfo(AkPluginInfo& out_rPluginInfo) override;
    void Execute(AkAudioBuffer* io_pBuffer) override;
    AkReal32 GetDuration() const override;

private:
    AK::IAkSourcePluginContext* m_pContext;
};

