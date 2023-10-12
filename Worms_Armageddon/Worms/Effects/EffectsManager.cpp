#include "Framework.h"

EffectsManager::EffectsManager()
{
	CreateEffects();
	Audio::Get()->Add("EffectSound", "Resources/Sounds/SmallExp.mp3");
}

EffectsManager::~EffectsManager()
{
}

void EffectsManager::Update()
{
	for (int i = 0; i < 20; i++)
	{
		if (effects[i]->isActive)
		{
			effects[i]->Update();
		}
	}
}

void EffectsManager::Render(HDC hdc)
{
	for (int i = 0; i < 20; i++)
	{
		if (effects[i]->isActive)
		{
			effects[i]->Render(hdc);
		}
	}
}

void EffectsManager::CreateEffects()
{
	effects.resize(20);

	for (int i = 0; i < 20; i++)
	{
		texture = Texture::Add(L"Resources/Textures/Effect/BombEffect_200.bmp", 1, 9);
		effects[i] = new Effects(texture);
	}
}

void EffectsManager::Active(Vector2 pos)
{
	for (int i = 0; i < 20; i++)
	{
		if (!effects[i]->isActive)
		{
			effects[i]->Active(pos);
			Audio::Get()->Play("EffectSound", 0.05f);
			return;
		}
	}
}
