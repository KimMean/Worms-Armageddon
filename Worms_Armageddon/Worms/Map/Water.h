#pragma once

class Water
{
private :
	const wstring WATER_FULL_FILENAME = L"Resources/Textures/Map/Background/WaterFull.bmp";
	const wstring WATER_WAVE_FILENAME = L"Resources/Textures/Map/Background/WaterWave.bmp";
	const UINT WATER_WAVE_COUNT = 3;

public:
	Water();
	~Water();

	void Update();
	void Render(HDC hdc);

private:
	ImageRect* waterFull;
	vector<ImageRect*> waterWaves;
	vector<Animation*> waterAnimation;


};