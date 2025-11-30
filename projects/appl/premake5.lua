project "Appl"
    kind "consoleapp"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}")

    files {
        "**.h",
        "**.cpp"
    }

    includedirs {
        "%{IncludeDirectories.Core}",
        "%{IncludeDirectories.spdlog}",
        "%{IncludeDirectories.glm}",
        "%{IncludeDirectories.imgui}",
        "%{IncludeDirectories.entt}",
        "%{IncludeDirectories.raylib}",
        "src/",
    }

    filter "system:linux"
        -- Link order: Core -> raylib -> ImGui -> system libs
        -- Using linkoptions to ensure raylib comes right after Core
        linkoptions {
            "-Wl,--whole-archive",
            "%{wks.location}/vendors/raylib/build/raylib/libraylib.a",
            "-Wl,--no-whole-archive"
        }
    
    links {
        "Core",
        "ImGui"
    }

    filter "system:linux"
        links {
            "GL",
            "m",
            "pthread",
            "dl",
            "rt",
            "X11"
        }

    filter "system:windows"
        systemversion "latest"

    filter { "action:vs*" }
        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines {
            "APPL_DEBUG",
            "CORE_DEBUG",
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {
            "APPL_RELEASE",
            "CORE_RELEASE"
        }
        runtime "Release"
        optimize "On"
