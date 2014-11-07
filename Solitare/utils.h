#pragma once
#if !defined(__UTILS_H__)
#define __UTILS_H__
// Library Includes
#include <strstream>
// Local Includes
// Types
// Constants
// Prototypes
#define VALIDATE(a) if (!a) return (false)

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