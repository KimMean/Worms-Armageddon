#pragma once

class HelthPoint : public ImageRect
{
public:
	HelthPoint();
	~HelthPoint();

	void Render(HDC hdc);

	void SetValue(float value) { this->value = value; }
	void SetName(wstring name) { this->name = name; }

private:
	Texture* hpTexture;
	float value;

	wstring name;

};