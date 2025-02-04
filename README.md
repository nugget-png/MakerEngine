# Maker Engine
  Maker Engine is an early-stage 2D game engine written in C++ that I have just started developing, with plans to add 3D support in the future. 
  At the moment, the engine is in its initial stages, with basic project structure and some code setup in place. The focus is on laying down the foundation for future features.

  The engine is aimed at beginners while allowing for more advanced features in the future.

## Current Status
   - The foundation of the engine is being developed using a CMake-based build system.
   - The engine will use Vulkan for rendering, however no functionality has been implemented yet.
   - The engine plans to eventually support multiple platforms (Windows, macOS, Linux).
   - The engine can create a very basic window, but can't render anything.
   - The engine can execute lua scripts, but there isn't an API to use.

## Planned Features
  - Scripting with Lua
  - An editor implemented with ImGui
  - 3D support 
  - An entity component system
  - Scene management
    
## Building the Engine
Before building the engine, please make sure you have the following dependencies installed:
1. **Vulkan SDK**
   - For all platforms except macOS, make sure you have the [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/).
2. **MoltenVK (For macOS)**
   - macOS users need [MoltenVK](https://github.com/KhronosGroup/MoltenVK) instead of the standard SDK to interface with Apple's Metal framework.

### Building in Visual Studio:
1. **Install [Visual Studio](https://visualstudio.microsoft.com/downloads/)** if you haven't already.
2. **Clone the repository**:
    ```shell
    git clone https://github.com/nugget-png/MakerEngine.git
    ```
3. **Open the folder in Visual Studio**.
4. **Select your desired build configuration**.
5. **Press Run** (the green button on the toolbar) or press **F5** to build and run the engine.
 
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
3. **Build the Engine**:
   - Build type can be Release, Debug, or RelWithDebugInfo
   ```shell
   cmake -DCMAKE_BUILD_TYPE=[YourBuildType] ..
   cmake --build .
   ```

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
