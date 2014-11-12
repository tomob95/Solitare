//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// 2014 (c) Media Design School
//
// File Name	: Utils.h
// Description	: Header for the utilities class
// Author		: Tom O'Brien, Kelsey Scheurich, Tom Butler
// Mail			: kelsey.scheurich@mediadesign.school.nz
//

#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <strstream>
#include <Windows.h>

// Prototypes
#define VALIDATE(a) if (!a) return (false)

// Const variables
const int CARD_WIDTH	=  132;
const int CARD_HEIGHT	=  192;
const int MASK_X		=  132;
const int MASK_Y		=  768;
const int BACK_X		=  0;
const int BACK_Y		=  768;

static HWND hwnd;

// To string template
template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
};

// Enum to store card suit
enum eSuit: int { SPADE = 0, CLUB, HEART, DIAMOND };

#endif // __UTILS_H__