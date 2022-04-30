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
IncludeDir["GLFW"] = "Celestial/vendor/GLFWgit/include"
IncludeDir["Glad"] = "Celestial/vendor/Glad/include"
IncludeDir["ImGUI"] = "Celestial/vendor/ImGUI"
IncludeDir["glm"] = "Celestial/vendor/glm"

include "Celestial/vendor/GLFWgit"
include "Celestial/vendor/Glad"
include "Celestial/vendor/ImGUI"

project "Celestial"
	location "Celestial"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "clpch.h"
	pchsource "Celestial/src/clpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CL_BUILD_DLL",
			"CL_ENABLE_ASSERTS",
			"CL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "CL_DEBUG"
		symbols "On"
		runtime "Debug"
	filter "configurations:Release"
		defines "CL_RELEASE"
		optimize "On"
		runtime "Release"
	filter "configurations:Dist"
		defines "CL_DIST"
		optimize "On"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

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
		"Celestial",
		"%{IncludeDir.glm}",
		"Celestial/vendor"
	}

	links
	{
		"Celestial"
	}

	filter "system:windows"
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