#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define height 10
#define width 10
#define number 15

void test_printmaps(char map[height][width], int mines[height][width]); //列印地圖狀況
void initial(char map[height][width], int mines[height][width], int mines_number); //創建地圖(介面,地圖狀況,地雷個數)
void chain(char map[height][width], int mines[height][width], int row, int col, int Height, int Weight); //連鎖(介面,地圖狀況,選擇行,選擇列,地圖長,地圖寬)

int main(){
    char map[height][width] = {' '}; //使用者看到的介面
    int mines[height][width] = {}; //地雷狀況: 0 無地雷, 1 有地雷, 2 標記, 3 翻開
    int mines_number = number;
    int Height = height;
    int Width = width;
    int row, col ;
    initial(map, mines, mines_number);
    test_printmaps(map, mines);
    scanf("%d%d",&row,&col);
    row = row-1;
    col = col-1;
    chain(map, mines, row, col, Height, Width);
    test_printmaps(map, mines);

    system("pause");
    return 0;
}

void initial(char map[height][width], int mines[height][width], int mines_number){
    srand(time(NULL));
    for(int i=0 ; i<height ; i++){
        for(int j=0 ; j<width ; j++){
            map[i][j] = '*' ;
            mines[i][j] = 0 ;
        }
    } 
    for(int n=0 ; n<mines_number ;){
        int row = rand()%height;
        int col = rand()%width;
        if(mines[row][col] != 1){
            mines[row][col] = 1 ;
            n++ ;
        }
    }    
}
void test_printmaps(char map[height][width], int mines[height][width]){
    for(int i=0 ; i<height ; i++){
        for(int j=0 ; j<width ; j++){
            printf("%2c%2d  ",map[i][j],mines[i][j]);
        }
        printf("\n");
    } 
}
void chain(char map[height][width], int mines[height][width], int row, int col, int Height, int Weight){
    int count = 0;

    for(int i=row-1 ; i<=row+1 ; i++){
        for(int j=col-1 ; j<=col+1 ; j++){
            if(i<0 || i> Height-1 || j<0 || j >Weight-1){
                continue;
            }
            if(mines[i][j] == 1){
                count++;
            }
        }
    }
    map[row][col] = '0' + count ;
}