#include "Framework.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
	srand(time(0));
	//hFont = CreateFont(20, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
	//	100, 0, 0, 0, L"배달의민족 주아");
	//SetFont(hFont, 40, RED);

	playerNum = MAX_PLAYER_NUM;
	
	terrain = new Terrain();
	water = new Water();
	background = new Background();
	//CreateWorms();

	//worm = new Worms();
	//aim = new Aim();
	Wind::Get();
	CharacterManager::Get();
	WeaponManager::Get()->SetLandTexture(terrain->terrain->GetTexture());
	EffectsManager::Get();
	Audio::Get()->Add("Background", "Resources/Sounds/BackMusic.mp3", true, true);
	Audio::Get()->Play("Background");
	Camera::Get()->SetMapRect(terrain->terrain);
}

BattleScene::~BattleScene()
{
	delete terrain;
	delete water;
	delete background;

	Wind::Delete();
	CharacterManager::Delete();
	WeaponManager::Delete();
	EffectsManager::Delete();
}

void BattleScene::Update()
{
	terrain->Update();
	water->Update();


	CharacterManager::Get()->Update();
	WeaponManager::Get()->Update();
	EffectsManager::Get()->Update();

}

void BattleScene::Render(HDC hdc)
{
	background->Render(hdc);
	terrain->Render(hdc);
	water->Render(hdc);

	Wind::Get()->Render(hdc);
	CharacterManager::Get()->Render(hdc);
	WeaponManager::Get()->Render(hdc);
	EffectsManager::Get()->Render(hdc);

	//wstring str = L"Mouse Pos : " + to_wstring(mousePos.x) + L", " + to_wstring(mousePos.y);
	//TextOut(hdc, 0, 40, str.c_str(), (int)str.length());
}

void BattleScene::Start()
{

	CharacterManager::Get()->Start(terrain->terrain->GetTexture());
}

void BattleScene::End()
{

}

