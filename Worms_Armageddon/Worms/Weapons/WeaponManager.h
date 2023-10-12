#pragma once

class WeaponManager : public Singleton<WeaponManager>
{


private :
	const wstring WEAPON_BASE_PATH = L"Resources/Textures/Weapon/";
	const Vector2 CUT_SIZE = { 60, 60 };
	const unordered_map<string, int> BASE_WEAPON_LIST =		// 웜즈가 기본적으로 가지고 있는 무기 리스트와 개수
	{
		{"GRENADE", -1},
		{"BANANA", -1},
		{"CLUSTER", -1},
	};

private :
	friend class Singleton;
	WeaponManager();
	~WeaponManager();

	void CreateWeapons();	// 무기 이름, 타입, 범위, 데미지 등 나중에 파일로 바꿔놓으면 좋을 듯 함

public :
	void Update();
	void Render(HDC hdc);


	void SetLandTexture(Texture* texture);
	unordered_map<string, int> GetBaseWeaponList() { return BASE_WEAPON_LIST; }
	Weapon* GetWeapon(string weaponName);	// 키값으로 무기 반환

	void ActiveWeapon(string weaponName, Vector2 pos, Vector2 direction, float power);

	void MaskLandTexture(Vector2 pos, float bombRange);

private:
	unordered_map<string, Weapon*> weapons;
	unordered_map<string, Weapon*>::iterator weaponIter;

	Texture* texture;
	Texture* landTexture;

	HBRUSH hBrush;
	HPEN hPen;

};