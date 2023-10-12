#include "Framework.h"
#include "Aim.h"

Aim::Aim()
{
	texture = Texture::Add(L"Resources/Textures/UI/Aim.bmp", CUT_SIZE);
	animation = new Animation(texture->GetFrame());
	animation->SetDefault();
	ImageRect::SetTexture(texture);
	curFrameY = 0;
}

Aim::~Aim()
{
}

void Aim::Render(HDC hdc)
{
	if (isActive)
	{
		//ImageRect::CamRender(hdc, animation->GetFrame());
		ImageRect::CamRender(hdc, {0, curFrameY});
	}
}

void Aim::SetCurFrame(int frameY)
{
	curFrameY = frameY;
}
