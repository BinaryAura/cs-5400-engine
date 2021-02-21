project "hadron-engine"
  cppdialect "C++17"
  pic "On"
  kind "StaticLib"
  language "C++"
  targetdir (out_dir .. "bin/" .. out_struct .. "%{prj.name}")
  objdir (out_dir .. "build/" .. out_struct .. "%{prj.name}")

  includedirs {
  }

  links {
  }

  files {
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    optimize "On"
