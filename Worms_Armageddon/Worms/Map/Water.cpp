#include "Framework.h"
#include "Water.h"
Water::Water()
{
	waterFull = new ImageRect(WATER_FULL_FILENAME);
	waterFull->pos = waterFull->Half();
	waterFull->pos.y = WIN_HEIGHT - waterFull->Half().y;

	waterWaves.resize(WATER_WAVE_COUNT);
	waterAnimation.resize(WATER_WAVE_COUNT);
	for (UINT i = 0; i < WATER_WAVE_COUNT; i++)
	{
		waterWaves[i] = new ImageRect(WATER_WAVE_FILENAME, 1, 8);
		waterWaves[i]->pos = waterWaves[i]->Half();
		waterWaves[i]->pos.y = WIN_HEIGHT - waterFull->Half().y - 150 + ( 30 * i);
		waterAnimation[i] = new Animation(waterWaves[i]->GetTexture()->GetFrame());
		waterAnimation[i]->SetPart(0, 7, true);
		waterAnimation[i]->SetSpeed(0.2f * (i + 1));
		waterAnimation[i]->Play();
		
	}


	//waterFull = Texture::Add(WATER_FULL_FILENAME);
	//waterWaves.resize(WATER_WAVE_COUNT);

	//for (Texture* texture : waterWaves)
	//{
	//	texture = Texture::Add(WATER_WAVE_FILENAME);
	//}
}

Water::~Water()
{
	delete waterFull;
	for (UINT i = 0; i < WATER_WAVE_COUNT; i++)
	{
		delete waterWaves[i];
		delete waterAnimation[i];
	}
}

void Water::Update()
{
	for (UINT i = 0; i < WATER_WAVE_COUNT; i++)
	{
		waterAnimation[i]->Update();
	}
}

void Water::Render(HDC hdc)
{
	waterFull->CamRender(hdc);

	for (UINT i = 0; i < WATER_WAVE_COUNT; i++)
	{
		waterWaves[i]->CamRender(hdc, waterAnimation[i]->GetFrame());
	}
}
