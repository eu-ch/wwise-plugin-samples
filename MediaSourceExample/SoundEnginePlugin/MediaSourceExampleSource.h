#pragma once

#include "MediaSourceExampleSourceParams.h"
#include <AK/Plugin/PluginServices/AkFXDurationHandler.h>

class MediaSourceExampleSource
	: public AK::IAkSourcePlugin
{
public:
	MediaSourceExampleSource() = default;
	~MediaSourceExampleSource() = default;

	AKRESULT Init(AK::IAkPluginMemAlloc* in_pAllocator, AK::IAkSourcePluginContext* in_pContext, AK::IAkPluginParam* in_pParams, AkAudioFormat& in_rFormat) override;
	AKRESULT Term(AK::IAkPluginMemAlloc* in_pAllocator) override;
	AKRESULT Reset() override;
	AKRESULT GetPluginInfo(AkPluginInfo& out_rPluginInfo) override;
	void Execute(AkAudioBuffer* io_pBuffer) override;
	AkReal32 GetDuration() const override;

private:
	MediaSourceExampleSourceParams* m_pParams = nullptr;
	AK::IAkPluginMemAlloc* m_pAllocator = nullptr;
	AK::IAkSourcePluginContext* m_pContext = nullptr;
	AkFXDurationHandler m_durationHandler = {};
};

