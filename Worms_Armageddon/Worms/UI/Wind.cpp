#include "Framework.h"
#include "Wind.h"

Wind::Wind()
    : ImageRect(L"Resources/Textures/UI/windBackground.bmp")
{
    pos = { 50 + Half().x, SCREEN_HEIGHT - 50};

    SetWindForce(0);
    
	//backgroundTexture = Texture::Add(L"Resources/Textures/UI/windBackground.bmp");
	windLeftTexture = Texture::Add(L"Resources/Textures/UI/windLeft.bmp");
	windRightTexture = Texture::Add(L"Resources/Textures/UI/windRight.bmp");

}

Wind::~Wind()
{
}

void Wind::Render(HDC hdc)
{
    //pos = { 50 + Half().x, 1000 };
    ImageRect::Render(hdc);

    //ImageRect::Render(hdc);

    //if (KEY_PRESS(VK_NUMPAD4))
    //{
    //    SetWindForce(windForce - 1);
    //}
    //
    //if (KEY_PRESS(VK_NUMPAD6))
    //{
    //    SetWindForce(windForce + 1);
    //}
    
    int imageSizeX = windLeftTexture->GetImageSize().x;
    int imageSizeY = windLeftTexture->GetImageSize().y;


    if (windForce < 0)
    {
        GdiTransparentBlt(
            hdc,
            (int)Left() + (imageSizeX * (1 - value)) + 15, (int)Top() + 2,
            (int)(imageSizeX * value), imageSizeY,
            windLeftTexture->GetMemDC(),
            (int)(imageSizeX * (1 - value)), 0,
            (int)(imageSizeX * value), imageSizeY,
            MAGENTA
        );
    }
    else
    {
        // Wind Right
        GdiTransparentBlt(
            hdc,
            (int)Left() + Half().x + 4, (int)Top() + 2,
            (int)(imageSizeX * value), imageSizeY,
            windRightTexture->GetMemDC(),
            0, 0,
            (int)(imageSizeX * value), imageSizeY,
            MAGENTA
        );
    }

}

void Wind::SetWindForce(float force)
{
    windForce = force;

    value = abs(windForce / MAX_WIND_FORCE);
}
