#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;

class Texture {
public: 
	Texture(SDL_Renderer* Renderer);
	~Texture();

	//draw the texture to the rendere 
	bool ImportTexture(const char* PathToFile);

	//copy the texture
	void CopyTexture(Texture* CopyTexture);

	//draw the texture to the renderer 
	void Draw();

	//deallocate memory 
	void Cleanup();

	const char* GetPath() const { return m_Path; }

	//set the clip for the text ure 
	void SetClip(int x, int y, int w, int h);

public: 
	//position x & y to render to
	int m_PosX, m_PosY;

	// retation of the image 
	float m_Angle;

	float m_ScaleX, m_ScaleY; 
	//determine whether or not render the texture 
	bool m_IsVisible;

private: 
	//Texture that SDL understands
	SDL_Texture* m_TextureRef;

	//store the assigned renderer
	SDL_Renderer* m_RendererRef;

	//surface data for the original image 
	SDL_Surface* m_SurfaceData;

	//path to the original image 
	const char* m_Path;

	//store the clip for the texture 
	SDL_Rect* m_ClipRect;


};