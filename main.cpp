#include <time.h>
#include <stdlib.h>

#include <iostream>

enum dir {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

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
  printf("\n");
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

// return val is if merge was done

bool slideLeft(Tile board[4][4]) {
  bool merged = false;
  for (int i = 0; i < 4; i++) {
    int merge_idx = 0; // index to merge with
    for (int j = 1; j < 4; j++) {
      if ((j == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (board[i][j].val == board[i][merge_idx].val) { // merge
        board[i][merge_idx].val *= 2;
        merge_idx++;
        board[i][j].val = 0;
        merged = true;
      }
      else {
        if (board[i][merge_idx].val != 0) {
          merge_idx++;
        }
        if (board[i][merge_idx].val == 0) { // slide left into empty slot
          board[i][merge_idx].val = board[i][j].val;
          board[i][j].val = 0;
        }
      }
    }
  }
  return merged;
}

bool slideRight(Tile board[4][4]) {
  bool merged = false;
  for (int i = 0; i < 4; i++) {
    int merge_idx = 4 - 1; // index to merge with
    for (int j = (4 - 1) - 1; j >= 0; j--) {
      if ((j == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (board[i][j].val == board[i][merge_idx].val) { // merge
        board[i][merge_idx].val *= 2;
        merge_idx--;
        board[i][j].val = 0;
        merged = true;
      }
      else {
        if (board[i][merge_idx].val != 0) {
          merge_idx--;
        }
        if (board[i][merge_idx].val == 0) { // slide left into empty slot
          board[i][merge_idx].val = board[i][j].val;
          board[i][j].val = 0;
        }
      }
    }
  }
  return merged;
}

bool slideUp(Tile board[4][4]) {
  bool merged = false;
  for (int j = 0; j < 4; j++) {
    int merge_idx = 0; // index to merge with
    for (int i = 1; i < 4; i++) {
      if ((i == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (board[i][j].val == board[merge_idx][j].val) { // merge
        board[merge_idx][j].val *= 2;
        merge_idx++;
        board[i][j].val = 0;
        merged = true;
      }
      else {
        if (board[merge_idx][j].val != 0) {
          merge_idx++;
        }
        if (board[merge_idx][j].val == 0) { // slide left into empty slot
          board[merge_idx][j].val = board[i][j].val;
          board[i][j].val = 0;
        }
      }
    }
  }
  return merged;
}

bool slideDown(Tile board[4][4]) {
  bool merged = false;
  for (int j = 0; j < 4; j++) {
    int merge_idx = 4 - 1; // index to merge with
    for (int i = (4 - 1) - 1; i >= 0; i--) {
      if ((i == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (board[i][j].val == board[merge_idx][j].val) { // merge
        board[merge_idx][j].val *= 2;
        merge_idx--;
        board[i][j].val = 0;
        merged = true;
      }
      else {
        if (board[merge_idx][j].val != 0) {
          merge_idx--;
        }
        if (board[merge_idx][j].val == 0) { // slide left into empty slot
          board[merge_idx][j].val = board[i][j].val;
          board[i][j].val = 0;
        }
      }
    }
  }
  return merged;
}



int main() {
  srand(time(NULL));
  Tile board[4][4];
  //printBoard(board);
  int empty = 16;
  char action;
  while (true) {
    spawnTile(board, 1, empty);
    empty--;
    printBoard(board);
    std::cin >> action;
    switch (action) {
      case 'a':
        if (slideLeft(board)) {
          empty++;
        }
        break;
      case 's':
        if (slideDown(board)) {
          empty++;
        }
        break;
      case 'd':
        if (slideRight(board)) {
          empty++;
        }
        break;
      case 'w':
        if (slideUp(board)) {
          empty++;
        }
        break;
    }
  }
}
