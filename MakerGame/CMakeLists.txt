# Add source to this project's executable.
add_executable (MakerGame "MakerGame.cpp" "MakerGame.h")

# Use UTF-8 encoding for MSVC and non-MSVC compilers
if (MSVC)
  target_compile_options(MakerGame PRIVATE "/utf-8")
else()
  target_compile_options(MakerGame PRIVATE "-finput-charset=UTF-8")
endif()