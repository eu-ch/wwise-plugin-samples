if not _AK_PREMAKE then
    error('You must use the custom Premake5 scripts by adding the following parameter: --scripts="Scripts\\Premake"', 1)
end

local Plugin = {}
Plugin.name = "MediaSourceExample"
Plugin.factoryheader = "../SoundEnginePlugin/MediaSourceExampleSourceFactory.h"
Plugin.appleteamid = ""
Plugin.signtoolargs = {}
Plugin.sdk = {}
Plugin.sdk.static = {}
Plugin.sdk.shared = {}
Plugin.authoring = {}

-- Static plugin
Plugin.sdk.static.includedirs = {}
Plugin.sdk.static.files = {
    "**.cpp",
    "**.h",
    "**.hpp",
    "**.c",
}
Plugin.sdk.static.excludes = {
    "MediaSourceExampleSourceShared.cpp"
}
Plugin.sdk.static.links = {}
Plugin.sdk.static.libsuffix = "Source"
Plugin.sdk.static.libdirs = {}
Plugin.sdk.static.defines = {}

-- Shared plugin
Plugin.sdk.shared.includedirs = {}
Plugin.sdk.shared.files = {
    "MediaSourceExampleSourceShared.cpp",
    "MediaSourceExampleSourceFactory.h",
}
Plugin.sdk.shared.excludes = {}
Plugin.sdk.shared.links = {}
Plugin.sdk.shared.libdirs = {}
Plugin.sdk.shared.defines = {}

-- Authoring plugin
Plugin.authoring.includedirs = {}
Plugin.authoring.files = {
    "**.cpp",
    "**.h",
    "**.hpp",
    "**.c",
    "MediaSourceExample.def",
    "MediaSourceExample.xml",
    "**.rc",
}
Plugin.authoring.excludes = {}
Plugin.authoring.links = {}
Plugin.authoring.libdirs = {}
Plugin.authoring.defines = {}

return Plugin
