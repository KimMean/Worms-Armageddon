#pragma once


class Worms : public ImageRect
{
private:
	unordered_map<AnimationList, wstring> AnimtionLists =
	{
		{ AnimationList::IDLE, L"IDLE" },
		{ AnimationList::MOVE, L"MOVE" },
		{ AnimationList::JUMP, L"JUMP" },
		{ AnimationList::BACK_JUMP, L"BACK_JUMP" },
		{ AnimationList::WINNER, L"WINNER" },
		{ AnimationList::DIE, L"DIE" },
		{ AnimationList::GRENADE_READY, L"GRENADE_READY" },
		{ AnimationList::GRENADE_AIM, L"GRENADE_AIM" },
		{ AnimationList::BANANA_READY, L"BANANA_READY" },
		{ AnimationList::BANANA_AIM, L"BANANA_AIM" },
		{ AnimationList::CLUSTER_READY, L"CLUSTER_READY" },
		{ AnimationList::CLUSTER_AIM, L"CLUSTER_AIM" },
		//{ AnimationList::GRENADE_POCKET, L"GRENADE_POCKET" }
	};
	enum WormsStatus
	{
		NONE,
		IDLE,
		MOVE,
		JUMP,
		BACK_JUMP,
		WINNER,
		DIE,
		READY,
		AIM,
		ATTACK,
	};
	vector<wstring> singleAnimations =
	{
		L"JUMP",
		L"BACK_JUMP",
		L"WINNER",
		L"DIE",
	};

// 애니메이션 상태
private :
	typedef AnimationList ANIMATION;
	typedef AnimationDirection DIRECTION;
	typedef AnimationSlope SLOPE;

	// 이미지 관련
private :
	const Vector2 CUT_SIZE = { 60, 60 };
	const Vector2 COLLIDER_SIZE = { 20, 20 };
	const wstring BASE_ANIMATION_PATH = L"Resources/Textures/Character/";

	// 캐릭터 속성관련
private :
	const float MOVE_SPEED = 100.0f;
	const float JUMP_SPEED = 500.0f;
	const float BACK_JUMP_SPEED = 100.0f;
	const float AIM_MOVE_SPEED = 100.0f;
	const float AIM_DISTANCE = 100.0f;
	const int MAX_HELTH_POINT = 100;

public:
	Worms();
	~Worms();

	void Update();
	void Render(HDC hdc);

	void SetLand(Texture* texture) { landTexture = texture; }
	bool GetControllable() { return isControllable; }
	void SetControllable(bool isControl);

	void Control();
	void Winner();

	void AddForce(Vector2 power);
	void Damage(float damage);
	void SetNameTag(wstring name);
	HelthPoint* GetHelthPoint() { return helthPoint; }


private :
	void SetWormsStatus(WormsStatus status);

	void SetWeapon();
	void SetAim();
	Vector2 GetAimDirection();

	void Attack();
	void Bomb();

	void UpdateTexture();
	void LoadTextures();
	bool SingleAnimationCheck(wstring animName);
	void SetSpecifiedOption();

	void EndWeaponReady();

	void SetSlope();

	AnimationList GetAnimationKey(wstring name);
	void SetCurrentAnimation(ANIMATION animName);
	void SetAnimationName(ANIMATION animName, DIRECTION dir, SLOPE slope);
	wstring ToWstring(ANIMATION name);
	wstring ToWstring(DIRECTION dir);
	void SetDirection(DIRECTION dir);
	wstring ToWstring(SLOPE slope);
	void SetDirection(SLOPE slope);

private :
	// 현재 텍스쳐
	wstring animationName;
	wstring preAnimationName;
	Texture* texture;

	// 애니메이션 상태
	AnimationList anim = ANIMATION::IDLE;
	AnimationDirection direct = DIRECTION::LEFT;
	AnimationSlope slope = SLOPE::FLAT;

	// 애니메이션 목록
	unordered_map<wstring, Animation*> animations;

private :
	Texture* landTexture;	// 지형 참조
	Rect* boxCollider;		// 박스 충돌체
	Vector2 velocity;		// 속도

private :
	WormsStatus status;
	unordered_map<string, int>	weaponList;
	string curWeapon;
	bool isTakeWeapon;
	bool changeWeapon;

	bool isControllable;
	bool isAnimationNameChange;

	bool isJump;

	Aim* aim;
	float angle = 0;

	wstring name;
	NameTag* nameTag;

	float hp;
	HelthPoint* helthPoint;

	float power;
	float powerSpeed = 100;
	PowerGauge* powerGauge;
	bool isAttack;

	float bombTime;
};