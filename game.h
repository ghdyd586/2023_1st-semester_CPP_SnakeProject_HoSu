#include <time.h>

// window setting win1 = game board |win2 = mission board | win3= score board------------------------------
WINDOW* win1;
WINDOW* win2;
WINDOW* win3;
void score();
int itemcnt =0;
int poisoncnt = 0;
int selmap = 0;
int head_dir = 2;
int gatecnt=0;
int MaxSize = 0;
int size = 0;
int starttime,endtime,gettime;
int stagescore;
int scoreset[4] = {0};
void result(int num);
void reset(); //reset counts when the stage is changed.
void game();
// snake body object class---------------------------------------------------------
struct snakebody{
  int r, c;
  snakebody(int row, int col);
  snakebody();
};
snakebody::snakebody(int row, int col){
  r=row;
  c=col;
}
snakebody::snakebody(){
  r=0;
  c=0;
}
vector<snakebody> snake;
vector<snakebody> gate;
