#include "stdafx.h"

#include "Range.h"
#include <cstdlib>

static int Random(Range r)
{
	return r.m_low + rand() % ( (r.m_high + 1) - r.m_low );
}

static int Random(int min, int max)
{
	return min + rand() % ( (max + 1) - min );
}
