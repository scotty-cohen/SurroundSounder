include(CMake/GeneratePlugin.cmake)

cmake_minimum_required(VERSION 3.23.0)
project("SurroundSounder")
string(TIMESTAMP CurrentYear "%Y")

# Apple Targets Universal Architectures
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")

# If we are using MSVC we want dynamic runtime linkage
set (CMAKE_GENERATOR_TOOLSET ClangCL)
set (CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# If we are compiling for Mac OS we want to target OS versions down to 10.9
set (CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE INTERNAL "")

if(${UniversalBinary})
  message("ADDING UNIVERSAL BUILDS")
  set (CMAKE_OSX_ARCHITECTURES x86_64 arm64)
endif()

# Add JUCE
set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON)
add_subdirectory(SDKs/JUCE)

set_directory_properties(PROPERTIES JUCE_COMPANY_COPYRIGHT "Copyright ${CurrentYear} - Scott Cohen")
set_directory_properties(PROPERTIES JUCE_COMPANY_NAME "Scott Cohen")
# set_directory_properties(PROPERTIES JUCE_COMPANY_WEBSITE "https://www.example.com")
set_directory_properties(PROPERTIES JUCE_COMPANY_EMAIL "scottcohen@alum.calarts.edu")

# Plugins
if (NOT DEFINED PluginChoice)
  set(PluginChoice "All")
endif()

if(${PluginChoice} STREQUAL "All")
  add_subdirectory("Plugins/SurroundSounder")

else()
  add_subdirectory("Plugins/${PluginChoice}")
endif()


