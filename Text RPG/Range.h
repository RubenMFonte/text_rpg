#pragma once

struct Range
{
	Range()
	{ m_low = 0; m_high = 0; }

	Range(int low, int high)
	{ m_low = low; m_high = high; }
	
	int m_low;
	int m_high;
};
