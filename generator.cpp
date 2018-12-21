#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

#define MAXSIZE 100
#define MAXN 10001


typedef struct Point{
  int x, y;
}point;

point direction[8] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0},
                      {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
//수직, 수평, 대각선 방향

int puzzle[MAXSIZE][MAXSIZE], check[MAXSIZE][MAXSIZE];
int arr[MAXN];
/* puzzle : index가 표시되는 2차원배열
   check  : 들린 곳인지 아닌지 mark하는 2차원배열 
   arr    : 랜덤으로 고른 삭제되어질 인덱스 표시
            0 -> -1로 표시(삭제)    1 -> 중간값(삭제하지 않음) */


int Gen(int width, int height, point pos, int cnt, int N){
  int i;
  point next;


  if(cnt == N)  return 1;
  //마지막번호까지 퍼즐을 완성함

  for(i = 0; i < 8; i++){
    next.x = pos.x + direction[i].x;
    next.y = pos.y + direction[i].y;
 
    if(next.x >= 0 && next.x < width &&
       next.y >= 0 && next.y < height &&      //조건1 : x, y가 범위에 넘어가지 않아야함
       check[next.x][next.y] != 1 &&          //조건2 : 이미 mark한 곳이 아니어야 함
       puzzle[next.x][next.y] != 0){          //조건3 : 벽(그리드 밖)이 아니어야함
         check[next.x][next.y] = 1;
         if(arr[cnt+1] == 0)  puzzle[next.x][next.y] = -1;  //중간값이 아닐 경우 삭제
         else puzzle[next.x][next.y] = cnt+1;               //중간값

         if(Gen(width, height, next, cnt+1, N))  return 1;
         //만약 다음 번호로 넘어갈 수 있다면 종료 

         check[next.x][next.y] = 0;
         //그렇지 않을 경우 mark해제
       }
  }
  return 0;
}


int main(){
  ifstream input;
  input.open("input.txt");
  ofstream output;
  output.open("output.txt");


  int width, height;
  input >> width >> height;
  point start;


  int N = 0;        
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      input >> puzzle[i][j];
      if(puzzle[i][j] == 1) N++;
      check[i][j] = 0;
    }
  }
  srand(time(NULL));
  while(1)
  {
    start.x = rand() % width;
    start.y = rand() % height;
    if(puzzle[start.x][start.y] == 1) break;
  }
  // 랜덤으로 0이 아닌 시작점 잡기


  for(int i = 0; i <= N; i++) arr[i] = 1;
  int index = 1;
  while(index < N){
    int randtmp = rand()%4 +1;
    for(int i = 1; i <= randtmp; i++){
      index ++;
      if(index >= N) break;
      arr[index] = 0;
    }
    index++;
  }
  // 랜덤으로 중간값 삭제를 위해 삭제할 값들을 arr배열에 체크해둠

  check[start.x][start.y] = 1;
  puzzle[start.x][start.y] = 1;
  Gen(width, height, start, 1, N);

  output << width << " " << height << endl;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      output << puzzle[i][j] << " ";
    }
    output << endl;
  }
}
