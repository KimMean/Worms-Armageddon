#include "Framework.h"
#include "Weapon.h"

Weapon::Weapon(Texture* texture)
    : ImageRect(texture)
{
    animation = new Animation(texture->GetFrame());
    animation->SetDefault(true);
    animation->SetSpeed(10.0f);
    animation->Play();
    isActive = false;
}

Weapon::~Weapon()
{
    delete boxCollider;
}

void Weapon::Update()
{
    if (!isActive) return; 

    animation->Update();

    if (!velocity.IsZero())
    {
        velocity.y += GRAVITY * DELTA;
    }

    curTime += DELTA;   // 시간 계속 더해주고
    velocity.x += Wind::Get()->GetWindForce();
    pos += velocity * DELTA;

    boxCollider->pos = pos;

}

void Weapon::Render(HDC hdc)
{
    //animation->Render();
    boxCollider->CamLineRender(hdc);
    ImageRect::CamRender(hdc, animation->GetFrame());
}

void Weapon::IsRectCollision()
{
}

void Weapon::IsPixelCollision()
{

}

void Weapon::SetActive(Vector2 direction, float power)
{
    SetDirection(direction);
    SetSpeedPower(power);
    velocity = direction * -speedPower;
    

    isActive = true;
}
