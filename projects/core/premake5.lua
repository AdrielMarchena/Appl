project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
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

    includedirs {
        "%{IncludeDirectories.GLFW}",
        "%{IncludeDirectories.spdlog}",
        "%{IncludeDirectories.glm}",
        "%{IncludeDirectories.glad}",
        "%{IncludeDirectories.vulkan}",
        "%{IncludeDirectories.imgui}",
        "%{IncludeDirectories.entt}",
        "%{IncludeDirectories.webgpu}",

        "src/",
        "vendor/",
    }

    libdirs {
        "%{LibraryDirectories.vulkan}",
        "%{LibraryDirectories.webgpu}"
    }

    links {
        "GLFW",
        "glad",
        "vulkan-1.lib",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "WEBGPU_BACKEND_D3D12" }
    
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
