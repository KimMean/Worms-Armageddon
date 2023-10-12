#include "Framework.h"

CharacterManager::CharacterManager()
{
	playerNum = MAX_PLAYER_NUM;

	CreateWorms();
	Audio::Get()->Add("Die", "Resources/Sounds/ByeBye.mp3");
}

CharacterManager::~CharacterManager()
{
	for (UINT i = 0; i < MAX_PLAYER_NUM; i++)
	{
		delete worms[i];
	}
}

void CharacterManager::Update()
{
	// 각 플레이어의 시간 조절
	UpdatePlayTime();
	player->Control();
	PlayerUpdate();

	if (KEY_DOWN(VK_NUMPAD0))
	{
		ChangePlayer();
	}

}

void CharacterManager::Render(HDC hdc)
{
	for (UINT i = 0; i < playerNum; i++)
	{
		if (worms[i]->isActive)
		{
			worms[i]->Render(hdc);
			// 체력바 출력
			worms[i]->GetHelthPoint()->Render(hdc);
		}
	}

	SetTextColor(hdc, BLACK);
	
	wstring playTimeText = to_wstring((int)(MAX_PLAY_TIME - playTime));
	TextOut(hdc, SCREEN_WIDTH / 2, 50, playTimeText.c_str(), playTimeText.length());
}

void CharacterManager::Start(Texture* landTexture)
{
	targetNum = 0;
	ChangePlayer();

	for (int i = 0; i < playerNum; i++)
	{
		worms[i]->SetLand(landTexture);
		worms[i]->SetNameTag(L"Player " + to_wstring(i));
		float randomPosX = Random(100.0f, WIN_WIDTH - 100.0f);
		worms[i]->pos = { randomPosX, 100.0f };
	}
}

void CharacterManager::End()
{
}

void CharacterManager::SetPlayerNum(int num)
{
	if (0 < num && num <= MAX_PLAYER_NUM)
		playerNum = num;
}

void CharacterManager::ChangePlayer()
{
	Wind::Get()->SetWindForce(Random(-5.0f, 5.0f));
	if(player)
		player->SetControllable(false);
	while (true)
	{
		if (targetNum == playerNum)
			targetNum = 0;

		if (player == worms[targetNum])
		{
			// 겜끝
			// 플레이어 승리
			// 승리 모션 하면 좋고
			player->Winner();
			return;
		}

		if (!worms[targetNum]->isActive)
		{
			targetNum++;
			continue;
		}

		player = worms[targetNum];
		player->SetControllable(true);
		Camera::Get()->SetTarget(player);
		targetNum++;
		playTime = 0.0f;
		Wind::Get()->SetWindForce(Random(-5.0f, 5.0f));
		break;
	}

}

void CharacterManager::CollisionBomb(Weapon* weapon)
{
	isBomb = true;
	player->SetControllable(false);
	
	float range = weapon->GetBombRange();
	float maxDamage = weapon->GetMaxDamage();

	for (int i = 0; i < playerNum; i++)
	{
		if (worms[i]->isActive)
		{
			Vector2 vec = worms[i]->pos - weapon->pos;
			float dist = vec.Length();
			if (dist < range)
			{
				float ratio = (range - dist) / range;
				Vector2 velocity = vec.GetNormalized() * 500 * ratio;

				float damage = maxDamage * ratio;
				// worms[i] 체력 깍기
				// 체력이 0 이하가 아니라면 날리기
				worms[i]->Damage(damage);
				worms[i]->AddForce(velocity);
			}
		}
	}
}

void CharacterManager::UpdatePlayTime()
{
	if (isBomb)
		bombTime += DELTA;
	else
		playTime += DELTA;
	
	if (playTime > MAX_PLAY_TIME || bombTime > MAX_BOMB_TIME)
	{
		if (isBomb)
		{
			bombTime = 0;
			isBomb = false;
		}

		ChangePlayer();
	}

}

void CharacterManager::PlayerUpdate()
{
	int cnt = 1;
	float padding = 30;

	for (UINT i = 0; i < playerNum; i++)
	{
		if (worms[i]->isActive)
		{
			worms[i]->Update();

			worms[i]->GetHelthPoint()->pos =
			{ worms[i]->GetHelthPoint()->Half().x + 30  , padding * cnt++ };
		}
	}
}

void CharacterManager::CreateWorms()
{
	// 10 마리의 웜즈를 생성
	worms.resize(MAX_PLAYER_NUM);
	for (UINT i = 0; i < MAX_PLAYER_NUM; i++)
	{
		worms[i] = new Worms();
	}
}
