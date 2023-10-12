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
	//HBRUSH hBrush;			// �ȼ� ����� ���� �귯��
	//HPEN hPen;				// �ȼ� ����� ���� ��
	vector<ThrowingWeapon*> cluster;
	bool isClusterType = false;
	float bombRange = 100.0f;		// ���� ����
	

};