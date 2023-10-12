#pragma once

class Weapon : public ImageRect
{
public:
	Weapon(Texture* texture);
	~Weapon();

	virtual void Update();
	virtual void Render(HDC hdc);

	void IsRectCollision();		// 지렁이나 오브젝트와 충돌
	void IsPixelCollision();	// 바닥(지형)과 충돌

	void SetLandTexture(Texture* texture) { landTexture = texture; }
	void SetBrush(HBRUSH brush, HPEN pen) { hBrush = brush, hPen = pen; }

	void SetActive(Vector2 direction, float power);
	void SetDirection(Vector2 direction) { this->direction = direction; }
	void SetSpeedPower(float power) { speedPower = power; }	// 대상 스피드
	void SetMaxDamage(float damage) { maxDamage = damage; }	// 최대 데미지 설정
	void SetBombTime(float time) { bombTime = time; }		// 폭파까지 걸리는 시간
	float GetMaxDamage() { return maxDamage; }	// 최대 데미지 리턴
	float GetBombRange() { return bombRange; }

protected:
	Texture* landTexture;	// Pixel충돌을 위한 지형 가져오기

	HBRUSH hBrush;			// 픽셀 지우기 위한 브러쉬
	HPEN hPen;				// 픽셀 지우기 위한 펜

protected :
	Animation* animation;	// 무기의 애니메이션
	Rect* boxCollider;		// 무기의 충돌체

protected :
	Vector2 velocity;		// 무기의 속도, 총알, 낙하, 투척, 날다
	Vector2 direction;		// 무기의 방향
	float speedPower;		// 해당 방향으로 힘
	float maxDamage = 100.0f;		// 무기 최대 데미지
	float bombRange = 100.0f;		// 폭파 범위
	float bombTime = 3;
	float curTime;			// 터지는 시간, 소멸 시간

};