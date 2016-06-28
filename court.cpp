#include "court.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <unistd.h>

Court::Court(int w, int h, Ball newball, std::array<Team,2>& teams)
    : width(w), height(h),  clubs(teams), ball(newball)
{
    clubs[0].addplayer({w/6, h/6},"Bartosz Kurek",'1');     //rectangular positions
    clubs[0].addplayer({w/6, 4*h/10},"Fabian Drzyzga",'2');
    clubs[0].addplayer({w/2, 4*h/10},"Dmytro Pashytskyy",'3');
    clubs[0].addplayer({5*w/6, 4*h/10},"Thomas Jaeschke",'4');
    clubs[0].addplayer({5*w/6, h/6},"Piotr Nowakowski",'5');
    clubs[0].addplayer({w/2, h/6},"Olieg Achrem",'6');

//    clubs[0].addplayer({w/10, 0},"Bartosz Kurek",'1');    //serving positions
//    clubs[0].addplayer({w/6, h/2-1},"Thomas Jaeschke",'2');
//    clubs[0].addplayer({w/2, h/2-1},"Dmytro Pashytskyy",'3');
//    clubs[0].addplayer({5*w/6, h/2-1},"Fabian Drzyzga",'4');
//    clubs[0].addplayer({5*w/6, h/6},"Olieg Achrem",'5');
//    clubs[0].addplayer({w/2, 1*h/10},"Piotr Nowakowski",'6');

    clubs[1].addplayer({5*w/6, 5*h/6},"Maxim Mikhaylov",'1');
    clubs[1].addplayer({5*w/6, 6*h/10},"Aleksandr Butko",'2');
    clubs[1].addplayer({w/2, 6*h/10},"Andrey Aschev",'3');
    clubs[1].addplayer({w/6, 6*h/10},"Matthew Anderson",'4');
    clubs[1].addplayer({w/6, 5*h/6},"Aleksandr Gutsalyuk",'5');
    clubs[1].addplayer({w/2, 5*h/6},"Wilfredo Leon",'6');

//    clubs[1].addplayer({9*w/10, 9*h/10},"Maxim Mikhaylov",'1');   //receiving position
//    clubs[1].addplayer({w/6, 5*h/6},"Matthew Anderson",'2');
//    clubs[1].addplayer({w/10, 7*h/10},"Andrey Aschev",'3');
//    clubs[1].addplayer({w/10, 6*h/10},"Aleksandr Butko",'4');
//    clubs[1].addplayer({w/2, 5*h/6},"Wilfredo Leon",'5');
//    clubs[1].addplayer({5*w/6, 5*h/6},"Aleksandr Gutsalyuk",'6');

    court.reserve(width);
    for (int i=0; i<width; ++i)
    {
        court.push_back(std::vector<char> (height,' ') );
        court[i].front() = '-';
        court[i].back() = '-';
        court[i][court[i].size()/2] = '=';
        court[i][court[i].size()/2 + court[i].size()/6] = '-';
        court[i][court[i].size()/2 - court[i].size()/6] = '-';
    }
    initialcourt = court;
}

std::ostream& operator << (std::ostream& output, Court& courtclass)
{
    output << courtclass.clubs[0].getname() << "\t      " << courtclass.clubs[0].getpoints();
    output << ":";
    output << courtclass.clubs[1].getpoints() << "\t   " << courtclass.clubs[1].getname() << "\n\n";
    output << "\t" << courtclass.clubs[0].getsets() << "\t\t\t\t" << courtclass.clubs[1].getsets() << "\n\n";
    for(std::size_t i=0; i<courtclass.clubs[0].getplayers().size(); ++i)  //printing teams
    {
        output << courtclass.clubs[0].getplayers()[i] << "\t\t"
                            << courtclass.clubs[1].getplayers()[i] << '\n';
    }

    output << std::endl;
    for (int i=0; i<courtclass.height; ++i)
    {
        for (int j=0; j<courtclass.width; ++j)
        {
            if (j==0)
            {
                output << "\t|" << " ";
            }
            else if (j == courtclass.width-1)
            {
                output << "|" << " ";
            }
            else
            {
                output << courtclass.court[j][i] << " ";
            }
        }
        output << std::endl;
    }
    return output;
}

void Court::setposition (std::pair<int,int> position, char sym)
{
    court[position.first][position.second] = sym;
}

void Court::update ()
{
    court = initialcourt;
    for (std::size_t j=0; j<clubs.size(); ++j)
    {
        for (std::size_t i=0; i<clubs[j].getplayers().size(); ++i)
        {
            setposition(clubs[j].getplayers()[i].getposition(), clubs[j].getplayers()[i].getsymbol());
        }
    }

    if (ball.getposition().first >= 0 && ball.getposition().first < width
            && ball.getposition().second >= 0 && ball.getposition().second < height)
    {
        setposition(ball.getposition(),ball.getsymbol());
    }

    std::cout << *this;

    ball.update();

    usleep(0.2*1000000);        //delay (k*1s)
}

Team& Court::getteam(int teamID)
{
    return clubs[teamID];
}

Ball& Court::getball()
{
    return ball;
}
