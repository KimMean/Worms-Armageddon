#pragma once

class Button : public ImageRect
{
private:
    enum State
    {
        NORMAL, OVER, DOWN
    };

public:
    Button(wstring file);
    Button(Texture* texture);
    ~Button();

    void Update();
    void Render(HDC hdc);

    void SetFont(HFONT font, int fontSize = 20, COLORREF fontColor = BLACK);

    void SetEvent(Event event) { this->event = event; }

    void SetOverTexture(Texture* texture) { overTexture = texture; }
    void SetDownTexture(Texture* texture) { downTexture = texture; }

    void SetText(string text) { this->text = text; }

protected:
    State state = NORMAL;

    bool isClick = false;

    Event event = nullptr;

    Texture* normalTexture = nullptr;
    Texture* overTexture = nullptr;
    Texture* downTexture = nullptr;

    string text;

    HFONT font = nullptr, oldFont = nullptr;
    int fontSize = 20;
    COLORREF fontColor = BLACK;
};