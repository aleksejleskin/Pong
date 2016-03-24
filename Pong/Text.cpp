#include "Text.h"


Text::Text(TextSetup &_parameter)
{
	Initialize(_parameter);
}


Text::~Text()
{

}

bool Text::Initialize(TextSetup &_parameters)
{
	m_FontName = _parameters._FontName;
	m_Colour = _parameters._Colour;
	

	//m_Font = TTF_OpenFont((char*)_parameters._FontName.c_str(), _parameters._FontSize);
	m_Font = TTF_OpenFont("lazy.ttf", _parameters._FontSize);
	if (m_Font == nullptr)
	{
		return false;
	}

	SetFontSize(_parameters._FontSize);
	SetPosition(_parameters._Position);
	SetText(_parameters._Text);
	return true;
}

void Text::Render(SDL_Renderer * _renderer)
{
	SDL_SetRenderDrawColor(_renderer, 0, 207, 0, 0);

	//create new texture if text changed, and surface exists;
	if (m_TextChanged && surfaceMessage != nullptr)
	{
		MessageTexture = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
		m_TextChanged = false;
	}

	int h, w;
	SDL_QueryTexture(MessageTexture, NULL, NULL, &w, &h);

	Text_rect.h = h;
	Text_rect.w = w;
	//draw new text
	if (MessageTexture != nullptr)
	{
		SDL_RenderCopy(_renderer, MessageTexture, NULL, &Text_rect);
	}

}

void Text::SetColour(const SDL_Color &_newColour)
{
	m_Colour = _newColour;
}

void Text::SetText(const std::string _newText)
{
	m_TextChanged = true;
	//destroy previous message , free up memory.
	if (surfaceMessage != nullptr)
	{
		SDL_FreeSurface(surfaceMessage);
	}
	m_Text = _newText;

	surfaceMessage = TTF_RenderText_Solid(m_Font, (char*)_newText.c_str(), m_Colour);
}

void Text::SetFontSize(const float &_newSize)
{
	m_FontSize = _newSize;

	Text_rect.w = _newSize;
	Text_rect.h = _newSize;
}

float Text::GetFontSize()
{
	return m_FontSize;
}

void Text::SetPosition(const spVector3 &_vNewPos)
{
	m_position = _vNewPos;

	Text_rect.x = _vNewPos.x;
	Text_rect.y = _vNewPos.y;
}
