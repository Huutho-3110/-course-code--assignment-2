#include "eniesLobby.h"

/*
 * BattleContext
 */
BattleContext::BattleContext()
{
    turnCount = 0;
    morale = 0;
    alarmLevel = 0;
    rescueProgress = 0;
    escapeProgress = 0;
    busterCallTimer = 0;
    mainGateDestroyed = false;
    robinRescued = false;
    bridgeOpened = false;
    battleEnded = false;
    resultCode = "";
}

void BattleContext::nextTurn()
{
    // TODO: implement
    this->turnCount++;
}

/*
 * Character
 */
Character::Character()
{
    name = "";
    hp = 0;
    maxHp = 0;
    atk = 0;
    def = 0;
    speed = 0;
    energy = 0;
    alive = false;
    this->isLowest = false;
    this->killInTurn = false;
}

Character::Character(string name, int hp, int atk, int def, int speed, int energy)
{
    // TODO: implement
    this->name = name;
    if (hp <= 0)
    {
        this->maxHp = 0;
    }
    else
    {
        this->maxHp = hp;
    }
    if (hp <= 0)
        this->hp = 0;
    else if (hp > maxHp)
        this->hp = maxHp;
    else
    {
        this->hp = hp;
    }
    this->atk = atk;
    this->def = def;
    this->speed = speed;
    if (energy > 100)
        this->energy = 100;
    else if (energy <= 0)
        this->energy = 0;
    else
        this->energy = energy;
    if (hp > 0)
        this->alive = true;
    else
        this->alive = false;
    this->isLowest = false;
    this->killInTurn = false;
}

Character::~Character()
{
    // TODO: implement if needed
}

int Character::attack(Building *target, BattleContext &context)
{
    return 0;
}

int Character::specialSkill(Building *target, BattleContext &context)
{
    return 0;
}

void Character::endTurn(BattleContext &context)
{
    return;
}

void Character::receiveDamage(int damage)
{
    // TODO: implement
    int realDmg = damage - this->def;
    if (realDmg < 0)
        realDmg = 0;

    this->hp -= realDmg;
    if (this->hp <= 0)
    {
        this->hp = 0;
        this->alive = false;
    }
    this->hp = max(0, min(this->hp, this->maxHp));
}

bool Character::isAlive() const
{
    // TODO: implement
    return this->alive;
}

string Character::getName() const
{
    // TODO: implement
    return this->name;
}

int Character::getHP() const
{
    // TODO: implement
    return this->hp;
}

int Character::getDef() const
{
    return this->def;
}

int Character::getEnergy() const
{
    // TODO: implement
    return this->energy;
}

bool Character::isStrawHat() const
{
    return false;
}

bool Character::isCP9() const
{
    return false;
}
void Character::updateMoral(BattleContext &context, bool isSpecialSkill)
{
    if (this->isCP9())
        context.morale -= 5;
    if (this->isStrawHat())
        context.morale += 5;
}
int Character::getMaxHp() const
{
    return this->maxHp;
}
void Character::receiveSanji(Character *target) const
{
    if (target == nullptr)
        return;
    if (target->isCP9())
    {
        if (dynamic_cast<Jabra *>(target) != nullptr)
        {
            target->setDef(target->def - 12);
        }
        else
        {
            target->setDef(target->def - 8);
        }
    }
}
void Character::receiveNami(Character *target) const
{
    if (target == nullptr)
        return;
    target->setSpeed(target->speed - 10);
}
void Character::healFromChopper(Character *target, int healAmount) const
{
    if (target->hp + healAmount >= target->maxHp)
        target->hp = target->maxHp;
    else
    {
        target->hp += healAmount;
    }
}
int Character::getSpeed() const
{
    return this->speed;
}

void Character::receiveUssop(Character *target) const
{
    if (target == nullptr)
        return;
    target->setSpeed(target->speed - 12);
}
int Character::getAtk() const
{
    return this->atk;
}
void Character::receiveFranky(Character *target) const
{
    if (target == nullptr)
        return;
    target->setSpeed(target->speed - 8);
}
void Character::receiveKalifa(Character *target) const
{
    if (target == nullptr)
        return;
    target->setSpeed(target->speed - 6);
}
bool Character::lowestHpTag() const
{
    return this->isLowest;
}
void Character::setIsLowest(bool isLowest)
{
    this->isLowest = isLowest;
}
void Character::setDef(int newDef)
{
    this->def = max(0, newDef);
}

void Character::setSpeed(int newSpeed)
{
    this->speed = max(0, newSpeed);
}
/*
 * StrawHat
 */
StrawHat::StrawHat() : Character()
{
    bounty = 0;
}

StrawHat::StrawHat(string name, int hp, int atk, int def,
                   int speed, int energy, long long bounty) : Character(name, hp, atk, def, speed, energy)
{
    // TODO: implement
    this->bounty = bounty;
}

bool StrawHat::isStrawHat() const
{
    // TODO: implement
    return true;
}

string StrawHat::str() const
{
    // TODO: implement
    return "StrawHat[name=" + this->name +
           ", hp=" + to_string(this->hp) +
           ", atk=" + to_string(this->atk) +
           ", def=" + to_string(this->def) +
           ", speed=" + to_string(this->speed) +
           ", energy=" + to_string(this->energy) +
           ", bounty=" + to_string(this->bounty) + "]";
}

/*
 * Luffy
 */
Luffy::Luffy(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
}

int Luffy::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    double percent = (double)this->hp / this->maxHp;
    int currDmg = this->atk;
    if (percent > 0.5)
        currDmg = this->atk;
    else if (percent > 0.3)
        currDmg = (int)ceil(this->atk * 115 / 100.0);
    else
        currDmg = (int)ceil(this->atk * 130 / 100.0);

    int realDmg = currDmg - target->getDef();
    if (realDmg < 0)
        realDmg = 0;

    target->receiveDamage(currDmg);
    if (!target->isAlive())
    {
        context.morale += 5;
        this->killInTurn = true;
    }

    this->energy = max(0, min(this->energy, 100));
    context.morale = max(0, min(context.morale, 100));
    return realDmg;
}

