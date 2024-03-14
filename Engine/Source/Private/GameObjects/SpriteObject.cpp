#include "GameObjects/SpriteObject.h"

void SpriteObject::Cleanup()
{
	for (auto Sprite : m_SpriteStack) {
		delete Sprite;
		Sprite = nullptr; 
	}
}

Animation* SpriteObject::AddSprite(const char* PathToFile, AnimationParams* Params)
{

	Animation* NewAnim = new Animation();

	if (!NewAnim->CreateAnimation(PathToFile, Params)) {
		return nullptr;
	}

	//set the aprites position to match the objects
	NewAnim->SetPosition((int)GetTransform().Position.x, (int)GetTransform().Position.y);
	//set the sprite rotation to matc hthe object 
	NewAnim->SetRotation(GetTransform().Rotation);
	//set the sprite scale to match the object 
	NewAnim->SetScale(GetTransform().Scale.x, GetTransform().Scale.y);

	m_SpriteStack.push_back(NewAnim);

	return NewAnim;
}

void SpriteObject::OnPostUpdate(float DeletaTIme)
{
	for (auto Sprite : m_SpriteStack) {
		if (Sprite == nullptr) {
			continue;
		}

	    
		//set the aprites position to match the objects
		Sprite->SetPosition((int)GetTransform().Position.x, (int)GetTransform().Position.y);
		//set the sprite rotation to matc hthe object 
		Sprite->SetRotation(GetTransform().Rotation);
		//set the sprite scale to match the object 
		Sprite->SetScale(GetTransform().Scale.x, GetTransform().Scale.y);
	}
}
