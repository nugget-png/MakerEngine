#pragma once

#include "MakerEngine.h"

#include <optional>

namespace MakerEngine {
    namespace Graphics {
        namespace Vulkan {
            namespace Bootstrap {
                struct MAKERENGINE_API QueueFamilyIndices {
                    std::optional<uint32_t> graphicsFamily;
                    // Add more necessary queue family indices here

                    bool isComplete() {
                        return graphicsFamily.has_value();
                    }
                };
            }
        }
    }
}
