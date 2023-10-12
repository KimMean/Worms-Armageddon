#include "Framework.h"

Effects::Effects(Texture* texture)
	: ImageRect(texture)
{
	//isActive = false;
	animation = new Animation(texture->GetFrame(), 2.0f);

	animation->SetEndEvent(bind(&Effects::EndEffectAnimation, this));
	animation->SetDefault();
	animation->Play();

	pos = { 300, 300 };
}

Effects::~Effects()
{
}

void Effects::Update()
{
	//if (!isActive) return;
	animation->Update();
}

void Effects::Render(HDC hdc)
{
	//if (!isActive) return;
	ImageRect::CamRender(hdc, animation->GetFrame());
}

void Effects::Active(Vector2 pos)
{
	this->pos = pos;
	isActive = true;
	
	animation->Play();
}

void Effects::EndEffectAnimation()
{
	isActive = false;
}
