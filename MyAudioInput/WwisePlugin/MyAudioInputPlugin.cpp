#include "MyAudioInputPlugin.h"
#include "../SoundEnginePlugin/MyAudioInputSourceFactory.h"

bool MyAudioInputPlugin::GetBankParameters(const GUID & in_guidPlatform, AK::Wwise::Plugin::DataWriter& in_dataWriter) const
{
    return true;
}

AK_DEFINE_PLUGIN_CONTAINER(MyAudioInput);
AK_EXPORT_PLUGIN_CONTAINER(MyAudioInput);
AK_ADD_PLUGIN_CLASS_TO_CONTAINER(MyAudioInput, MyAudioInputPlugin, MyAudioInputSource);
DEFINE_PLUGIN_REGISTER_HOOK
DEFINE_PLUGIN_ASSERT_HOOK;
