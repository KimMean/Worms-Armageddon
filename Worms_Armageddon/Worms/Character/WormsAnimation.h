#pragma once


enum class AnimationList
{
	// ����
	IDLE,
	MOVE,
	JUMP,
	BACK_JUMP,
	WINNER,
	DIE,
	// ���� ����
	GRENADE_READY,
	GRENADE_AIM,
	BANANA_READY,
	BANANA_AIM,
	CLUSTER_READY,
	CLUSTER_AIM,
	//GRENADE_POCKET,
	//GRENADE
};

//AnimationList GetAnimationKey(wstring name);
//wstring AnimationListToString(AnimationList animName);

enum class AnimationDirection
{
	LEFT,
	RIGHT
};

wstring AnimationDirectionToString(AnimationDirection direction);

enum class AnimationSlope
{
	FLAT,
	UP,
	DOWN
};

wstring AnimationSlopeToString(AnimationSlope slope);
