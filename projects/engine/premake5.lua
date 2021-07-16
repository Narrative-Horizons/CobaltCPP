project("Engine")
    kind("StaticLib")
    language("C++")
    cppdialect("C++17")

    targetdir(binaries)
    objdir(intermediate)

    files({
        "include/**.hpp",
        "src/**.cpp",
        "src/**.hpp", -- private headers
    })

    includedirs({
        "%{Dependencies.diligent.include}",
        "%{Projects.engine.include}",
        "%{NativeIncludeDirs.glfw}",
        "src" -- private headers
    })

    libdirs({
        "%{Dependencies.diligent.lib}"
    })

    postbuildcommands {
        "{COPY} %{Dependencies.diligent.bin} %{binaries}"
    }

    links({
        "GLFW@3.3.3"
    })

    filter("Debug")
        defines({
            "DILIGENT_DEBUG",
            "DEBUG"
        })

        symbols("On")

    filter("system:Windows")

        linkoptions({
            "/IGNORE:4006",
            "/IGNORE:4099"
        })

        defines({
            "PLATFORM_WIN32",
            "GLFW_EXPOSE_NATIVE_WIN32",
            "D3D11_SUPPORTED",
            "D3D12_SUPPORTED",
            "GL_SUPPORTED",
            "VULKAN_SUPPORTED",
            "ENGINE_DLL",
            "NOMINMAX"
        })

        links({
            "DiligentCore.lib",
            "DiligentTools.lib",
            "LibJpeg.lib",
            "LibPng.lib",
            "LibTiff.lib",
            "DiligentFX.lib",
            "SPIRV-Tools-opt.lib",
            "SPIRV-Tools.lib",
            "Diligent-GraphicsTools.lib",
        })

    filter({"system:Windows", "Debug"})
        links({
            "GenericCodeGend.lib",
            "GraphicsEngineVk_64d.lib",
            "MachineIndependentd.lib",
            "OSDependentd.lib",
            "SPIRVd.lib",
            "spirv-cross-cored.lib",
        })

    filter({"system:Windows", "Release"})

        links({
            "GenericCodeGen.lib",
            "GraphicsEngineVk_64r.lib",
            "MachineIndependent.lib",
            "OSDependent.lib",
            "SPIRV.lib",
            "spirv-cross-core.lib",
        })

    filter({})