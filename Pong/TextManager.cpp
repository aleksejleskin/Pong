#include "TextManager.h"
#include "HelperFunctions.h"
TextManager::TextManager()
{
	if (TTF_Init() == -1)
	{
	//	return false;
	}
}


TextManager::~TextManager()
{
	for each (Text *obj in m_TextObjects)
	{
		SAFE_DELETE(obj);
	}
	m_TextObjects.clear();
}

Text * TextManager::CreateNewText(Text::TextSetup &_textValues)
{
	Text *newText = new Text(_textValues);
	m_TextObjects.push_back(newText);
	return newText;
}

void TextManager::AddText(Text *_existingText)
{
	if (_existingText != nullptr)
	{
		m_TextObjects.push_back(_existingText);
	}
}

void TextManager::Render(SDL_Renderer *_renderer)
{
	for each (Text *textObj in m_TextObjects)
	{
		if (textObj != nullptr)
		{
			textObj->Render(_renderer);
		}
	}
}
