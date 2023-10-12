#pragma once

class ThrowingWeapon : public Weapon
{
private :
	const int CLUSTER_NUM = 3;

public:
	ThrowingWeapon(Texture* texture);
	~ThrowingWeapon();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void SetBrush(HBRUSH brush, HPEN pen) { hBrush = brush, hPen = pen; }

	void SetCluster();
	void BombCheck();
	//void MaskLandTexture();
	void CheckLandCollision();
	bool CollisionLandTexture(Vector2 pos);

private:
	//HBRUSH hBrush;			// 픽셀 지우기 위한 브러쉬
	//HPEN hPen;				// 픽셀 지우기 위한 펜
	vector<ThrowingWeapon*> cluster;
	bool isClusterType = false;
	float bombRange = 100.0f;		// 폭파 범위
	

};