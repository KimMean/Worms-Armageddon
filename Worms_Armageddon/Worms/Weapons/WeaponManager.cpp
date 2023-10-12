#include "Framework.h"
#include "WeaponManager.h"

WeaponManager::WeaponManager()
{
    hBrush = CreateSolidBrush(MAGENTA);
    hPen = CreatePen(PS_SOLID, 1, MAGENTA);
    CreateWeapons();
}

WeaponManager::~WeaponManager()
{
    DeleteObject(hBrush);
    DeleteObject(hPen);
}

void WeaponManager::Update()
{
    for (weaponIter = weapons.begin(); weaponIter != weapons.end(); weaponIter++)
    {
        weaponIter->second->Update();
    }
}

void WeaponManager::Render(HDC hdc)
{
    for (weaponIter = weapons.begin(); weaponIter != weapons.end(); weaponIter++)
    {
        weaponIter->second->Render(hdc);
    }
}

void WeaponManager::SetLandTexture(Texture* texture)
{
    landTexture = texture;
    for (weaponIter = weapons.begin(); weaponIter != weapons.end(); weaponIter++)
    {
        weaponIter->second->SetLandTexture(texture);
    }
}

Weapon* WeaponManager::GetWeapon(string weaponName)
{
    return weapons[weaponName];
}

void WeaponManager::ActiveWeapon(string weaponName, Vector2 pos, Vector2 direction, float power)
{
    weapons[weaponName]->pos = pos;
    weapons[weaponName]->SetActive(direction, power);
    //weapons[weaponName]->SetDirection(direction);
    //weapons[weaponName]->SetSpeedPower(power);
    //weapons[weaponName]->isActive = true;
}

void WeaponManager::MaskLandTexture(Vector2 pos, float bombRange)
{
    SelectObject(landTexture->GetMemDC(), hBrush);
    SelectObject(landTexture->GetMemDC(), hPen);
    Ellipse(landTexture->GetMemDC(), pos.x - bombRange, pos.y - bombRange, pos.x + bombRange, pos.y + bombRange);
}

void WeaponManager::CreateWeapons()
{
    unordered_map<string, int>::const_iterator iter;
    for (iter = BASE_WEAPON_LIST.begin(); iter != BASE_WEAPON_LIST.end(); iter++)
    {
        texture = Texture::Add(WEAPON_BASE_PATH +
            ToWString(iter->first) + L".bmp", CUT_SIZE);


        weapons[iter->first] = new ThrowingWeapon(texture);
        weapons[iter->first]->SetBrush(hBrush, hPen);
        //weapons[iter->first]->isActive = false;
        if (iter->first.find("BANANA") != string::npos || iter->first.find("CLUSTER") != string::npos)
        {
            ((ThrowingWeapon*)(weapons[iter->first]))->SetCluster();
        }
        //weapons[iter->first]->pos = { 300, 60 };
    }

    texture = nullptr;
}



