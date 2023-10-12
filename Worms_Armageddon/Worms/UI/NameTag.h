#pragma once

class NameTag : public ImageRect
{
public:
	NameTag();
	~NameTag();

	void Render(HDC hdc);
	void SetName(wstring name) { this->name = name; }

	//void SetFont(HFONT font, int fontSize, COLORREF fontColor);

private:
	//HFONT font = nullptr;
	//int fontSize = 20;
	//COLORREF fontColor = WHITE;

	wstring name = L"Unknown";
};