int Luffy::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    int minHpRequired = (int)ceil(this->maxHp * 15 / 100.0);
    if (this->energy < 20 || this->hp < minHpRequired)
        return 0;
    this->energy -= 20;
    int currSpe = this->atk * 2;
    int realDmg = currSpe - target->getDef();
    if (realDmg < 0)
        realDmg = 0;
    target->receiveDamage(currSpe);
    if (!target->isAlive())
    {
        this->killInTurn = true;
    }
    this->atk += 15;
    this->speed += 15;
    int hpLoss = (int)ceil(this->maxHp * 8 / 100.0);
    this->hp -= hpLoss;
    context.alarmLevel += 10;
    context.alarmLevel = max(0, min(context.alarmLevel, 100));
    if (this->hp <= 0)
    {
        this->hp = 0;
        this->alive = false;
    }
    this->hp = max(0, min(this->hp, this->maxHp));
    this->energy = max(0, min(this->energy, 100));
    return realDmg;
}

int Luffy::attack(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed())
        return 0;
    double percent = (double)this->hp / this->maxHp;
    int currDmg = this->atk;
    if (percent > 0.5)
        currDmg = this->atk;
    else if (percent > 0.3)
        currDmg = (int)ceil(this->atk * 115 / 100.0);
    else
        currDmg = (int)ceil(this->atk * 130 / 100.0);

    int realDmg = currDmg;
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);

    if (!wasDestroyed && target->isDestroyed())
    {
        target->onDestroyed(context);
    }
    return realDmg;
}
int Luffy::specialSkill(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed())
        return 0;

    int minHpRequired = (int)ceil(this->maxHp * 15 / 100.0);
    if (this->energy < 20 || this->hp < minHpRequired)
        return 0;
    this->energy -= 20;

    int currSpe = this->atk * 2;
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(currSpe);
    if (!wasDestroyed && target->isDestroyed())
    {
        target->onDestroyed(context);
    }
    this->atk += 15;
    this->speed += 15;
    int hpLoss = (int)ceil(this->maxHp * 8 / 100.0);
    this->hp -= hpLoss;
    context.alarmLevel += 10;
    context.alarmLevel = max(0, min(context.alarmLevel, 100));
    if (this->hp <= 0)
    {
        this->hp = 0;
        this->alive = false;
    }

    this->hp = max(0, min(this->hp, this->maxHp));
    this->energy = max(0, min(this->energy, 100));
    return currSpe;
}

void Luffy::endTurn(BattleContext &context)
{
    // TODO: implement
    if ((double)this->hp / this->maxHp <= 30 / 100.0)
    {
        context.morale += 3;
    }
    if (this->killInTurn)
    {
        this->energy += 5;
        this->killInTurn = false;
    }
    context.morale = max(0, min(context.morale, 100));
    this->energy = max(0, min(this->energy, 100));
}

/*
 * Zoro
 */
Zoro::Zoro(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
}

int Zoro::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    int currAtk = (int)ceil(this->atk + this->def * 20 / 100.0);
    if ((double)target->getHP() / target->getMaxHp() < 0.40)
    {
        currAtk = (int)ceil(currAtk * 115 / 100.0);
    }
    int realDmg = currAtk - target->getDef();
    if (realDmg < 0)
        realDmg = 0;
    target->receiveDamage(currAtk);

    if (!target->isAlive())
        this->killInTurn = true;
    return realDmg;
}

int Zoro::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 15)
        return 0;
    this->energy -= 15;
    int currSpe = (int)ceil(this->atk * 220 / 100.0);
    if ((double)target->getHP() / target->getMaxHp() < 0.50)
    {
        currSpe = (int)ceil(currSpe * 150 / 100.0);
    }
    int realDmg = currSpe - target->getDef();
    if (realDmg < 0)
        realDmg = 0;
    target->receiveDamage(currSpe);

    if (!target->isAlive())
    {
        this->energy += 8;
        context.morale += 4;
        this->killInTurn = true;
    }
    this->energy = max(0, min(this->energy, 100));
    context.morale = max(0, min(context.morale, 100));
    return realDmg;
}

int Zoro::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || target->isDestroyed())
        return 0;
    int realDmg = (int)ceil(this->atk + this->def * 20 / 100.0);

    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);

    if (!wasDestroyed && target->isDestroyed())
    {
        target->onDestroyed(context);
    }
    return realDmg;
}

int Zoro::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || target->isDestroyed() || this->energy < 15)
        return 0;
    this->energy -= 15;
    int realDmg = (int)ceil(this->atk * 220 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);

    if (!wasDestroyed && target->isDestroyed())
    {
        target->onDestroyed(context);
    }
    this->energy = max(0, min(this->energy, 100));
    return realDmg;
}

void Zoro::endTurn(BattleContext &context)
{
    // TODO: implement
    if (this->killInTurn)
    {
        this->atk = (int)ceil(this->atk * 1.05);
        context.morale += 6;
        this->killInTurn = false;
    }
    context.morale = max(0, min(context.morale, 100));
}

/*
 * Sanji
 */
Sanji::Sanji(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
}

int Sanji::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;

    int currAtk = (int)ceil(this->atk + this->speed * 50 / 100.0);
    if (target->getDef() < this->def)
    {
        currAtk = (int)ceil(currAtk * 110 / 100.0);
    }

    int realDmg = currAtk - target->getDef();
    if (realDmg < 0)
        realDmg = 0;

    target->receiveDamage(currAtk);

    if (!target->isAlive())
    {
        this->killInTurn = true;
    }
    return realDmg;
}

