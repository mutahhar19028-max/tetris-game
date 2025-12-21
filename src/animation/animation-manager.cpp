#include "animation-manager.h"

const char* AnimationManager::animationNames[] = {
    "Square",
    "Particle Burst",
    "Spiral Dots",
    "Wavy Lines",
    "Ball"
};

int AnimationManager::currentAnimationIndex = 0;

AnimationManager::AnimationManager() {
    animations[static_cast<int>(AnimationType::SQUARE)] = new FloatingSquareAnimation();
    animations[static_cast<int>(AnimationType::PARTICLE_BURST)] = new ParticleBurstAnimation();
    animations[static_cast<int>(AnimationType::SPIRAL_DOTS)] = new SpiralDotsAnimation();
    animations[static_cast<int>(AnimationType::WAVY_LINES)] = new WavyLinesAnimation();
    animations[static_cast<int>(AnimationType::BALL)] = new BallAnimation();

    currentType = AnimationType::SQUARE;
    currentAnimation = animations[static_cast<int>(currentType)];
}

void AnimationManager::SetAnimation(AnimationType type) {
    if(type >= AnimationType::COUNT) 
        return;
    currentType = type;
    currentAnimation = animations[static_cast<int>(type)];
}

Speed AnimationManager::GetSpeed() const { return speed; }

void AnimationManager::Update() { if(currentAnimation) currentAnimation->Update(); }

void AnimationManager::Draw() { if(currentAnimation) currentAnimation->Draw(); }

void AnimationManager::CycleNextAnimation() {
    int nextIndex = (static_cast<int>(currentType) + 1) % static_cast<int>(AnimationType::COUNT);
    SetAnimation(static_cast<AnimationType>(nextIndex));
}

void AnimationManager::CyclePreviousAnimation() {
    int nextIndex = (static_cast<int>(currentType) - 1) % static_cast<int>(AnimationType::COUNT);
    SetAnimation(static_cast<AnimationType>(nextIndex));
}

void AnimationManager::SetSpeed(Speed s) {
    speed = s;
    for (int i = 0; i < static_cast<int>(AnimationType::COUNT); ++i)
        animations[i]->SetSpeed(speed);
}

AnimationManager::~AnimationManager() {
    for (int i = 0; i < static_cast<int>(AnimationType::COUNT); ++i) {
        delete animations[i];
        animations[i] = nullptr;
    }
}