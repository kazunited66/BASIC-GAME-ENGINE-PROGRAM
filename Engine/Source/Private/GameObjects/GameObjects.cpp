#include"GameObjects/GameObjects.h"
#include"Debug.h"

void GameObject::Start()
{
	if (IsPendingDestroy()) {
		return;
	}
	EE_LOG("GameObject", "GameObject has spawned into the game");
	OnStart();
}

void GameObject::ProcessInput(Input* GameInput)
{
	if (IsPendingDestroy()) {
		return;
	}
	OnProcessInput(GameInput); 
} 

void GameObject::Update(float DeltaTime)
{
	if (IsPendingDestroy()) {
		return;
	}
	OnUpdate(DeltaTime);
}

void GameObject::PostUpdate(float DeltaTime)
{
	if (IsPendingDestroy()) {
		return;
	}
	OnPostUpdate(DeltaTime);
}

void GameObject::DestreyObject()
{
	if (!m_ShouldDestroy) {
		OnDestroy();
	}

	m_ShouldDestroy = true;
}

void GameObject::SetTransform(EETransform Transform)
{
	m_Transform = Transform;
}

void GameObject::SetPosition(Vector2 Position)
{
	EETransform NewTransform(
		Position,
		m_Transform.Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetRotation(float Rotation)
{
	EETransform NewTransform(
		m_Transform.Position,
		Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetScale(Vector2 Scale)
{
	EETransform NewTransform(
		m_Transform.Position,
		m_Transform.Rotation,
		Scale
	);

	SetTransform(NewTransform);
}

void GameObject::OnDestroy()
{
	EE_LOG("GameObject", "GameObject has been destroyed");
}

 
