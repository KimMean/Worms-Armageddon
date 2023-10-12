// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define WIN_START_X 0
#define WIN_START_Y 0

#define WIN_WIDTH 3840
#define WIN_HEIGHT 2160

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define PI 3.141592f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)

#define GRAVITY 980.0f

#define DELTA Timer::Get()->GetElapsedTime()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <functional>

using namespace std;

typedef function<void()> Event;
typedef function<void(void*)> ParamEvent;


//FMOD Library
#include "Libraries/inc/fmod.hpp"
#pragma comment(lib, "Libraries/lib/fmod_vc.lib")

//Framework Header
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Audio.h"

using namespace Utility;

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"

using namespace GameMath;

#include "Framework/Render/Texture.h"
#include "Framework/Render/Animation.h"
#include "Framework/Render/Camera.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Line.h"
#include "Objects/Basic/ImageRect.h"
#include "Objects/Basic/Effect.h"

#include "Objects/UI/ProgressBar.h"
#include "Objects/UI/Button.h"

#include "Objects/Manager/PoolingManager.h"
#include "Objects/Manager/EffectManager.h"
#include "Objects/Manager/Observer.h"
#include "Objects/Manager/DataManager.h"

// Worms


// UI
#include "Worms/UI/Aim.h"
#include "Worms/UI/Wind.h"
#include "Worms/UI/NameTag.h"
#include "Worms/UI/HelthPoint.h"
#include "Worms/UI/PowerGauge.h"

// Effect
#include "Worms/Effects/Effects.h"
#include "Worms/Effects/EffectsManager.h"

// 지형, 배경
#include "Worms/Map/Water.h"
#include "Worms/Map/Terrain.h"
#include "Worms/Map/Background.h"

// 캐릭터
#include "Worms/Character/WormsAnimation.h"
#include "Worms/Character/Worms.h"
#include "Worms/Character/CharacterManager.h"

// 무기
#include "Worms/Weapons/Weapon.h"
#include "Worms/Weapons/ThrowingWeapon.h"
#include "Worms/Weapons/WeaponManager.h"



//Scene Header
#include "Scenes/Scene.h"

//Manager Header
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern Vector2 mousePos;
extern HINSTANCE hInst;
extern HWND hWnd;
