#include <SFML/Graphics.hpp>
#include <iostream>
#include "global.h"

using namespace std;

sf::Event Event;
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

Images tableImage("images/table.bmp");
Images piese[12];

int table[8][8]=
{
    { 1, 2, 3, 4, 6, 3, 2, 1},
    { 5, 5, 5, 5, 5, 5, 5, 5},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    {-5,-5,-5,-5,-5,-5,-5,-5},
    {-1,-2,-3,-4,-6,-3,-2,-1}
};

int piecesInd[12]={1,2,3,6,4,5,-1,-2,-3,-6,-4,-5};

bool chessMate[8][8],kingMate[8][8];

int i,j,k,h,PIESA,pTurn=1,nry,nrx,ind1,ind2;
sf::Vector2i initialMouse,mouse,select1,select2;
bool ok1=0,ok2=1,ok3=0;

struct Pion
{
    int x,y;
    bool first;
    Pion(){first=true;};
}blackPioni[8],whitePioni[8];

int main()
{
    piese[0].loadImage("images/whiteTura.bmp");
    piese[1].loadImage("images/whiteCal.bmp");
    piese[2].loadImage("images/whiteNebun.bmp");
    piese[3].loadImage("images/whiteRege.bmp");
    piese[4].loadImage("images/whiteRegina.bmp");
    piese[5].loadImage("images/whitePion.bmp");

    piese[6].loadImage("images/blackTura.bmp");
    piese[7].loadImage("images/blackCal.bmp");
    piese[8].loadImage("images/blackNebun.bmp");
    piese[9].loadImage("images/blackRege.bmp");
    piese[10].loadImage("images/blackRegina.bmp");
    piese[11].loadImage("images/blackPion.bmp");

    for(i=0;i<8;i++)
    {
        blackPioni[i].x=i;
        blackPioni[i].y=1;
        whitePioni[i].x=i;
        whitePioni[i].y=6;
    }
    while(window.isOpen())
    {
        while(window.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
                window.close();

            if(Event.type==sf::Event::MouseButtonPressed)
                if(Event.mouseButton.button==sf::Mouse::Left)
                {
                    initialMouse=sf::Mouse::getPosition(window);
                    select1.x=initialMouse.x/100;
                    select1.y=initialMouse.y/100;

                    PIESA=table[select1.y][select1.x];
                }
            if(Event.type==sf::Event::MouseButtonReleased)
                if(Event.mouseButton.button==sf::Mouse::Left)
                {
                    initialMouse=sf::Mouse::getPosition(window);
                    select2.x=initialMouse.x/100;
                    select2.y=initialMouse.y/100;
                    if(table[select2.y][select2.x]!=9)///DACA NU MANANCA REGELE
                    {
                        cout<<PIESA<<endl;
                        if(PIESA==1&&pTurn==1)///tura
                        {
                            if(select1.x==select2.x&& select1.y!=select2.y)
                            {
                                bool ok=0;
                                for(i=select1.y+1;i<select2.y;i++)
                                    if(table[i][select1.x]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=1&&table[select2.y][select2.x]<=5)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(select1.y==select2.y&& select1.x!=select2.x)
                            {
                                bool ok=0;
                                for(i=select1.x+1;i<select2.x;i++)
                                    if(table[select1.y][i]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=1&&table[select2.y][select2.x]<=5)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                        }
                        else if(PIESA==-1&&pTurn==-1)///tura
                        {
                            if(select1.x==select2.x&& select1.y!=select2.y)
                            {
                                bool ok=0;
                                for(i=select1.y+1;i<select2.y;i++)
                                    if(table[i][select1.x]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=-5&&table[select2.y][select2.x]<=-1)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(select1.y==select2.y&& select1.x!=select2.x)
                            {
                                bool ok=0;
                                for(i=select1.x+1;i<select2.x;i++)
                                    if(table[select1.y][i]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=-5&&table[select2.y][select2.x]<=-1)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                        }
                        else if(PIESA==2&&pTurn==1)///cal
                        {
                            if((table[select2.y][select2.x]>=-5&&table[select2.y][select2.x]<=-1)||table[select2.y][select2.x]==0)
                            {
                                if((select1.x-1==select2.x&&select1.y-2==select2.y)||
                                   (select1.x+1==select2.x&&select1.y-2==select2.y)||
                                   (select1.x+2==select2.x&&select1.y-1==select2.y)||
                                   (select1.x+2==select2.x&&select1.y+1==select2.y)||
                                   (select1.x+1==select2.x&&select1.y+2==select2.y)||
                                   (select1.x-1==select2.x&&select1.y+2==select2.y)||
                                   (select1.x-2==select2.x&&select1.y+1==select2.y)||
                                   (select1.x-2==select2.x&&select1.y-1==select2.y))
                                    {
                                        table[select1.y][select1.x]=0;
                                        table[select2.y][select2.x]=PIESA;
                                        pTurn=-pTurn;
                                    }
                            }
                        }
                        else if(PIESA==-2&&pTurn==-1)///cal
                        {
                            if((table[select2.y][select2.x]>=1&&table[select2.y][select2.x]<=5)||table[select2.y][select2.x]==0)
                            {
                                if((select1.x-1==select2.x&&select1.y-2==select2.y)||
                                   (select1.x+1==select2.x&&select1.y-2==select2.y)||
                                   (select1.x+2==select2.x&&select1.y-1==select2.y)||
                                   (select1.x+2==select2.x&&select1.y+1==select2.y)||
                                   (select1.x+1==select2.x&&select1.y+2==select2.y)||
                                   (select1.x-1==select2.x&&select1.y+2==select2.y)||
                                   (select1.x-2==select2.x&&select1.y+1==select2.y)||
                                   (select1.x-2==select2.x&&select1.y-1==select2.y))
                                    {
                                        table[select1.y][select1.x]=0;
                                        table[select2.y][select2.x]=PIESA;
                                        pTurn=-pTurn;
                                    }
                            }
                        }
                        else if(PIESA==3&&pTurn==1)///nebun
                        {
                            nry=select2.y-select1.y;
                            nrx=select2.x-select1.x;
                            if(nry>0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i++,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x+1;i!=select2.y&&j!=select2.x;i++,j++)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry>0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i++,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x-1;i!=select2.y&&j!=select2.x;i++,j--)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i--,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x+1;i!=select2.y&&j!=select2.x;i--,j++)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i--,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x-1;i!=select2.y&&j!=select2.x;i--,j--)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                        }
                        else if(PIESA==-3&&pTurn==-1)///nebun
                        {
                            nry=select2.y-select1.y;
                            nrx=select2.x-select1.x;
                            if(nry>0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i++,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x+1;i!=select2.y&&j!=select2.x;i++,j++)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry>0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i++,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x-1;i!=select2.y&&j!=select2.x;i++,j--)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i--,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x+1;i!=select2.y&&j!=select2.x;i--,j++)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i--,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x-1;i!=select2.y&&j!=select2.x;i--,j--)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                        }
                        else if(PIESA==4&&pTurn==1)///regina
                        {
                            if(select1.x==select2.x&& select1.y!=select2.y)
                            {
                                bool ok=0;
                                for(i=select1.y+1;i<select2.y;i++)
                                    if(table[i][select1.x]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=1&&table[select2.y][select2.x]<=5)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(select1.y==select2.y&& select1.x!=select2.x)
                            {
                                bool ok=0;
                                for(i=select1.x+1;i<select2.x;i++)
                                    if(table[select1.y][i]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=1&&table[select2.y][select2.x]<=5)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            nry=select2.y-select1.y;
                            nrx=select2.x-select1.x;
                            if(nry>0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i++,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x+1;i!=select2.y&&j!=select2.x;i++,j++)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry>0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i++,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x-1;i!=select2.y&&j!=select2.x;i++,j--)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i--,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x+1;i!=select2.y&&j!=select2.x;i--,j++)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i--,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x-1;i!=select2.y&&j!=select2.x;i--,j--)
                                        if(!((table[i][j]>=-5 && table[i][j]<=-1) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                        }
                        else if(PIESA==-4&&pTurn==-1)///regina
                        {
                            if(select1.x==select2.x&& select1.y!=select2.y)
                            {
                                bool ok=0;
                                for(i=select1.y+1;i<select2.y;i++)
                                    if(table[i][select1.x]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=-5&&table[select2.y][select2.x]<=-1)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(select1.y==select2.y&& select1.x!=select2.x)
                            {
                                bool ok=0;
                                for(i=select1.x+1;i<select2.x;i++)
                                    if(table[select1.y][i]!=0)
                                        {ok=1;break;}
                                if(table[select2.y][select2.x]>=-5&&table[select2.y][select2.x]<=-1)
                                    ok=1;
                                if(ok==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            nry=select2.y-select1.y;
                            nrx=select2.x-select1.x;
                            if(nry>0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i++,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x+1;i!=select2.y&&j!=select2.x;i++,j++)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry>0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y+1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i++,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y+1,j=select1.x-1;i!=select2.y&&j!=select2.x;i++,j--)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx>0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x+1;i>=0&&i<8&&j>=0&&j<8;i--,j++)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x+1;i!=select2.y&&j!=select2.x;i--,j++)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                            if(nry<0&&nrx<0)
                            {
                                ok1=0,ok2=0;
                                for(i=select1.y-1,j=select1.x-1;i>=0&&i<8&&j>=0&&j<8;i--,j--)
                                    if(i==select2.y&&j==select2.x)
                                        ok1=1;
                                if(ok1==1)
                                    for(i=select1.y-1,j=select1.x-1;i!=select2.y&&j!=select2.x;i--,j--)
                                        if(!((table[i][j]>=1 && table[i][j]<=5) || table[i][j]==0))
                                                {ok2=1;break;}
                                if(ok1==1&&ok2==0)
                                {
                                    table[select1.y][select1.x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    pTurn=-pTurn;
                                }
                            }
                        }
                        if(PIESA==5&&pTurn==1)///pion
                        {
                            for(i=0;i<8;i++)
                                if(blackPioni[i].x==select1.x && blackPioni[i].y==select1.y)
                                    break;
                            if(blackPioni[i].first==true)
                            {
                                if((blackPioni[i].x==select2.x && blackPioni[i].y+2==select2.y && table[select2.y][select2.x]==0)||
                                   (blackPioni[i].x==select2.x && blackPioni[i].y+1==select2.y && table[select2.y][select2.x]==0))
                                    {
                                        table[blackPioni[i].y][blackPioni[i].x]=0;
                                        table[select2.y][select2.x]=PIESA;
                                        blackPioni[i].y=select2.y;
                                        blackPioni[i].first=false;
                                        pTurn=-pTurn;
                                    }
                            }
                            else if(blackPioni[i].x==select2.x && blackPioni[i].y+1==select2.y &&
                                    table[select2.y][select2.x]==0)
                                {
                                    table[blackPioni[i].y][blackPioni[i].x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    blackPioni[i].y=select2.y;
                                    pTurn=-pTurn;
                                }
                            else if(blackPioni[i].x+1==select2.x    && blackPioni[i].y+1==select2.y &&
                                    table[select2.y][select2.x]>=-5 && table[select2.y][select2.x]<=-1)
                                {
                                    table[blackPioni[i].y][blackPioni[i].x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    blackPioni[i].y=select2.y;
                                    blackPioni[i].x=select2.x;
                                    pTurn=-pTurn;
                                }
                            else if(blackPioni[i].x-1==select2.x    && blackPioni[i].y+1==select2.y &&
                                    table[select2.y][select2.x]>=-5 && table[select2.y][select2.x]<=-1)
                                {
                                    table[blackPioni[i].y][blackPioni[i].x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    blackPioni[i].y=select2.y;
                                    blackPioni[i].x=select2.x;
                                    pTurn=-pTurn;
                                }
                        }
                        if(PIESA==-5&&pTurn==-1)
                        {
                            for(i=0;i<8;i++)
                                if(whitePioni[i].x==select1.x && whitePioni[i].y==select1.y)
                                    break;
                            if(whitePioni[i].first==true)
                            {
                                if((whitePioni[i].x==select2.x && whitePioni[i].y-2==select2.y && table[select2.y][select2.x]==0)||
                                   (whitePioni[i].x==select2.x && whitePioni[i].y-1==select2.y && table[select2.y][select2.x]==0))
                                    {
                                        table[whitePioni[i].y][whitePioni[i].x]=0;
                                        table[select2.y][select2.x]=PIESA;
                                        whitePioni[i].y=select2.y;
                                        whitePioni[i].first=false;
                                        pTurn=-pTurn;
                                    }
                            }
                            else if(whitePioni[i].x==select2.x && whitePioni[i].y-1==select2.y &&
                                    table[select2.y][select2.x]==0)
                                {
                                    table[whitePioni[i].y][whitePioni[i].x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    whitePioni[i].y=select2.y;
                                    pTurn=-pTurn;
                                }
                            else if(whitePioni[i].x+1==select2.x    && whitePioni[i].y-1==select2.y &&
                                    table[select2.y][select2.x]>=1 && table[select2.y][select2.x]<=5)
                                {
                                    table[whitePioni[i].y][whitePioni[i].x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    whitePioni[i].y=select2.y;
                                    whitePioni[i].x=select2.x;
                                    pTurn=-pTurn;
                                }
                            else if(whitePioni[i].x-1==select2.x    && whitePioni[i].y-1==select2.y &&
                                    table[select2.y][select2.x]>=1 && table[select2.y][select2.x]<=5)
                                {
                                    table[whitePioni[i].y][whitePioni[i].x]=0;
                                    table[select2.y][select2.x]=PIESA;
                                    whitePioni[i].y=select2.y;
                                    whitePioni[i].x=select2.x;
                                    pTurn=-pTurn;
                                }

                        }
                        else if(PIESA==6&&pTurn==1)
                        {
                            for(i=0;i<8;i++)
                                for(j=0;j<8;j++)
                                {
                                    chessMate[i][j]=0;
                                    kingMate[i][j]=0;
                                }
                            for(i=0;i<8;i++)
                                for(j=0;j<8;j++)
                                {
                                    if(table[i][j]==-1)///TURA
                                    {
                                        for(k=j+1;k<8&&table[i][k]==0;k++)
                                            chessMate[i][k]=1;
                                        for(k=j-1;k>0&&table[i][k]==0;k--)
                                            chessMate[i][k]=1;
                                        for(k=i+1;k<8&&table[k][j]==0;k++)
                                            chessMate[k][j]=1;
                                        for(k=i-1;k>0&&table[k][j]==0;k--)
                                            chessMate[k][j]=1;
                                    }
                                    if(table[i][j]==-2)///CAL
                                    {
                                        ind1=i-1;ind2=j-2;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                        ind1=i+1;ind2=j-2;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                        ind1=i+2;ind2=j-1;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                        ind1=i+2;ind2=j+1;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                        ind1=i+1;ind2=j+2;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                        ind1=i-1;ind2=j+2;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                        ind1=i-2;ind2=j+1;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                        ind1=i-2;ind2=j-1;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                chessMate[ind1][ind2]=1;
                                    }
                                    if(table[i][j]==-3)///NEBUN
                                    {
                                        for(k=i+1,h=j+1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k++,h++)
                                            chessMate[k][h]=1;
                                        for(k=i+1,h=j-1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k++,h--)
                                            chessMate[k][h]=1;
                                        for(k=i-1,h=j+1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k--,h++)
                                            chessMate[k][h]=1;
                                        for(k=i-1,h=j-1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k--,h--)
                                            chessMate[k][h]=1;
                                    }
                                    if(table[i][j]==-4)///REGINA
                                    {
                                        for(k=j+1;k<8&&table[i][k]==0;k++)
                                            chessMate[i][k]=1;
                                        for(k=j-1;k>0&&table[i][k]==0;k--)
                                            chessMate[i][k]=1;
                                        for(k=i+1;k<8&&table[k][j]==0;k++)
                                            chessMate[k][j]=1;
                                        for(k=i-1;k>0&&table[k][j]==0;k--)
                                            chessMate[k][j]=1;
                                        for(k=i+1,h=j+1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k++,h++)
                                            chessMate[k][h]=1;
                                        for(k=i+1,h=j-1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k++,h--)
                                            chessMate[k][h]=1;
                                        for(k=i-1,h=j+1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k--,h++)
                                            chessMate[k][h]=1;
                                        for(k=i-1,h=j-1;k>=0&&k<8&&h>=0&&h<8&&table[k][h]==0;k--,h--)
                                            chessMate[k][h]=1;
                                    }
                                    if(table[i][j]==-5)///PION
                                    {
                                        ind1=i-1;ind2=j-1;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            chessMate[ind1][ind2]=1;
                                        ind1=i-1;ind2=j+1;
                                        if(ind1>=0&&ind1<8&&ind2>=0&&ind2<8)
                                            chessMate[ind1][ind2]=1;
                                    }
                                    if(table[i][j]==-6)///REGE
                                    {
                                        ind1=i+1;ind2=j+1;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                        ind1=i-1;ind2=j+1;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                        ind1=i+1;ind2=j-1;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                        ind1=i-1;ind2=j-1;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                        ind1=i;ind2=j+1;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                        ind1=i;ind2=j-1;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                        ind1=i+1;ind2=j;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                        ind1=i-1;ind2=j;
                                        if(ind1>0&&ind1<8&&ind2>0&&ind2<8)
                                            if(table[ind1][ind2]==0)
                                                kingMate[ind1][ind2]=1;
                                    }
                                }
                            bool sahMat=true;
                            if((select1.y+1==select2.y&&select1.x+1==select2.x)||
                               (select1.y+1==select2.y&&select1.x-1==select2.x)||
                               (select1.y-1==select2.y&&select1.x+1==select2.x)||
                               (select1.y-1==select2.y&&select1.x-1==select2.x)||
                               (select1.y+1==select2.y&&select1.x  ==select2.x)||
                               (select1.y-1==select2.y&&select1.x  ==select2.x)||
                               (select1.y  ==select2.y&&select1.x+1==select2.x)||
                               (select1.y  ==select2.y&&select1.x-1==select2.x))
                                {
                                    if(chessMate[select2.y][select2.x]==0&&kingMate[select2.y][select2.x]==0)
                                    {
                                        sahMat=false;
                                        table[select1.y][select1.x]=0;
                                        table[select2.y][select2.x]=PIESA;
                                    }
                                }
                            //if(sahMat==true)
                                //cout<<"CHESS MATE";
                        }

                    }
                }
        }
        window.clear();
        window.draw(tableImage.sprite);
        for(i=0;i<8;i++)
            for(j=0;j<8;j++)
            {
                for(k=0;k<12;k++)
                    if(piecesInd[k]==table[i][j])
                    {
                        piese[k].sprite.setPosition(100*j+27,100*i+27);
                        window.draw(piese[k].sprite);
                    }
            }
        window.display();
    }
    return 0;
}
