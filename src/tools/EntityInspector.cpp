#include "EntityInspector.h"
#include <imgui.h>
#include "core/Components.h"
#include <glm/gtc/type_ptr.hpp>

namespace VE {

    entt::entity EntityInspector::s_SelectedEntity = entt::null;

    void EntityInspector::OnUIRender(entt::registry& registry) {
        ImGui::Begin("Entity Inspector");

        registry.view<TagComponent>().each([&](auto entity, auto& tag) {
            DrawEntityNode(registry, entity);
        });

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
            s_SelectedEntity = entt::null;
        }

        ImGui::End();

        ImGui::Begin("Properties");
        if (s_SelectedEntity != entt::null) {
            DrawComponents(registry, s_SelectedEntity);
        }
        ImGui::End();
    }

    void EntityInspector::DrawEntityNode(entt::registry& registry, entt::entity entity) {
        auto& tag = registry.get<TagComponent>(entity).Tag;

        ImGuiTreeNodeFlags flags = ((s_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

        if (ImGui::IsItemClicked()) {
            s_SelectedEntity = entity;
        }

        if (opened) {
            ImGui::TreePop();
        }
    }

    void EntityInspector::DrawComponents(entt::registry& registry, entt::entity entity) {
        if (registry.any_of<TagComponent>(entity)) {
            auto& tag = registry.get<TagComponent>(entity).Tag;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        }

        ImGui::Separator();

        if (registry.any_of<TransformComponent>(entity)) {
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
                auto& tc = registry.get<TransformComponent>(entity);
                ImGui::DragFloat3("Translation", glm::value_ptr(tc.Translation), 0.1f);
                
                glm::vec3 rotationDegrees = glm::degrees(tc.Rotation);
                if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotationDegrees), 0.1f)) {
                    tc.Rotation = glm::radians(rotationDegrees);
                }
                
                ImGui::DragFloat3("Scale", glm::value_ptr(tc.Scale), 0.1f);

                ImGui::TreePop();
            }
        }

        if (registry.any_of<RigidBodyComponent>(entity)) {
            ImGui::Separator();
            if (ImGui::TreeNodeEx((void*)typeid(RigidBodyComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "RigidBody")) {
                auto& rbc = registry.get<RigidBodyComponent>(entity);
                
                float mass = rbc.Body->GetMass();
                if (ImGui::DragFloat("Mass", &mass, 0.1f, 0.0f, 100.0f)) {
                    rbc.Body->SetMass(mass);
                }

                glm::vec3 vel = rbc.Body->GetVelocity();
                if (ImGui::DragFloat3("Velocity", glm::value_ptr(vel), 0.1f)) {
                    rbc.Body->SetVelocity(vel);
                }

                ImGui::TreePop();
            }
        }
    }

}
