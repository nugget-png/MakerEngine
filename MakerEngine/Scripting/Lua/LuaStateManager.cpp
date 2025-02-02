#include "LuaStateManager.h"

namespace MakerEngine {
    namespace Scripting {
        namespace Lua {
            LuaStateManager::LuaStateManager()
                : luaState(nullptr)
            {
                luaState = luaL_newstate();
                if (!luaState) {
                    spdlog::critical("Failed to create Lua state!");
                    throw std::runtime_error("Failed to create Lua state!");
                }
                luaL_openlibs(luaState);
                spdlog::debug("Lua state created successfully");
                spdlog::debug("Lua state address: {}", luaState);
            }

            void LuaStateManager::executeFile(const std::string& path) {
                spdlog::debug("Attempting to execute lua file: {}", path);

                int result = luaL_dofile(luaState, path.c_str());
                if (result != LUA_OK) {
                    // Log the error message
                    spdlog::error("(SCRIPT) Error while executing file: {}", lua_tostring(luaState, -1));
                    lua_pop(luaState, 1); // Clear the error message from the lua stack
                }
                else {
                    spdlog::debug("(SCRIPT) Execution successful");
                }
            }

            void LuaStateManager::executeString(const std::string& string) {
                spdlog::debug("Attempting to execute lua string: {}", string);

                int result = luaL_dostring(luaState, string.c_str());
                if (result != LUA_OK) {
                    // Log the error message
                    spdlog::error("(SCRIPT) Error while executing string: {}", lua_tostring(luaState, -1));
                    lua_pop(luaState, 1); // Clear the error message from the lua stack
                }
                else {
                    spdlog::debug("(SCRIPT) Execution successful");
                }
            }

            lua_State* LuaStateManager::getLuaState() const {
                return luaState;
            }

            LuaStateManager::~LuaStateManager() {
                if (luaState) {
                    lua_close(luaState);
                }
            }
        }
    }
}
