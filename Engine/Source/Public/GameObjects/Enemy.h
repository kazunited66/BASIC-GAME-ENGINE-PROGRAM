#pragma once
#include"Character.h"

class Enemy : public Charactor {
public: 
	Enemy();
protected: 
	virtual void OnStart() override; 
	virtual void OnUpdate(float DeltTime) override;
protected:
	

};