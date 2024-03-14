#include "GameObjects/PhysicsObject.h"

void PhysicsObject::OnStart()
{
	SetPosition({ 640, 360.0f });

	AnimationParams AnimParams;
	AnimParams.fps = 24.0f;
	AnimParams.MaxFrames = 12;
	AnimParams.EndFrame = 11;
	AnimParams.FrameWidth = 64;
	AnimParams.FrameHeight = 64;


	m_Sprite = AddSprite("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Round Shield.png",
		&AnimParams);
}

void PhysicsObject::OnProcessInput(Input* GameInput)
{
}

void PhysicsObject::OnUpdate(float DeltaTime)
{
	if (m_Sprite != nullptr) {
		m_Sprite->Update(DeltaTime);
		
	}
}
