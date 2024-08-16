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
void fluctuate(Tile board[4][4], int &empty) {
  int idx = rand() % (4 * 4);
  int i = idx / 4;
  int j = idx % 4;
  if (board[i][j].val != 0) {
    if (rand() % 2 == 0) {
      board[i][j].val++;
    }
    /*else {
      if (board[i][j].val == 0) {
        empty++;
      }
      board[i][j].val--;
    }*/
  }
}

int log2(int n) {
  int power = 0;
  while (n > 0) {
    n /= 2;
    power++;
  }
  return power - 1;
}


// return val is # of merges

bool slideLeft(Tile board[4][4], int &empty) {
  bool valid = false;
  for (int i = 0; i < 4; i++) {
    int merge_idx = 0; // index to merge with
    for (int j = 1; j < 4; j++) {
      if ((j == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (log2(board[i][j].val) == log2(board[i][merge_idx].val)) { // merge
        board[i][merge_idx].val += board[i][j].val;
        if (board[i][merge_idx].val == 2048) {
          std::cout << "You win!" << std::endl;
          exit(0);
        }
        merge_idx++;
        board[i][j].val = 0;
        empty++;
        valid = true;
      }
      else {
        if (board[i][merge_idx].val != 0) {
          merge_idx++;
        }
        if (board[i][merge_idx].val == 0) { // slide left into empty slot
          board[i][merge_idx].val = board[i][j].val;
          board[i][j].val = 0;
          valid = true;
        }
      }
    }
  }
  return valid;
}

bool slideRight(Tile board[4][4], int &empty) {
  bool valid = false;
  for (int i = 0; i < 4; i++) {
    int merge_idx = 4 - 1; // index to merge with
    for (int j = (4 - 1) - 1; j >= 0; j--) {
      if ((j == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (log2(board[i][j].val) == log2(board[i][merge_idx].val)) { // merge
        board[i][merge_idx].val += board[i][j].val;
        if (board[i][merge_idx].val == 2048) {
          std::cout << "You win!" << std::endl;
          exit(0);
        }
        merge_idx--;
        board[i][j].val = 0;
        empty++;
        valid = true;
      }
      else {
        if (board[i][merge_idx].val != 0) {
          merge_idx--;
        }
        if (board[i][merge_idx].val == 0) { // slide left into empty slot
          board[i][merge_idx].val = board[i][j].val;
          board[i][j].val = 0;
          valid = true;
        }
      }
    }
  }
  return valid;
}

bool slideUp(Tile board[4][4], int &empty) {
  bool valid = false;
  for (int j = 0; j < 4; j++) {
    int merge_idx = 0; // index to merge with
    for (int i = 1; i < 4; i++) {
      if ((i == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (log2(board[i][j].val) == log2(board[merge_idx][j].val)) { // merge
        board[merge_idx][j].val += board[i][j].val;
        if (board[i][merge_idx].val == 2048) {
          std::cout << "You win!" << std::endl;
          exit(0);
        }
        merge_idx++;
        board[i][j].val = 0;
        empty++;
        valid = true;
      }
      else {
        if (board[merge_idx][j].val != 0) {
          merge_idx++;
        }
        if (board[merge_idx][j].val == 0) { // slide left into empty slot
          board[merge_idx][j].val = board[i][j].val;
          board[i][j].val = 0;
          valid = true;
        }
      }
    }
  }
  return valid;
}

bool slideDown(Tile board[4][4], int &empty) {
  bool valid = false;
  for (int j = 0; j < 4; j++) {
    int merge_idx = 4 - 1; // index to merge with
    for (int i = (4 - 1) - 1; i >= 0; i--) {
      if ((i == merge_idx) || (board[i][j].val == 0)) {
        continue;
      }
      if (log2(board[i][j].val) == log2(board[merge_idx][j].val)) { // merge
        board[merge_idx][j].val += board[i][j].val;
        if (board[i][merge_idx].val == 2048) {
          std::cout << "You win!" << std::endl;
          exit(0);
        }
        merge_idx--;
        board[i][j].val = 0;
        empty++;
        valid = true;
      }
      else {
        if (board[merge_idx][j].val != 0) {
          merge_idx--;
        }
        if (board[merge_idx][j].val == 0) { // slide left into empty slot
          board[merge_idx][j].val = board[i][j].val;
          board[i][j].val = 0;
          valid = true;
        }
      }
    }
  }
  return valid;
}



int main() {
  srand(time(NULL));
  Tile board[4][4];

  int empty = 16;
  char action;
  while (true) {
    spawnTile(board, (rand() % 2 == 0) ? 2 : 4, empty);
    empty--;
    fluctuate(board, empty);
    printBoard(board);
    bool repeat = true;
    while (repeat) {
      std::cin >> action;
      switch (action) {
        case 'a':
          repeat = !slideLeft(board, empty);
          break;
        case 's':
          repeat = !slideDown(board, empty);
          break;
        case 'd':
          repeat = !slideRight(board, empty);
          break;
        case 'w':
          repeat = !slideUp(board, empty);
          break;
      }
    }
  }
}
