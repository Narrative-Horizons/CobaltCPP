workspace("Cobalt")
    configurations({
        "Debug",
        "Release"
    })

    sln = solution()
    binaries = "%{sln.location}/bin/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"
    intermediate = "%{sln.location}/bin-int/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

    startproject("entrypoint")
    architecture("x64")

    group "External Dependencies"
    include "dependencies/GLFW@3.3.3"
    group ""

    include("projects/engine")
    include("projects/entrypoint")

    Dependencies = {}
    Dependencies["diligent"] = {
        bin = "%{sln.location}/dependencies/diligent/bin/%{cfg.buildcfg}/%{cfg.system}",
        include = "%{sln.location}/dependencies/diligent/include",
        lib = "%{sln.location}/dependencies/diligent/lib/%{cfg.buildcfg}/%{cfg.system}"
    }
    Dependencies["imgui"] = {
        include = "%{sln.location}/dependencies/diligent/include/DiligentTools/ThirdParty/imgui"
    }

    Projects = {}
    Projects["engine"] = {
        include = "%{sln.location}/projects/engine/include"
    }
    Projects["entrypoint"] = {
        include = "%{sln.location}/projects/entrypoint/include"
    }

    NativeIncludeDirs = {}
    NativeIncludeDirs["glfw"] = "%{sln.location}/dependencies/GLFW@3.3.3/include"