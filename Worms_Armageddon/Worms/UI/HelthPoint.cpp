#include "Framework.h"
#include "HelthPoint.h"

HelthPoint::HelthPoint()
	: ImageRect(L"Resources/Textures/UI/HPBar.bmp")
{
    hpTexture = Texture::Add(L"Resources/Textures/UI/HP.bmp");
}

HelthPoint::~HelthPoint()
{
}

void HelthPoint::Render(HDC hdc)
{
    pos += Camera::Get()->GetPos();
    ImageRect::CamRender(hdc);
    int imageSizeX = hpTexture->GetImageSize().x;
    int imageSizeY = hpTexture->GetImageSize().y;

    GdiTransparentBlt(
        hdc,
        (int)Left() + 90 - Camera::Get()->GetPos().x, (int)Top() - Camera::Get()->GetPos().y + 5,
        (int)(imageSizeX * value), imageSizeY,
        hpTexture->GetMemDC(),
        0, 0,
        (int)(imageSizeX * value), imageSizeY,
        MAGENTA
    );

    Vector2 namePos = pos - Camera::Get()->GetPos();
    TextOut(hdc, namePos.x - size.x * 0.4f, namePos.y - size.y * 0.4f, name.c_str(), name.size());


}
