#pragma once
#include "GameObjects/GameObjects.h"
#include"Graphics/Animation.h"

class SpriteObject : public GameObject {
public: 

	SpriteObject() = default;
	virtual ~SpriteObject() = default;

	virtual   void Cleanup() override;


protected:
	//add a animation/sprite to the sprite stack 
	Animation* AddSprite(const char* PathToFile, AnimationParams* Params = nullptr);

	virtual void OnPostUpdate(float DeletaTIme) override;

	



private:

	//store all sprites related to this object 
	TArray<Animation*>m_SpriteStack;



};
