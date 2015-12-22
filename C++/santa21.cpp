#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Creature {
    public:
        int hp;
        int dam;
        int arm;

        Creature(int h, int d, int a) : hp{h}, dam{d}, arm{a} {}

        virtual void getHit(const int& hurt) {
            hp -= std::max(1, hurt - arm);
        }

        virtual void hit(Creature& c) {
//            std::cout << "Boss deals " << dam << " flat damage";
            c.getHit(dam);
//            std::cout << "; player goes down to " << c.hp << std::endl;
        }
};

class Item {
    public:
        std::string name;
        int cost, dam, arm;
        Item(std::string n, int c, int d, int a) : name{n}, cost{c}, dam{d}, arm{a} {}
};

class Player : Creature {
    public:

        Player(int h, int d, int a) : Creature(h, d, a)  { }

        std::vector<Item> items;

        void addItem(const Item& i) {
            items.push_back(i);
        }

        virtual void hit(Creature& c) {
            int d = dam;
            for (Item i: items) {
                d += i.dam;
            }

//            std::cout << "Player deals " << d << " flat damage";
            c.getHit(d);
//            std::cout << "; boss goes down to " << c.hp << " health" << std::endl;
        }

        virtual void getHit(const int& hurt) {
            int armour = arm;

            for (Item i: items) {
                armour += i.arm;
            }
            hp -= std::max(1, hurt - armour);
        }

        int calculateCost() const {
            int c = 0;
            for (Item i : items) {
                c += i.cost;
            }
            return c;
        }


        friend std::ostream& operator<<(std::ostream& os, const Player& p) {
            os << "I have (HP: " << p.hp << ", DM: " << p.dam << ", ARM: " << p.arm << ")" << std::endl <<
                  "\tWeapon: " << p.items[0].name << " (C: " << p.items[0].cost << ", DM: " << p.items[0].dam << ", ARM: " << p.items[0].arm << ")" << std::endl <<
                  "\tArmour: " << p.items[1].name << " (C: " << p.items[1].cost << ", DM: " << p.items[1].dam << ", ARM: " << p.items[1].arm << ")" << std::endl <<
                  "\tRing1:  " << p.items[2].name << " (C: " << p.items[2].cost << ", DM: " << p.items[2].dam << ", ARM: " << p.items[2].arm << ")" << std::endl <<
                  "\tRing2:  " << p.items[3].name << " (C: " << p.items[3].cost << ", DM: " << p.items[3].dam << ", ARM: " << p.items[3].arm << ")" << std::endl;

            return os;
        }

        bool fight(Creature c) {
            bool myTurn = true;
            while (hp > 0 && c.hp > 0) {
                if (myTurn) {
                    hit(c);
                } else {
                    c.hit(*this);
                }
                myTurn = !myTurn;
            }

            if (hp > 0) {
                return true;
            } else {
                return false;
            }
        }
};

int main() {
    std::vector<Item> weapons, armors, rings;

    weapons.push_back(Item("Dagger", 8, 4, 0));
    weapons.push_back(Item("Shortsword", 10, 5, 0));
    weapons.push_back(Item("Warhammer", 25, 6, 0));
    weapons.push_back(Item("Longsword", 40, 7, 0));
    weapons.push_back(Item("Greataxe", 74, 8, 0));

    armors.push_back(Item("", 0, 0, 0));
    armors.push_back(Item("Leather", 13, 0, 1));
    armors.push_back(Item("Chainmail", 31, 0, 2));
    armors.push_back(Item("Splintmail", 53, 0, 3));
    armors.push_back(Item("Bandedmail", 75, 0, 4));
    armors.push_back(Item("Platemail", 102, 0, 5));

    rings.push_back(Item("", 0, 0, 0));
    rings.push_back(Item("Damage +1", 25, 1, 0));
    rings.push_back(Item("Damage +2", 50, 2, 0));
    rings.push_back(Item("Damage +3", 100, 3, 0));
    rings.push_back(Item("Defense +1", 20, 0, 1));
    rings.push_back(Item("Defense +2", 40, 0, 2));
    rings.push_back(Item("Defense +3", 80, 0, 3));

    Player me(10, 0, 0);
    Creature boss(20, 2, 6);

    int max = 0;
    for (Item weapon : weapons) {
        for (Item armor : armors) {
            for (Item ring1 : rings) {
                for (Item ring2 : rings) {

                    Player me(100, 0, 0);
                    Creature boss(100, 8, 2);
                    me.addItem(weapon);
                    me.addItem(armor);
                    me.addItem(ring1);
                    me.addItem(ring2);

                    if (me.fight(boss) == false) {
                        if (me.calculateCost() > max) {
                            max = me.calculateCost();
                        }
                    }
                }
            }
        }
    }

    std::cout << "Min cost was " << max << std::endl;
}
