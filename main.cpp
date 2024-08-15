#include <time.h>
#include <stdlib.h>

#include <iostream>

class Tile {
public:
  int val;
  Tile(int n): val(n) {
  }
  Tile(): val(0) {
  }
  std::string toString() {
    std::string out = "";
    out += std::to_string(val);
    return out;
  }
};

void printBoard(Tile board[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%4s", board[i][j].toString().c_str());
    }
    printf("\n");
  }
}

void spawnTile(Tile board[4][4], int val, int empty) {
  int num_left = rand() % empty;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j].val == 0) {
        if (num_left == 0) {
          board[i][j] = Tile(val);
        }
        num_left--;
      }
    }
  }
}

int main() {
  srand(time(NULL));
  Tile board[4][4];
  //printBoard(board);
  spawnTile(board, 5, 16);
  printBoard(board);
}
