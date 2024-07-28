
workspace "ImageConvolution"
    architecture "x64"
    startproject "main"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    configurations {
            "Debug",
            "Release",
            "ReleaseSIMD",
            "ReleaseCSIMD"
    }

    filter "configurations:ReleaseCSIMD"
        defines { "NDEBUG", "CSIMD" }
        buildoptions { "-fopenmp", "-mavx2", "-O3" }
        linkoptions { "-fopenmp" }

    filter "configurations:ReleaseSIMD"
        defines { "NDEBUG", "SIMD" }
        buildoptions { "-fopenmp", "-mavx2", "-O3" }
        linkoptions { "-fopenmp" }

    filter "configurations:Release"
        defines { "NDEBUG", "NOSIMD" }
        buildoptions { "-fopenmp"}
        linkoptions { "-fopenmp" }

    project "convLibrary"
        kind "SharedLib"
        location "convLibrary"
        language "C++"
        cppdialect "C++20"
        systemversion "latest"
        
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("obj/" .. outputdir .. "/%{prj.name}")
    
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs {
            "%{prj.name}/src",
            "/usr/include/opencv4"
        }

        libdirs { "/usr/lib" }

        links {
            "opencv_core",
            "opencv_imgcodecs",
            "opencv_highgui",
            "opencv_imgproc"
        }

        filter "configurations:Debug"
            defines { "DEBUG", "LOGGING" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG", "NOSIMD" }
            buildoptions { "-fopenmp", "-O2" }
            linkoptions { "-fopenmp" }

        filter "configurations:ReleaseSIMD"
            defines { "NDEBUG", "SIMD" }
            buildoptions { "-fopenmp", "-mavx2", "-O3" }
            linkoptions { "-fopenmp" }

        filter "configurations:ReleaseCSIMD"
            defines { "NDEBUG", "CSIMD" }
            buildoptions { "-fopenmp", "-mavx2" }
            linkoptions { "-fopenmp" }


    project "main"
        location "main"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        systemversion "latest"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("obj/" .. outputdir .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs {
            "convLibrary/src",
            "%{prj.name}/src",
            "/usr/include/opencv4"
        }

        libdirs { "/usr/lib" }

        links {
            "convLibrary",
            "opencv_core",
            "opencv_imgcodecs",
            "opencv_highgui",
            "opencv_imgproc"
        }

        filter "configurations:Debug"
            defines { "DEBUG", "LOGGING" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG", "NOSIMD" }
            buildoptions { "-fopenmp" }
            linkoptions { "-fopenmp" }

        filter "configurations:ReleaseSIMD"
            defines { "NDEBUG", "SIMD" }
            buildoptions { "-fopenmp", "-mavx2", "-O3" }
            linkoptions { "-fopenmp" }

        filter "configurations:ReleaseCSIMD"
            defines { "NDEBUG", "CSIMD" }
            buildoptions { "-fopenmp", "-mavx2" }
            linkoptions { "-fopenmp" }