int Sanji::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 18)
        return 0;

    this->energy -= 18;
    int currSpe = (int)ceil(this->atk * 210 / 100.0);

    int realDmg = currSpe - target->getDef();
    if (realDmg < 0)
        realDmg = 0;

    target->receiveDamage(currSpe);

    if (!target->isAlive())
    {
        this->killInTurn = true;
    }

    this->receiveSanji(target);
    return realDmg;
}

int Sanji::attack(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed())
        return 0;
    int realDmg = (int)ceil(this->atk + this->speed * 50 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);
    if (!wasDestroyed && target->isDestroyed())
        target->onDestroyed(context);
    return realDmg;
}

int Sanji::specialSkill(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed() || this->energy < 18)
        return 0;

    this->energy -= 18;
    int realDmg = (int)ceil(this->atk * 210 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);
    if (!wasDestroyed && target->isDestroyed())
        target->onDestroyed(context);
    return realDmg;
}

void Sanji::endTurn(BattleContext &context)
{
    // TODO: implement
    if (this->killInTurn)
    {
        context.morale += 8;
        this->atk = (int)ceil(this->atk * 110 / 100.0);
        this->killInTurn = false;
    }
    context.morale = max(0, min(context.morale, 100));
}

/*
 * Nami
 */
Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
}

int Nami::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    int effectiveDef = (int)ceil(target->getDef() * 70 / 100.0);
    int realDmg = max(0, this->atk - effectiveDef);
    target->receiveDamage(realDmg + target->getDef());
    if (!target->isAlive())
    {
        context.morale += 5;
        this->killInTurn = true;
    }
    context.morale = max(0, min(context.morale, 100));
    return realDmg;
}

int Nami::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    if (this->energy < 20)
    {
        return 0;
    }
    this->energy -= 20;
    int currSpe = this->atk + 40;
    this->receiveNami(target);
    context.busterCallTimer++;
    context.alarmLevel -= 5;
    context.alarmLevel = max(0, min(context.alarmLevel, 100));
    target->receiveDamage(currSpe);
    int realDmg = currSpe - target->getDef();
    if (!target->isAlive())
    {
        context.morale += 5;
        this->killInTurn = true;
    }
    context.morale = max(0, min(context.morale, 100));
    return realDmg;
}

int Nami::attack(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed())
        return 0;
    int realDmg = (int)ceil(this->atk * 50 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);
    if (!wasDestroyed && target->isDestroyed())
    {
        target->onDestroyed(context);
    }
    return realDmg;
}

int Nami::specialSkill(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed() || this->energy < 20)
        return 0;

    this->energy -= 20;
    int currDmg = this->atk + 40;
    int realDmg = (int)ceil(currDmg * 150 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);
    if (!wasDestroyed && target->isDestroyed())
        target->onDestroyed(context);
    context.busterCallTimer++;
    context.alarmLevel -= 5;
    this->energy = max(0, min(this->energy, 100));
    context.alarmLevel = max(0, min(context.alarmLevel, 100));
    return realDmg;
}
void Nami::endTurn(BattleContext &context)
{
    // TODO: implement
    if (this->killInTurn)
    {
        this->energy += 6;
        this->killInTurn = false;
    }
    this->energy = max(0, min(this->energy, 100));
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
}

int Chopper::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->atk - target->getDef() < 0)
        return 0;
    target->receiveDamage(this->atk);
    return this->atk - target->getDef();
}

int Chopper::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || !target->isStrawHat())
        return 0;
    if (this->energy < 15)
        return 0;
    this->energy -= 15;
    double temp = this->atk;
    int healAmount = ceil(35 + temp * 50 / 100.0);
    target->healFromChopper(target, healAmount);
    if (dynamic_cast<Luffy *>(target) != nullptr)
    {
        context.morale += 5;
    }
    return 0;
}

int Chopper::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || target->isDestroyed())
        return 0;

    int realDmg = this->atk;
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);

    if (!wasDestroyed && target->isDestroyed())
    {
        target->onDestroyed(context);
    }
    return realDmg;
}

void Chopper::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Usopp
 */
Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
}

int Usopp::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    double temp = this->atk;
    int currAtk = this->atk;
    if (target->getSpeed() < 50)
    {
        currAtk = ceil(temp * 120 / 100.0);
    }
    target->receiveDamage(currAtk);
    return max(0, currAtk - target->getDef());
}

int Usopp::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    if (this->energy < 16)
        return 0;

    this->energy -= 16;
    double temp = this->atk;
    int currSpe = ceil(temp * 80 / 100.0);
    target->receiveDamage(currSpe);
    this->receiveUssop(target);
    context.escapeProgress += 8;
    this->energy = max(0, min(this->energy, 100));
    context.escapeProgress = max(0, min(context.escapeProgress, 100));

    int realDmg = currSpe - target->getDef();
    if (realDmg <= 0)
        return 0;
    return realDmg;
}

int Usopp::attack(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed())
        return 0;
    int realDmg = (int)ceil(this->atk * 50 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);
    if (!wasDestroyed && target->isDestroyed())
        target->onDestroyed(context);
    return (int)ceil(this->atk * 50 / 100.0);
}

int Usopp::specialSkill(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed() || this->energy < 16)
        return 0;

    this->energy -= 16;
    int realDmg = (int)ceil(this->atk * 80 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);
    if (!wasDestroyed && target->isDestroyed())
        target->onDestroyed(context);
    context.escapeProgress += 8;
    this->energy = max(0, min(this->energy, 100));
    context.escapeProgress = max(0, min(context.escapeProgress, 100));

    return realDmg;
}

