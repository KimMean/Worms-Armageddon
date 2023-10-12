#pragma once

class Effects : public ImageRect
{
public:
	Effects(Texture* texture);
	~Effects();

	virtual void Update();
	virtual void Render(HDC hdc);

	void Active(Vector2 pos);
private :
	void EndEffectAnimation();

private:
	Animation* animation;
};