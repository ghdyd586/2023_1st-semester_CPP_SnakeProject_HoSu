#include <time.h>
#include "gate.h"


// input directon function---------------------------------------------------------
int input_Direction(int input_key, int* snake_direction){
  switch(input_key) {
    case KEY_UP:
        if(*snake_direction == 2){
          result(3);
          delwin(win1);
          exit(0);
        }
        *snake_direction =0;
        return 0;
        break;
    case KEY_RIGHT:
        if(*snake_direction == 3){
          result(3);
          delwin(win1);
          exit(0);
        }
        *snake_direction =1;
        return 1;
        break;
    case KEY_DOWN:
        if(*snake_direction == 0){
          result(3);
          delwin(win1);
          exit(0);
        }
        *snake_direction =2;
        return 2;
        break;
    case KEY_LEFT:
        if(*snake_direction == 1){
          result(3);
          delwin(win1);
          exit(0);
        }
        *snake_direction =3;
        return 3;
        break;
  }
  return *snake_direction; //if input is null
}

void snake_make(vector<snakebody>& snake, int selmap){
//possible location (map, row, colum)
  int snake_positon[4][3][2]={
    {{4, 23}, {6, 8}, {18, 16}},
    {{15, 14}, {21, 9}, {2, 13}},
    {{4, 15}, {27, 18}, {16, 20}},
    {{26, 22}, {6, 12}, {3, 10}}
  };

  // make random number-> random location and snake location setting
  srand((unsigned)time(0));
  int sel_r = rand()%3;
  snake.clear();

  //head setting ->snake <vector> has head positon and body position
  //######################
  // #####Important######
  //#######################
  //ex) row ==4 colum==23
  for(int i=0; i<3; i++){
    snake.push_back(snakebody(snake_positon[selmap][sel_r][0], snake_positon[selmap][sel_r][1]+i));}
  map[selmap][snake[0].r][snake[0].c] = 3; //snake head is 3

  // body setting
  for(int i=1; i<3; i++){
    map[selmap][snake[i].r][snake[i].c] = 4;} //snake body is 4
}
  // item ----------------------------------------------------------------------------------------------
void make_item(int selmap){
    initialize_item(selmap); //initialize map
    srand((unsigned) time(0));
    int num_growth = rand() % 4; //0~3 growth item can be generated
    int num=0,tmpX=0,tmpY=0; //num of growth item, location

    while(num<3){ //while lower than maximum item num
      tmpX = rand()%28+1;
      tmpY = rand()%28+1;

      if(map[selmap][tmpY][tmpX] != 0) //can place item only if it's blank
        continue;

      else if(num<num_growth){
        map[selmap][tmpY][tmpX] = 5; //set the growth item location
        num++;
        continue;
      }
      map[selmap][tmpY][tmpX]=6; //set the poison item location
      num++;
    }
}

// moving process--------------------------------------------------------------------------------
void snake_move(vector<snakebody>& snake, vector<snakebody>& gate, int* snake_direction, bool* gate_crossing, int* cross_cnt, int* cnt2){
  int new_head_row=snake[0].r;
  int new_head_col=snake[0].c;
  int new_body_row=snake[snake.size()-1].r;
  int new_body_col=snake[snake.size()-1].c;
  int out_gate_row, out_gate_col;

  switch (*snake_direction) {
      case 0: //up
        new_head_row--;
        break;
      case 1: //right
        new_head_col++;
        break;
      case 2: //down
        new_head_row++;
        break;
      case 3: //left
        new_head_col--;
        break;
      default: //another key
        break;
      }


  if (map[selmap][new_head_row][new_head_col]==5){ //encounter growth item
      snake.push_back(snakebody(new_body_row, new_body_col)); //body_length+=1
      itemcnt++; //item_count +=1
    }

  else if (map[selmap][new_head_row][new_head_col]==6){ //encounter poison item
      snake.pop_back(); //body_length-=1
      map[selmap][snake[snake.size()].r][snake[snake.size()].c] = 0;
      poisoncnt++; //poison_count +=1
      if (snake.size() < 3){ //if snake size is shorter than 3
        result(3);
        delwin(win1);
        exit(0);
      }
    }

  else if (map[selmap][new_head_row][new_head_col]==7){ //encounter gate
    if (new_head_row==gate[0].r&&new_head_col==gate[0].c){ //gate[0] is in_gate
      out_gate_row=gate[1].r; out_gate_col=gate[1].c; //gate[1] is out_gate
    }
    else{ //gate[1] is in_gate
      out_gate_row=gate[0].r; out_gate_col=gate[0].c; //gate[0] is out_gate

    }
    cross_gate(out_gate_row, out_gate_col, &new_head_row, &new_head_col, snake_direction, selmap);  //set head location through the gate
    gatecnt++;
    *gate_crossing=true;
    }

  else if (map[selmap][new_head_row][new_head_col]==1){ //encounter wall
    result(3);
    delwin(win1);
    exit(0);
  }
  else if (map[selmap][new_head_row][new_head_col]==2){ //encounter immune wall
    result(3);
    delwin(win1);
    exit(0);
  }
  snake.insert(snake.begin(), snakebody(new_head_row, new_head_col)); //insert new head
  snake.pop_back(); //delete last snake body //body_length-=1
  for(int i=snake.size()-1; i>=0; i--){
    if(i==snake.size()-1){ //remove last snake body
      map[selmap][snake[snake.size()].r][snake[snake.size()].c] = 0;
      continue;
    }
    else if(i!=0){ //move snake body
      map[selmap][snake[1].r][snake[1].c] = 4;
      continue;
    }
    map[selmap][snake[0].r][snake[0].c] = 3; //move snake head
  }

  if(*gate_crossing){ //if snake is crossing the gate
    if(*cross_cnt==snake.size()){
      *cross_cnt=0;
      make_gate(selmap, gate, cnt2); //new gate generates when snake crossed the gate
      *gate_crossing=false;
    }
     *cross_cnt+=1;
  }

  refresh();
}
