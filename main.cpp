#include <ncurses.h>
#include <iostream>
#include <vector>
#include <clocale>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <string>
#include "map.h"
using namespace std;
#define COLOR_GRAY 8
#include "map.cpp"
#include "snake.cpp"
#include "gate.cpp"


// main start-----------------------------------------------------------------------------------------
void game() {
    setlocale(LC_ALL, "");
    initscr();

    //color setting--------------------------------------------------------
    set_color();
    //time setting---------------------------------------------------------
    starttime = time(NULL);

  //background setting---------------------------------------------------
    back_setting();
    win1 = newwin(30, 60, 3, 30); //game board
    win2 = newwin(15, 35, 38, 26); //mission board
    win3 = newwin(15, 35, 38, 61); //score board
    window_setting(win1);
    reset();


//map setting--------------------------------------------------------------------------

    wrefresh(win2);
    wrefresh(win3);
    color_apply(selmap,win1);


//snake_positon---------------------------------------------------------------------------


    snake_make(snake,selmap);
    make_item(selmap);
    color_apply(selmap, win1);
    refresh();

//Snake moving --------------------------------------------------------------------------------------
    int snake_direction =1;
    int cnt=0;
    int cnt2=0;

    bool gate_crossing=false;
    int cross_cnt=0;

    while(TRUE){


      score();
      stagescore = itemcnt*200 - poisoncnt*100 + gatecnt*100;
    // directon decide
      keypad(stdscr, TRUE);
      nodelay(stdscr, TRUE); //to move snake without input

      int input_key=getch();
      if(input_key==KEY_F(1)){
        break;
    }
      snake_direction=input_Direction(input_key, &snake_direction);
      snake_move(snake, gate, &snake_direction, &gate_crossing, &cross_cnt, &cnt2);
      color_apply(selmap, win1);
      usleep(180000); //move snake per 0.18 sec
      cnt+=1;
      cnt2+=1;
      if (cnt%32==0){ //generate item per 8sec
        make_item(selmap);
        cnt=0;
      }

      if(cnt2%52==0){ //gate appears after 13sec
        make_gate(selmap, gate, &cnt2);
      }

      color_apply(selmap, win1);
      refresh();

  }


      delwin(win1);
      delwin(win2);
      delwin(win3);

      getch();
      endwin();

}

int main(){
  system("echo Please connect to the network to run this game...");
  system("sleep 3");
  system("echo If you already installed xterm, then just press ctrl+c to skip the installation...");
  system("sleep 1");
  system("echo instead of entering password...");
  system("sleep 1");
  system("echo If you press ctrl+c, the game will start right away...");
  system("sleep 1");
  system("echo Or system will install xterm within 5 seconds...");
  system("sleep 5");

  system("sudo apt install xterm");
  system("resize -s 75 120");
  game();
  system("reset");
}
