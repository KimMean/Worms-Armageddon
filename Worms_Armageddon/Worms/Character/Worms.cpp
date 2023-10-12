#include "Framework.h"
#include "Worms.h"


Worms::Worms()
{
	SetWormsStatus(NONE);

	weaponList = WeaponManager::Get()->GetBaseWeaponList();	// ���� ����Ʈ ������
	
	nameTag = new NameTag();

	aim = new Aim();

	helthPoint = new HelthPoint();
	helthPoint->SetValue(1);
	hp = MAX_HELTH_POINT;

	powerGauge = new PowerGauge();

	boxCollider = new Rect(pos, COLLIDER_SIZE);

	LoadTextures();
	SetAnimationName(anim, direct, slope);
	animations[animationName]->SetDefault(true);
	animations[animationName]->Play();

	bombTime = 0;
	//pos = { 300, 480 };


}

Worms::~Worms()
{
	delete nameTag;
	delete aim;
	delete helthPoint;
	delete powerGauge;
	delete boxCollider;
}

void Worms::Update()
{
	//Control();

	velocity.y += GRAVITY * DELTA;
	pos.x += velocity.x * DELTA;
	pos.y += velocity.y * DELTA;
	boxCollider->pos = pos;

	Vector2 bottomPos = boxCollider->pos;
	float height = landTexture->GetPixelHeight(bottomPos, Half().y);
	if (boxCollider->Bottom() > height)
	{
		if (velocity.y > 0.0f)
		{
			isJump = false;
			velocity.y = 0.0f;
			velocity.x = 0.0f;
			pos.y = height - boxCollider->Half().y;
		}
	}
	
	// ������ ����ٴϰ�
	nameTag->pos = TopPos();
	powerGauge->pos = RightPos();

	SetSlope();		// ���� �˻��ؼ� ��� ��ȯ

	if(isAnimationNameChange)
	{
		SetAnimationName(anim, direct, slope);		// �ִϸ��̼� �̸� ������Ʈ
	}


	UpdateTexture();							// �ִϸ��̼� �̸����� �ؽ��� ������Ʈ
	animations[animationName]->Update();

	ImageRect::SetTexture(texture);

	if (status == DIE)
	{
		bombTime += DELTA;
		if (bombTime > 2.0f)
		{
			EffectsManager::Get()->Active(pos);
			CharacterManager::Get()->CollisionBomb(WeaponManager::Get()->GetWeapon("GRENADE"));
			WeaponManager::Get()->MaskLandTexture(pos, 100.0f);
			Audio::Get()->Play("Die");
			isActive = false;
		}
	}

}

