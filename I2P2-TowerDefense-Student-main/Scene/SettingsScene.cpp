#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Slider.hpp"
#include "SettingsScene.hpp"

void SettingsScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    AddNewControlObject(UIGroup = new Group());
    UIGroup->AddNewObject(new Engine::Image("our_game/background1.png", 0, 0, 1600, 900));
    // Yuli
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("stage-select/back.png", "stage-select/on.png", halfW - 200, halfH * 3 / 2 - 50,
                                  400, 100);
    btn->SetOnClickCallback(std::bind(&SettingsScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    
    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(40 + halfW - 95, halfH - 50 - 2, 190, 4);
    sliderBGM->SetOnValueChangedCallback(
            std::bind(&SettingsScene::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(
            new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH - 50, 0, 0, 0, 255, 0.5,
                              0.5));
    sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190, 4);
    sliderSFX->SetOnValueChangedCallback(
            std::bind(&SettingsScene::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(
            new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH + 50, 0, 0, 0, 255, 0.5,
                              0.5));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
    sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}

void SettingsScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}

void SettingsScene::PlayOnClick(int stage) {
    // Yuli
    Engine::GameEngine::GetInstance().ChangeScene("start");
    // Yuli
}

void SettingsScene::BGMSlideOnValueChanged(float value) {
    AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}

void SettingsScene::SFXSlideOnValueChanged(float value) {
    AudioHelper::SFXVolume = value;
}
