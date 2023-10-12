#include "Framework.h"
//#include "Worms/Character/WormsAnimation.h"

//AnimationList GetAnimationKey(wstring name)
//{
//	unordered_map<AnimationList, wstring>::iterator iter;
//	for (iter = AnimLists.begin(); iter != AnimLists.end(); iter++);
//	//{
//	//
//	//}
//	//{
//	//	if (list.second.compare(name) == 0)
//	//	{
//	//		return list.first;
//	//	}
//	//}
//	return AnimationList();
//}

//wstring AnimationListToString(AnimationList animName)
//{
//	switch (animName)
//	{
//	case AnimationList::IDLE:		return	L"IDLE";
//	case AnimationList::MOVE:		return	L"MOVE";
//	case AnimationList::JUMP:		return	L"JUMP";
//	case AnimationList::BACK_JUMP:	return	L"BACK_JUMP";
//	}
//}

wstring AnimationDirectionToString(AnimationDirection direction)
{
	switch (direction)
	{
	case AnimationDirection::LEFT:	return	L"LEFT";
	case AnimationDirection::RIGHT:	return	L"RIGHT";
	}
}

wstring AnimationSlopeToString(AnimationSlope slope)
{
	switch (slope)
	{
	case AnimationSlope::FLAT:	return	L"FLAT";
	case AnimationSlope::UP:	return	L"UP";
	case AnimationSlope::DOWN:	return	L"DOWN";
	}
}
