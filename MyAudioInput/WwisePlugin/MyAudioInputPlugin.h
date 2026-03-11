#pragma once

#include <AK/Wwise/Plugin.h>

class MyAudioInputPlugin final
    : public AK::Wwise::Plugin::AudioPlugin
{
public:
    MyAudioInputPlugin() = default;
    ~MyAudioInputPlugin() = default;
    bool GetBankParameters(const GUID & in_guidPlatform, AK::Wwise::Plugin::DataWriter& in_dataWriter) const override;
};

AK_DECLARE_PLUGIN_CONTAINER(MyAudioInput);
