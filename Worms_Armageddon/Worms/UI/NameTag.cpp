#include "Framework.h"

NameTag::NameTag()
	: ImageRect(L"Resources/Textures/UI/NameTag.bmp")
{
	//font = CreateFont(20, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
	//	50, 0, 0, 0, L"배달의민족 주아");
}

NameTag::~NameTag()
{
}

void NameTag::Render(HDC hdc)
{
	ImageRect::CamRender(hdc);

	//SelectObject(hdc, font);
	SetTextColor(hdc, WHITE);
	Vector2 namePos = pos - Camera::Get()->GetPos();
	TextOut(hdc, namePos.x - size.x * 0.3f, namePos.y - size.y * 0.4f, name.c_str(), name.size());
	//이름 출력
}

//void NameTag::SetFont(HFONT font, int fontSize, COLORREF fontColor)
//{
//}
