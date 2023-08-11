#pragma once

#include "BulletScript.h"
#include "Engine/Engine.h"
#include <iostream>
#include <memory>


namespace Game {

    using namespace Engine;

    class PlayerLogic : public CGameLogic::ILogic {
    public:
        PlayerLogic(Entity e, Coordinator& c) : m_entity{e}, m_coord{c} {
        }

        void RegisterScript(
            CGameLogic::Script& on_create, CGameLogic::Script& on_update, CGameLogic::Script& on_destroy) override {
            on_create  = [this]() { OnCreate(); };
            on_update  = [this]() { OnUpdate(); };
            on_destroy = [this]() { OnDestroy(); };
        }

        Event<uint32_t> killEnemy;
        Event<> died;

    private:
        void OnCreate() {
            auto& sprite    = m_coord.AddComponent<CSpriteRenderer>(m_entity);
            sprite.color    = {1, 1, 1, 1};
            sprite.texture  = Renderer2D::CreateTexture("Game/assets/classic-border-red-circle-free-png-x2X5ZG.png");
            sprite.priority = 0;

            m_bullet_texture = Renderer2D::CreateTexture("Game/assets/awesomeface.png");

            auto& trans    = m_coord.AddComponent<CTransform>(m_entity);
            trans.position = {400, 300, 0}; // TODO
            trans.scale    = {80, 80, 1};


            auto& move          = m_coord.AddComponent<CMove>(m_entity);
            move.move_speed     = 150;
            move.rotation_speed = 100;

            m_shoot.AddCallback(MEM_FN_NOARGS_TO_LMD(Shoot));

            CCircleCollider& collider = m_coord.AddComponent<CCircleCollider>(m_entity);
            collider.radius           = 30.0f;
            collider.layer            = 0;
            collider.on_collision     = [this]() { OnCollision(); };
        }

        void OnUpdate() {
            HandleInput();
        }
        void OnDestroy() {
        }

    private:
        void HandleInput() {
            static CMove& move = m_coord.GetComponent<CMove>(m_entity);

            move.direction = {};
            if (Input::IsKeyPress(KeyCode::A)) {
                move.direction.x = -1;
            }

            if (Input::IsKeyPress(KeyCode::D)) {
                move.direction.x = 1;
            }

            if (Input::IsKeyPress(KeyCode::S)) {
                move.direction.y = 1;
            }

            if (Input::IsKeyPress(KeyCode::W)) {
                move.direction.y = -1;
            }

            static bool shot{false};
            if (Input::IsMouseButtonPress(MouseButtonCode::MOUSE_BUTTON_LEFT) && !shot) {
                m_shoot.Invoke();
            }
            shot = Input::IsMouseButtonPress(MouseButtonCode::MOUSE_BUTTON_LEFT);
        }

        void Shoot() {
            Vector2 pos_mouse;
            auto pair   = Input::GetMousePos();
            pos_mouse.x = pair.first;
            pos_mouse.y = pair.second;


            Vector2 player_pos = m_coord.GetComponent<CTransform>(m_entity).position;
            Vector2 dir{pos_mouse - player_pos};
            if (dir != Vector2{}) {
                dir = glm::normalize(dir);
            }

            Entity bullet = m_coord.CreateEntity();
            auto bullet_s = std::make_shared<BulletScript>(bullet, m_coord);
            auto& logic   = m_coord.AddComponent<CGameLogic>(bullet);
            logic.SetScript(bullet_s);

            auto& move     = m_coord.GetComponent<CMove>(bullet);
            move.direction = {dir, 0};

            auto& renderer   = m_coord.GetComponent<CSpriteRenderer>(bullet);
            renderer.texture = m_bullet_texture;

            auto& bullet_position    = m_coord.GetComponent<CTransform>(bullet);
            bullet_position.position = {player_pos, 0};
            bullet_position.scale    = {40, 40, 0};

            bullet_s->collision.AddCallback(MEM_FN_NOARGS_TO_LMD(InvokeKillEvent));
        }

        void OnCollision() {
            auto& trans    = m_coord.GetComponent<CTransform>(m_entity);
            trans.position = {400, 300, 0}; // TODO
            died.Invoke();
            score = 0;
        }

        void InvokeKillEvent() {
            killEnemy.Invoke(++score);
        }

    private:
        Entity m_entity;
        Coordinator& m_coord;
        Engine::Event<> m_shoot{};
        uint32_t score{};
        Ref<Texture> m_bullet_texture;
    };
} // namespace Game
