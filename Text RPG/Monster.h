#pragma once

#include "Weapon.h"
#include "Random.cpp"
#include <string>
#include <iostream>

class Player;

class Monster
{
public:
	Monster(const std::string& name, int hp, int acc, int xpReward, int goldReward,
			int armor, const std::string& weaponName, int lowDamage, int highDamage);
	
	bool isDead();
	int getXPReward();
	int getGoldReward();
	std::string getName();
	int getArmor();

	void attack(Player& player);
	void takeDamage(int damage);
	void displayHitPoints();

private:
	std::string mName;
	int mHitpoints;
	int mMaxHitpoints;
	int mAccuracy;
	int mExpReward;
	int mGoldReward;
	int mArmor;
	Weapon mWeapon;
};

