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
IncludeDir["glm"] = "Neato/vendor/glm"
-- Copies the premake5.lua file in the GLFW repo

group "Dependencies"
	include "Neato/vendor/GLFW"
	include "Neato/vendor/Glad"
	include "Neato/vendor/imgui"
	
group ""

project "Neato"
	location "Neato"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	pchheader "NeatoPCH.h"
	pchsource "Neato/src/NeatoPCH.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
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
		symbols "on"

	filter "configurations:Release"
		defines "NEATO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NEATO_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
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
		"Neato/src",
		"Neato/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Neato"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"NEATO_PLATFORM_WINDOWS",
		}
		postbuildcommands
		{
			("{COPY} ../bin/" .. outputdir .. "/Neato/Neato.pdb" .. " ../bin/" .. outputdir .. "/%{prj.name}")
		}

	filter "configurations:Debug"
		defines "NEATO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NEATO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NEATO_DIST"
		runtime "Release"
		optimize "on"