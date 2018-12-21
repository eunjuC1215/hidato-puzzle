#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MAXSIZE 100

typedef struct Point{
  int x, y;
}point;

point direction[8] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0},
                      {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

int puzzle[MAXSIZE][MAXSIZE];
int width, height;
int cnt = 0;

// n : 퍼즐을 채워나가는 index
bool solve(int r, int c, int n){

  //n이 마지막번호까지 도달했음 = 퍼즐을 solve 함
  if(n > cnt)
    return true;

  //이미 채운곳일 경우 false
  if(puzzle[r][c] != -1 && puzzle[r][c] != n)
    return false;

  //벽일 경우 false
  if(puzzle[r][c] == 0)
    return false;

  //좌표를 계속 바꾸며 옮길때, 그 방향에서 움직일수 없을시 다시 돌아와야한다. 그때를 대비해 backup 값으로 저장.
  int back = puzzle[r][c];

  puzzle[r][c] = n;

  point nextpos;
  for(int i = 0; i < 8; i++){
    nextpos.x = r+direction[i].x;
    nextpos.y = c+direction[i].y;

    if(nextpos.x >= 0 && nextpos.x < width &&
       nextpos.y >= 0 && nextpos.y < height &&
       puzzle[nextpos.x][nextpos.y] != 0){  //세그멘테이션 오류방지
         if(solve(nextpos.x, nextpos.y, n+1))
           return true;
       }
  }

  // 위에서 8방향을 돌아본 데서 다음 단계로 가지 못하면 원래대로 돌아옴
  puzzle[r][c] = back;
  return false;
}

int main(){
  //generator의 output.txt를 input으로 사용 
  ifstream input("output.txt");
  ofstream output("solved.txt");

  input >> width >> height;

  Point start;

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      input >> puzzle[i][j];

      if(puzzle[i][j] == 1){
        start.x = i;
        start.y = j;
      } // find starting point
      
      if(puzzle[i][j] != 0)
        cnt++;
    }
  }

  solve(start.x, start.y, 1);

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      output << puzzle[i][j] << " ";
    }
    output << endl;
  }

}
