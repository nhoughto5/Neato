workspace "Neato"
	architecture "x64"
	startproject "Sandbox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "Neato/vendor/GLFW/include"
IncludeDir["Glad"] = "Neato/vendor/Glad/include"
IncludeDir["ImGui"] = "Neato/vendor/imgui"
-- Copies the premake5.lua file in the GLFW repo

group "Dependencies"
	include "Neato/vendor/GLFW"
	include "Neato/vendor/Glad"
	include "Neato/vendor/imgui"
	
group ""

project "Neato"
	location "Neato"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	pchheader "NeatoPCH.h"
	pchsource "Neato/src/NeatoPCH.cpp"
	staticruntime "off"
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"NEATO_PLATFORM_WINDOWS",
			"NEATO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "NEATO_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NEATO_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NEATO_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	staticruntime "off"
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
		systemversion "latest"
		defines
		{
			"NEATO_PLATFORM_WINDOWS",
		}
		postbuildcommands
		{
			("{COPY} ../bin/" .. outputdir .. "/Neato/Neato.dll" .. " ../bin/" .. outputdir .. "/%{prj.name}"),
			("{COPY} ../bin/" .. outputdir .. "/Neato/Neato.pdb" .. " ../bin/" .. outputdir .. "/%{prj.name}")
		}

	filter "configurations:Debug"
		defines "NEATO_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NEATO_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NEATO_DIST"
		runtime "Release"
		optimize "On"