#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
    TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
        : m_text(text), m_font(std::move(font))
    {
    }

    void TextComponent::Update()
    {
        if (m_needsUpdate)
        {
            const SDL_Color color = { 255,255,255,255 };
            const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
            if (!surf)
            {
                throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
            }
            auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
            if (!texture)
            {
                throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
            }
            SDL_FreeSurface(surf);

            m_textTexture = std::make_shared<Texture2D>(texture);
            m_needsUpdate = false;
        }
    }

    void TextComponent::Render() const
    {
        if (m_textTexture)
        {
            // render at Transform
            const auto transform = GetOwner()->GetComponent<TransformComponent>();
            if (!transform) return;

            const auto& pos = transform->GetPosition();
            Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
        }
    }

    void TextComponent::SetText(const std::string& text)
    {
        if (text != m_text)
        {
            m_text = text;
            m_needsUpdate = true;
        }
    }
}
