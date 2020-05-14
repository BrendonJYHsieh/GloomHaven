#include "Monster_Base.h"
Monster_Base::Monster_Base() {
	this->Hp = 0;
	this->Name = "";
}
Monster_Base::Monster_Base(string name,int hp) {
	this->Hp = hp;
	this->Name = name;
}
Monster_Base::Monster_Base(string name, int hp, int atk, int range, int elite_hp, int elite_damage, int elite_range)
{
	this->Name = name; this->Hp = hp; this->Damage = atk; this->Range = range; this->Elite_Hp = elite_hp; this->Elite_Damage = elite_damage; this->Elite_Range = elite_range;
}