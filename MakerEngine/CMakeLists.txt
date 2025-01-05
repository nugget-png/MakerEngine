
# Add source to this library
add_library(MakerEngine SHARED 
"EngineMain.cpp" 
"Global/MakerEngine.h" 
"Global/MakerEngine.cpp"
"Libraries/spdlog/async.cpp"
"Libraries/spdlog/bundled_fmtlib_format.cpp"
"Libraries/spdlog/cfg.cpp"
"Libraries/spdlog/color_sinks.cpp"
"Libraries/spdlog/file_sinks.cpp"
"Libraries/spdlog/stdout_sinks.cpp"
"Libraries/spdlog/spdlog.cpp"
)

# Define MAKERENGINE_EXPORTS to export symbols
target_compile_definitions(MakerEngine PRIVATE MAKERENGINE_EXPORTS)

# Define SPDLOG_COMPILED_LIB to build spdlog
target_compile_definitions(MakerEngine PRIVATE SPDLOG_COMPILED_LIB)

# Use UTF-8 encoding for MSVC and non-MSVC compilers
if (MSVC)
  target_compile_options(MakerEngine PRIVATE "/utf-8")
else()
  target_compile_options(MakerEngine PRIVATE "-finput-charset=UTF-8")
endif()

# Include directories
include_directories(MakerEngine PUBLIC "Global")
include_directories(MakerEngine PUBLIC "Libraries")