void Worms::Render(HDC hdc)
{
	nameTag->Render(hdc);

	//if(isTakeWeapon && status == AIM)
	//	aim->Render(hdc);
	boxCollider->CamLineRender(hdc);
	if(isAttack)
		powerGauge->Render(hdc);
	if (status == AIM)
	{
		int aimFrame = ((angle + 90) / 5.625f);
		ImageRect::CamRender(hdc, {0 , aimFrame });
		aim->Render(hdc);
	}
	else
		ImageRect::CamRender(hdc, animations[animationName]->GetFrame());
}
void Worms::SetControllable(bool isControl)
{
	isControllable = isControl;
	isTakeWeapon = false;
	curWeapon = "NONE";
	if (!isControllable)
	{
		velocity = { 0, 0 };
		SetCurrentAnimation(ANIMATION::IDLE);
		SetWormsStatus(IDLE);
	}
}
void Worms::Control()
{
	// ���ۿ� ���� �ִϸ��̼� �̸� ��ȯ
	// �����̴� ���⿡ ���� ���� ��ȯ
	// ���ؽ� �ִϸ��̼� curFrame ����, �����ϴ� ������ curFrame�ٲ��ֱ�
	if (!isControllable) return;
	if (isJump) return;

	// �ٴ� �˻��ؼ� �浹 ó��
	bool isMove = false;
	
	if (KEY_PRESS(VK_RIGHT))
	{
		//SetCurrentAnimation(ANIMATION::MOVE);
		SetDirection(DIRECTION::RIGHT);
		velocity.x = MOVE_SPEED;
		isMove = true;
	}
	else if (KEY_PRESS(VK_LEFT))
	{
		//SetCurrentAnimation(ANIMATION::MOVE);
		SetDirection(DIRECTION::LEFT);
		velocity.x = -MOVE_SPEED;
		isMove = true;
	}



	if (KEY_DOWN('X'))
	{
		if (!isJump)
		{
			//SetCurrentAnimation(ANIMATION::JUMP);
			//velocity.y = JUMP_SPEED;
			isJump = true;
			velocity.y = -JUMP_SPEED;
			SetCurrentAnimation(ANIMATION::JUMP);
			SetWormsStatus(JUMP);
		}
	}

	// ������
	if (KEY_DOWN('Z'))
	{
		if (!isJump)
		{
			isJump = true;
			if (direct == AnimationDirection::LEFT)
				velocity.x = BACK_JUMP_SPEED;
			else
				velocity.x = -BACK_JUMP_SPEED;
			velocity.y = -JUMP_SPEED;
			SetCurrentAnimation(ANIMATION::BACK_JUMP);
			SetWormsStatus(JUMP);
		}
	}

	if (!isJump)
	{
		if (isMove)
		{
			SetCurrentAnimation(ANIMATION::MOVE);
			SetWormsStatus(MOVE);
		}
		else
		{
			if(!isTakeWeapon)
			{
				SetCurrentAnimation(ANIMATION::IDLE);
				SetWormsStatus(IDLE);
			}
			else
			{
				SetWormsStatus(READY);
				//if (status == READY)
				//	SetWormsStatus(AIM);
			}
			velocity.x = 0;
		}
	}
	
	SetWeapon();
	if (isTakeWeapon && status == AIM)
	{

		SetAim();
		Attack();
	}
	
}
void Worms::Winner()
{
	SetCurrentAnimation(ANIMATION::WINNER);
	SetWormsStatus(WINNER);
}
void Worms::AddForce(Vector2 power)
{
	velocity = power;
}
void Worms::Damage(float damage)
{
	hp -= damage;
	float value = hp / MAX_HELTH_POINT;
	helthPoint->SetValue(value);

	if (hp <= 0)
	{
		SetCurrentAnimation(ANIMATION::DIE);
		SetWormsStatus(DIE);
	}
}
void Worms::SetNameTag(wstring name)
{
	this->name = name;
	nameTag->SetName(name);
	helthPoint->SetName(name);
}
void Worms::SetWormsStatus(WormsStatus status)
{
	if (this->status == status) return;
	if (this->status == DIE) return;
	if (this->status == WINNER) return;

	if (this->status == AIM && status == READY && !changeWeapon) return;


	if (status == READY)
	{
		AnimationList anim = GetAnimationKey(ToWString(curWeapon) + L"_READY");
		SetCurrentAnimation(anim);
		changeWeapon = false;
	}
	if (status == AIM)
	{
		AnimationList anim = GetAnimationKey(ToWString(curWeapon) + L"_AIM");
		SetCurrentAnimation(anim);
	}

	this->status = status;
	//if (this->status == POCKET)
	//{
	//	AnimationList anim = GetAnimationKey(ToWString(curWeapon) + L"_POCKET");
	//	SetCurrentAnimation(anim);
	//}
}
void Worms::SetWeapon()
{
	if (KEY_DOWN(VK_NUMPAD1))
	{
		curWeapon = "GRENADE";
		isTakeWeapon = true;
		changeWeapon = true;
	}
	else if (KEY_DOWN(VK_NUMPAD2))
	{
		curWeapon = "BANANA";
		isTakeWeapon = true;
		changeWeapon = true;
	}
	else if (KEY_DOWN(VK_NUMPAD3))
	{
		curWeapon = "CLUSTER";
		isTakeWeapon = true;
		changeWeapon = true;
	}
	if (changeWeapon)
	{
		//AnimationList anim = GetAnimationKey(ToWString(curWeapon) + L"_READY");
		//SetCurrentAnimation(anim);
		SetWormsStatus(READY);
	}
}
void Worms::SetAim()
{
	//if (status != AIM) return;

	if (KEY_PRESS(VK_UP))
	{
		angle += AIM_MOVE_SPEED * DELTA;
		if (angle > 90) angle = 90;
	}
	else if (KEY_PRESS(VK_DOWN))
	{
		angle -= AIM_MOVE_SPEED * DELTA;
		if (angle < -90) angle = -90;
	}

	Vector2 aimDirection = GetAimDirection();
	aim->pos = aimDirection + pos;
	int aimFrame = 32-((angle + 90) / 5.625f);
	aim->SetCurFrame(aimFrame);
}
Vector2 Worms::GetAimDirection()
{
	Vector2 aimDirection;
	float radian = angle * PI / 180;

	if (direct == AnimationDirection::LEFT)
		aimDirection.x = cos(radian) * -AIM_DISTANCE;
	else if (direct == AnimationDirection::RIGHT)
		aimDirection.x = cos(radian) * AIM_DISTANCE;
	aimDirection.y = -sin(radian) * AIM_DISTANCE;

	return aimDirection;
}
// ���� !
void Worms::Attack()
{
	// �������� �� ��Ҵٰ� �߻�
	if (KEY_DOWN(VK_SPACE))
	{
		// AIM �����϶� �߻�
		// ������ ���� Vector2 ���� �� Normalize
		power = 0;
		powerGauge->SetValue(0);
		isAttack = true;
	}
	else if (KEY_PRESS(VK_SPACE))
	{
		power += powerSpeed * DELTA;
		if (power > 100)
		{
			power = 100;
		}
		powerGauge->SetValue(power / 100);
	}
	else if (KEY_UP(VK_SPACE))
	{
		Bomb();
	}
}
// �߻� !
void Worms::Bomb()
{
	isAttack = false;
	isTakeWeapon = false;
	// ���� ����ִ� ��� ��

	Vector2 aimDirection = GetAimDirection().GetNormalized();
	WeaponManager::Get()->ActiveWeapon(curWeapon, pos, aimDirection, -power * 20);

	Camera::Get()->SetTarget(WeaponManager::Get()->GetWeapon(curWeapon));
	
}

