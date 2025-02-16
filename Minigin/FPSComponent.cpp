#include "FPSComponent.h"
#include "TextComponent.h"
#include "Time.h"

namespace dae
{
    void FPSComponent::Update()
    {
        // Count frames
        m_timePassed += Time::GetInstance().GetDeltaTime();
        ++m_frameCount;

        if (m_timePassed >= 1.0f) // every 1 second
        {
            const auto fps = m_frameCount / m_timePassed;
            m_timePassed = 0.f;
            m_frameCount = 0;

            // Update the text if available
            if (m_textComponent)
            {
                m_textComponent->SetText(std::to_string((int)fps) + " FPS");
            }
        }
    }
}