void Usopp::endTurn(BattleContext &context)
{
    // TODO: implement
    context.morale += 10;
    context.morale = max(0, min(context.morale, 100));
}

/*
 * Franky
 */
Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty) : StrawHat(name, hp, atk, def, speed, energy, bounty)

{
    // TODO: implement
}

int Franky::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    double tempDef = this->def;
    double temp = this->atk;
    int currAtk = ceil(tempDef * 30 / 100.0 + temp);
    if (target->isCP9())
    {
        double tempCurr = currAtk;
        currAtk = ceil(tempCurr * 110 / 100.0);
    }
    target->receiveDamage(currAtk);
    if (!target->isAlive())
    {
        context.morale += 5;
        this->killInTurn = true;
    }
    context.morale = max(0, min(context.morale, 100));
    return max(0, currAtk - target->getDef());
}

int Franky::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement yêu tiên dùng skill có năng lượng cao nhất
    if (target == nullptr || !target->isAlive() || this->energy < 20)
        return 0;

    int currSpe = 0;
    if (this->energy >= 30)
    {
        this->energy -= 30;
        currSpe = (int)ceil(this->atk * 120 / 100.0);
    }
    else if (this->energy < 30 && this->energy >= 20)
    {
        this->energy -= 20;
        currSpe = (int)ceil(this->atk * 180 / 100.0);
        this->receiveFranky(target);

        if (dynamic_cast<Lucci *>(target) != nullptr)
        {
            currSpe = (int)ceil(currSpe * 120 / 100.0);
        }
    }

    target->receiveDamage(currSpe);
    if (!target->isAlive())
    {
        context.morale += 5;
        this->killInTurn = true;
    }
    context.morale = max(0, min(context.morale, 100));
    return max(0, currSpe - target->getDef());
}

int Franky::attack(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed())
        return 0;
    int realDmg = (int)ceil(this->atk + this->def * 30 / 100.0);
    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);
    if (!wasDestroyed && target->isDestroyed())
        target->onDestroyed(context);
    return (int)ceil(this->atk + this->def * 30 / 100.0);
}

int Franky::specialSkill(Building *target, BattleContext &context)
{
    if (target == nullptr || target->isDestroyed() || this->energy < 20)
        return 0;

    int realDmg = 0;
    if (this->energy >= 30)
    {
        this->energy -= 30;
        realDmg = target->getHP();
    }
    else
    {
        this->energy -= 20;
        realDmg = (int)ceil(this->atk * 180 / 100.0);
    }

    bool wasDestroyed = target->isDestroyed();
    target->receiveDamage(realDmg);

    if (!wasDestroyed && target->isDestroyed())
    {
        target->onDestroyed(context);
    }

    this->energy = max(0, min(this->energy, 100));
    return realDmg;
}

void Franky::endTurn(BattleContext &context)
{
    // TODO: implement
    double percentHp = (double)this->hp / this->maxHp;
    if (percentHp > 0.70)
    {
        this->def += 5;
    }
    else if (percentHp < 0.30)
    {
        this->atk = (int)ceil(this->atk * 110 / 100.0);
    }
}

/*
 * CP9Agent
 */
CP9Agent::CP9Agent() : Character()
{
    doriki = 0;
}

CP9Agent::CP9Agent(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) : Character(name, hp, atk, def, speed, energy)
{
    // TODO: implement
    this->doriki = doriki;
}

bool CP9Agent::isCP9() const
{
    // TODO: implement
    return true;
}

string CP9Agent::str() const
{
    // TODO: implement
    return "CP9[name=" + this->name +
           ", hp=" + std::to_string(this->hp) +
           ", atk=" + std::to_string(this->atk) +
           ", def=" + std::to_string(this->def) +
           ", speed=" + std::to_string(this->speed) +
           ", energy=" + std::to_string(this->energy) +
           ", doriki=" + std::to_string(this->doriki) + "]";
}

/*
 * Lucci
 */
Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Lucci::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    int currAtk = ceil(this->atk + (this->doriki / 20.0));
    if ((double)target->getHP() / target->getMaxHp() < 0.50)
    {
        currAtk = (int)ceil(currAtk * 120 / 100.0);
    }
    target->receiveDamage(currAtk);
    return max(0, currAtk - target->getDef());
}

int Lucci::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 25)
        return 0;

    this->energy -= 25;
    int effectiveDef = (int)ceil(target->getDef() * 50 / 100.0);
    int currDmg = (int)ceil(this->atk * 280 / 100.0);

    int realDmg = currDmg - effectiveDef;
    if (realDmg < 0)
        realDmg = 0;
    target->receiveDamage(realDmg + target->getDef());

    if (!target->isAlive())
    {
        context.morale -= 10;
    }

    this->energy = max(0, min(this->energy, 100));
    context.morale = max(0, min(context.morale, 100));
    return realDmg;
}

void Lucci::endTurn(BattleContext &context)
{
    // TODO: implement
    if ((double)this->hp / this->maxHp < 0.40)
    {
        this->atk = (int)ceil(this->atk * 105 / 100.0);
    }
}

/*
 * Kaku
 */
Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Kaku::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    if (this->atk - target->getDef() <= 0)
        return 0;
    target->receiveDamage(this->atk);
    if (!target->isAlive())
    {
        context.morale -= 5;
    }
    context.morale = max(0, min(context.morale, 100));
    return this->atk - target->getDef();
}

int Kaku::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 20)
        return 0;
    this->energy -= 20;
    int currSpe = 0;
    int multiDmg[] = {120, 100, 80};
    for (int i = 0; i < 3; i++)
    {
        if (!target->isAlive())
            break;
        int rawDmg = ceil(this->atk * multiDmg[i] / 100.0);
        target->receiveDamage(rawDmg);
        currSpe += max(0, rawDmg - target->getDef());
        if (!target->isAlive())
        {
            context.morale -= 5;
            break;
        }
    }
    this->energy = max(0, min(this->energy, 100));
    context.morale = max(0, min(context.morale, 100));

    if (currSpe <= 0)
        return 0;
    return currSpe;
}

