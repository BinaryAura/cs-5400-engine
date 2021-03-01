-- Spdlog doesn't have a premake5 file
project "spdlog"
    kind "StaticLib"
    language "C"

    pic "On"

    targetdir (out_dir .. "lib/" .. out_struct .. "/%{prj.name}")
    objdir (out_dir .. "build/" .. out_struct .. "/%{prj.name}")

    includedirs {
        "spdlog/include"
    }

    files {
        "spdlog/src/**.cpp",
        "spdlog/include/**.h"
    }

    filter "system:linux"
        systemversion "latest"
        staticruntime "On"

        defines "SPDLOG_COMPILED_LIB"

include_dirs["spdlog"] = "deps/spdlog/include"

include_dirs["entt"] = "deps/entt/single_include/entt"

include_dirs["glm"] = "deps/glm"
