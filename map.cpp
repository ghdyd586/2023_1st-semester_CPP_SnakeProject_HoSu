//include "main.h"
#include "game.h"


void set_color(){
  start_color();
  init_pair(10, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(11, COLOR_BLACK, COLOR_WHITE);

  init_pair(12, COLOR_WHITE, COLOR_WHITE); // null box
  init_color(COLOR_GRAY, 270, 270, 270);      // Gray
  init_pair(1, COLOR_GRAY, COLOR_GRAY);       // Wall
  init_color(COLOR_BLACK, 0, 0,0);
  init_pair(2, COLOR_BLACK, COLOR_BLACK); // Immune Wall
  init_pair(3, COLOR_CYAN, COLOR_CYAN);       // Snake Head
  init_pair(4, COLOR_BLUE, COLOR_BLUE);       // Snake Body
  init_pair(5, COLOR_GREEN, COLOR_GREEN);       // Growth item
  init_pair(6, COLOR_RED, COLOR_RED);     //Poison item
  init_color(COLOR_MAGENTA, 1000, 250, 500);
  init_pair(7, COLOR_YELLOW,COLOR_YELLOW); // gate

}

void back_setting(){

//========decorate the title of the game, each letter of snake=====
  bkgd(COLOR_PAIR(10));
  attron(COLOR_PAIR(11));
  border('|', '|', '-', '-', '.', '.', '.', '.');
  mvprintw(1, 47, "#SNAKE GAME made by HoSu#");
  attroff(COLOR_PAIR(11));
  attron(COLOR_PAIR(10));

  mvprintw(35, 45, "<<Press arrow keys to move snake!>>");

  attroff(COLOR_PAIR(10));
  refresh();
}

void window_setting(WINDOW* win1){
  //window setting win1 = game board |win2 = mission board | win3= score board
  wbkgd(win1, COLOR_PAIR(10));
  wattron(win1, COLOR_PAIR(10));
  wborder(win1, '|', '|', '-', '-', '.', '.', '.', '.');
}

void score(){
  int goal[4][4] = {{4, 1, 1, 1}, {5, 1, 1, 2}, {6, 1, 2, 1}, {7, 3, 1, 2}}; //set the goal for each stage

  //============mission board========
  wbkgd(win2, COLOR_PAIR(11));
  wattron(win2, COLOR_PAIR(11));
  mvwprintw(win2, 1, 13, "[MISSION]");
  wborder(win2, '|', '|', '-', '-', '.', '.', '.', '.');
  mvwprintw(win2, 3, 8, "B : %d", goal[selmap][0]);
  mvwprintw(win2, 5, 8, "+ : %d", goal[selmap][1]);
  mvwprintw(win2, 7, 8, "- : %d", goal[selmap][2]);
  mvwprintw(win2, 9, 8, "G : %d", goal[selmap][3]);

  int current_size = snake.size();
  MaxSize = max(current_size,size);+


//===========score board===========
  wbkgd(win3, COLOR_PAIR(11));
  wattron(win3, COLOR_PAIR(11));
  mvwprintw(win3, 1, 13, "[SCORE]");
  wborder(win3, '|', '|', '-', '-', '.', '.', '.', '.');
  mvwprintw(win3, 3, 2, "B : %d / %d", current_size, MaxSize);
  mvwprintw(win3, 5, 2, "+ :   %d   ", itemcnt);
  mvwprintw(win3, 7, 2, "- :   %d   ", poisoncnt);
  mvwprintw(win3, 9, 2, "G :   %d   ", gatecnt);
  mvwprintw(win3, 11, 2, "=======================");
  mvwprintw(win3, 13, 2, "S :   %d   ",stagescore);



//==========checkbox=============
  if(current_size < goal[selmap][0]){
    mvwprintw(win3, 3, 14, "(   )");
  }
  else{
    mvwprintw(win3, 3, 14, "( V )");

  }
  if(itemcnt < goal[selmap][1]){
    mvwprintw(win3, 5, 14, "(   )");
    mvwprintw(win3, 6, 1, "[+200 points per item]");
  }
  else{
    mvwprintw(win3, 5, 14, "( V )");
    mvwprintw(win3, 6, 1, "[+200 points per item]");
  }
  if(poisoncnt < goal[selmap][2]){
    mvwprintw(win3, 7, 14, "(   )");
    mvwprintw(win3, 8, 1, "[-100 points per poison]");
  }
  else{
    mvwprintw(win3, 7, 14, "( V )");
    mvwprintw(win3, 8, 1, "[-100 points per poison]");
  }

  if(gatecnt< goal[selmap][3]){
    mvwprintw(win3, 9, 14, "(   )" );
    mvwprintw(win3, 10, 1, "[+100 points per gate]" );

  }
  else{
    mvwprintw(win3, 9, 14, "( V )");
    mvwprintw(win3, 10, 1, "[+100 points per gate]");
  }

//if player get all of requirements, that stage should be finished

  if(current_size>=goal[selmap][0])
    if(itemcnt>=goal[selmap][1])
      if(poisoncnt>=goal[selmap][2])
        if(gatecnt>=goal[selmap][3]){
          if(selmap==3){
            result(2);
            delwin(win1);
            exit(0);
          }
          else{
          result(1);
          selmap++;
          reset();
          game();
         }
        }
  wrefresh(win2);
  wrefresh(win3);
}

//when the stage changes, all of the counts should be set to 0.
void reset(){
  itemcnt = 0;
  poisoncnt = 0;
  gatecnt = 0;

}
// color apply function-------------------------------------------------------------
void color_apply(int selmap,WINDOW* win1){
  // color apply
  for (int i = 0; i < 30; i++) { //map print
    int temp=0; //temporary x positon. to equalize the map size
      for (int j = 0; j < 30; j++) {
        // null box is white
          if (map[selmap][i][j] == 0) {
              wattron(win1, COLOR_PAIR(12));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]); //space in behind
              wattroff(win1, COLOR_PAIR(12));
              temp+=2; //update x position

          }
          //Wall is gray
          else if (map[selmap][i][j] == 1) {
              wattron(win1, COLOR_PAIR(1));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]);
              wattroff(win1, COLOR_PAIR(1));
              temp+=2;
          }
          // Immune Wall is black
          else if (map[selmap][i][j] == 2) {
              wattron(win1, COLOR_PAIR(2));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]);
              wattroff(win1, COLOR_PAIR(2));
              temp+=2;
          }
          // Snake Head is cyan
          else if (map[selmap][i][j] == 3) {
              wattron(win1, COLOR_PAIR(3));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]);
              wattroff(win1, COLOR_PAIR(3));
              temp+=2;
          }
          // Snake Body is blue
          else if (map[selmap][i][j] == 4) {
              wattron(win1, COLOR_PAIR(4));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]);
              wattroff(win1, COLOR_PAIR(4));
              temp+=2;
          }
          // Growth item is green
          else if (map[selmap][i][j] == 5) {
              wattron(win1, COLOR_PAIR(5));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]);
              wattroff(win1, COLOR_PAIR(5));
              temp+=2;
          }
          //Poison item is red
          else if (map[selmap][i][j] == 6) {
              wattron(win1, COLOR_PAIR(6));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]);
              wattroff(win1, COLOR_PAIR(6));
              temp+=2;
          }
          // Gate is Bright pink
          else if (map[selmap][i][j] == 7) {
              wattron(win1, COLOR_PAIR(7));
              mvwprintw(win1, i, temp, "%d ", map[selmap][i][j]);
              wattroff(win1, COLOR_PAIR(7));
              temp+=2;
          }
      }
  }
  wrefresh(win1);
}
//initialize map function---------------------------------------------------
void initialize_item(int selmap){
  for (int i=0; i<30; i++){
    for(int j=0; j<30; j++){
      if (map[selmap][i][j]==5||map[selmap][i][j]==6)
        map[selmap][i][j]=0;
    }
  }
}

