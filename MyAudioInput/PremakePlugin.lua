if not _AK_PREMAKE then
    error('You must use the custom Premake5 scripts by adding the following parameter: --scripts="Scripts\\Premake"', 1)
end

local plugin_types_file_path = path.join(_WORKING_DIR, "SoundEnginePlugin", "MyAudioInputTypes.h")
local ak_include_plugin_dir = path.join(_AK_SDK_ROOT, "include", "AK", "Plugin")

-- Common
local Plugin = {}
Plugin.name = "MyAudioInput"
Plugin.factoryheader = "../SoundEnginePlugin/MyAudioInputSourceFactory.h"
Plugin.appleteamid = ""
Plugin.signtoolargs = {}
Plugin.sdk = {}
Plugin.sdk.static = {}
Plugin.sdk.shared = {}
Plugin.authoring = {}

-- StaticLib
Plugin.sdk.static.includedirs = {}
Plugin.sdk.static.files = { "**.cpp", "**.h", "**.hpp", "**.c", }
Plugin.sdk.static.excludes = { "MyAudioInputSourceShared.cpp" }
Plugin.sdk.static.links = {}
Plugin.sdk.static.libsuffix = "Source"
Plugin.sdk.static.libdirs = {}
Plugin.sdk.static.defines = {}

-- DynamicLib
Plugin.sdk.shared.includedirs = {}
Plugin.sdk.shared.files =
{
    "MyAudioInputSourceShared.cpp",
    "MyAudioInputSourceFactory.h",
}
Plugin.sdk.shared.excludes = {}
Plugin.sdk.shared.links = {}
Plugin.sdk.shared.libdirs = {}
Plugin.sdk.shared.defines = {}

-- Authoring plugin
Plugin.authoring.includedirs = {}
Plugin.authoring.files =
{
    "**.cpp",
    "**.h",
    "**.hpp",
    "**.c",
    "MyAudioInput.def",
    "MyAudioInput.xml",
    "**.rc",
}
Plugin.authoring.excludes = {}
Plugin.authoring.links = {}
Plugin.authoring.libdirs = {}
Plugin.authoring.defines = {}
Plugin.authoring.custom = function()
   postbuildcommands {
      "{COPYFILE} " .. plugin_types_file_path .. " " .. ak_include_plugin_dir
   }
end

return Plugin
