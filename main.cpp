#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <graphics.h>
using namespace std;
ifstream f("Save.txt");
bool sh=1,snb=0;
int score=0, sn_ln=3, HighScore[10], current_lvl,s;
void Menu();
void Menu2();
void select_level();
enum limba
{
    RO,
    EN
}lb=EN;
enum dirrection
{
    up,
    down,
    lefty,
    righty
}dr;
enum Status
{
    air,
    apple,
    shorten,
    block,
    snake_body,
    snake_head
};
struct Grid
{
    Status st;
    struct{int x,y;}colt[2];
}Patrat[15][20];
struct snake
{
    int i,j;
}Snake[300],t,v,zero,mar;
void read_file()
{
    for(int k=0;k<10;k++)
        f>>HighScore[k];
    f.close();
}
void init()
{
    zero.i=0;
    zero.j=0;
    Patrat[0][0].colt[0].x=0;
    Patrat[0][0].colt[0].y=0;
    Patrat[0][0].colt[1].x=40;
    Patrat[0][0].colt[1].y=40;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<20;j++)
        {
            Patrat[i][j].st=air;
            if(j!=0)
            {
                Patrat[i][j].colt[0].x=Patrat[i][j-1].colt[0].x+40;
                Patrat[i][j].colt[0].y=Patrat[i][j-1].colt[0].y;
                Patrat[i][j].colt[1].x=Patrat[i][j-1].colt[1].x+40;
                Patrat[i][j].colt[1].y=Patrat[i][j-1].colt[1].y;
            }
            if(j==0&&i!=0)
            {
                Patrat[i][j].colt[0].x=Patrat[i-1][j].colt[0].x;
                Patrat[i][j].colt[0].y=Patrat[i-1][j].colt[0].y+40;
                Patrat[i][j].colt[1].x=Patrat[i-1][j].colt[1].x;
                Patrat[i][j].colt[1].y=Patrat[i-1][j].colt[1].y+40;
            }
        }
    }
}
void in_game_frame()
{
    setcolor(WHITE);
    line(801,0,801,600);
    settextstyle(3, HORIZ_DIR,3);
    if(lb==EN)outtextxy(900-textwidth("SCORE")/2,100,"SCORE");
    else outtextxy(900-textwidth("SCOR")/2,100,"SCOR");
    char arr[10];
    if(!snb)
    {
        outtextxy(900-textwidth("HIGHSCORE")/2,200,"HIGHSCORE");
        sprintf(arr, "%d", HighScore[current_lvl-1]);
        outtextxy(900-textwidth(arr)/2,250,arr);
    }
    sprintf(arr, "%d", score);
    outtextxy(900-textwidth(arr)/2,150,arr);
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<20;j++)
        {
            switch(Patrat[i][j].st)
            {
                case apple:
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(Patrat[i][j].colt[0].x,Patrat[i][j].colt[0].y,Patrat[i][j].colt[1].x,Patrat[i][j].colt[1].y);
                    setfillstyle(SOLID_FILL, RED);
                    bar(Patrat[i][j].colt[0].x+10,Patrat[i][j].colt[0].y+10,Patrat[i][j].colt[1].x-10,Patrat[i][j].colt[1].y-10);
                    break;
                }
                case shorten:
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(Patrat[i][j].colt[0].x,Patrat[i][j].colt[0].y,Patrat[i][j].colt[1].x,Patrat[i][j].colt[1].y);
                    setfillstyle(SOLID_FILL, YELLOW);
                    bar(Patrat[i][j].colt[0].x+10,Patrat[i][j].colt[0].y+10,Patrat[i][j].colt[1].x-10,Patrat[i][j].colt[1].y-10);
                    break;
                }
                case snake_body:
                {
                    setfillstyle(SOLID_FILL, GREEN);
                    bar(Patrat[i][j].colt[0].x,Patrat[i][j].colt[0].y,Patrat[i][j].colt[1].x,Patrat[i][j].colt[1].y);
                    break;
                }
                case snake_head:
                {
                    setfillstyle(SOLID_FILL, GREEN);
                    bar(Patrat[i][j].colt[0].x,Patrat[i][j].colt[0].y,Patrat[i][j].colt[1].x,Patrat[i][j].colt[1].y);

                    break;

                }
                case air:
                {
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(Patrat[i][j].colt[0].x,Patrat[i][j].colt[0].y,Patrat[i][j].colt[1].x,Patrat[i][j].colt[1].y);
                }
            }
            setfillstyle(SOLID_FILL,RED);
            if(dr==up)
            {
                if(Patrat[Snake[0].i-2][Snake[0].j-1].st!=block)
                {
                    if(Snake[0].i-1==0)bar(Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x+19,600,Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x+21,590);
                    else bar(Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x+19,Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].y,Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x+21,Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].y-10);
                }
            }
            if(dr==down)
            {
                if(Patrat[Snake[0].i][Snake[0].j-1].st!=block)
                {
                    if(Snake[0].i-1==14)bar(Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x+19,10,Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x+21,0);
                    else bar(Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].x-19,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].x-21,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y+10);
                }
            }
            if(dr==righty)
            {
                if(Patrat[Snake[0].i-1][Snake[0].j].st!=block)
                {
                    if(Snake[0].j-1==19)bar(0,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-19,10,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-21);
                    else bar(Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].x,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-19,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].x+10,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-21);
                }
            }
            if(dr==lefty)
            {
                if(Patrat[Snake[0].i-1][Snake[0].j-2].st!=block)
                {
                    if(Snake[0].j-1==0)bar(800,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-19,790,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-21);
                    else bar(Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-19,Patrat[Snake[0].i-1][Snake[0].j-1].colt[0].x-10,Patrat[Snake[0].i-1][Snake[0].j-1].colt[1].y-21);
                }
            }
        }

    }

}
int random(int x)
{
    return rand()%x;
}
void bricks()
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(Patrat[i][j].st==block)
            readimagefile("Brick.jpg",Patrat[i][j].colt[0].x,Patrat[i][j].colt[0].y,Patrat[i][j].colt[1].x,Patrat[i][j].colt[1].y);
        }
    }
}
void save()
{
    ofstream g;
    g.open("Save.txt",ofstream::out | ofstream::trunc);
    for(int k=0;k<10;k++)
    {
        g<<HighScore[k]<<endl;
    }
    g.close();
}
void init_lvl1()
{
    score=0;
    current_lvl=1;
    dr=up;
    Snake[0].i=13;
    Snake[0].j=3;
    Patrat[12][2].st=snake_head;
    Snake[1].i=14;
    Snake[1].j=3;
    Patrat[13][2].st=snake_body;
    Snake[2].i=15;
    Snake[2].j=3;
    Patrat[14][2].st=snake_body;
}
void init_lvl2()
{
    score=0;
    current_lvl=2;
    dr=up;
    Snake[0].i=12;
    Snake[0].j=3;
    Patrat[11][2].st=snake_head;
    Snake[1].i=13;
    Snake[1].j=3;
    Patrat[12][2].st=snake_body;
    Snake[2].i=14;
    Snake[2].j=3;
    Patrat[13][2].st=snake_body;
    for(int k=0; k<20; k++)
    {
        Patrat[0][k].st=block;
        Patrat[14][k].st=block;
    }
    bricks();
}
void init_lvl3()
{
    score=0;
    current_lvl=3;
    dr=up;
    Snake[0].i=13;
    Snake[0].j=3;
    Patrat[12][2].st=snake_head;
    Snake[1].i=14;
    Snake[1].j=3;
    Patrat[13][2].st=snake_body;
    Snake[2].i=15;
    Snake[2].j=3;
    Patrat[14][2].st=snake_body;
    for(int k=3; k<17; k++)
    {
        Patrat[5][k].st=block;
        Patrat[9][k].st=block;
    }
    bricks();

}
void init_lvl4()
{
    score=0;
    current_lvl=4;
    dr=up;
    Snake[0].i=13;
    Snake[0].j=3;
    Patrat[12][2].st=snake_head;
    Snake[1].i=14;
    Snake[1].j=3;
    Patrat[13][2].st=snake_body;
    Snake[2].i=15;
    Snake[2].j=3;
    Patrat[14][2].st=snake_body;
    for(int k=0; k<20; k++)
    {
        Patrat[7][k].st=block;
        if(k<15)Patrat[k][10].st=block;
    }
    bricks();
}
void init_lvl5()
{
    score=0;
    current_lvl=5;
    dr=up;
    Snake[0].i=12;
    Snake[0].j=3;
    Patrat[11][2].st=snake_head;
    Snake[1].i=13;
    Snake[1].j=3;
    Patrat[12][2].st=snake_body;
    Snake[2].i=14;
    Snake[2].j=3;
    Patrat[13][2].st=snake_body;
    for(int k=0; k<20; k++)
    {
        Patrat[0][k].st=block;
        Patrat[14][k].st=block;
        if(k<15)
        {
            Patrat[k][0].st=block;
            Patrat[k][19].st=block;
        }
    }
    bricks();
}
void init_lvl6()
{
    score=0;
    current_lvl=6;
    sh=0;
    dr=up;
    Snake[0].i=13;
    Snake[0].j=3;
    Patrat[12][2].st=snake_head;
    Snake[1].i=14;
    Snake[1].j=3;
    Patrat[13][2].st=snake_body;
    Snake[2].i=15;
    Snake[2].j=3;
    Patrat[14][2].st=snake_body;
    for(int k=0; k<20; k++)
    {
        Patrat[7][k].st=block;
        if(k<15)
        {
            Patrat[k][0].st=block;
            Patrat[k][19].st=block;
        }
    }
    bricks();
}
void init_lvl7()
{
    score=0;
    current_lvl=7;
    sh=0;
    dr=up;
    Snake[0].i=12;
    Snake[0].j=3;
    Patrat[11][2].st=snake_head;
    Snake[1].i=13;
    Snake[1].j=3;
    Patrat[12][2].st=snake_body;
    Snake[2].i=14;
    Snake[2].j=3;
    Patrat[13][2].st=snake_body;
    for(int k=0; k<20; k++)
    {
        if(k<6)
        {
            Patrat[k][5].st=block;
            Patrat[5][k].st=block;
        }
        if(k>14)
        {
            Patrat[k-5][14].st=block;
            Patrat[9][k].st=block;
        }
    }
    Patrat[9][14].st=block;
    bricks();
}
void init_lvl8()
{
    score=0;
    current_lvl=8;
    sh=0;
    dr=up;
    Snake[0].i=13;
    Snake[0].j=3;
    Patrat[12][2].st=snake_head;
    Snake[1].i=14;
    Snake[1].j=3;
    Patrat[13][2].st=snake_body;
    Snake[2].i=15;
    Snake[2].j=3;
    Patrat[14][2].st=snake_body;
    for(int k=3; k<17; k++)
    {
        Patrat[5][k].st=block;
        Patrat[9][k].st=block;
    }
    for(int k=0; k<20; k++)
    {
        Patrat[0][k].st=block;
        Patrat[14][k].st=block;
        if(k<6||k>8)
        {
            Patrat[k][0].st=block;
            Patrat[k][19].st=block;
        }
    }
    bricks();
}
void init_lvl9()
{
    score=0;
    current_lvl=9;
    sh=0;
    dr=up;
    Snake[0].i=13;
    Snake[0].j=3;
    Patrat[12][2].st=snake_head;
    Snake[1].i=14;
    Snake[1].j=3;
    Patrat[13][2].st=snake_body;
    Snake[2].i=15;
    Snake[2].j=3;
    Patrat[14][2].st=snake_body;
    for(int k=0; k<20; k++)
    {
        Patrat[7][k].st=block;
        if(k<15)Patrat[k][10].st=block;
        if(k>10)
        {
            Patrat[0][k].st=block;
            Patrat[14][k].st=block;
        }
    }
    bricks();
}
void init_lvl10()
{
    score=0;
    current_lvl=10;
    sh=0;
    dr=up;
    Snake[0].i=13;
    Snake[0].j=3;
    Patrat[12][2].st=snake_head;
    Snake[1].i=14;
    Snake[1].j=3;
    Patrat[13][2].st=snake_body;
    Snake[2].i=15;
    Snake[2].j=3;
    Patrat[14][2].st=snake_body;
    for(int k=0; k<20; k++)
    {
        Patrat[7][k].st=block;
        if(k<7)
        {
            Patrat[k][6].st=block;
            Patrat[k][13].st=block;
        }
        if(k>7&&k<15)
        {
            Patrat[k][0].st=block;
            Patrat[k][9].st=block;
            Patrat[k][19].st=block;
        }
    }
    bricks();
}
void spawn_apple()
{
    int i,j,pos;
    do
    {
        i=random(15);
        //cout<<i<<' ';
        j=random(20);
        //cout<<j<<endl;
    }
    while(Patrat[i][j].st!=air);
    //if(Patrat[i][j].st!=air)cout<<"!!!";
    mar.i=i;
    mar.j=j;
    pos=random(10);
    //cout<<pos<<endl;
    if(pos==0 &&sn_ln>6 && sh)Patrat[i][j].st=shorten;
    else Patrat[i][j].st=apple;
}
void You_Lost()
{

    cleardevice();
    setcolor(RED);
    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    outtextxy(500-textwidth("GAME OVER")/2, 100, "GAME OVER");
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    setcolor(WHITE);
    if(lb==EN)outtextxy(500-textwidth("BACK TO MENU")/2,300-textheight("BACK TO MENU")/2,"BACK TO MENU");
    else outtextxy(500-textwidth("INAPOI LA MENIU")/2,300-textheight("INAPOI LA MENIU")/2,"INAPOI LA MENIU");
    if(!snb)
        if(score>HighScore[current_lvl-1])
        {
            HighScore[current_lvl-1]=score;
            if(lb==EN)outtextxy(800-textwidth("NEW HIGHSCORE")/2,300-textheight("HIGHSCORE NOU")/2,"NEW HIGHSCORE");
            else outtextxy(800-textwidth("HIGHSCORE NOU")/2,250-textheight("HIGHSCORE NOU")/2,"HIGHSCORE NOU");
            char arr[10];
            sprintf(arr, "%d", score);
            outtextxy(800-textwidth(arr)/2,350,arr);
            save();
        }
    snb=0;
    setcolor(BLUE);
    rectangle(350, 260,650, 340);
    int x,y,n=1;
    while(n)
    {
          getmouseclick(WM_LBUTTONDOWN, x, y);
          if(x>350&&x<650&&y>260&&y<340)
          {
              cleardevice();
              select_level();
          }
    }
}
void move_snake()
{
    t=Snake[0];
    switch (dr)
    {
    case up:
        if(Snake[0].i==1)Snake[0].i=15;
        else Snake[0].i--;
        break;
    case down:
        if(Snake[0].i==15)Snake[0].i=1;
        else Snake[0].i++;
        break;
    case lefty:
        if(Snake[0].j==1)Snake[0].j=20;
        else Snake[0].j--;
        break;
    case righty:
        if(Snake[0].j==20)Snake[0].j=1;
        else Snake[0].j++;
        break;
    }
    if(Patrat[Snake[0].i-1][Snake[0].j-1].st==block || Patrat[Snake[0].i-1][Snake[0].j-1].st==snake_body)
    {
        for(int k=0;k<15;k++)
            for(int l=0;l<20;l++)
            Patrat[k][l].st=air;
        sn_ln=3;
        You_Lost();
    }
    if(Patrat[Snake[0].i-1][Snake[0].j-1].st==apple)
    {
        score+=s+sn_ln;
        Snake[sn_ln]=t;
        sn_ln++;
        spawn_apple();
    }
    if(Patrat[Snake[0].i-1][Snake[0].j-1].st==shorten)
    {
        score+=s-sn_ln*2;
        spawn_apple();
        Patrat[Snake[0].i-1][Snake[0].j-1].st=air;
        for(int k=1; k<sn_ln; k++)
        {
            Patrat[Snake[k].i-1][Snake[k].j-1].st=air;
            v=Snake[k];
            Snake[k]=t;
            t=v;
        }
        for(int k=sn_ln/2; k<sn_ln;k++)
        {
            Snake[k]=zero;
        }
        sn_ln/=2;
    }
    else
    {
        Patrat[Snake[0].i-1][Snake[0].j-1].st=air;
        for(int k=1; k<sn_ln; k++)
        {
            Patrat[Snake[k].i-1][Snake[k].j-1].st=air;
            v=Snake[k];
            Snake[k]=t;
            t=v;
        }
    }
    Patrat[Snake[0].i-1][Snake[0].j-1].st=snake_head;
    for(int k=0; k<sn_ln; k++)
    {
        Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_body;
    }
}
void Game()
{
    char c;
    spawn_apple();
    in_game_frame();
    while(1)
    {
        if(kbhit( ))
        {
            c = (char) getch( );
            c = (char) getch( );
            switch (c)
            {
                case KEY_UP:
                    if(dr!=down)dr=up;
                    break;
                case KEY_LEFT:
                    if(dr!=righty)dr=lefty;
                    break;
                case KEY_RIGHT:
                    if(dr!=lefty)dr=righty;
                    break;
                case KEY_DOWN:
                    if(dr!=up)dr=down;
                    break;
                case 0:break;
            }
        }
        if(score<5000)
            {
                s=75;
                delay(150);
            }
        else if(score<10000)
            {
                s=100;
                delay(125);
            }
        else if(score<12500)
            {
                s=125;
                delay(100);
            }
        else
        {
            s=150;
            delay(75);
        }
        move_snake();
        in_game_frame();
    }
}
void select_level()
{
    setcolor(RED);
    settextstyle(BOLD_FONT,HORIZ_DIR,6);
    if(lb==EN)outtextxy(500-textwidth("SELECT LEVEL")/2,150/2,"SELECT LEVEL");
    else outtextxy(500-textwidth("SELECTEAZA NIVELUL")/2,150/2,"SELECTEAZA NIVELUL");
    setcolor(WHITE);
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    rectangle(125,250,175,300);
    outtextxy(150-textwidth("1")/2,275-textheight("1")/2,"1");
    rectangle(300,250,350,300);
    outtextxy(325-textwidth("2")/2,275-textheight("2")/2,"2");
    rectangle(475,250,525,300);
    outtextxy(500-textwidth("3")/2,275-textheight("3")/2,"3");
    rectangle(650,250,700,300);
    outtextxy(675-textwidth("4")/2,275-textheight("4")/2,"4");
    rectangle(825,250,875,300);
    outtextxy(850-textwidth("5")/2,275-textheight("5")/2,"5");

    rectangle(125,425,175,475);
    outtextxy(150-textwidth("6")/2,450-textheight("6")/2,"6");
    rectangle(300,425,350,475);
    outtextxy(325-textwidth("7")/2,450-textheight("7")/2,"7");
    rectangle(475,425,525,475);
    outtextxy(500-textwidth("8")/2,450-textheight("8")/2,"8");
    rectangle(650,425,700,475);
    outtextxy(675-textwidth("9")/2,450-textheight("9")/2,"9");
    rectangle(825,425,875,475);
    outtextxy(850-textwidth("10")/2,450-textheight("10")/2,"10");

    rectangle(20,20,60,60);
    line(25,40,55,40);
    line(25,40,35,30);
    line(25,40,35,50);
    setfillstyle(SOLID_FILL, GREEN);
    bar(50,163, 262, 213);
    bar(262, 213, 212, 562);
    bar(213, 562, 0,512);
    bar(1000,512,562,562);
    bar(562,562,612,337);
    bar(612,337,387,387);
    setfillstyle(SOLID_FILL, RED);
    bar(388,359,377,364);
    int x,y,n=1;
    while(n)
    {
          getmouseclick(WM_LBUTTONDOWN, x, y);
          if(x>20&&x<60&&y>20&&y<60)
          {
              cleardevice();
              Menu2();
          }
          if(x>125&&x<175&&y>250&&y<300)
          {
              cleardevice();
              init_lvl1();
              Game();
          }
          if(x>300&&x<350&&y>250&&y<300)
          {
              cleardevice();
              init_lvl2();
              Game();
          }
          if(x>475&&x<525&&y>250&&y<300)
          {
              cleardevice();
              init_lvl3();
              Game();
          }
          if(x>650&&x<700&&y>250&&y<300)
          {
              cleardevice();
              init_lvl4();
              Game();
          }
          if(x>825&&x<875&&y>250&&y<300)
          {
              cleardevice();
              init_lvl5();
              Game();
          }
          if(x>125&&x<175&&y>425&&y<475)
          {
              cleardevice();
              init_lvl6();
              Game();
          }
          if(x>300&&x<350&&y>425&&y<475)
          {
              cleardevice();
              init_lvl7();
              Game();
          }
          if(x>475&&x<525&&y>425&&y<475)
          {
              cleardevice();
              init_lvl8();
              Game();
          }
          if(x>650&&x<700&&y>425&&y<475)
          {
              cleardevice();
              init_lvl9();
              Game();
          }
          if(x>825&&x<875&&y>425&&y<475)
          {
              cleardevice();
              init_lvl10();
              Game();
          }
    }

}
void Sandbox()
{
    init_lvl1();
    snb=1;
    dr=up;
    Status mouse=air;
    cleardevice();
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    line(801,0,801,600);
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<20;j++)
        {
            rectangle(Patrat[i][j].colt[0].x,Patrat[i][j].colt[0].y,Patrat[i][j].colt[1].x,Patrat[i][j].colt[1].y);
        }
    }
    setfillstyle(SOLID_FILL, WHITE);
    bar(840,50,880,90);
    if(lb==EN)outtextxy(860-textwidth("AIR")/2,110-textheight("AIR")/2,"AIR");
    else outtextxy(860-textwidth("AER")/2,110-textheight("AER")/2,"AER");
    readimagefile("Brick.jpg",920,50,960,90);
    if(lb==EN)outtextxy(940-textwidth("WALL")/2,110-textheight("WALL")/2,"WALL");
    else outtextxy(940-textwidth("PERETE")/2,110-textheight("PERETE")/2,"PERETE");
    setfillstyle(SOLID_FILL, GREEN);
    bar(840,130,880,170);
    if(lb==EN)outtextxy(860-textwidth("SNAKE")/2,190-textheight("SNAKE")/2,"SNAKE");
    else outtextxy(860-textwidth("SARPE")/2,190-textheight("SARPE")/2,"SARPE");
    setfillstyle(SOLID_FILL, WHITE);
    bar(920,130,960,170);
    outtextxy(940-textwidth("DIR.")/2,190-textheight("DIR.")/2,"DIR.");
    setcolor(WHITE);
    sh=1;
    rectangle(840, 460, 960, 520);
    outtextxy(900-textwidth("START")/2,490-textheight("START")/2,"START");
    rectangle(840,210,860,230);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(841,211, WHITE);
    if(lb==EN)outtextxy(870,220-textheight("GOLDEN APPLE")/2,"GOLDEN APPLE");
    else outtextxy(870,220-textheight("MAR DE AUR")/2,"MAR DE AUR");
    setcolor(BLACK);
    line(940,135,940,165);
    line(940,135,930,145);
    line(940,135,950,145);
    setcolor(WHITE);
    rectangle(840, 380, 880, 420);
    line(845,400,875,400);
    line(845,400,855,390);
    line(845,400,855,410);
    int x,y,n=1;
    while(n)
    {
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>840&&x<880&&y>380&&y<420)
        {
            cleardevice();
            Menu2();
        }
        if(x>840&&x<960&&y>450&&y<520)
        {
            snb=1;
            cleardevice();
            bricks();
            Game();

        }
        if(x>840&&x<860&&y>210&&y<230)
        {
            if(sh)
            {
                sh=0;
                setfillstyle(SOLID_FILL, BLACK);
                floodfill(841,211, WHITE);
            }
            else
            {
                sh=1;
                setfillstyle(SOLID_FILL, YELLOW);
                floodfill(841,211, WHITE);
            }
        }
        if(x>840&&x<880&&y>50&&y<90)
        {
            mouse=air;
        }
        if(x>920&&x<960&&y>50&&y<90)
        {
            mouse=block;
        }
        if(x>840&&x<880&&y>130&&y<170)
        {
            mouse=snake_head;
        }
        if(x>920&&x<960&&y>130&&y<170)
        {
            switch(dr)
            {
                case up:
                {
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(920,130,960,170);
                    setcolor(BLACK);
                    line(925,150,955,150);
                    line(925,150,935,140);
                    line(925,150,935,160);
                    dr=lefty;
                    break;
                }
                case lefty:
                {
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(920,130,960,170);
                    setcolor(BLACK);
                    line(940,135,940,165);
                    line(940,165,930,155);
                    line(940,165,950,155);
                    dr=down;
                    break;
                }
                case down:
                {
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(920,130,960,170);
                    setcolor(BLACK);
                    line(925,150,955,150);
                    line(955,150,945,140);
                    line(955,150,945,160);
                    dr=righty;
                    break;
                }
                case righty:
                {
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(920,130,960,170);
                    setcolor(BLACK);
                    line(940,135,940,165);
                    line(940,135,930,145);
                    line(940,135,950,145);
                    dr=up;
                    break;
                }
            }
        }
        if(x>0&&x<800&&y>0&&y<600)
        {
            switch(mouse)
            {
            case air:
                if(Patrat[y/40][x/40].st==snake_body || Patrat[y/40][x/40].st==snake_head)
                {
                    for(int k=0;k<3;k++)
                    {
                        Patrat[Snake[k].i][Snake[k].j].st=air;
                        setfillstyle(SOLID_FILL, BLACK);
                        floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                    }
                }
                else
                {
                    setcolor(WHITE);
                    rectangle(Patrat[y/40][x/40].colt[0].x,Patrat[y/40][x/40].colt[0].y,Patrat[y/40][x/40].colt[1].x,Patrat[y/40][x/40].colt[1].y);
                    Patrat[y/40][x/40].st=air;
                    setfillstyle(SOLID_FILL, BLACK);
                    floodfill(Patrat[y/40][x/40].colt[0].x+1,Patrat[y/40][x/40].colt[0].y+1, WHITE);
                }
                break;
            case block:
                Patrat[y/40][x/40].st=block;
                readimagefile("Brick.jpg",Patrat[y/40][x/40].colt[0].x,Patrat[y/40][x/40].colt[0].y,Patrat[y/40][x/40].colt[1].x,Patrat[y/40][x/40].colt[1].y);
                setcolor(WHITE);
                rectangle(Patrat[y/40][x/40].colt[0].x,Patrat[y/40][x/40].colt[0].y,Patrat[y/40][x/40].colt[1].x,Patrat[y/40][x/40].colt[1].y);
                break;
            case snake_head:
                switch(dr)
                {
                case up:
                    if(y/40<13)
                    {
                        for(int k=0;k<3;k++)
                        {
                            Patrat[Snake[k].i-1][Snake[k].j-1].st=air;
                            setfillstyle(SOLID_FILL, BLACK);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            Snake[k].i=y/40+k;
                            Snake[k].j=x/40;
                            setcolor(WHITE);
                            if(Patrat[Snake[k].i][Snake[k].j].st==block)
                            {
                                rectangle(Patrat[Snake[k].i][Snake[k].j].colt[0].x,Patrat[Snake[k].i][Snake[k].j].colt[0].y,Patrat[Snake[k].i][Snake[k].j].colt[1].x,Patrat[Snake[k].i][Snake[k].j].colt[1].y);
                                setfillstyle(SOLID_FILL, BLACK);
                                floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            }
                            if(!k)Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_head;
                            else Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_body;
                            setfillstyle(SOLID_FILL, GREEN);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                        }
                    }
                    break;
                case down:
                    if(y/40>1)
                    {
                        for(int k=0;k<3;k++)
                        {
                            Patrat[Snake[k].i-1][Snake[k].j-1].st=air;
                            setfillstyle(SOLID_FILL, BLACK);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            Snake[k].i=y/40-k;
                            Snake[k].j=x/40;
                            setcolor(WHITE);
                            if(Patrat[Snake[k].i][Snake[k].j].st==block)
                            {
                                rectangle(Patrat[Snake[k].i][Snake[k].j].colt[0].x,Patrat[Snake[k].i][Snake[k].j].colt[0].y,Patrat[Snake[k].i][Snake[k].j].colt[1].x,Patrat[Snake[k].i][Snake[k].j].colt[1].y);
                                setfillstyle(SOLID_FILL, BLACK);
                                floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            }
                            if(!k)Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_head;
                            else Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_body;
                            setfillstyle(SOLID_FILL, GREEN);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                        }
                    }
                    break;
                case righty:
                    if(x/40>1)
                    {
                        for(int k=0;k<3;k++)
                        {
                            Patrat[Snake[k].i-1][Snake[k].j-1].st=air;
                            setfillstyle(SOLID_FILL, BLACK);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            Snake[k].i=y/40;
                            Snake[k].j=x/40-k;
                            setcolor(WHITE);
                            if(Patrat[Snake[k].i][Snake[k].j].st==block)
                            {
                                rectangle(Patrat[Snake[k].i][Snake[k].j].colt[0].x,Patrat[Snake[k].i][Snake[k].j].colt[0].y,Patrat[Snake[k].i][Snake[k].j].colt[1].x,Patrat[Snake[k].i][Snake[k].j].colt[1].y);
                                setfillstyle(SOLID_FILL, BLACK);
                                floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            }
                            if(!k)Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_head;
                            else Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_body;
                            setfillstyle(SOLID_FILL, GREEN);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                        }
                    }
                    break;
                case lefty:
                    if(x/40<18)
                    {
                        for(int k=0;k<3;k++)
                        {
                            Patrat[Snake[k].i-1][Snake[k].j-1].st=air;
                            setfillstyle(SOLID_FILL, BLACK);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            Snake[k].i=y/40;
                            Snake[k].j=x/40+k;
                            setcolor(WHITE);
                            if(Patrat[Snake[k].i][Snake[k].j].st==block)
                            {
                                rectangle(Patrat[Snake[k].i][Snake[k].j].colt[0].x,Patrat[Snake[k].i][Snake[k].j].colt[0].y,Patrat[Snake[k].i][Snake[k].j].colt[1].x,Patrat[Snake[k].i][Snake[k].j].colt[1].y);
                                setfillstyle(SOLID_FILL, BLACK);
                                floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                            }
                            if(!k)Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_head;
                            else Patrat[Snake[k].i-1][Snake[k].j-1].st=snake_body;
                            setfillstyle(SOLID_FILL, GREEN);
                            floodfill(Patrat[Snake[k].i][Snake[k].j].colt[0].x+1,Patrat[Snake[k].i][Snake[k].j].colt[0].y+1, WHITE);
                        }
                    }
                    break;
                }
                break;
            }
        }

    }
}
void HELP()
{
    cleardevice();
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR,3);
    rectangle(20,20,60,60);
    line(25,40,55,40);
    line(25,40,35,30);
    line(25,40,35,50);
    setfillstyle(SOLID_FILL,GREEN);
    bar(80,20,200,60);
    setfillstyle(SOLID_FILL,RED);
    bar(200,37,210,42);
    bar(30,200,50,220);
    setfillstyle(SOLID_FILL,YELLOW);
    bar(30,260,50,280);
    readimagefile("Brick.jpg",20,320,60,360);
    if(lb==EN)outtextxy(240,40-textheight("SNAKE")/2,"SNAKE");
    else outtextxy(240,40-textheight("SARPE")/2,"SARPE");
    if(lb==EN)outtextxy(20,110-textheight("KEYBOARD")/2,"KEYBOARD");
    else outtextxy(20,110-textheight("SAGETILE DE")/2,"SAGETILE DE");
    if(lb==EN)outtextxy(20,130-textheight("ARROWS")/2,"ARROWS");
    else outtextxy(20,130-textheight("LA TASTATURA")/2,"LA TASTATURA");
    if(lb==EN)outtextxy(240,120-textheight("CHANGE SNAKE'S DIRRECTION")/2,"CHANGE SNAKE'S DIRRECTION");
    else outtextxy(240,120-textheight("SCHIMBA DIRECTIA SARPELUI")/2,"SCHIMBA DIRECTIA SARPELUI");
    if(lb==EN)outtextxy(240,220-textheight("APPLE")/2,"APPLE");
    else outtextxy(240,220-textheight("MAR")/2,"MAR");
    if(lb==EN)outtextxy(240,270-textheight("GOLDEN APPLE")/2,"GOLDEN APPLE");
    else outtextxy(240,270-textheight("MAR DE AUR")/2,"MAR DE AUR");
    if(lb==EN)outtextxy(240,340-textheight("WALL")/2,"WALL");
    else outtextxy(240,340-textheight("PERETE")/2,"PERETE");
    int x,y,n=1;
    while(n)
    {
          getmouseclick(WM_LBUTTONDOWN, x, y);
          if(x>20&&x<60&&y>20&&y<60)
          {
              cleardevice();
              Menu();
          }
    }

}
void Menu2()
{
    cleardevice();
    setcolor(RED);
    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    outtextxy(500-textwidth("SNAKE")/2, 100, "SNAKE");
    setfillstyle(SOLID_FILL,GREEN);
    bar(50,50,200,100);
    bar(150,100,200,500);
    bar(200,450,700,500);
    bar(700,500,750,200);
    bar(750,200,900,250);
    setfillstyle(SOLID_FILL,RED);
    bar(900,223,910,227);
    setcolor(BLUE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    rectangle(350, 260,650, 340);
    rectangle(350,360,650,440);
    setcolor(WHITE);
    rectangle(20,540,60,580);
    line(25,560,55,560);
    line(25,560,35,550);
    line(25,560,35,570);
    setcolor(GREEN);
    if(lb==EN)outtextxy(500-textwidth("LEVELS")/2, 300-textheight("LEVELS")/2, "LEVELS");
    else outtextxy(500-textwidth("NIVELE")/2, 300-textheight("NIVELE")/2, "NIVELE");
    outtextxy(500-textwidth("SANDBOX")/2, 400-textheight("SANDBOX")/2, "SANDBOX");
    int x,y,n=1;
    while(n)
    {
          getmouseclick(WM_LBUTTONDOWN, x, y);
          if(x>20&&x<60&&y>540&&y<580)
          {
              cleardevice();
              Menu();
          }
          if(x>400&&x<600&&y>260&&y<340)
          {
              n=0;
              cleardevice();
              select_level();
          }
          if(x>350&&x<650&&y>360&&y<440)
          {
              n=0;
              Sandbox();
              getch();
          }
    }
}
void Menu()
{
    setcolor(BLUE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    rectangle(400, 260,600, 340);
    rectangle(425,360,575,420);
    rectangle(980,580,940,540);
    setcolor(WHITE);
    if(lb==EN)outtextxy(960-textwidth("EN")/2,560-textheight("EN")/2,"EN");
    else outtextxy(960-textwidth("RO")/2,560-textheight("RO")/2,"RO");
    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    setcolor(GREEN);
    if(lb==EN)outtextxy(500-textwidth("PLAY")/2, 300-textheight("PLAY")/2, "PLAY");
    else outtextxy(500-textwidth("JOACA")/2, 300-textheight("JOACA")/2, "JOACA");
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    if(lb==EN)outtextxy(500-textwidth("HELP")/2, 390-textheight("HELP")/2, "HELP");
    else outtextxy(500-textwidth("AJUTOR")/2, 390-textheight("AJUTOR")/2, "AJUTOR");
    setcolor(RED);
    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    outtextxy(500-textwidth("SNAKE")/2, 100, "SNAKE");
    setfillstyle(SOLID_FILL,GREEN);
    bar(50,50,200,100);
    bar(150,100,200,500);
    bar(200,450,700,500);
    bar(700,500,750,200);
    bar(750,201,900,250);
    setfillstyle(SOLID_FILL,RED);
    bar(900,223,910,227);
    int x,y,n=1;
    while(n)
    {
          getmouseclick(WM_LBUTTONDOWN, x, y);
          if(x>940&&x<980&&y>540&&y<580)
          {
              if(lb==EN)
              {
                  lb=RO;
              }
              else lb=EN;
              cleardevice();
              Menu();
          }
          if(x>400&&x<600&&y>260&&y<340)
          {
              n=0;
              Menu2();
          }
          if(x>425&&x<575&&y>360&&y<420)
          {
              n=0;
              HELP();
          }
    }
}

int main()
{
    read_file();
    srand(static_cast<unsigned int>(std::time(nullptr)));
    init();
    initwindow(1000,600, "Snake Game");
    Menu();
    getch();
    closegraph();
    return 0;
}
