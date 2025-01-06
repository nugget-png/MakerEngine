# Add source to this project's executable.
add_executable (GamePlayer "MakerGame.cpp" )

# Use UTF-8 encoding for MSVC and non-MSVC compilers
if (MSVC)
  target_compile_options(GamePlayer PRIVATE "/utf-8")
else()
  target_compile_options(GamePlayer PRIVATE "-finput-charset=UTF-8")
endif()

# Link to the MakerEngine library
target_link_libraries(GamePlayer PUBLIC ${CMAKE_BINARY_DIR}/MakerEngine/MakerEngine.lib)

# Add MakerEngine include directories
target_include_directories(GamePlayer PUBLIC ${CMAKE_SOURCE_DIR}/MakerEngine)
target_include_directories(GamePlayer PUBLIC ${CMAKE_SOURCE_DIR}/MakerEngine/Libraries)
target_include_directories(GamePlayer PUBLIC ${CMAKE_SOURCE_DIR}/MakerEngine/Global)