void Worms::UpdateTexture()
{
	// ���� �ؽ�ó�� �ٲ� �ؽ�ó�� �ٸ� �� ����

	if (preAnimationName == animationName) return;

	preAnimationName = animationName;
	//wstring tempStr = BASE_ANIMATION_PATH + ToWstring(anim) + L"/" + animationName + L".bmp";
	texture = Texture::GetTexture(BASE_ANIMATION_PATH +
		ToWstring(anim) + L"/" + animationName + L".bmp");

	if (!animations[animationName]->IsPlay())
	{
		animations[animationName]->Play();
	}
	// ���ε� üũ�ؼ� ������ �־���
}
void Worms::LoadTextures()
{
	int cnt = 0;
	bool endEnum = false;

	// �⺻ ���
	for (int i = (int)ANIMATION::IDLE; i <= (int)ANIMATION::CLUSTER_AIM; i++)
	{
		for (int j = (int)DIRECTION::LEFT; j <= (int)DIRECTION::RIGHT; j++)
		{
			for (int k = (int)SLOPE::FLAT; k <= (int)SLOPE::DOWN; k++)
			{
				SetAnimationName(ANIMATION(i), DIRECTION(j), SLOPE(k));
				
				texture = Texture::Add(BASE_ANIMATION_PATH +
					ToWstring((ANIMATION)i) + L"/" + animationName + L".bmp",
					CUT_SIZE);
				animations[animationName] = new Animation(texture->GetFrame());
				animations[animationName]->SetDefault();

				wstring str = ToWstring(ANIMATION(i));
				if (str.find(L"READY") != wstring::npos)
				{
					//animations[animationName]->SetEndEvent()
					animations[animationName]->SetEndEvent(bind(&Worms::EndWeaponReady, this));
				}
				if (SingleAnimationCheck(ToWstring(ANIMATION(i))))
				{
					break;
				}
			}
		}
	}
	SetSpecifiedOption();
}

bool Worms::SingleAnimationCheck(wstring animName)
{
	for (wstring str : singleAnimations)
	{
		if (animName == str)
			return true;
	}
	return false;
}

void Worms::SetSpecifiedOption()
{
	animations[L"BACK_JUMP_LEFT_FLAT"]->SetSpeed(3.0f);
	animations[L"BACK_JUMP_RIGHT_FLAT"]->SetSpeed(3.0f);
	animations[L"WINNER_LEFT_FLAT"]->SetDefault(true);
}

void Worms::EndWeaponReady()
{
	if (isTakeWeapon)
		SetWormsStatus(AIM);
}


// �������
void Worms::SetSlope()
{
	Vector2 leftBottomPos = boxCollider->pos;
	Vector2 rightBottomPos = boxCollider->pos;
	leftBottomPos.x -= boxCollider->Half().x;
	rightBottomPos.x += boxCollider->Half().x;
	int leftFloorHeight = landTexture->GetPixelHeight(leftBottomPos, Half().y);
	int rightFloorHeight = landTexture->GetPixelHeight(rightBottomPos, Half().y);

	if (leftFloorHeight == rightFloorHeight)
		SetDirection(SLOPE::FLAT);
	else if(leftFloorHeight < rightFloorHeight)
		SetDirection(SLOPE::UP);
	else if (leftFloorHeight > rightFloorHeight)
		SetDirection(SLOPE::DOWN);
}

AnimationList Worms::GetAnimationKey(wstring name)
{
	unordered_map<AnimationList, wstring>::iterator iter;
	for (iter = AnimtionLists.begin(); iter != AnimtionLists.end(); iter++)
	{
		if (iter->second.compare(name) == 0)
		{
			return iter->first;
		}
	}
	return ANIMATION();
}

// �ִϸ��̼� ����
void Worms::SetCurrentAnimation(ANIMATION animName)
{
	if (anim == animName) return;
	anim = animName; 

	isAnimationNameChange = true;
}

void Worms::SetAnimationName(ANIMATION animName, DIRECTION dir, SLOPE slope)
{
	if (SingleAnimationCheck(ToWstring(ANIMATION(animName))))
		slope = SLOPE::FLAT;

	animationName = 
		ToWstring(ANIMATION(animName)) + L"_" +
		ToWstring(DIRECTION(dir)) + L"_" +
		ToWstring(SLOPE(slope));

	isAnimationNameChange = false;
}

wstring Worms::ToWstring(ANIMATION name)
{
	return AnimtionLists[name];
	//return AnimationListToString(name);
}

wstring Worms::ToWstring(DIRECTION dir)
{
	return AnimationDirectionToString(dir);
}

void Worms::SetDirection(DIRECTION dir)
{
	if (direct == dir) return;

	direct = dir;
	isAnimationNameChange = true;
}

wstring Worms::ToWstring(SLOPE slope)
{
	return AnimationSlopeToString(slope);
}

void Worms::SetDirection(SLOPE slope)
{
	if (this->slope == slope) return;

	this->slope = slope;
	isAnimationNameChange = true;
}

