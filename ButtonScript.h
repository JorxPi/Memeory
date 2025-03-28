#pragma once

#include "Script.h"
#include "TextScript.h"
#include "GameManager.h"

class ButtonScript : public Script
{

	using Script::Script;

public:
	void tickScript(float deltaTime) override;
	void setTextScriptRef(TextScript* welcs);
	void setGameManagerRef(GameManager* gmr);
private:
	bool clicked = false;
	TextScript* welcRef; 
	GameManager* gameRef;
};