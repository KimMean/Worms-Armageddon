#pragma once

class Weapon;

class CharacterManager : public Singleton<CharacterManager>
{
private:
	const UINT MAX_PLAYER_NUM = 5;
	const float MAX_PLAY_TIME = 20.0f;
	const float MAX_BOMB_TIME = 5.0f;

private :
	friend class Singleton;

	CharacterManager();
	~CharacterManager();

public:
	void Update();
	void Render(HDC hdc);

	void Start(Texture* landTexture);
	void End();

	void SetPlayerNum(int num);
	void ChangePlayer();

	void CollisionBomb(Weapon* weapon);

private :
	void UpdatePlayTime();
	void PlayerUpdate();
	void CreateWorms();

private :
	vector<Worms*> worms;
	Worms* player;
	
	int playerNum;
	int targetNum;

	float playTime;
	bool isBomb;
	float bombTime;


};