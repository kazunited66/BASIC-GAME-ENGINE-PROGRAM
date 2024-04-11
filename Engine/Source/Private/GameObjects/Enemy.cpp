#include"GameObjects/Enemy.h"

#define Super Charactor 

#define SCALE 3.0f
#define SIZE ((48.0f - 16.0f) * SCALE)
#define HALF_SIZE (SIZE / 2.0f)
Enemy::Enemy()
{
	m_MaxSpeed = 100.0f;
	m_MainSprite = AddSprite(
		"Content/Sprites/Main Ship/MAin Ship - Bases/PNGs/Main Ship - Base - Very damaged.png");
	Bounds* EnemyBounds = AddBounds(0.0f, SIZE);
	EnemyBounds->m_OriginalOffset = -HALF_SIZE;
	EnemyBounds->m_Tag = "ENEMY";
}

void Enemy::OnStart()
{
	Super::OnStart();

	//start the enemy above the screan 
	SetPosition({ 640.0f, 0.0f - HALF_SIZE });
	//flip it 180 to look downward
	SetRotation(180.0f);
	//change the scale
	SetScale(SCALE);
}

void Enemy::OnUpdate(float DeltTime)
{
	Super::OnPostUpdate(DeltTime);

	AddMovementInput(Vector2(0.0f, 1.0f));

	if (GetTransform().Position.y -
		HALF_SIZE > 720.0f) {
		SetPosition({ 640.0f, 0.0f - HALF_SIZE });
	}
}
