project("googlemock")
    kind("StaticLib")
    language("C++")
    cppdialect("C++17")

    targetdir(binaries)
    objdir(intermediate)

    files({
        "include/**.h",
        "src/**.cc",
    })

    includedirs({
        "include/",
        ".",
        "%{Dependencies.googletest.include}"
    })

    dependson({
        "googletest"
    })

    links({
        "googletest"
    })

    filter("Debug")
        defines({
            "_DEBUG"
        })

        symbols("On")
    
    filter("Release")
        defines({
            "NDEBUG"
        })

        symbols("Off")