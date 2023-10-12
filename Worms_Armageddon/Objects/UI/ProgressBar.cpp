#include "Framework.h"

ProgressBar::ProgressBar(Texture* frontTexture, Texture* backTexture)
    : frontTexture(frontTexture), backTexture(backTexture)
{
    size = frontTexture->GetSize();
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Render(HDC hdc)
{
    if (backTexture)
        backTexture->Render(hdc, this);

    GdiTransparentBlt(
        hdc,
        (int)Left(), (int)Top(),
        (int)(size.x * value), (int)size.y,
        frontTexture->GetMemDC(),
        0, 0, (int)(size.x * value), (int)size.y,
        MAGENTA
    );
}
