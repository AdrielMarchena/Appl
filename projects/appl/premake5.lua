project "Appl"
    kind "consoleapp"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.name}")

    files {
        "**.h",
        "**.cpp"
    }

    includedirs {
        "%{IncludeDirectories.GLFW}",
        "%{IncludeDirectories.Core}",
        "%{IncludeDirectories.spdlog}",
        "%{IncludeDirectories.glm}",
        "%{IncludeDirectories.glad}",
        "%{IncludeDirectories.vulkan}",
        "%{IncludeDirectories.imgui}",
        "%{IncludeDirectories.entt}",
        "src/",
    }

    libdirs {
        "%{LibraryDirectories.vulkan}"
    }

    links {
        "GLFW",
        "Core",
        "glad",
        "vulkan-1.lib",
        "ImGui"
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
