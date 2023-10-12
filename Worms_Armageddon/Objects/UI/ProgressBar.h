#pragma once

class ProgressBar : public Rect
{
public:
    ProgressBar(Texture* frontTexture, Texture* backTexture = nullptr);
    ~ProgressBar();

    void Render(HDC hdc);

    void SetValue(const float& value) { this->value = value; }

private:
    Texture* frontTexture;
    Texture* backTexture;

    float value;
};