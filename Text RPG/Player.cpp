#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	mName			= "Default";
	mRace			= "Default";
	mClassName		= "Default";
	mAccuracy		= 0;
	mHitpoints		= 0;
	mMaxHitpoints	= 0;
	mMagicPoints    = 0;
	mMaxMagicPoints = 0;
	mExpPoints		= 0;
	mNextLevelExp	= 1000;
	mGold			= 0;
	mLevel			= 1;
	mArmor			= 0;
	mWeapon.mName	= "Default";

	mWeapon.mDamageRange.m_low	= 0;
	mWeapon.mDamageRange.m_high	= 0;

	mSpells.clear();
}

bool Player::isDead()
{
	return mHitpoints <= 0;
}

std::string Player::getName()
{
	return mName;
}

int Player::getArmor()
{
	return mArmor;
}

void Player::takeDamage(int damage)
{
	mHitpoints -= damage;
}

void Player::createClass()
{
	bool selectedRace = false, selectedClass = false;

	std::cout << "CHARACTER CLASS GENERATION" << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "Enter your character's name: ";
	getline(std::cin, mName);

	while (!selectedClass)
	{

		std::cout << "Select your class:" << std::endl;
		std::cout << "1) Fighter, 2) Wizard, 3) Cleric, 4) Thief : " << std::endl;

		int charNum = 1;
		std::cin >> charNum;

		switch (charNum)
		{
		case 1:
			mClassName = "Fighter";
			mAccuracy = 10;
			mHitpoints = 20;
			mMaxHitpoints = 20;
			mMagicPoints = 20;
			mMaxMagicPoints = 20;
			mArmor = 4;

			mWeapon.mName = "Long Sword";
			mWeapon.mDamageRange = Range(1,8);

			mSpells.push_back(Spell("Tackle", Range(4,7), 10));
			mSpells.push_back(Spell("Storm Slash", Range(6,10), 14));

			selectedClass = true;
			break;
		case 2:
			mClassName = "Wizard";
			mAccuracy = 5;
			mHitpoints = 10;
			mMaxHitpoints = 10;
			mMagicPoints = 50;
			mMaxMagicPoints = 50;
			mArmor = 1;

			mWeapon.mName = "Staff";
			mWeapon.mDamageRange = Range(1,4);

			mSpells.push_back(Spell("Fireball", Range(6,8), 15));
			mSpells.push_back(Spell("Thunder", Range(8,13), 22));

			selectedClass = true;
			break;
		case 3:
			mClassName = "Cleric";
			mAccuracy = 8;
			mHitpoints = 15;
			mMaxHitpoints = 15;
			mMagicPoints = 30;
			mMaxMagicPoints = 30;
			mArmor = 3;

			mWeapon.mName = "Flail";
			mWeapon.mDamageRange = Range(1,6);

			mSpells.push_back(Spell("Light Spark", Range(5,10), 10));
			mSpells.push_back(Spell("Judgement", Range(9,13), 25));

			selectedClass = true;
			break;
		case 4:
			mClassName = "Thief";
			mAccuracy = 7;
			mHitpoints = 12;
			mMaxHitpoints = 12;
			mMagicPoints = 30;
			mMaxMagicPoints = 30;
			mArmor = 2;

			mWeapon.mName = "Dagger";
			mWeapon.mDamageRange = Range(2,5);

			mSpells.push_back(Spell("Cut-throat", Range(5,10), 10));
			mSpells.push_back(Spell("Shadow Assault", Range(8,13), 22));

			selectedClass = true;
			break;
		default:
			std::cout << "Invalid Input!" << std::endl;
			break;
		}

		while (!selectedRace)
		{
			std::cout << "Select your race:" << std::endl;
			std::cout << "1) Human, 2) Elf, 3) Dwarf : " << std::endl;

			int charNum = 1;
			std::cin >> charNum;

			switch (charNum)
			{
			case 1:
				mRace			 = "Human";
				mHitpoints		+= 4;
				mMaxHitpoints	+= 4;
				mArmor			+= 2;
				selectedRace = true;
				break;
			case 2:
				mRace			 = "Elf";
				mAccuracy		+= 4;
				selectedRace = true;
				break;
			case 3:
				mRace			 = "Dwarf";
				mHitpoints		+= 8;
				mMaxHitpoints	+= 8;
				selectedRace = true;
				break;
			default:
				std::cout << "Invalid Input!" << std::endl;
				break;
			}
		}
	}
}

