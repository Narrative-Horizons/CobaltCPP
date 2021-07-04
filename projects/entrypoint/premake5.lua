project("Entrypoint")
    kind("ConsoleApp")
    language("C++")
    cppdialect("C++17")

    targetdir(binaries)
    objdir(intermediate)

    files({
        "include/**.hpp",
        "src/**.cpp"
    })

    includedirs({
        "%{Projects.engine.include}",
        "%{Projects.entrypoint.include}"
    })

    links({
        "Engine"
    })

    postbuildcommands {
        
    }
    