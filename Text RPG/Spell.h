#pragma once

#include <string>
#include "Range.h"

struct Spell
{
	Spell(std::string name, Range damage, int mpReq)
	{ mName = name; mDamageRange = damage; mMP_Required = mpReq; }

	std::string mName;
	Range mDamageRange;
	int mMP_Required;
};