bool Player::attack(Monster & monster)
{
	while (true)
	{
		AttackStart:
		int selection = 1;
		std::cout << "1) Attack, 2) Use Spell, 3) Run : ";
		std::cin >> selection;
		std::cout << std::endl;

		int damage = 0, roll = 0;

		switch(selection)
		{
		case 1: // Attack
			std::cout << "You attack " << monster.getName() << " with " << mWeapon.mName << "." << std::endl;

			if (Random(0, 20) < mAccuracy)
			{
				damage = Random(mWeapon.mDamageRange) - monster.getArmor();

				if(damage <= 0) std::cout << mName << "'Your attack failed to penetrate the " << monster.getName() << "'s armor." << std::endl;
				else
				{
					std::cout << "You hit the " << monster.getName() << " for " << damage << " damage." << std::endl;
					monster.takeDamage(damage);
				}
			}
			else
			{
				std::cout << "You miss!" << std::endl;
			}

			std::cout << std::endl;
			return false;
		case 2:
			while (true)
			{
				SpellStart:
				int i = 0;
				selection = 0;
				for (; i < mSpells.size(); i++) 
					std::cout << (i+1) << ") " << mSpells.at(i).mName << ", MP - " << mSpells.at(i).mMP_Required << "\n";
				std::cout << (i+1) << ") Back\n";
				std::cout << "Choose the spell:";
				std::cin >> selection;
				std::cout << std::endl;

				if(selection > 0 && selection <= mSpells.size())
				{
					if (mMagicPoints < mSpells.at(selection - 1).mMP_Required)
					{
						std::cout << "Insuficient MP!\n";
						goto SpellStart;
					}

					std::cout << "You attack " << monster.getName() << " with " << mSpells.at(selection - 1).mName << "." << std::endl;

					if (Random(0, 20) < mAccuracy)
					{
						damage = Random(mSpells.at(selection - 1).mDamageRange) - monster.getArmor();

						if(damage <= 0) std::cout << mName << "'Your spell failed to penetrate the " << monster.getName() << "'s armor." << std::endl;
						else
						{
							std::cout << "You hit the " << monster.getName() << " for " << damage << " damage." << std::endl;
							monster.takeDamage(damage);
						}
					}
					else
					{
						std::cout << "You miss!" << std::endl;
					}

					mMagicPoints -= mSpells.at(selection - 1).mMP_Required;

					return false;
				}
				else if(selection == mSpells.size() + 1) goto AttackStart;

				std::cout << "Invalid Spell!\n";
			}
		case 3: // Run
			roll = Random(1,3);

			if ( roll == 1 )
			{
				std::cout << "You couldn't escape!" << std::endl;
				return false;
			}
			else
			{
				std::cout << "You ran away!" << std::endl;
				return true;
			}
		default:
			std::cout << "Invalid Input!" << std::endl;
			break;
		}

	}
}

void Player::levelUp()
{
	if (mExpPoints >= mNextLevelExp)
	{
		std::cout << "You gained a level!" << std::endl;

		mLevel++;

		mNextLevelExp = mLevel * mLevel * 1000;

		int acc  = (mClassName == "Wizard" || mClassName == "Thief")	? Random(3,5) : Random(1,3);
		int hp   = (mClassName == "Fighter" || mClassName == "Cleric")	? Random(6,10) : Random(4,8);
		int armr = (mClassName == "Fighter" || mClassName == "Cleric")	? Random(2,4) : Random(1,3);
		int mp	 = (mClassName == "Wizard" || mClassName == "Cleric")	? Random(6,8) : Random(4,6);

		mAccuracy		+= acc;
		mMaxHitpoints	+= hp;
		mArmor			+= armr;
		mMaxMagicPoints += mp;

		mHitpoints		= mMaxHitpoints;
		mMagicPoints	= mMaxMagicPoints;
	}
}

void Player::rest()
{
	std::cout << "Resting..." << std::endl;

	mHitpoints		= mMaxHitpoints;
	mMagicPoints	= mMaxMagicPoints;
}

void Player::viewStats()
{
	std::cout << "PLAYER STATS" << std::endl;
	std::cout << "============" << std::endl << std::endl;
	std::cout << "Name = " << mName << std::endl;
	std::cout << "Race = " << mRace << std::endl;
	std::cout << "Class = " << mClassName << std::endl;
	std::cout << "Accuracy = " << mAccuracy << std::endl;
	std::cout << "Hitpoints = " << mHitpoints << std::endl;
	std::cout << "MaxHitpoints = " << mMaxHitpoints << std::endl;
	std::cout << "Magicpoints = " << mMagicPoints << std::endl;
	std::cout << "MaxMagicpoints = " << mMaxMagicPoints << std::endl;
	std::cout << "XP = " << mExpPoints << std::endl;
	std::cout << "XP for Next Lvl = " << mNextLevelExp << std::endl;
	std::cout << "Level = " << mLevel << std::endl;
	std::cout << "Armor = " << mArmor << std::endl;
	std::cout << "Gold = " << mGold << std::endl;
	std::cout << "Weapon Name = " << mWeapon.mName << std::endl;
	std::cout << "Weapon Damage = " << mWeapon.mDamageRange.m_low << "-" << mWeapon.mDamageRange.m_high << std::endl << std::endl;
	std::cout << "END PLAYER STATS" << std::endl;
	std::cout << "================" << std::endl << std::endl; 
}

void Player::victory(int xp, int gold)
{
	std::cout << "You won the battle!" << std::endl;
	std::cout << "You gained " << xp << " experience points and " << gold << " gold." << std::endl << std::endl;

	mExpPoints	+= xp;
	mGold		+= gold;
}

void Player::gameover()
{
	std::cout << "You died in battle..." << std::endl << std::endl;
	std::cout << "=======================" << std::endl;
	std::cout << "GAME OVER" << std::endl;
	std::cout << "=======================" << std::endl;
	std::cout << "Press 'q' to quit: ";
	char q = 'q';
	std::cin >> q;
	std::cout << std::endl;
}

void Player::displayHPandMP()
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
	std::cout << "-\n"; i = 0;

	std::cout << "MP: " << mMagicPoints << "/" << mMaxMagicPoints << "\n";
	
	// Print magicpoints bar
	std::cout << "-";
	while(i++ < mMaxMagicPoints) std::cout << "-";
	std::cout << "-\n"; i = 0;

	std::cout << "-";
	while(i++ < mMagicPoints) std::cout << "x";
	while(i++ <= mMaxMagicPoints) std::cout << " ";
	std::cout << "-\n"; i = 0;

	std::cout << "-";
	while(i++ < mMaxMagicPoints) std::cout << "-";
	std::cout << "-\n"; i = 0;
}
