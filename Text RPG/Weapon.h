#pragma once

#include <string>
#include "Range.h"

struct Weapon
{
	Weapon() { mName = "Default"; mDamageRange = Range(); }
	std::string mName;
	Range mDamageRange;
};
