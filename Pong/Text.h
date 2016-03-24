#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "spVector3.h"
#include <string>



class Text
{
public:

	struct TextSetup
	{
		std::string _Text;
		std::string _FontName;
		SDL_Color	_Colour;
		float		_FontSize;
		spVector3	_Position;
	};

	Text(TextSetup &_parameters);
	~Text();

	bool Initialize(TextSetup &_parameters);

	void Render(SDL_Renderer *_renderer);

	void SetText(const std::string _newText);
	char* GetText();

	void SetColour(const SDL_Color &_newColour);
	SDL_Color GetColour();

	void SetFont(const TTF_Font &_newFont);
	TTF_Font GetFont();

	void SetFontSize(const float &_newSize);
	float GetFontSize();

	void SetPosition(const spVector3 &_vNewPos);
	spVector3 m_position;

private:
	std::string		m_Text;
	std::string	m_FontName;// = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size
	TTF_Font*	m_Font;
	SDL_Color	m_Colour;// = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	float		m_FontSize;

	SDL_Surface* surfaceMessage;

	SDL_Texture* MessageTexture;

	SDL_Rect Text_rect;

	bool	m_TextChanged;
};

