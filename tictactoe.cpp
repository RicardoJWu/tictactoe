/*
  This program simulate tictactoe game. User will play first.
  The chessboard uses x-y coordinate in Quadrant I which both x and y are
  from 1 to 3
eg: chess at (2, 3)
3 - o -
2 - - -
1 - - -
  1 2 3
  You can run the code in your terminal directly. Be sure to choose a chess either
  lowercase "x" or "o" to start
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

struct Coordinate{
  int x;
  int y;
};

class tictactoe{
  private:
    char user;
    char fuxi;
    char turn;
    char board[4][4];

    bool isPlaced(int x, int y){
      if(board[x][y] != '-'){
        return true;
      }
      return false;
    }// end isPlaced

    bool isMove(Coordinate point){
      if(point.x == 0 && point.y == 0)
        return false;
      return true;
    }

    void move(int x, int y, char player){
      board[x][y] = player;
    }// end move

    void show(){
      for(int i=3; i>0; i--){
        for(int j=1; j<4; j++){
          cout << board[j][i] << " ";
        }
        cout << endl;
      }
    }// end show

    Coordinate about_win_row(char player);
    Coordinate about_win_col(char player);
    Coordinate about_win_dia(char player);

    bool isGameOver(){
      if(whoWins() != '-'){
        return true;
      }
      for(int i=1; i<4; i++){
        for(int j=1; j<4; j++){
          if(board[i][j] == '-')
            return false;
        }
      }
      return true;
    }// end isGameOver

    char whoWins(){
      char player = win_Row();
      if(player != '-') return player;
      player = win_Col();
      if(player != '-') return player;
      return win_Dia();
    }// end whoWins

    char win_Row(){
      for(int i=1; i<4; i++){
        if(board[i][1] != '-' && board[i][1] == board[i][2] &&
           board[i][2] == board [i][3])
           return board[i][1];
      }
      return '-';
    }// end win_Row

    char win_Col(){
      for(int j=1; j<4; j++){
        if(board[1][j] != '-' && board[1][j] == board[2][j] &&
           board[2][j] == board[3][j])
           return board[1][j];
      }
      return '-';
    }// end win_Col

    char win_Dia(){
      if(board[2][2] == '-') return '-';
      else if(board[1][1] == board[2][2] &&
              board[2][2] == board[3][3]) return board[1][1];
      else if(board[1][3] == board[2][2] &&
              board[2][2] == board[3][1]) return board[1][3];
      else return '-';
    }

    Coordinate fuxi_gote(){
      Coordinate play = {0, 0};

      play = about_win_col(fuxi);
      if(isMove(play)){
        // cout << "Win col ";
        return play;
      }

      play = about_win_row(fuxi);
      if(isMove(play)){
        // cout << "Win row ";
        return play;
      }

      play = about_win_dia(fuxi);
      if(isMove(play)){
        // cout << "Win dia ";
        return play;
      }

      play = about_win_col(user);
      if(isMove(play)){
        // cout << "Block col ";
        return play;
      }

      play = about_win_row(user);
      if(isMove(play)){
        // cout << "Block row ";
        return play;
      }

      play = about_win_dia(user);
      if(isMove(play)){
        // cout << "Block dia ";
        return play;
      }

      if(! isPlaced(2, 2)){
        // cout << "Go Middle ";
        play.x = play.y = 2;
        return play;
      }

      // cout << "Go random ";
      while(true){
        play.x = rand() % 3 + 1;
        play.y = rand() % 3 + 1;
        if(!isPlaced(play.x, play.y)) return play;
      }// end while

    }// end fuxi_gote

  public:
    tictactoe(){
      fuxi = user = '-';
      for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
          board[i][j] = '-';
        }
      }
    }// end constructor

    void start();

}; // end class

Coordinate tictactoe::about_win_row(char player){
  Coordinate point = {0, 0};
  for(int col=1; col<4; col++){
    // o o -
    if(board[1][col] == player && board[2][col] == player && board[3][col] == '-'){
      point.x = 3;
      point.y = col;
      return point;
    }
    // - o o
    else if(board[2][col] == player && board[3][col] == player && board[1][col] == '-'){
      point.x = 1;
      point.y = col;
      return point;
    }
    // o - o
    else if(board[1][col] == player && board[3][col] == player && board[2][col] == '-'){
      point.x = 2;
      point.y = col;
      return point;
    }
  }
  return point;
}// end about_win_row

Coordinate tictactoe::about_win_col(char player){
  Coordinate point = {0, 0};
  for(int row=1; row<4; row++){
    /* o
       o
       - */
    if(board[row][1] == player && board[row][2] == player && board[row][3] == '-'){
      point.x = row;
      point.y = 3;
      return point;
    }
    /* -
       o
       o */
    else if(board[row][2] == player && board[row][3] == player && board[row][1] == '-'){
      point.x = row;
      point.y = 1;
      return point;
    }
    /* o
       -
       o */
    else if(board[row][1] == player && board[row][3] == player && board[row][2] == '-'){
      point.x = row;
      point.y = 2;
      return point;
    }
  }
  return point;
}// end about_win_row

Coordinate tictactoe::about_win_dia(char player){
  Coordinate point = {0, 0};
  int num_chess = 0;
  /* - - o
     - o -
     o - -  */
  for(int i=1; i<4; i++){
    if(board[i][i] == player){
      num_chess += 1;
    }
    else if(board[i][i] == '-'){
      point.x = point.y = i;
    }
  }
  if(num_chess == 2){
    return point;
  }

  num_chess = 0;
  /* o - -
     - o -
     - - o  */
  for(int i=1; i<4; i++){
    if(board[i][4-i] == player){
      num_chess += 1;
    }
    else if(board[i][4-i] == '-'){
      point.x = i;
      point.y = 4 - i;
    }
  }
  if(num_chess == 2){
    return point;
  }
  point.x = point.y = 0;
  return point;
}// about_win_dia

void tictactoe::start(){
  int x, y;
  Coordinate play;
  cout << "Welcome to tictactoe\n";
  show();
  cout << "Input lowercase \'x\' or \'o\' to be your chess: ";
  cin >> this->user;

  if(this->user == 'o') this->fuxi = 'x';
  else this->fuxi = 'o';

  cout << "Please input two numbers as a coordinate to play a chess(Enter -1 to quit)\n";
  while(! isGameOver()){
    this->turn = this->user;
    cout << "Your turn: ";
    cin >> x;
    if(x == -1) break;
    cin >> y;
    move(x, y, this->turn);
    show();
    if(isGameOver()) break;

    cout << "Computer made a move at: ";
    this->turn = this->fuxi;
    play = fuxi_gote();
    move(play.x, play.y, this->turn);
    cout << "(" << play.x << ", " << play.y << ")" << endl;
    show();
    this->turn = this->user;
  }
  if(user == whoWins()){
    cout << "You Win!!! Nice Play!\n";
  }
  else if(fuxi == whoWins()){
    cout << "You Lose!!! Try Agin!\n";
  }
  else{
    cout << "Tie!!! Try Agin!\n";
  }
}// end play


int main(){
  tictactoe game;
  game.start();
  return 0;
}
