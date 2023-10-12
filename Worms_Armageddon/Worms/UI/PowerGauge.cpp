#include "Framework.h"

PowerGauge::PowerGauge()
	: ImageRect(L"Resources/Textures/UI/PowerGauge.bmp")
{
	texture = Texture::Add(L"Resources/Textures/UI/Power.bmp");
}

PowerGauge::~PowerGauge()
{
}

void PowerGauge::Render(HDC hdc)
{
	ImageRect::CamRender(hdc);

    //pos = pos + Camera::Get()->GetPos();

    int imageSizeX = texture->GetImageSize().x;
    int imageSizeY = texture->GetImageSize().y;

    GdiTransparentBlt(
        hdc,
        (int)Left() - Camera::Get()->GetPos().x + 3, (int)Top() - Camera::Get()->GetPos().y + (imageSizeY * (1 - value)) + 2,
        (int)imageSizeX, (int)(imageSizeY * value),
        texture->GetMemDC(),
        0, (int)(imageSizeY * (1 - value)),
        (int)imageSizeX, (int)(imageSizeY * value),
        MAGENTA
    );

}
