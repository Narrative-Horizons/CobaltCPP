project("Entrypoint")
    kind("ConsoleApp")
    language("C++")
    cppdialect("C++17")

    targetdir(binaries)
    objdir(intermediate)

    debugdir("../../")

    files({
        "include/**.hpp",
        "src/**.cpp"
    })

    includedirs({
        "%{Projects.engine.include}",
        "%{Projects.entrypoint.include}",
        "%{NativeIncludeDirs.glfw}"
    })

    links({
        "Engine",
    })

    postbuildcommands({

    })
