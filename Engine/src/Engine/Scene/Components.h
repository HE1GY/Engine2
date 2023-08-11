#pragma once

#include "Engine/Log/Log.h"
#include "Engine/LowAPI/Renderer/Texture.h"
#include "Engine/Math/Math.h"

#include "glm/ext/matrix_transform.hpp"


namespace Engine {

    struct CTransform {
        Vector3 position{};
        Vector3 rotation{};
        Vector3 scale{1.f, 1.f, 1.f};

        Mat4 GetTransform() const { // TODO own math methods
            return glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale)
                 * glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
                 * glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
                 * glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        }
    };


    struct CSpriteRenderer {
        glm::vec4 color{1, 1, 1, 1};
        Ref<Texture> texture{nullptr};
        uint32_t priority{}; // 0 most
    };

    struct CMove {
        Vector3 direction{};
        float move_speed{};
        float rotation_speed{};
    };


    struct CGameLogic {

        using Script = std::function<void()>;

        class ILogic {
        public:
            virtual void RegisterScript(Script& on_create, Script& on_update, Script& on_destroy) = 0;
        };

        void SetScript(std::shared_ptr<ILogic> logic) {
            script_object = logic;
            logic->RegisterScript(on_create, on_update, on_destroy);
            if (on_create) {
                on_create();
            }

            CORE_ASSERT_LOG(on_update, "On update must exists!");
        }

        Script on_create;
        Script on_update;
        Script on_destroy;

        std::shared_ptr<ILogic> script_object;

        CGameLogic& operator=(CGameLogic&& other) {
            if (on_destroy) {
                on_destroy();
            }
            return *this;
        }
    };


    struct CCircleCollider {
        float radius{};
        std::function<void()> on_collision{};
        uint32_t layer{};
    };
} // namespace Engine
