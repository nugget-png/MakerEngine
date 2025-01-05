# Maker Engine
  Maker Engine is an early-stage 2D game engine written in C++ that I have just started developing, with plans to add 3D support in the future. 
  At the moment, the engine is in its initial stages, with basic project structure and some code setup in place. The focus is on laying down the foundation for future features.

  The engine is aimed at beginners while allowing for more advanced features in the future.

## Current Status
   - The foundation of the engine is being developed using a CMake-based build system.
   - The engine currently doesn't have many source files since the project just started.
   - The engine will use Vulkan for rendering, however no functionality has been implemented yet.
   - The engine will eventually support multiple platforms (Windows, macOS, Linux).
   - The engine does not currently have the ability to create windows or render anything.

## Planned Features
(Some of these features might not be added until way later on)
  - Scripting with Lua
  - An editor implemented with ImGui
  - 3D support 
  - An entity component system
  - Scene management
    
## Building the Engine

Before building, make sure you have the [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/) installed on your system.

### Building in Visual Studio:
1. **Install [Visual Studio](https://visualstudio.microsoft.com/downloads/)** if you haven't already.
2. **Clone the repository**:
    ```shell
    git clone https://github.com/nugget-png/MakerEngine.git
    ```
3. **Open the folder in Visual Studio**.
4. **Press Run** (the green button on the toolbar) or press **F5** to build and run the engine.
 
### Building with CMake:
1. **Clone the repository**:
    ```shell
    git clone https://github.com/nugget-png/MakerEngine.git
    ```
2. **Make a build directory**:
    ```shell
    cd MakerEngine
    mkdir build
    cd build
    ```
3. **Build the Engine**
   - Build type can be Release, Debug, or RelWithDebugInfo
   ```shell
   cmake -DCMAKE_BUILD_TYPE=[YourBuildType] ..
   cmake --build .
   ```

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