void Kaku::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Jabra
 */
Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Jabra::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    if (this->atk - target->getDef() <= 0)
        return 0;
    target->receiveDamage(this->atk);
    return this->atk - target->getDef();
}

int Jabra::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    if (this->energy < 18)
        return 0;
    this->energy -= 18;
    int currSpe = ceil(this->atk * 150 / 100.0);
    if ((double)this->hp / this->maxHp < 0.30)
    {
        currSpe = ceil(currSpe * 125 / 100.0);
    }
    target->receiveDamage(currSpe);
    int realDmg = currSpe - target->getDef();

    if (!target->isAlive())
    {
        context.morale -= 5;
    }
    context.morale = max(0, min(context.morale, 100));

    if (realDmg <= 0)
        return 0;
    return realDmg;
}

void Jabra::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Blueno
 */
Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Blueno::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    if (this->atk - target->getDef() <= 0)
        return 0;
    target->receiveDamage(this->atk);
    if (!target->isAlive())
    {
        context.morale -= 5;
    }
    context.morale = max(0, min(context.morale, 100));
    return this->atk - target->getDef();
}

int Blueno::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 15)
        return 0;

    this->energy -= 15;
    int currSpe = ceil(this->atk * 130 / 100.0);
    if ((double)this->hp / this->maxHp > 0.50)
    {
        currSpe += 20;
    }
    else
    {
        currSpe += 40;
    }
    target->receiveDamage(currSpe);
    if (!target->isAlive())
    {
        context.morale -= 5;
    }
    this->energy = max(0, min(this->energy, 100));
    context.morale = max(0, min(context.morale, 100));
    if (currSpe - target->getDef() <= 0)
        return 0;
    return currSpe - target->getDef();
}

void Blueno::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Kalifa
 */
Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Kalifa::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;

    if (this->atk - target->getDef() <= 0)
        return 0;
    target->receiveDamage(this->atk);
    return this->atk - target->getDef();
}

int Kalifa::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 18)
        return 0;
    this->energy -= 18;
    int currSpe = ceil(this->atk * 140 / 100.0);

    if (dynamic_cast<Nami *>(target) != nullptr)
    {
        context.morale -= 12;
        target->receiveDamage(currSpe);
        this->receiveKalifa(target);
    }
    else
    {
        context.morale -= 8;
        target->receiveDamage(currSpe);
        this->receiveKalifa(target);
    }

    context.morale = max(0, min(context.morale, 100));

    if (currSpe - target->getDef() <= 0)
        return 0;
    return currSpe - target->getDef();
}

void Kalifa::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Kumadori
 */
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Kumadori::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    if (target == nullptr || !target->isAlive())
        return 0;
    target->receiveDamage(this->atk);
    if (!target->isAlive())
    {
        context.morale -= 5;
    }
    context.morale = max(0, min(context.morale, 100));
    if (this->atk - target->getDef() <= 0)
    {
        return 0;
    }
    return this->atk - target->getDef();
}

int Kumadori::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 16)
        return 0;
    this->energy -= 16;
    int currSpe = ceil(30 + (this->doriki / 10.0));
    if ((double)this->hp / this->maxHp < 0.40)
    {
        currSpe += 25;
    }
    target->receiveDamage(currSpe);
    if (!target->isAlive())
    {
        context.morale -= 5;
    }
    context.morale = max(0, min(context.morale, 100));
    if (currSpe - target->getDef() <= 0)
        return 0;
    return currSpe - target->getDef();
}

void Kumadori::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Fukurou
 */
Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki) : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Fukurou::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive())
        return 0;
    target->receiveDamage(this->atk);
    if (this->atk - target->getDef() <= 0)
        return 0;
    return this->atk - target->getDef();
}

int Fukurou::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (target == nullptr || !target->isAlive() || this->energy < 14)
        return 0;
    this->energy -= 14;
    int currDmg = (int)ceil(this->atk * 130 / 100.0);
    if (target->lowestHpTag())
    {
        currDmg += 20;
    }
    int realDmg = max(0, currDmg - target->getDef());
    target->receiveDamage(currDmg);

    if (!target->isAlive())
        context.morale -= 6;
    context.morale = max(0, min(context.morale, 100));

    return realDmg;
}

void Fukurou::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Building
 */

Building::Building(string name, int hp)
{
    this->name = name;
    if (hp <= 0)
    {
        this->maxHP = 0;
        this->destroyed = true;
    }
    else
    {
        this->maxHP = hp;
        this->destroyed = false;
    }

    if (hp <= 0)
        this->hp = 0;
    else if (hp > this->maxHP)
        this->hp = this->maxHP;
    else
        this->hp = hp;
}

Building::~Building() {}

void Building::receiveDamage(int damage)
{
    this->hp -= damage;
    if (this->hp <= 0)
    {
        this->hp = 0;
        this->destroyed = true;
    }
}

bool Building::isDestroyed() const { return this->destroyed; }
void Building::onDestroyed(BattleContext &context) { return; }
string Building::str() const
{
    return "Building[name=" + this->name + ", hp=" + to_string(this->hp) +
           ", maxHP=" + to_string(this->maxHP) + ", destroyed=" +
           (this->destroyed ? "true" : "false") + "]";
}
string Building::getName() const { return this->name; }
int Building::getHP() const { return this->hp; }
int Building::getMaxHP() const { return this->maxHP; }

/*
 * MainGate
 */
MainGate::MainGate(string name, int hp) : Building(name, hp) {}

void MainGate::applyEffect(BattleContext &context)
{
    // TODO: implement
    return;
}

