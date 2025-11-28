-- premake5.lua (root)
include "Dependencies.lua"

workspace "Appl"
	startproject "Appl"
    platforms
	{
		"x64",
		"x86"
	}

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

    filter "platforms:x64"
		architecture "x64"
	
	filter "platforms:x86"
		architecture "x86"

	filter "system:Windows"
		system "windows"
		
	filter "system:Unix"
		system "linux"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

rootDir = "../"

group "Dependencies"
include "vendors/wgpu-native"
include "vendors/glfw"
include "vendors/glad"
include "vendors/imgui"

group "Core"
include "projects/core"

group "App"
include "projects/appl"

group ""
