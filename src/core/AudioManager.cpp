#include "AudioManager.h"

#include "raylib.h"

namespace {
Sound g_fireBall = {};
Sound g_explosion = {};
Sound g_hammerSmash = {};
Sound g_knife = {};
Sound g_laser = {};
Sound g_magicWand = {};
Sound g_shieldImpact = {};
Sound g_thunder = {};

Sound g_mainMenuMusic = {};
Sound g_gameOverMusic = {};
Sound g_victoryMusic = {};
Sound* g_currentMusic = nullptr;

AudioManager::MusicState g_currentMusicState = AudioManager::MusicState::MainMenu;
bool g_hasMusicState = false;
bool g_initialized = false;

void PlayLoadedSound(const Sound& sound) {
    if (!g_initialized || sound.frameCount == 0) return;
    PlaySound(sound);
}

Sound* GetMusicByState(AudioManager::MusicState state) {
    switch (state) {
        case AudioManager::MusicState::MainMenu: return &g_mainMenuMusic;
        case AudioManager::MusicState::InGame: return &g_mainMenuMusic;
        case AudioManager::MusicState::GameOver: return &g_gameOverMusic;
        case AudioManager::MusicState::Victory: return &g_victoryMusic;
    }
    return nullptr;
}

float GetMusicVolumeByState(AudioManager::MusicState state) {
    switch (state) {
        case AudioManager::MusicState::MainMenu: return 1.0f;
        case AudioManager::MusicState::InGame: return 0.35f;
        case AudioManager::MusicState::GameOver: return 1.0f;
        case AudioManager::MusicState::Victory: return 1.0f;
    }
    return 1.0f;
}

const char* GetMusicStateLabel(AudioManager::MusicState state) {
    switch (state) {
        case AudioManager::MusicState::MainMenu: return "MainMenu";
        case AudioManager::MusicState::InGame: return "InGame";
        case AudioManager::MusicState::GameOver: return "GameOver";
        case AudioManager::MusicState::Victory: return "Victory";
    }
    return "Unknown";
}
}

namespace AudioManager {
void Initialize() {
    if (g_initialized) return;

    InitAudioDevice();
    g_fireBall = LoadSound("Sound/FireBall.mp3");
    g_explosion = LoadSound("Sound/Explosion.mp3");
    g_hammerSmash = LoadSound("Sound/HammerSmash.mp3");
    g_knife = LoadSound("Sound/Knife.mp3");
    g_laser = LoadSound("Sound/Laser.mp3");
    g_magicWand = LoadSound("Sound/MagicWand.mp3");
    g_shieldImpact = LoadSound("Sound/ShieldImpact.mp3");
    g_thunder = LoadSound("Sound/Thunder.mp3");

    g_mainMenuMusic = LoadSound("Sound/Mainmenusound.mp3");
    g_gameOverMusic = LoadSound("Sound/GameOver.mp3");
    g_victoryMusic = LoadSound("Sound/GameVictory.mp3");

    g_initialized = true;
    SetMusicState(MusicState::MainMenu);
}

void Shutdown() {
    if (!g_initialized) return;

    if (g_currentMusic != nullptr) {
        StopSound(*g_currentMusic);
        g_currentMusic = nullptr;
    }

    UnloadSound(g_fireBall);
    UnloadSound(g_explosion);
    UnloadSound(g_hammerSmash);
    UnloadSound(g_knife);
    UnloadSound(g_laser);
    UnloadSound(g_magicWand);
    UnloadSound(g_shieldImpact);
    UnloadSound(g_thunder);

    UnloadSound(g_mainMenuMusic);
    UnloadSound(g_gameOverMusic);
    UnloadSound(g_victoryMusic);

    CloseAudioDevice();
    g_hasMusicState = false;
    g_initialized = false;
}

void Update() {
    if (!g_initialized || g_currentMusic == nullptr) return;

    if (!IsSoundPlaying(*g_currentMusic)) {
        PlaySound(*g_currentMusic);
    }
}

void SetMusicState(MusicState state) {
    if (!g_initialized) return;
    Sound* nextMusic = GetMusicByState(state);
    if (nextMusic == nullptr) return;

    if (g_currentMusic != nullptr && g_hasMusicState && g_currentMusicState == state) {
        SetSoundVolume(*g_currentMusic, GetMusicVolumeByState(state));
        return;
    }

    if (g_currentMusic == nextMusic) {
        g_currentMusicState = state;
        g_hasMusicState = true;
        SetSoundVolume(*g_currentMusic, GetMusicVolumeByState(state));
        TraceLog(LOG_INFO, "AudioManager: adjusted music state %s", GetMusicStateLabel(state));
        return;
    }

    if (g_currentMusic != nullptr) {
        StopSound(*g_currentMusic);
    }

    g_currentMusicState = state;
    g_hasMusicState = true;
    g_currentMusic = nextMusic;

    if (g_currentMusic != nullptr) {
        SetSoundVolume(*g_currentMusic, GetMusicVolumeByState(state));
        PlaySound(*g_currentMusic);
        TraceLog(LOG_INFO, "AudioManager: playing music state %s", GetMusicStateLabel(state));
    }
}

const char* GetMusicStateName(MusicState state) {
    return GetMusicStateLabel(state);
}

void PlayFireBall() { PlayLoadedSound(g_fireBall); }
void PlayExplosion() { PlayLoadedSound(g_explosion); }
void PlayHammerSmash() { PlayLoadedSound(g_hammerSmash); }
void PlayKnife() { PlayLoadedSound(g_knife); }
void PlayLaser() { PlayLoadedSound(g_laser); }
void PlayMagicWand() { PlayLoadedSound(g_magicWand); }
void PlayShieldImpact() { PlayLoadedSound(g_shieldImpact); }
void PlayThunder() { PlayLoadedSound(g_thunder); }
}