void MainGate::onDestroyed(BattleContext &context)
{
    // TODO: implement
    this->destroyed = true;
    context.mainGateDestroyed = true;
    context.rescueProgress += 20;
    context.morale += 5;
    context.rescueProgress = max(0, min(context.rescueProgress, 100));
    context.morale = max(0, min(context.morale, 100));
}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (this->isDestroyed())
        return;
    context.alarmLevel += 5;
    context.alarmLevel = max(0, min(context.alarmLevel, 100));
}

void Courthouse::onDestroyed(BattleContext &context)
{
    // TODO: implement
    context.alarmLevel -= 20;
    context.alarmLevel = max(0, min(context.alarmLevel, 100));
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (this->isDestroyed())
        return;
    if (context.mainGateDestroyed && !context.robinRescued)
    {
        context.rescueProgress += 5;
        context.rescueProgress = max(0, min(context.rescueProgress, 100));
        if (context.rescueProgress == 100)
        {
            context.robinRescued = true;
            context.morale += 10;
            context.morale = max(0, min(context.morale, 100));
        }
    }
}

/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp) {}

void BridgeOfHesitation::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (this->isDestroyed())
        return;
    if (context.robinRescued)
    {
        context.bridgeOpened = true;
        context.escapeProgress += 5;
        if (context.escapeProgress >= 100)
        {
            context.escapeProgress = 100;
            context.battleEnded = true;
            context.resultCode = "STRAW_HAT_WIN";
        }
    }
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

void BusterCallShip::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (!this->isDestroyed())
    {
        context.busterCallTimer -= 1;
        if (context.busterCallTimer <= 0)
        {
            context.busterCallTimer = 0;
            context.battleEnded = true;
            context.resultCode = "BUSTER_CALL";
        }
    }
}

void BusterCallShip::onDestroyed(BattleContext &context)
{
    // TODO: implement
    context.busterCallTimer += 3;
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string &filename)
{
    // TODO: implement
    this->strawHatCount = 0;
    this->buildingCount = 0;
    this->cp9Count = 0;
    this->strawHats = new Character *[7];
    this->cp9Agents = new Character *[7];
    this->buildings = new Building *[5];
    this->turnOrder = nullptr;
    this->loadFromFile(filename);
}

EniesLobbyBattle::~EniesLobbyBattle()
{
    // TODO: implement
    for (int i = 0; i < strawHatCount; i++)
    {
        delete strawHats[i];
    }
    delete[] strawHats;
    for (int i = 0; i < cp9Count; i++)
    {
        delete cp9Agents[i];
    }
    delete[] cp9Agents;
    for (int i = 0; i < buildingCount; i++)
    {
        delete buildings[i];
    }
    delete[] buildings;
    while (turnOrder != nullptr)
    {
        TurnNode *newNode = this->turnOrder;
        this->turnOrder = this->turnOrder->next;
        delete newNode;
    }
    this->turnOrder = nullptr;
}

void EniesLobbyBattle::loadFromFile(const string &filename)
{
    // TODO: implement
    ifstream file(filename);

    if (!file.is_open())
        return;

    // TODO CODE
    string l;
    while (getline(file, l))
    {
        stringstream ss(l);
        string object;
        ss >> object;
        if (object == "CONTEXT")
        {
            ss >> context.morale >> context.alarmLevel >> context.rescueProgress >> context.escapeProgress >> context.busterCallTimer >> maxTurns;
        }
        else if (object == "STRAW_HAT")
        {
            string name;
            int hp, atk, def, speed, energy;
            long long bounty;
            ss >> name >> hp >> atk >> def >> speed >> energy >> bounty;
            Character *characHat = nullptr;
            if (name == "Luffy")
                characHat = new Luffy(name, hp, atk, def, speed, energy, bounty);
            else if (name == "Zoro")
                characHat = new Zoro(name, hp, atk, def, speed, energy, bounty);
            else if (name == "Sanji")
                characHat = new Sanji(name, hp, atk, def, speed, energy, bounty);
            else if (name == "Nami")
                characHat = new Nami(name, hp, atk, def, speed, energy, bounty);
            else if (name == "Chopper")
                characHat = new Chopper(name, hp, atk, def, speed, energy, bounty);
            else if (name == "Usopp")
                characHat = new Usopp(name, hp, atk, def, speed, energy, bounty);
            else if (name == "Franky")
                characHat = new Franky(name, hp, atk, def, speed, energy, bounty);

            if (characHat)
                this->addStrawHat(characHat);
        }
        else if (object == "CP9")
        {
            string name;
            int hp, atk, def, speed, energy, doriki;
            ss >> name >> hp >> atk >> def >> speed >> energy >> doriki;
            Character *characCP9 = nullptr;
            if (name == "Lucci")
                characCP9 = new Lucci(name, hp, atk, def, speed, energy, doriki);
            else if (name == "Kaku")
                characCP9 = new Kaku(name, hp, atk, def, speed, energy, doriki);
            else if (name == "Jabra")
                characCP9 = new Jabra(name, hp, atk, def, speed, energy, doriki);
            else if (name == "Blueno")
                characCP9 = new Blueno(name, hp, atk, def, speed, energy, doriki);
            else if (name == "Kalifa")
                characCP9 = new Kalifa(name, hp, atk, def, speed, energy, doriki);
            else if (name == "Kumadori")
                characCP9 = new Kumadori(name, hp, atk, def, speed, energy, doriki);
            else if (name == "Fukurou")
                characCP9 = new Fukurou(name, hp, atk, def, speed, energy, doriki);
            if (characCP9)
                this->addCP9Agent(characCP9);
        }
        else if (object == "BUILDING")
        {
            string name;
            int hp;
            ss >> name >> hp;
            Building *build = nullptr;
            if (name == "MainGate")
                build = new MainGate(name, hp);
            else if (name == "Courthouse")
                build = new Courthouse(name, hp);
            else if (name == "TowerOfJustice")
                build = new TowerOfJustice(name, hp);
            else if (name == "BridgeOfHesitation")
                build = new BridgeOfHesitation(name, hp);
            else if (name == "BusterCallShip")
                build = new BusterCallShip(name, hp);
            if (build)
                this->addBuilding(build);
        }
    }
    file.close();
    this->buildTurnOrder();
}

