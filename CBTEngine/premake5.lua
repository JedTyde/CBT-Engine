workspace "CBTEngine"
architecture "x64"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "CBTEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "CBTEngine/vendor/GLAD/include"
IncludeDir["imgui"] = "CBTEngine/vendor/imgui/include"
IncludeDir["rapidjson"] = "CBTEngine/vendor/rapidjson/include"
IncludeDir["glm"] = "CBTEngine/vendor/glm"
IncludeDir["assimp"] = "CBTEngine/vendor/Assimp/include"

include "CBTEngine/vendor/GLFW"
include "CBTEngine/vendor/GLAD"
include "CBTEngine/vendor/imgui"

project "CBTEngine"
    location "CBTEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "CBTpch.h"
    pchsource "CBTEngine/src/CBTpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    
    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
        "%{IncludeDir.assimp}"
	}
		
	links
	{
		"GLFW",
		"GLAD",
		"imgui",
        "CBTEngine/vendor/Assimp/lib/x64/debug/assimp-vc143-mtd.lib"
		--"opengl132.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "CBT_PLATFORM_WINDOWS",
            "CBT_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../Editor")
        }

    filter "configurations:Debug"
        defines "CBT_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "CBT_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "CBT_DIST"
        buildoptions "/MD"
        optimize "On"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir ("Editor")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    
    includedirs
    {
        "CBTEngine/vendor/spdlog/include",
        "CBTEngine/src"
    }

    links
    {
        "CBTEngine",
		"ImGui"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "CBT_PLATFORM_WINDOWS"
        }
		
		postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../Editor")
        }

    filter "configurations:Debug"
        defines "CBT_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "CBT_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "CBT_DIST"
        buildoptions "/MD"
        optimize "On"