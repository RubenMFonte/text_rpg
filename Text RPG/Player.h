#pragma once

#include "Weapon.h"
#include "Monster.h"
#include "Spell.h"
#include <vector>
#include <string>
#include <iostream>

typedef std::vector<Spell> Spellbook;

class Player
{
public:
	Player();

	bool isDead();

	std::string getName();
	int			getArmor();

	void takeDamage(int damage);

	void createClass();
	bool attack(Monster& monster);
	void levelUp();
	void rest();
	void viewStats();
	void victory(int xp, int gold);
	void gameover();
	void displayHPandMP();

private:
	std::string mName;
	std::string mRace;
	std::string mClassName;
	int			mAccuracy;
	int			mHitpoints;
	int			mMaxHitpoints;
	int			mMagicPoints;
	int			mMaxMagicPoints;
	int			mExpPoints;
	int			mGold;
	int			mNextLevelExp;
	int			mLevel;
	int			mArmor;
	Weapon		mWeapon;
	Spellbook	mSpells;
};
