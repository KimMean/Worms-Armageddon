#include "Framework.h"
#include "Background.h"

Background::Background()
{
	skyBackground = new ImageRect(BACKGROUND_FILE_NAME);
	skyBackground->pos = skyBackground->Half();
}

Background::~Background()
{
	delete skyBackground;
}

void Background::Update()
{
}

void Background::Render(HDC hdc)
{
	skyBackground->CamRender(hdc);
}
