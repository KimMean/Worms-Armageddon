#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain()
{
	terrain = new ImageRect(TERRAIN_FILE_NAME);
	terrain->pos = terrain->Half();

	//terrain->pos.y = WIN_HEIGHT - terrain->Half().y;
}

Terrain::~Terrain()
{
	delete terrain;
}

void Terrain::Update()
{
}

void Terrain::Render(HDC hdc)
{
	terrain->CamRender(hdc);
}
