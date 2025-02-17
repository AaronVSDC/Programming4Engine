#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

// Components
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Font.h"
#include <iostream>

void LoadDemo()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    // 1) Background
    {
        auto background = std::make_shared<dae::GameObject>();
        background->AddComponent<dae::TransformComponent>()->SetPosition(0, 0);
        background->AddComponent<dae::RenderComponent>()->SetTexture("background.tga");
        scene.Add(background);
    }

    // 2) Logo
    {
        auto logo = std::make_shared<dae::GameObject>();
        auto transform = logo->AddComponent<dae::TransformComponent>();
        transform->SetPosition(216.f, 180.f);

        auto render = logo->AddComponent<dae::RenderComponent>();
        render->SetTexture("logo.tga");

        scene.Add(logo);
    }

    // 3) Text: "Programming 4 Assignment"
    {
        auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

        auto textGO = std::make_shared<dae::GameObject>();
        textGO->AddComponent<dae::TransformComponent>()->SetPosition(80.f, 20.f);

        auto textComp = textGO->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);

        scene.Add(textGO);
    }

    // 4) FPS Counter
    {
        auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

        auto fpsGO = std::make_shared<dae::GameObject>();
        fpsGO->AddComponent<dae::TransformComponent>()->SetPosition(0.f, 0.f);

        // Create the text component that will display the FPS
        auto fpsText = fpsGO->AddComponent<dae::TextComponent>("0 FPS", font);

        // Create the FPSComponent
        auto fpsComp = fpsGO->AddComponent<dae::FPSComponent>();
        fpsComp->SetTextComponent(fpsText);

        scene.Add(fpsGO);
    }
}

int main(int, char* [])
{
    // Initialize engine
    dae::Minigin engine("../Data/");

    try
    {
        engine.Run(LoadDemo);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
