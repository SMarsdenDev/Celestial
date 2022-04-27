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
	kind "SharedLib"
	language "C++"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CL_BUILD_DLL",
			"CL_ENABLE_ASSERTS",
			"CL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
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
		buildoptions "/MDd"
	filter "configurations:Release"
		defines "CL_RELEASE"
		optimize "On"
		staticruntime "off"
		runtime "Release"
		buildoptions "/MD"
	filter "configurations:Dist"
		defines "CL_DIST"
		optimize "On"
		staticruntime "off"
		runtime "Release"
		buildoptions "/MD"

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
		"Celestial",
		"%{IncludeDir.glm}"
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