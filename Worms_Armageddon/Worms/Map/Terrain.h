#pragma once

class Terrain
{


private :
	//const wstring TERRAIN_FILE_NAME = L"Resources/Textures/Map/Terrain/PIRATES_UHD.bmp";
	const wstring TERRAIN_FILE_NAME = L"Resources/Textures/Map/Terrain/TNT_UHD.bmp";

public:
	Terrain();
	~Terrain();
	void Update();
	void Render(HDC hdc);


public:
	ImageRect* terrain;

};