void initialize_gate(int selmap){
  for (int i=0; i<30; i++){
    for(int j=0; j<30; j++){
      if (map[selmap][i][j]==7)
        map[selmap][i][j]=1;
    }
  }
}

void caltime(){
  endtime = time(NULL);
  gettime = endtime - starttime;
}

void result(int resultnum){
  wclear(win1);
  if (resultnum == 1){
    caltime();
    mvwprintw(win1,15,25,"Stage%d Clear!!",selmap+1);
    mvwprintw(win1,16,14,"Press Any Key to Move Next Stage...");
    mvwprintw(win1,17,11,"You spent %d seconds to clear this stage",gettime);
    mvwprintw(win1,18,18,"Your current score is : %d ",stagescore);
    scoreset[selmap] = stagescore;
    size = snake.size();


  }
  else if (resultnum == 2){
    caltime();
    scoreset[selmap] = stagescore;
    mvwprintw(win1,10,25,"Stage All Clear!!");
    mvwprintw(win1,12,16,"Press Any Key to Exit the Game...");
    mvwprintw(win1,14,11,"You spent %d seconds to clear this stage",gettime);
    mvwprintw(win1,15,16,"===========<Score Board>==========");
    mvwprintw(win1,16,27,"[Stage 1 : %d]",scoreset[0]);
    mvwprintw(win1,17,27,"[Stage 2 : %d]",scoreset[1]);
    mvwprintw(win1,18,27,"[Stage 3 : %d]",scoreset[2]);
    mvwprintw(win1,19,27,"[Stage 4 : %d]",scoreset[3]);


  }
  else if (resultnum == 3){
    mvwprintw(win1,15,25,"Game Over!!");
    mvwprintw(win1,16,16,"Press Any Key to Exit the Game...");

  }
  wrefresh(win1);
  nodelay(stdscr, false);
  getch();
  wclear(win1);

}
