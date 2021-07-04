project("Engine")
    kind("StaticLib")
    language("C++")
    cppdialect("C++17")

    targetdir(binaries)
    objdir(intermediate)

    files({
        "include/**.hpp",
        "src/**.cpp"
    })

    includedirs({
        "%{Dependencies.diligent.include}",
        "%{Projects.engine.include}"
    })

    libdirs({
        "%{Dependencies.diligent.lib}"
    })

    postbuildcommands {
        "{COPY} %{Dependencies.diligent.bin} %{binaries}"
    }

    filter("Debug")
        
        defines({
            "DILIGENT_DEBUG"
        })

    filter("system:Windows")

        defines({
            "PLATFORM_WIN32"
        })

        links({
            "DiligentCore.lib",
            "SPIRV-Tools-opt.lib",
            "SPIRV-Tools.lib",
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