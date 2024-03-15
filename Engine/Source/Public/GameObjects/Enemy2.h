#pragma once
#include"Character.h"
class Enemy2 : public Charactor {
public:
	Enemy2();
protected:
	virtual void OnStart() override;
	virtual void OnUpdate(float DeltTime) override;
protected:

	
};