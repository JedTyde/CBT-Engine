workspace "CBTEngine"
architecture "x64"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CBTEngine"
    location "CBTEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    
    includedirs
    {
        "%{prj.name}/src"
        "%{prj.name}/vendor/spdlog/include"
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
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "CBT_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CBT_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CBT_DIST"
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
        "%{prj.name}/src/**.cpp",
    }
    
    includedirs
    {
        "CBTEngine/vendor/spdlog/include",
        "CBTEngine/src"
    }

    links
    {
        "CBTEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "CBT_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "CBT_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CBT_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CBT_DIST"
        optimize "On"