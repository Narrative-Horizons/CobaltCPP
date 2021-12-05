project "vk-bootstrap"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    architecture "x64"

    targetdir (binaries)
    objdir (intermediate)

    files {
        "src/**.*"
    }

    includedirs {
        "%{NativeIncludeDirs.vulkan}"
    }

    toolset "clang"

    -- OS filters
    filter "system:windows"
        systemversion "latest"
        staticruntime "Off"

    filter {}

    -- Configuration Filters
    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "Full"
        runtime "Release"
        symbols "Off"

    filter {}
