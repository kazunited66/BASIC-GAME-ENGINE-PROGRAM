#pragma once
#include "GameState.h"
class TextObject;

class PlayState : public GameState {
public: 
	PlayState() ;

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float DeltaTime) override; 

	
	void EnemySpawner(float DeltaTime);

	float GetRandomFloatRange(float min = 0.0f, float max = 1.0f) const;

	void UpdateScore();
	void UpdateFrequencyText();


protected:

	TextObject* m_ScoreText; 

	TextObject* m_FreqText;
		
		;

	float m_EnemyFrequency; 

	float m_EnemySpawnTimer;
};