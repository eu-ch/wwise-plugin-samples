#pragma once

#include "../MyAudioInputPlugin.h"

class MyAudioInputPluginGUI final
	: public AK::Wwise::Plugin::PluginMFCWindows<>
	, public AK::Wwise::Plugin::GUIWindows
{
public:
	MyAudioInputPluginGUI() = default;

};
