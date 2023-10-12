#pragma once

class BattleScene : public Scene
{
private :
	const UINT MAX_PLAYER_NUM = 10;

public:
	BattleScene();
	~BattleScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

	void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
	void SetPlayerNum(int num);
	
private :
	void CreateWorms();
	void CameraControl();

private :
	HFONT hFont;

private :
	Terrain* terrain;
	Background* background;
	Water* water;
	Wind* wind;

	vector<Worms*> worms;
	Worms* player;

private :
	int playerNum;
	int targetNum;

	//Aim* aim;
};