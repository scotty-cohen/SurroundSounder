function(Generate_Plugin)
  message("ADDING ${PLUGIN_NAME}")

  # -------
  # Defines
  # -------

  set(BINARY_DATA_NAME "${PROJECT_NAME}_BinaryData")
  set(TARGETS_FOLDER "${PROJECT_NAME}/Targets")
  set(EXTERNALS_FOLDER "${PROJECT_NAME}/Externals")
  set(FORMAT_LIST AU VST3 Standalone)
  
  # Add Plugin
  juce_add_plugin(${PROJECT_NAME}
    PLUGIN_NAME ${PLUGIN_NAME}
    PRODUCT_NAME ${PLUGIN_NAME}
    ICON_BIG ${ICON_PATH}
    ICON_SMALL ${ICON_PATH}
    FORMATS ${FORMAT_LIST}
    COPY_PLUGIN_AFTER_BUILD TRUE
    IS_SYNTH ${IS_SYNTH}
    NEEDS_MIDI_INPUT ${MIDI_INPUT}
    NEEDS_MIDI_OUTPUT ${MIDI_OUTPUT}
    IS_MIDI_EFFECT FALSE
    PLUGIN_MANUFACTURER_CODE "SCTT"
    PLUGIN_CODE ${PLUGIN_CODE})

  
  # Set Build Flags
  target_compile_definitions(${PROJECT_NAME}
    PUBLIC
      DONT_SET_USING_JUCE_NAMESPACE=0
      COPY_PLUGIN_AFTER_BUILD=TRUE
      JUCE_WEB_BROWSER=0
      JUCE_USE_CURL=0
      JUCE_VST3_CAN_REPLACE_VST2=0
      JUCE_MODAL_LOOPS_PERMITTED=1
      JUCE_DISABLE_CAUTIOUS_PARAMETER_ID_CHECKING=1
      JUCE_COREGRAPHICS_DRAW_ASYNC=1
      JUCE_DISPLAY_SPLASH_SCREEN=1
      JUCE_DISABLE_JUCE_VERSION_PRINTING=1
      SPLICE_BUILD=${SPLICE_BUILD}
      MKU_SIDECHAIN=${SIDECHAIN_INPUT})

  
  # We use JuceHeader.h
  juce_generate_juce_header(${PROJECT_NAME})
  
  # ----------------------------------
  # Add Sources And Mark Source Groups
  # ----------------------------------
    
  # Add Source Files
  file(GLOB_RECURSE Source ${CMAKE_CURRENT_LIST_DIR}/Source/*.cpp ${CMAKE_CURRENT_LIST_DIR}/Source/*.h)
  target_sources(${PROJECT_NAME} PRIVATE ${Source})
  source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${Source})
  
  # Add Project Source Files
  file(GLOB_RECURSE Project_Source ${CMAKE_CURRENT_LIST_DIR}/Project_Source/*.cpp ${CMAKE_CURRENT_LIST_DIR}/Project_Source/*.h)
  target_sources(${PROJECT_NAME} PRIVATE ${Project_Source})
  source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${Project_Source})

  # Add Lib Files
  file(GLOB_RECURSE Lib ${CMAKE_CURRENT_LIST_DIR}/../../Lib/*.cpp ${CMAKE_CURRENT_LIST_DIR}/../../Lib/*.h)
  target_sources(${PROJECT_NAME} PRIVATE ${Lib})
  source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/../../Lib PREFIX "Lib" FILES ${Lib})
  
  # -----------
  # Binary Data
  # -----------

  file(GLOB_RECURSE assets
          ${CMAKE_CURRENT_LIST_DIR}/../../Lib/Assets/*.svg
          ${CMAKE_CURRENT_LIST_DIR}/../../Lib/Assets/*.png
          ${CMAKE_CURRENT_LIST_DIR}/../../Lib/Assets/*.ttf
          ${CMAKE_CURRENT_LIST_DIR}/Project_Source/Assets/*.svg
          ${CMAKE_CURRENT_LIST_DIR}/Project_Source/Assets/*.png
          ${CMAKE_CURRENT_LIST_DIR}/Project_Source/Assets/*.ttf
          )


  juce_add_binary_data(${BINARY_DATA_NAME} SOURCES ${assets})
  
  # --------------------
  # Linking Requirements
  # --------------------

  
  target_link_libraries(
    ${PROJECT_NAME} 
      PRIVATE
        ${BINARY_DATA_NAME}
        juce_audio_utils
        juce_gui_extra
        juce_dsp
        juce_cryptography
      PUBLIC
        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags
  )

  if(${LTOActive})
    message("ADDING LTO")
    target_link_libraries(
      ${PROJECT_NAME} 
        PUBLIC
          juce::juce_recommended_lto_flags
    )
  endif()

  # -------------------
  # Optional Unity Builds
  # -------------------
#  if(${UnityBuild})
#    message("ADDING UNITY BUILD")
#    set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)
#    set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD_BATCH_SIZE 50)
#    file(GLOB_RECURSE JUCE_SOURCES ${CMAKE_SOURCE_DIR}/SDKs/JUCE/*.cpp  ${CMAKE_SOURCE_DIR}/SDKs/JUCE/*.mm ${CMAKE_SOURCE_DIR}/SDKs/JUCE/*.r)
#    set_source_files_properties(${JUCE_SOURCES} PROPERTIES SKIP_PRECOMPILE_HEADERS TRUE SKIP_UNITY_BUILD_INCLUSION TRUE)
#  endif()
  
  # -------------------
  # Header Search Paths
  # -------------------
  
  set(HEADER_GROUPS "Source" "Project_Source" "../../Lib")

  foreach(header_group ${HEADER_GROUPS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${header_group})
    file(GLOB_RECURSE sources_list LIST_DIRECTORIES true ${CMAKE_CURRENT_LIST_DIR}/${header_group}/*)
    foreach(dir ${sources_list})
        IF(IS_DIRECTORY ${dir})
          target_include_directories(${PROJECT_NAME} PRIVATE ${dir})
        ELSE()
            CONTINUE()
        ENDIF()
    endforeach()
  endforeach()
  
  foreach(target ${FORMAT_LIST} "All")
    if(TARGET ${PROJECT_NAME}_${target})
      set_target_properties(${PROJECT_NAME}_${target} PROPERTIES FOLDER ${TARGETS_FOLDER})
    endif()
  endforeach()
  
  set_target_properties(${BINARY_DATA_NAME} PROPERTIES FOLDER ${TARGETS_FOLDER})

  # Silence JUCE Files
  file(GLOB_RECURSE JUCE_SOURCES ${CMAKE_SOURCE_DIR}/SDKs/JUCE/*.cpp  ${CMAKE_SOURCE_DIR}/SDKs/JUCE/*.mm ${CMAKE_SOURCE_DIR}/SDKs/JUCE/*.r)
  set_source_files_properties(${JUCE_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
  target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/SDKs/JUCE/modules)

endfunction()
