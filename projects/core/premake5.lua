project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}")

    files {
        "src/Core/**.h",
        "src/Core/**.cpp",
        "src/Core/**.ixx",
        "src/Core/**.cppm",
        "vendor/**.h",
        "vendor/**.cpp",
    }

    removefiles {
        "src/Core/Renderer/**",
    }

    includedirs {
        "%{IncludeDirectories.spdlog}",
        "%{IncludeDirectories.glm}",
        "%{IncludeDirectories.imgui}",
        "%{IncludeDirectories.entt}",
        "%{IncludeDirectories.raylib}",

        "src/",
        "vendor/",
    }

    links {
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"
    
    filter { "action:vs*" }
        buildoptions { "/utf-8" }

    filter "configurations:Debug"
        defines {
            "CORE_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {
            "CORE_RELEASE"
        }
        runtime "Release"
        optimize "On"
