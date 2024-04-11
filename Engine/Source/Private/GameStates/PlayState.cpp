#include "GameStates/PlayState.h"
#include"GameObjects/Enemy.h"
#include"GameObjects/Player.h"	
#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include"Input.h"
#include"GameObjects/Enemy.h"
#include"GameObjects/Player.h"
#include"GameObjects/TextObject.h"
#include<string>

#include "Debug.h"
#define Super GameState 

void PlayState::OnStart()
{
	Super::OnStart();

	AddGameObject<Player>();
	AddGameObject<Enemy>();

	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 25.0f, 25.0f });
	m_ScoreText->SetFontSize(50);
	m_ScoreText->SetText("Score: 0");
	m_ScoreText->SetAlignment(AL_TOP_LEFT);
	
}


void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	static float score = 0.0f;
	score += DeltaTime * 10.0f;



	std::string scoreString = "Score: " + std::to_string(static_cast<int>(std::truncf(score)));

	m_ScoreText->SetText(scoreString.c_str());
}