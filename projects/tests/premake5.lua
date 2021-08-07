project("Tests")
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
        "%{Dependencies.imgui.include}",
        "%{Dependencies.googlemock.include}",
        "%{Dependencies.googletest.include}",
        "%{NativeIncludeDirs.glfw}",
    })

    links({
        "Engine",
        "googlemock",
        "googletest"
    })

    filter("system:Windows")

        linkoptions({
            "/IGNORE:4099"
        })

    filter("Debug")
        symbols("On")

    postbuildcommands({

    })
