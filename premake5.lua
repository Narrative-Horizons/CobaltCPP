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

    include("projects/engine")
    include("projects/entrypoint")

    Dependencies = {}
    Dependencies["diligent"] = {
        bin = "%{sln.location}/dependencies/diligent/bin/%{cfg.buildcfg}/%{cfg.system}",
        include = "%{sln.location}/dependencies/diligent/include",
        lib = "%{sln.location}/dependencies/diligent/lib/%{cfg.buildcfg}/%{cfg.system}"
    }
    
    Projects = {}
    Projects["engine"] = {
        include = "%{sln.location}/projects/engine/include"
    }
    Projects["entrypoint"] = {
        include = "%{sln.location}/projects/entrypoint/include"
    }