
# Add source to this library
add_library(MakerEngine SHARED "EngineMain.cpp" "Global/MakerEngine.h" "Global/MakerEngine.cpp")

# Include directories
include_directories(MakerEngine PUBLIC "Global")