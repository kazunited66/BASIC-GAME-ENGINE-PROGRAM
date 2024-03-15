#pragma once
#include "PhysicsObject.h"

class Charactor : public PhysicsObject {
public:
	Charactor();
	//move the charactor in the direction based on the accleration speed and max speed 
	void AddMovementInput(Vector2 Direction, float Scale = 1.0f);
protected: 
	virtual void OnPostUpdate(float DeltaTime) override;
protected:
	//main sprite that represent the charactor 
	Sprite* m_MainSprite;
	
	//speed the charactor will move to max speed 
	float m_AccelerationSpeed;
 
	Vector2 m_MoveDirection;
};
