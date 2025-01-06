
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
  "Application/Window.h" "Application/Window.cpp")

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

# Target link libraries
target_link_libraries(MakerEngine PRIVATE ${CMAKE_SOURCE_DIR}/MakerEngine/Libraries/GLFW/glfw3.lib)

# Include directories
include_directories(MakerEngine PUBLIC "Global")
include_directories(MakerEngine PUBLIC "Libraries")

# Using VulkanSDK 1.3.296.0
set (VulkanSDK "C:/VulkanSDK/1.3.296.0") # Change this to your VulkanSDK path if building from source
include_directories(MakerEngine PUBLIC "${VulkanSDK}/Include")
target_link_libraries(MakerEngine PRIVATE "${VulkanSDK}/Lib/vulkan-1.lib")
