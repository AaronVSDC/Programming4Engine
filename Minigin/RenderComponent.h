#pragma once
#include "Component.h"
#include <string>
#include <memory>

namespace dae
{
    class Texture2D;

    class RenderComponent final : public Component
    {
    public:
        RenderComponent() = default;
        virtual ~RenderComponent() = default;

        void Update() override {}
        void Render() const override;

        void SetTexture(const std::string& filename);
        // Optionally, add a SetTexture(std::shared_ptr<Texture2D>) if you want

    private:
        std::shared_ptr<Texture2D> m_texture{};
    };
}
