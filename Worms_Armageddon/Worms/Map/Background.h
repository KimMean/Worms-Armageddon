#pragma once

class Background
{
private:
	const wstring BACKGROUND_FILE_NAME = L"Resources/Textures/Map/Background/Sky.bmp";

public:
	Background();
	~Background();
	void Update();
	void Render(HDC hdc);

public:
	ImageRect* skyBackground;
	// ÀÙ»ç±Í ¶³±¸±â , ¹Ù¶÷ Àû¿ë
};