-- Default out_dir and out_struct
if(out_dir == nil) then
  out_dir = "%{wks.location}/"
end
if(out_struct == nil) then
  out_struct = "%{cfg.buildcfg}/"
end
if(include_dirs == nil) then
  include_dirs = {}
end

include "deps"

project "hadron"
  cppdialect "C++17"
  pic "On"
  kind "StaticLib"
  language "C++"
  targetdir (out_dir .. "bin/" .. out_struct .. "%{prj.name}")
  objdir (out_dir .. "build/" .. out_struct .. "%{prj.name}")
  buildoptions {"-Wfatal-errors"}

  includedirs {
    "%{include_dirs.spdlog}",
    "%{include_dirs.entt}",
    "%{include_dirs.glm}",
    "include"
  }

  links {
    "spdlog",
    "ncurses"
  }

  pchheader "hadron/hgepch.h"
  pchsource "src/hgepch.cpp"

  files {
    "src/application/main.cpp",
    "src/input/cursesinput.cpp",
    "src/physics/tilephysics.cpp",
    "src/renderer/cursesrenderer.cpp",
    "src/window/curseswindow.cpp",
    "src/utility/log.cpp",
    "src/scene/scene.cpp"
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    optimize "On"
