#pragma once

class EffectsManager : public Singleton<EffectsManager>
{
private :
	friend class Singleton;

	EffectsManager();
	~EffectsManager();


	void CreateEffects();

public :
	void Update();
	void Render(HDC hdc);
	void Active(Vector2 pos);

private:
	Texture* texture;
	vector<Effects*> effects;
};