#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
    class TextComponent;

    class FPSComponent final : public Component
    {
    public:
        FPSComponent() = default;
        ~FPSComponent() override = default;

        void Update() override;

        void SetTextComponent(std::shared_ptr<TextComponent> textComp)
        {
            m_textComponent = textComp;
        }

    private:
        float m_timePassed{};
        int   m_frameCount{};
        std::shared_ptr<TextComponent> m_textComponent{};
    };
}
