#pragma once

#include <MakerEngine.h>
#include <lua54/lua.hpp>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string>

namespace MakerEngine {
    namespace Scripting {
        namespace Lua {
            class MAKERENGINE_API LuaStateManager {
            public:
                LuaStateManager();
                ~LuaStateManager();

                void executeFile(const std::string& path);
                void executeString(const std::string& string);

                lua_State* getLuaState() const;

            private:
                lua_State* luaState;
            };
        }
    }
}
