workspace "Neato"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Neato"
	location "Neato"
	kind "SharedLib"
	language "C++"
	targetdir ("bin" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	include
	{
		"%{prj.name}/vendor/spdlog/include"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.16299.0"
		defines
		{
			"NEATO_PLATFORM_WINDOWS",
			"NEATO_BUILD_DLL"
		}
		postbuildcommnads
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
	targetdir ("bin" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int" .. outputdir .. "/%{prj.name}")
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	include
	{
		"%{prj.name}/vendor/spdlog/include",
		"Neato/src"
	}

	links
	{
		"Neato"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.16299.0"
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