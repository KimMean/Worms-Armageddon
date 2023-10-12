#include "Framework.h"

ThrowingWeapon::ThrowingWeapon(Texture* texture)
	: Weapon(texture)
{
	boxCollider = new Rect(pos, { 10, 10 });
	bombTime = 3.0f;
}

ThrowingWeapon::~ThrowingWeapon()
{
	if (isClusterType)
	{
		for (int i = 0; i < CLUSTER_NUM; i++)
		{
			delete cluster[i];
		}
	}
}

void ThrowingWeapon::Update()
{
	//if (!isActive) return;
	//boxCollider->pos = pos;
	if (isClusterType)
	{
		for (int i = 0; i < CLUSTER_NUM; i++)
		{
			cluster[i]->Update();
		}
	}
	if (!isActive) return;

	Weapon::Update();
	CheckLandCollision();
	BombCheck();
}

void ThrowingWeapon::Render(HDC hdc)
{
	if (isClusterType)
	{
		for (int i = 0; i < CLUSTER_NUM; i++)
		{
			cluster[i]->Render(hdc);
		}
	}
	if (!isActive) return;

	Weapon::Render(hdc);

}

void ThrowingWeapon::SetCluster()
{
	isClusterType = true;
	cluster.resize(CLUSTER_NUM);
	for (int i = 0; i < CLUSTER_NUM; i++)
	{
		cluster[i] = new ThrowingWeapon(texture);
	}
	
}

void ThrowingWeapon::BombCheck()
{
	if (KEY_DOWN(VK_SPACE))
		curTime = bombTime;
	if (curTime >= bombTime)
	{
		CharacterManager::Get()->CollisionBomb(this);
		EffectsManager::Get()->Active(pos);
		WeaponManager::Get()->MaskLandTexture(pos, bombRange);

		if (isClusterType)
		{
			for (int i = 0; i < CLUSTER_NUM; i++)
			{
				cluster[i]->SetLandTexture(landTexture);
				cluster[i]->pos = pos;
				cluster[i]->SetBombTime(1.0f);
				float velocityX = Random(-1.0f, 1.0f);
				cluster[i]->SetActive({ velocityX , 1 }, 300.0f);
			}
		}

		curTime = 0;
		isActive = false;
	}
}

//void ThrowingWeapon::MaskLandTexture()
//{
//	SelectObject(landTexture->GetMemDC(), hBrush);
//	SelectObject(landTexture->GetMemDC(), hPen);
//	Ellipse(landTexture->GetMemDC(), pos.x - bombRange, pos.y - bombRange, pos.x + bombRange, pos.y + bombRange);
//}

void ThrowingWeapon::CheckLandCollision()
{
	bool isCollision = false;
	if (CollisionLandTexture(boxCollider->LeftPos()))
	{
		isCollision = true;

		pos.x += boxCollider->Half().x;
		velocity.x *= -1;
	}
	if (CollisionLandTexture(boxCollider->RightPos()))
	{
		isCollision = true;

		pos.x -= boxCollider->Half().x;
		velocity.x *= -1;
	}
	if (CollisionLandTexture(boxCollider->TopPos()))
	{
		isCollision = true;

		pos.y += boxCollider->Half().y;
		velocity.y *= -1;
	}
	if (CollisionLandTexture(boxCollider->BottomPos()))
	{
		isCollision = true;

		pos.y -= boxCollider->Half().y;
		velocity.y *= -1;
	}
	if (isCollision)
	{
		velocity *= 0.5f;
	}
	if (velocity.Length() < 10.0f)
		velocity = { 0, 0 };

}

bool ThrowingWeapon::CollisionLandTexture(Vector2 pos)
{
	if (landTexture->IsCollisionPixel(pos)) return true;

	return false;
}
