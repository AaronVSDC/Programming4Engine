#include "GameObject.h"

namespace dae
{
    void GameObject::Update()
    {
        // Update each component
        for (auto& comp : m_components)
        {
            comp->Update();
        }
    }

    void GameObject::Render() const
    {
        // Render each component
        for (auto& comp : m_components)
        {
            comp->Render();
        }
    }
}
