# ---------
# Arguments
# ---------

set(PLUGIN_NAME "SurroundSounder")
set(VERSION "0.0.1")
set(IS_SYNTH FALSE)
set(SIDECHAIN_INPUT 0)
set(MIDI_INPUT FALSE)
set(MIDI_OUTPUT FALSE)
set(PLUGIN_CODE "SSDR") # Must be 4 characters


project(SurroundSounder VERSION ${VERSION})

Generate_Plugin()