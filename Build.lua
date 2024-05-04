workspace "Words counter"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "WCounterApp"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "WCounterCore/Build-Core.lua"
group ""

include "WCounterApp/Build-App.lua"