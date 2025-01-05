
# Add source to this library
add_library(MakerEngine SHARED "EngineMain.cpp" "Global/MakerEngine.h" "Global/MakerEngine.cpp")

# Define MAKERENGINE_EXPORTS to export symbols
target_compile_definitions(MakerEngine PRIVATE MAKERENGINE_EXPORTS)

# Include directories
include_directories(MakerEngine PUBLIC "Global")