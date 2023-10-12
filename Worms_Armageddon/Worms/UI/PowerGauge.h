#pragma once

class PowerGauge : public ImageRect
{
public:
	PowerGauge();
	~PowerGauge();

	void Render(HDC hdc);
	void SetValue(float value) { this->value = value; }

private:
	Texture* texture;

	float value;
};