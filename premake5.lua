workspace "Celestial"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Celestial/vendor/GLFW/include"

include "Celestial/vendor/GLFW"

project "Celestial"
	location "Celestial"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "clpch.h"
	pchsource "Celestial/src/clpch.cpp"

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
			"CL_BUILD_DLL",
			"CL_ENABLE_ASSERTS",
			"CL_PLATFORM_WINDOWS"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CL_DEBUG"
		symbols "On"
		staticruntime "off"
		runtime "Debug"
	filter "configurations:Release"
		defines "CL_RELEASE"
		optimize "On"
		staticruntime "off"
		runtime "Release"
	filter "configurations:Dist"
		defines "CL_DIST"
		optimize "On"
		staticruntime "off"
		runtime "Release"

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
		"Celestial/vendor/spdlog/include",
		"Celestial"
	}

	links
	{
		"Celestial"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CL_DEBUG"
		symbols "on"
	filter "configurations:Release"
		defines "CL_RELEASE"
		optimize "on"
	filter "configurations:Dist"
		defines "CL_DIST"
		optimize "on"