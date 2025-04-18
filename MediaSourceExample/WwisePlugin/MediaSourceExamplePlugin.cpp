#include "MediaSourceExamplePlugin.h"
#include "AK/Tools/Common/AkFNVHash.h"
#include <filesystem>

#include "../MediaSourceExampleConfig.h"
#include "../SoundEnginePlugin/MediaSourceExampleSourceFactory.h"

bool MediaSourceExamplePlugin::GetBankParameters(const GUID& in_guidPlatform, AK::Wwise::Plugin::DataWriter& in_dataWriter) const
{
	in_dataWriter.WriteReal32(m_propertySet.GetReal32(in_guidPlatform, "Duration"));
	return true;
}

AK::Wwise::Plugin::ConversionResult MediaSourceExamplePlugin::ConvertFile(
	const GUID& in_guidPlatform,
	const BasePlatformID& in_basePlatform,
	const AkOSChar* in_szSourceFile,
	const AkOSChar* in_szDestFile,
	AkUInt32 in_uSampleRate,
	AkUInt32 in_uBlockLength,
	AK::Wwise::Plugin::IProgress* in_pProgress,
	AK::Wwise::Plugin::IWriteString* io_pError) const
{
	std::error_code error_code;
	std::filesystem::copy(in_szSourceFile, in_szDestFile, std::filesystem::copy_options::overwrite_existing, error_code);
	return error_code
		? AK::Wwise::Plugin::ConversionFailed
		: AK::Wwise::Plugin::ConversionSuccess;
}

uint32_t MediaSourceExamplePlugin::GetCurrentConversionSettingsHash(
	const GUID& in_guidPlatform,
	AkUInt32 in_uSampleRate,
	AkUInt32 in_uBlockLength) const
{
	AkOSChar szInputFileName[_MAX_PATH];
	const uint32_t uPathLen = m_objectMedia.GetMediaSourceFileName(szInputFileName, _MAX_PATH, MediaSourceExampleConfig::ExampleMediaIndex);
	if (uPathLen > 0)
	{
		for (int i = 0; i < uPathLen; ++i)
		{
			szInputFileName[i] = tolower(szInputFileName[i]);
		}
		return AK::FNVHash32().Compute(szInputFileName, uPathLen);
	}
	return 0;
}

void MediaSourceExamplePlugin::NotifyPluginMediaChanged()
{
	m_host.NotifyInternalDataChanged(AK::IAkPluginParam::ALL_PLUGIN_DATA_ID, /*MakeProjectDirty=*/ true);
}

AK_DEFINE_PLUGIN_CONTAINER(MediaSourceExample);
AK_EXPORT_PLUGIN_CONTAINER(MediaSourceExample);
AK_ADD_PLUGIN_CLASS_TO_CONTAINER(MediaSourceExample, MediaSourceExamplePlugin, MediaSourceExampleSource);
DEFINE_PLUGIN_REGISTER_HOOK
DEFINEDUMMYASSERTHOOK;
