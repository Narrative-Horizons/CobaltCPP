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
        "%{Dependencies.diligent.include}",
        "%{Projects.engine.include}",
        "%{Projects.entrypoint.include}",
        "%{Dependencies.PhysX.include}",
        "%{NativeIncludeDirs.glfw}",
        "%{Dependencies.imgui.include}",
        "%{NativeIncludeDirs.vkbootstrap}",
        "%{NativeIncludeDirs.vulkan}",
        "%{NativeIncludeDirs.vma}"
    })

    links({
        "Engine",
    })

    filter("system:Windows")
        staticruntime("Off")

        linkoptions({
            "/IGNORE:4099"
        })

        defines({
            "PLATFORM_WIN32",
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

    postbuildcommands({

    })
