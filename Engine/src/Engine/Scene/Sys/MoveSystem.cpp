#include "MoveSystem.h"

#include "Engine/Core/Time.h"
#include "Engine/Scene/Components.h"

namespace Engine {

    void MoveSystem::Update() {
        for (auto& e : m_filtered_entities) {
            auto& move      = m_coord.GetComponent<CMove>(e);
            auto& transform = m_coord.GetComponent<CTransform>(e);

            if (move.direction != Vector3{}) {
                move.direction = glm::normalize(move.direction);
            }

            transform.position += move.direction * move.move_speed * Time::s_delta_time;
            transform.rotation.z += Time::s_delta_time * move.rotation_speed;
        }
    }

} // namespace Engine
