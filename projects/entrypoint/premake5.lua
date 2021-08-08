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
        "%{Dependencies.PhysX.include}",
        "%{NativeIncludeDirs.glfw}",
        "%{Dependencies.imgui.include}",
    })

    links({
        "Engine",
    })

    filter("system:Windows")
        staticruntime("Off")

        linkoptions({
            "/IGNORE:4099"
        })

    filter("Debug")
        symbols("On")

    postbuildcommands({

    })
