#include "GameStates/PlayState.h"
#include"GameObjects/Enemy.h"
#include"GameObjects/Player.h"	
#include "Game.h"
#include "GameStates/GameStateMachine.h"
#include"Input.h"
#include"GameObjects/TextObject.h"



#include<string>
#include<iomanip>
#include<random>
#include<sstream>

#include "Debug.h"

#define Super GameState 

std::default_random_engine RandGenerator; 

PlayState::PlayState() :
m_ScoreText(nullptr),
m_FreqText(nullptr),
m_EnemyFrequency(3.0f),
m_EnemySpawnTimer(5.0f)
{}

void PlayState::OnStart()
{
	Super::OnStart();

	Player* P = AddGameObject<Player>();
	P->SetPosition({ Game::GetGame()->WindowWidth()/ 2.0f, Game::GetGame()->WindowHeightF() - P->ScaleHalfSize()});


	m_ScoreText = AddGameObject<TextObject>();
	m_ScoreText->SetPosition({ 25.0f, 25.0f });
	m_ScoreText->SetFontSize(50);
	m_ScoreText->SetAlignment(AL_TOP_LEFT);
	UpdateScore();

	m_FreqText = AddGameObject<TextObject>();
	m_FreqText->SetPosition({ 25.0f, 70.0f });
	m_FreqText->SetFontSize(25);
	m_FreqText->SetAlignment(AL_TOP_LEFT);
	UpdateFrequencyText();

	RandGenerator.seed(time(nullptr));
}


void PlayState::OnUpdate(float DeltaTime)
{
	Super::OnUpdate(DeltaTime);

	EnemySpawner(DeltaTime);

	UpdateScore();
	
}

void PlayState::UpdateScore()
{
	std::string scoreString = "Score: " + std::to_string(0);
	m_ScoreText->SetText(scoreString.c_str());
}

void PlayState::UpdateFrequencyText()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << m_EnemyFrequency;
	std::string freqString = "Enemy Spawn Time: " + stream.str();

	m_FreqText->SetText(freqString.c_str());
}





void PlayState::EnemySpawner(float DeltaTime)
{
	m_EnemySpawnTimer -= DeltaTime; 

	if (m_EnemySpawnTimer <= 0.0f) {
		Enemy* E = AddGameObject<Enemy>();

		float PosX = GetRandomFloatRange(E->ScaleHalfSize(), Game::GetGame()->WindowWidthF() - E->ScaleHalfSize());
		E->SetPosition({ PosX, -E->ScaleHalfSize()});

		m_EnemySpawnTimer = m_EnemyFrequency;

		m_EnemyFrequency = std::max(0.1f, m_EnemyFrequency - 0.1f);
	}
}

float PlayState::GetRandomFloatRange(float min, float max) const
{
	std::uniform_real_distribution<float> RandNum(min, max);

	return RandNum(RandGenerator);
}
