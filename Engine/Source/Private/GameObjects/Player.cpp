#include "GameObjects/Player.h"
#include "Input.h"
#include "GameObjects/Enemy.h"


#define Super Charactor 
#define ENGINE_IDLE 0
#define ENGINE_POWERED 1
#define SCALE 3.0f
#define SIZE ((48.0f - 16.0f) * SCALE)
#define HALF_SIZE (SIZE/2.0f)

Player::Player()
{
	m_MaxSpeed  = 600.0f; 
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 5000.0f;
	
	AddSprite(
		"Content/Sprites/Main Ship/MAin Ship - Engines/PNGs/Main Ship - Engines - Supercharged Engine.png"
	);

	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/MAin Ship - Bases/PNGs/Main Ship - Base - Full health.png"
	);
	AnimationParams AnimParams;
	AnimParams.fps = 24.0f;
	AnimParams.FrameHeight = 48.0f;
	AnimParams.FrameWidth = 48.0f;
	AnimParams.EndFrame = 3;
	AnimParams.MaxFrames = 4;


	//Add the idle engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&AnimParams
	));

	//add the idle power engine effect 
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&AnimParams
	));
	//hide the sprire by default 

	SetPoweredEngines(false);

	Bounds* PlayerBounds = AddBounds({ 640.0f,360.0f }, SIZE);
	PlayerBounds->m_OriginalOffset = -HALF_SIZE;
	
}

void Player::OnStart()
{
	Super::OnStart();
	SetPosition({ 640.0f, 360.0f });
	SetScale(SCALE);
}

void Player::OnProcessInput(Input* GameInput)
{

	Super::OnProcessInput(GameInput);
	if (GameInput->IsKeyDown(EE_KEY_W)) {
		AddMovementInput(Vector2(0.0f, -1.0f));
	}
	if (GameInput->IsKeyDown(EE_KEY_S)) {
		AddMovementInput(Vector2(0.0f, 1.0f));
	}
	if (GameInput->IsKeyDown(EE_KEY_A)) {
		AddMovementInput(Vector2(-1.0f, 0.0f));
	}
	if (GameInput->IsKeyDown(EE_KEY_D)) {
		AddMovementInput(Vector2(1.0f, 0.0f));
	}
}



void Player::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	if (m_MoveDirection.Length() > 0.0f) {
		SetPoweredEngines(true);
	}
	else {
		SetPoweredEngines(false);
	}
}

void Player::SetPoweredEngines(bool Powered)
{
	if (m_EngineEffects.size() > 1) {
		if (m_EngineEffects[ENGINE_IDLE] != nullptr || m_EngineEffects[ENGINE_POWERED] != nullptr) {
			m_EngineEffects[ENGINE_IDLE]->SetActive(!Powered);
			m_EngineEffects[ENGINE_POWERED]->SetActive(Powered);
		}

	}
}

void Player::OnOverlapEnter(Bounds* OverlapBoudns, Bounds* HitBounds)
{
	if (dynamic_cast<Enemy*>(OverlapBoudns->GetOwner())) {
		OverlapBoudns->GetOwner()->DestreyObject();
	}
}
