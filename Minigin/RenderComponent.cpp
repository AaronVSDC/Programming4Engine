#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
    void RenderComponent::Render() const
    {
        if (!m_texture) return;

        // We need the transform from our owner
        const auto transform = GetOwner()->GetComponent<TransformComponent>();
        if (!transform) return;  // If no transform, we can’t render

        const auto& pos = transform->GetPosition();
        Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
    }

    void RenderComponent::SetTexture(const std::string& filename)
    {
        m_texture = ResourceManager::GetInstance().LoadTexture(filename);
    }
}
