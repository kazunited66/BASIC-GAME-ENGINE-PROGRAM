#include"GameObjects/Enemy2.h"
#define Super Charactor 

#define SCALE 3.0f
#define SIZE (48.0f * SCALE)
#define HALF_SIZE (SIZE / 2.0f)
Enemy2::Enemy2()
{
	m_MaxSpeed = 100.0f;
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/MAin Ship - Bases/PNGs/Main Ship - Base - Slight damage.png");
}

void Enemy2::OnStart()
{
	Super::OnStart();

	//start the enemy above the screan 
	SetPosition({ 840.0f, 0.0f - HALF_SIZE });
	//flip it 180 to look downward
	SetRotation(180.0f);
	//change the scale
	SetScale(SCALE);
}

void Enemy2::OnUpdate(float DeltTime)
{
	Super::OnPostUpdate(DeltTime);

	AddMovementInput(Vector2(0.0f, 1.0f));

	if (GetTransform().Position.y -
		HALF_SIZE > 720.0f) {
		SetPosition({ 840.0f, 0.0f - HALF_SIZE });
	}
}
