#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <algorithm>

#include "Component.h"

namespace dae
{
    class GameObject final
    {
    public:
        GameObject() = default;
        ~GameObject() = default;
        GameObject(const GameObject& other) = delete;
        GameObject(GameObject&& other) = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other) = delete;

        void Update();
        void Render() const;

        // Add a component of type T
        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of<Component, T>::value,
                "T must derive from Component");

            // Create the component
            auto comp = std::make_shared<T>(std::forward<Args>(args)...);
            comp->SetOwner(this);
            comp->Initialize();

            // Store it
            m_components.emplace_back(comp);
            return comp;
        }

        // Get the first component of type T
        template<typename T>
        std::shared_ptr<T> GetComponent() const
        {
            static_assert(std::is_base_of<Component, T>::value,
                "T must derive from Component");

            for (auto& comp : m_components)
            {
                auto casted = std::dynamic_pointer_cast<T>(comp);
                if (casted)
                    return casted;
            }
            return nullptr;
        }

        // Check if a component of type T exists
        template<typename T>
        bool HasComponent() const
        {
            return (bool)GetComponent<T>();
        }

        // Remove the first component of type T
        template<typename T>
        void RemoveComponent()
        {
            static_assert(std::is_base_of<Component, T>::value,
                "T must derive from Component");

            auto it = std::remove_if(m_components.begin(), m_components.end(),
                [&](std::shared_ptr<Component>& comp)
                {
                    return std::dynamic_pointer_cast<T>(comp) != nullptr;
                }
            );
            if (it != m_components.end())
            {
                m_components.erase(it, m_components.end());
            }
        }

    private:
        std::vector<std::shared_ptr<Component>> m_components{};
    };
}
