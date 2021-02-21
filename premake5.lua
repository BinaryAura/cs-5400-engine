-- Default out_dir and out_struct
if(out_dir == nil)
  out_dir = "%{wks.location}/"
end
if(out_struct == nil)
  out_struct = "%{cfg.buildcfg}/"
end

project "hadron-engine"
  cppdialect "C++17"
  pic "On"
  kind "StaticLib"
  language "C++"
  targetdir (out_dir .. "bin/" .. out_struct .. "%{prj.name}")
  objdir (out_dir .. "build/" .. out_struct .. "%{prj.name}")

  includedirs {
    "include"
  }

  links {
    "spdlog",
    "entt"
    "ncurses"
  }

  pchheader "include/hgepch.h"
  pchsource "include/hgepch.cpp"

  files {
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    optimize "On"
