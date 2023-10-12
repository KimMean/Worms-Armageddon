#pragma once

class Aim : public ImageRect
{
private :
	const Vector2 CUT_SIZE = { 60, 60 };

public:
	Aim();
	~Aim();

	void Render(HDC hdc);
	void SetCurFrame(int frameY);

private:
	Texture* texture;
	Animation* animation;

	int curFrameY;
};