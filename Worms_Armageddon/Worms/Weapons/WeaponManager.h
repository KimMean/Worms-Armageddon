#pragma once

class WeaponManager : public Singleton<WeaponManager>
{


private :
	const wstring WEAPON_BASE_PATH = L"Resources/Textures/Weapon/";
	const Vector2 CUT_SIZE = { 60, 60 };
	const unordered_map<string, int> BASE_WEAPON_LIST =		// ��� �⺻������ ������ �ִ� ���� ����Ʈ�� ����
	{
		{"GRENADE", -1},
		{"BANANA", -1},
		{"CLUSTER", -1},
	};

private :
	friend class Singleton;
	WeaponManager();
	~WeaponManager();

	void CreateWeapons();	// ���� �̸�, Ÿ��, ����, ������ �� ���߿� ���Ϸ� �ٲ������ ���� �� ��

public :
	void Update();
	void Render(HDC hdc);


	void SetLandTexture(Texture* texture);
	unordered_map<string, int> GetBaseWeaponList() { return BASE_WEAPON_LIST; }
	Weapon* GetWeapon(string weaponName);	// Ű������ ���� ��ȯ

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