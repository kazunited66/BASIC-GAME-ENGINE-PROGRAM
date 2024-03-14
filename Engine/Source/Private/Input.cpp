#include"Input.h"
#include"SDL2/SDL.h"
#include"Game.h"
#include"Math/Vector2.h"

void Input::ProcessInput()
{
	//Data type that reads the SDL input events foe the windows
	SDL_Event InputEvent;

	//run through each input uin that frame
	while (SDL_PollEvent(&InputEvent)) {

		if (InputEvent.type == SDL_MOUSEBUTTONDOWN) {
			DetectMouseButtonState(InputEvent.button.button, true);

		}

		if (InputEvent.type == SDL_MOUSEBUTTONUP) {
			DetectMouseButtonState(InputEvent.button.button, false);
		}
		//if the cross button is pressed on the window, close the app
		if (InputEvent.type == SDL_QUIT) {
			Game::GetGame()->QuitApp();
		}
	}
}

bool Input::IsKeyDown(EE_Key Key) {
	const Uint8* KeyStates = SDL_GetKeyboardState(NULL);

	if (KeyStates == nullptr) {
		return false;
	}

		return KeyStates[Key]; 
}

bool Input::IsMouseButtonDown(EE_MouseButton Button)
{
	if (Button >= EE_NUM_BUTTONS) {
		return false; 
	}

	return m_MouseState[Button];
}

void Input::DetectMouseButtonState(unsigned int Event, bool Value)
{
	switch (Event) {
	case SDL_BUTTON_LEFT :
		m_MouseState[EE_MOUSE_LEFT] = Value; 
		break;
	case SDL_BUTTON_MIDDLE :
		m_MouseState[EE_MOUSE_MIDDLE] = Value;
		break;
	case SDL_BUTTON_RIGHT :
		m_MouseState[EE_MOUSE_RIGHT] = Value;
		break;

	}
}

Vector2 Input::GetMousePos() const
{
	int x(0);
	int y(0);

	SDL_GetMouseState(&x, &y);

	return Vector2((float)x,(float)y);
}
