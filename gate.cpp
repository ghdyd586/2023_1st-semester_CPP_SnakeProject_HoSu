void make_gate(int selmap, vector<snakebody>& gate, int* cnt2){
    *cnt2=0;
    initialize_gate(selmap);
    gate.clear();
    srand((unsigned) time(0));

    int in_gate_row=0, in_gate_col=0, out_gate_row=0, out_gate_col=0;
    in_gate_row=rand()%30;
    in_gate_col=rand()%30;
    out_gate_row=rand()%30;
    out_gate_row=rand()%30;
    while(TRUE){
      if(map[selmap][in_gate_row][in_gate_col] ==1) break; //possible to make in_gate
      in_gate_row=rand()%30;
      in_gate_col=rand()%30;
    }
    map[selmap][in_gate_row][in_gate_col]=7; //set in_gate

    while(TRUE){
      if(map[selmap][out_gate_row][out_gate_col] ==1) break; //possible to make out_gate
      out_gate_row=rand()%30;
      out_gate_col=rand()%30;
    }
    map[selmap][out_gate_row][out_gate_col]=7; //set out_gate

    gate.push_back(snakebody(in_gate_row,in_gate_col)); //gate[0] is in_gate
    gate.push_back(snakebody(out_gate_row,out_gate_col)); //gate[1] is out_gate
}


void cross_gate(int out_gate_row, int out_gate_col, int* new_head_row, int* new_head_col, int* snake_direction, int selmap){
  if (out_gate_row==0){ //out gate at top
    *snake_direction=2;
    *new_head_row=1; //downside
    *new_head_col=out_gate_col;
  }
  else if (out_gate_row==29){ //out gate at bottom
    *snake_direction=0;
    *new_head_row=28; //upside
    *new_head_col=out_gate_col;
  }
  else if (out_gate_col==0){ //out gate at left
    *snake_direction=1;
    *new_head_col=1; //to rightside
    *new_head_row=out_gate_row;
  }
  else if (out_gate_col==29){ //out gate at right
    *snake_direction=3;
    *new_head_col=28; //to leftside
    *new_head_row=out_gate_row;
  }
  else{ //out gate not in boundary
    int status=0; //not modified
    while(status==0){ //until snake head position changes
      switch(*snake_direction){
        case 0: //up
          if(map[selmap][out_gate_row-1][out_gate_col]==1||map[selmap][out_gate_row-1][out_gate_col]==2){ //wall|immune wall in upside
            *snake_direction+=1; //turn right
            continue;
          }
          status=1;
          *new_head_row=out_gate_row-1;
          *new_head_col=out_gate_col;
          break;

        case 1: //right
          if(map[selmap][out_gate_row][out_gate_col+1]==1||map[selmap][out_gate_row][out_gate_col+1]==2){ //wall|immune wall in rightside
            *snake_direction+=1;
            continue;
          }
          status=1;
          *new_head_row=out_gate_row;
          *new_head_col=out_gate_col+1;
          break;

        case 2: //down
          if (map[selmap][out_gate_row+1][out_gate_col]==1||map[selmap][out_gate_row+1][out_gate_col]==2){
            *snake_direction+=1;
            continue;
          }
          status=1;
          *new_head_row=out_gate_row+1;
          *new_head_col=out_gate_col;
          break;

        case 3: //left
          if (map[selmap][out_gate_row][out_gate_col-1]==1||map[selmap][out_gate_row][out_gate_col-1]==2){
            *snake_direction=0;
            continue;
          }
          status=1;
          *new_head_row=out_gate_row;
          *new_head_col=out_gate_col-1;
          break;
      }
    }
  }
}
