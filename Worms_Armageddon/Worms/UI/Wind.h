#pragma once
class Wind : public ImageRect, public Singleton<Wind>
{
private :
	const float MIN_WIND_FORCE = -5;
	const float MAX_WIND_FORCE = 5;

private :
	friend class Singleton;
	Wind();
	~Wind();

public :
	void Render(HDC hdc);

	float GetWindForce() { return windForce; }
	void SetWindForce(float force);


private:
	//Texture* backgroundTexture;
	Texture* windLeftTexture;
	Texture* windRightTexture;
	//ProgressBar windLeftProgressBar;
	//ProgressBar windRightProgressBar;
   
	// -100 ~ 100
	float windForce; 
	float value;

};