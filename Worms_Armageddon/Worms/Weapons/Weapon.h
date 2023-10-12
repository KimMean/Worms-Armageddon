#pragma once

class Weapon : public ImageRect
{
public:
	Weapon(Texture* texture);
	~Weapon();

	virtual void Update();
	virtual void Render(HDC hdc);

	void IsRectCollision();		// �����̳� ������Ʈ�� �浹
	void IsPixelCollision();	// �ٴ�(����)�� �浹

	void SetLandTexture(Texture* texture) { landTexture = texture; }
	void SetBrush(HBRUSH brush, HPEN pen) { hBrush = brush, hPen = pen; }

	void SetActive(Vector2 direction, float power);
	void SetDirection(Vector2 direction) { this->direction = direction; }
	void SetSpeedPower(float power) { speedPower = power; }	// ��� ���ǵ�
	void SetMaxDamage(float damage) { maxDamage = damage; }	// �ִ� ������ ����
	void SetBombTime(float time) { bombTime = time; }		// ���ı��� �ɸ��� �ð�
	float GetMaxDamage() { return maxDamage; }	// �ִ� ������ ����
	float GetBombRange() { return bombRange; }

protected:
	Texture* landTexture;	// Pixel�浹�� ���� ���� ��������

	HBRUSH hBrush;			// �ȼ� ����� ���� �귯��
	HPEN hPen;				// �ȼ� ����� ���� ��

protected :
	Animation* animation;	// ������ �ִϸ��̼�
	Rect* boxCollider;		// ������ �浹ü

protected :
	Vector2 velocity;		// ������ �ӵ�, �Ѿ�, ����, ��ô, ����
	Vector2 direction;		// ������ ����
	float speedPower;		// �ش� �������� ��
	float maxDamage = 100.0f;		// ���� �ִ� ������
	float bombRange = 100.0f;		// ���� ����
	float bombTime = 3;
	float curTime;			// ������ �ð�, �Ҹ� �ð�

};