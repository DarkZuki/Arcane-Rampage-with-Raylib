#pragma once

namespace AudioManager {
enum class MusicState {
    MainMenu,
    InGame,
    GameOver,
    Victory
};

void Initialize();
void Shutdown();
void Update();
void SetMusicState(MusicState state);

void PlayFireBall();
void PlayExplosion();
void PlayHammerSmash();
void PlayKnife();
void PlayLaser();
void PlayMagicWand();
void PlayShieldImpact();
void PlayThunder();
}
