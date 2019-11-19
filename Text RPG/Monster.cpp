#include "stdafx.h"
#include "Monster.h"
#include "Player.h"

Monster::Monster(const std::string & name, int hp, int acc, int xpReward, int goldReward, int armor,
				 const std::string & weaponName, int lowDamage, int highDamage)
{
	mName			= name;
	mHitpoints		= hp;
	mMaxHitpoints   = hp;
	mAccuracy		= acc;
	mExpReward		= xpReward;
	mArmor			= armor;
	mGoldReward		= goldReward;

	mWeapon.mName				= weaponName;
	mWeapon.mDamageRange.m_low	= lowDamage;
	mWeapon.mDamageRange.m_high = highDamage;
}

bool Monster::isDead()
{
	return mHitpoints <= 0;
}

int Monster::getXPReward()
{
	return mExpReward;
}

int Monster::getGoldReward()
{
	return mGoldReward;
}

std::string Monster::getName()
{
	return mName;
}

int Monster::getArmor()
{
	return mArmor;
}

void Monster::attack(Player & player)
{
	std::cout << mName << " attacks you with " << mWeapon.mName << std::endl;

	if (Random(0, 20) < mAccuracy)
	{
		int damage = Random(mWeapon.mDamageRange) - player.getArmor();

		if(damage <= 0) std::cout << mName << "'s attack failed to penetrate your armor." << std::endl;
		else
		{
			std::cout << "You are hit for " << damage << " damage." << std::endl;
			player.takeDamage(damage);
		}
	}
	else
	{
		std::cout << mName << " misses!" << std::endl;
	}

	std::cout << std::endl;
}

void Monster::takeDamage(int damage)
{
	mHitpoints -= damage;
}

void Monster::displayHitPoints()
{
	int i = 0;
	std::cout << mName << std::endl << "HP: " << mHitpoints << "/" << mMaxHitpoints << "\n";

	// Print hitpoints bar
	std::cout << "-";
	while(i++ < mMaxHitpoints) std::cout << "-";
	std::cout << "-\n"; i = 0;

	std::cout << "-";
	while(i++ < mHitpoints) std::cout << "x";
	while(i++ <= mMaxHitpoints) std::cout << " ";
	std::cout << "-\n"; i = 0;

	std::cout << "-";
	while(i++ < mMaxHitpoints) std::cout << "-";
	std::cout << "-\n";
}
