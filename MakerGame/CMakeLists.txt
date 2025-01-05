# Add source to this project's executable.
add_executable (MakerGame "MakerGame.cpp" )

# Use UTF-8 encoding for MSVC and non-MSVC compilers
if (MSVC)
  target_compile_options(MakerGame PRIVATE "/utf-8")
else()
  target_compile_options(MakerGame PRIVATE "-finput-charset=UTF-8")
endif()

# Link to the MakerEngine library
target_link_libraries(MakerGame PUBLIC ${CMAKE_BINARY_DIR}/MakerEngine/MakerEngine.lib)

# Add MakerEngine include directories
include_directories(MakerGame PUBLIC ${CMAKE_SOURCE_DIR}/MakerEngine)
include_directories(MakerGame PUBLIC ${CMAKE_SOURCE_DIR}/MakerEngine/Libraries)
include_directories(MakerGame PUBLIC ${CMAKE_SOURCE_DIR}/MakerEngine/Global)
