#pragma once
#if !defined(__UTILS_H__)
#define __UTILS_H__
// Library Includes
#include <strstream>
#include <Windows.h>
// Local Includes
// Types
// Constants
// Prototypes
#define VALIDATE(a) if (!a) return (false)

const int CARD_WIDTH	=  132;
const int CARD_HEIGHT	=  192;
const int MASK_X		=  132;
const int MASK_Y		=  768;
const int BACK_X		=  0;
const int BACK_Y		=  768;
static HWND hwnd;
template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
};

enum eSuit: int { SPADE = 0, CLUB, DIAMOND, HEART };

//std::wstring  wstrFace[] = { L"ACE", L"TWO", L"THREE", L"FOUR", L"FIVE", L"SIX", L"SEVEN", L"EIGHT", L"NINE", L"TEN", L"JACK", L"QUEEN", L"KING" };

#endif // __UTILS_H__