#ifndef OPPOSITESPIKER_H
#define OPPOSITESPIKER_H
#include "player.h"

class OppositeSpiker : public Player
{
    public:
        OppositeSpiker(std::pair<int,int>newposition, std::string sur, std::string newteam, char sym);
        virtual std::pair<std::pair<double,double>,int> doaction(std::array<Team,2>& teams, int myside, int last, int &atackteam) final;
};

#endif // OPPOSITESPIKER_H
