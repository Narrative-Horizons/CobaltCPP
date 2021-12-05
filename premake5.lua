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
    include "dependencies/googletest@1.11.0/googlemock"
    include "dependencies/googletest@1.11.0/googletest"
    include "dependencies/vk-bootstrap"
    group ""

    include("projects/engine")
    include("projects/entrypoint")
    include("projects/tests")

    Dependencies = {}
    Dependencies["diligent"] = {
        bin = "%{sln.location}/dependencies/diligent/bin/%{cfg.buildcfg}/%{cfg.system}",
        include = "%{sln.location}/dependencies/diligent/include",
        lib = "%{sln.location}/dependencies/diligent/lib/%{cfg.buildcfg}/%{cfg.system}"
    }
    Dependencies["googlemock"] = {
        include = "%{sln.location}/dependencies/googletest@1.11.0/googlemock/include"
    }
    Dependencies["googletest"] = {
        include = "%{sln.location}/dependencies/googletest@1.11.0/googletest/include"
    }
    Dependencies["imgui"] = {
        include = "%{sln.location}/dependencies/diligent/include/DiligentTools/ThirdParty/imgui"
    }
    Dependencies["PhysX"] = {
        bin = "%{sln.location}/dependencies/physx@4.1.2/bin/%{cfg.buildcfg}/%{cfg.system}",
        include = "%{sln.location}/dependencies/physx@4.1.2/include",
        lib = "%{sln.location}/dependencies/physx@4.1.2/lib/%{cfg.buildcfg}/%{cfg.system}"
    }
    Dependencies["assimp"] = {
        bin = "%{sln.location}/dependencies/assimp@5.0.1/bin/%{cfg.buildcfg}/%{cfg.system}",
        include = "%{sln.location}/dependencies/assimp@5.0.1/include",
        lib = "%{sln.location}/dependencies/assimp@5.0.1/lib/%{cfg.buildcfg}/%{cfg.system}"
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
    NativeIncludeDirs["vkbootstrap"] = "%{sln.location}/dependencies/vk-bootstrap/src"
    NativeIncludeDirs["vulkan"] = "%{sln.location}/dependencies/Vulkan-Headers@1.2.194/include"
    NativeIncludeDirs["vma"] = "%{sln.location}/dependencies/VMA@2.3.0/include"