void EniesLobbyBattle::addStrawHat(Character *character)
{
    // TODO: implement
    if (this->strawHatCount < 7)
    {
        this->strawHats[this->strawHatCount] = character;
        this->strawHatCount++;
    }
}

void EniesLobbyBattle::addCP9Agent(Character *character)
{
    // TODO: implement
    if (this->cp9Count < 7)
    {
        this->cp9Agents[this->cp9Count] = character;
        this->cp9Count++;
    }
}

void EniesLobbyBattle::addBuilding(Building *building)
{
    // TODO: implement
    if (this->buildingCount < 5)
    {
        this->buildings[this->buildingCount] = building;
        this->buildingCount++;
    }
}

void EniesLobbyBattle::buildTurnOrder()
{
    // TODO: implement
    TurnNode *tail = nullptr;
    for (int i = 0; i < this->strawHatCount; i++)
    {
        TurnNode *newChar = new TurnNode();
        newChar->data = this->strawHats[i];
        newChar->next = nullptr;
        if (this->turnOrder == nullptr)
        {
            this->turnOrder = newChar;
        }
        else
        {
            tail->next = newChar;
        }
        tail = newChar;
    }
    for (int i = 0; i < this->cp9Count; i++)
    {
        TurnNode *newChar = new TurnNode();
        newChar->data = this->cp9Agents[i];
        newChar->next = nullptr;
        if (this->turnOrder == nullptr)
        {
            this->turnOrder = newChar;
        }
        else
        {
            tail->next = newChar;
        }
        tail = newChar;
    }
}

void EniesLobbyBattle::runBattle()
{
    // TODO: implement
    this->checkEndCondition();
    while (!context.battleEnded && context.turnCount < maxTurns)
    {
        TurnNode *current = this->turnOrder;
        if (current == nullptr)
            break;
        Character *currChar = current->data;
        if (currChar->isAlive())
        {
            this->processTurn(currChar);
        }
        if (turnOrder->next != nullptr)
        {
            turnOrder = turnOrder->next;
            current->next = nullptr;
            TurnNode *temp = turnOrder;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = current;
        }
        this->processBuildings();
        context.nextTurn();
        this->checkEndCondition();
        if (context.turnCount >= this->maxTurns && !context.battleEnded)
        {
            context.battleEnded = true;
            context.resultCode = "TIME_OUT";
        }
    }
}

