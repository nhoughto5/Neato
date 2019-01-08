workspace "Neato"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "Neato/vendor/GLFW/include"

-- Copies the premake5.lua file in the GLFW repo
include "Neato/vendor/GLFW"

project "Neato"
	location "Neato"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	pchheader "NeatoPCH.h"
	pchsource "Neato/src/NeatoPCH.cpp"
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"NEATO_PLATFORM_WINDOWS",
			"NEATO_BUILD_DLL"
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "NEATO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NEATO_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NEATO_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"Neato/vendor/spdlog/include",
		"Neato/src"
	}

	links
	{
		"Neato"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"NEATO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NEATO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NEATO_Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NEATO_DIST"
		optimize "On"