void EniesLobbyBattle::processTurn(Character *character)
{
    if (character == nullptr || !character->isAlive())
    {
        return;
    }
    Character *lowestStrawHat = nullptr;
    for (int i = 0; i < this->strawHatCount; i++)
    {
        if (this->strawHats[i]->isAlive())
        {
            if (lowestStrawHat == nullptr || this->strawHats[i]->getHP() < lowestStrawHat->getHP())
            {
                lowestStrawHat = this->strawHats[i];
            }
        }
    }
    for (int i = 0; i < this->strawHatCount; i++)
    {
        if (this->strawHats[i] != nullptr)
        {
            this->strawHats[i]->setIsLowest(this->strawHats[i] == lowestStrawHat);
        }
    }
    Character *targetChar = nullptr;
    Building *targetBuild = nullptr;
    Building *mainGate = nullptr;
    Building *courtHouse = nullptr;
    Building *busterCallShip = nullptr;
    Building *bridgeHes = nullptr;

    for (int i = 0; i < this->buildingCount; i++)
    {
        string temp = this->buildings[i]->getName();
        if (temp == "MainGate")
            mainGate = this->buildings[i];
        else if (temp == "Courthouse")
            courtHouse = this->buildings[i];
        else if (temp == "BridgeOfHesitation")
            bridgeHes = this->buildings[i];
        else if (temp == "BusterCallShip")
            busterCallShip = this->buildings[i];
    }

    bool canUseSpe = false;
    int en = character->getEnergy();
    string n = character->getName();

    if (n == "Luffy")
    {
        int minHp = ceil(character->getMaxHp() * 0.15);
        if (en >= 20 && character->getHP() >= minHp)
            canUseSpe = true;
    }
    else if (n == "Zoro" || n == "Chopper" || n == "Blueno")
    {
        if (en >= 15)
            canUseSpe = true;
    }
    else if (n == "Sanji" || n == "Jabra" || n == "Kalifa")
    {
        if (en >= 18)
            canUseSpe = true;
    }
    else if (n == "Nami" || n == "Kaku" || n == "Franky")
    {
        if (en >= 20)
            canUseSpe = true;
    }
    else if (n == "Usopp" || n == "Kumadori")
    {
        if (en >= 16)
            canUseSpe = true;
    }
    else if (n == "Lucci")
    {
        if (en >= 25)
            canUseSpe = true;
    }
    else if (n == "Fukurou")
    {
        if (en >= 14)
            canUseSpe = true;
    }
    if (character->isStrawHat())
    {

        if (character->getName() == "Chopper" && canUseSpe)
        {
            targetChar = lowestStrawHat;
        }

        if (targetChar == nullptr)
        {
            if (mainGate != nullptr && !mainGate->isDestroyed())
            {
                targetBuild = mainGate;
            }
            else if (this->context.mainGateDestroyed && this->context.alarmLevel >= 50 && courtHouse != nullptr && !courtHouse->isDestroyed())
            {
                targetBuild = courtHouse;
            }
            else if (this->context.busterCallTimer <= 5 && busterCallShip != nullptr && !busterCallShip->isDestroyed())
            {
                targetBuild = busterCallShip;
            }
            else if (!this->context.robinRescued)
            {
                for (int i = 0; i < this->cp9Count; i++)
                {
                    if (this->cp9Agents[i]->isAlive())
                    {
                        targetChar = this->cp9Agents[i];
                        break;
                    }
                }
            }
            else
            {
                if (bridgeHes != nullptr && !bridgeHes->isDestroyed())
                {
                    targetBuild = bridgeHes;
                }
                else
                {
                    for (int i = 0; i < this->cp9Count; i++)
                    {
                        if (this->cp9Agents[i]->isAlive())
                        {
                            targetChar = this->cp9Agents[i];
                            break;
                        }
                    }
                }
            }
        }
    }
    else if (character->isCP9())
    {

        for (int i = 0; i < strawHatCount; ++i)
        {
            if (this->strawHats[i]->isAlive())
            {
                targetChar = this->strawHats[i];
                break;
            }
        }
    }

    if (targetChar == nullptr && targetBuild == nullptr)
        return;

    int dmg = 0;

    if (targetChar != nullptr)
    {
        if (character->getName() == "Fukurou" && targetChar == lowestStrawHat)
        {
            targetChar->setIsLowest(true);
        }

        if (character->getName() == "Chopper" && canUseSpe)
        {
            dmg = character->specialSkill(targetChar, this->context);
        }
        else
        {
            if (canUseSpe)
                dmg = character->specialSkill(targetChar, this->context);
            else
                dmg = character->attack(targetChar, this->context);
        }
    }
    else if (targetBuild != nullptr)
    {
        if (canUseSpe)
        {
            dmg = character->specialSkill(targetBuild, context);
        }
        else
        {
            dmg = character->attack(targetBuild, context);
        }
    }
    character->endTurn(this->context);
    if (this->context.morale > 100)
        this->context.morale = 100;
    if (this->context.morale < 0)
        this->context.morale = 0;
    if (this->context.alarmLevel > 100)
        this->context.alarmLevel = 100;
    if (this->context.alarmLevel < 0)
        this->context.alarmLevel = 0;
    if (this->context.rescueProgress > 100)
        this->context.rescueProgress = 100;
    if (this->context.rescueProgress < 0)
        this->context.rescueProgress = 0;
    if (this->context.escapeProgress > 100)
        this->context.escapeProgress = 100;
    if (this->context.escapeProgress < 0)
        this->context.escapeProgress = 0;
    if (this->context.busterCallTimer < 0)
        this->context.busterCallTimer = 0;
}
void EniesLobbyBattle::processBuildings()
{
    // TODO: implement
    for (int i = 0; i < this->buildingCount; i++)
    {
        if (this->buildings[i] != nullptr && !this->buildings[i]->isDestroyed())
        {
            this->buildings[i]->applyEffect(this->context);
        }
    }
    if (this->context.morale > 100)
        this->context.morale = 100;
    if (this->context.morale < 0)
        this->context.morale = 0;

    if (this->context.alarmLevel > 100)
        this->context.alarmLevel = 100;
    if (this->context.alarmLevel < 0)
        this->context.alarmLevel = 0;

    if (this->context.rescueProgress > 100)
        this->context.rescueProgress = 100;
    if (this->context.rescueProgress < 0)
        this->context.rescueProgress = 0;

    if (this->context.escapeProgress > 100)
        this->context.escapeProgress = 100;
    if (this->context.escapeProgress < 0)
        this->context.escapeProgress = 0;

    if (this->context.busterCallTimer < 0)
        this->context.busterCallTimer = 0;
}

void EniesLobbyBattle::checkEndCondition()
{
    // TODO: implement
    if (this->context.robinRescued == true && this->context.escapeProgress >= 100)
    {
        this->context.battleEnded = true;
        this->context.resultCode = "STRAW_HAT_WIN";
        return;
    }
    if (this->context.busterCallTimer <= 0)
    {
        this->context.battleEnded = true;
        this->context.resultCode = "BUSTER_CALL";
        return;
    }
    bool allStrawDead = true;
    for (int i = 0; i < this->strawHatCount; i++)
    {
        if (this->strawHats[i] != nullptr && this->strawHats[i]->isAlive())
        {
            allStrawDead = false;
            break;
        }
    }
    if (allStrawDead && this->strawHatCount >= 0)
    {
        this->context.battleEnded = true;
        this->context.resultCode = "CP9_WIN";
        return;
    }
    bool allCp9Dead = true;
    for (int i = 0; i < this->cp9Count; i++)
    {
        if (this->cp9Agents[i] != nullptr && this->cp9Agents[i]->isAlive())
        {
            allCp9Dead = false;
        }
    }
    if (allCp9Dead && this->cp9Count >= 0)
    {
        this->context.battleEnded = true;
        this->context.resultCode = "STRAW_HAT_WIN_BY_DEFEAT_CP9";
        return;
    }
    if (this->context.turnCount >= this->maxTurns)
    {
        this->context.battleEnded = true;
        this->context.resultCode = "TIME_OUT";
        return;
    }
}

string EniesLobbyBattle::getResult() const
{
    // TODO: implement

    return this->context.resultCode + " " +
           std::to_string(this->context.turnCount) + " " +
           std::to_string(this->context.morale) + " " +
           std::to_string(this->context.alarmLevel) + " " +
           std::to_string(this->context.rescueProgress) + " " +
           std::to_string(this->context.escapeProgress) + " " +
           std::to_string(this->context.busterCallTimer)
}

// Hello, welcome to my youtube chanel

// new cmt practice

// adding feature A

// adding feature B