#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define height 10
#define width 10
#define number 15

void test_printmaps(char map[height][width], int mines[height][width]); //列印地圖狀況
void menu();
void Game(int Height, int Width, int mines_number);
void initial(char map[height][width], int mines[height][width], int mines_number); //創建地圖(介面,地圖狀況,地雷個數)
void chain(char map[height][width], int mines[height][width], int row, int col, int Height, int Width); //連鎖(介面,地圖狀況,選擇行,選擇列,地圖長,地圖寬)
void check(char map[height][width], int mines[height][width], int Height, int Width);
int remain(char map[height][width], int Height, int Width);
void printmap(char map[height][width], int Height, int Width);


int main(){
    int mines_number = number;
    int Height = height;
    int Width = width;
    int input = 0;
    menu();
    do{
        printf("請輸入：");
        scanf("%d", &input);
        if(input == 1){
            printf("開始遊戲 %d x %d, %d個地雷\n", Height, Width, mines_number);
            Game(Height ,Width, mines_number);
        }
        else if(input == 0){
            printf("掰掰~\n");
        }
        else{
            printf("輸入錯誤!\n");
        }
    }while(input != 0);
    system("pause");
    return 0;
}

void Game(int Height, int Width, int mines_number){
    char map[Height][Width]; //使用者看到的介面 * 為翻  x 標記
    int mines[Height][Width]; //地雷狀況: 0 無地雷, 1 有地雷,
    int row, col ;
    int count;
    initial(map, mines, mines_number);
    test_printmaps(map, mines);
    printmap(map,Height,Width);
    while(1){
        printf("輸入座標：");
        scanf("%d%d",&row,&col);
        if(row > 0 && row <= Height && col > 0 && col <= Width){
            row = row-1;
            col = col-1;
            if(mines[row][col] == 1){
                printf("Game over\n");
                break;
            }
            else{
                chain(map,mines,row,col,Height,Width);
                printmap(map,Height,Width);
                count = remain(map,Height,Width);
                if(count == mines_number){
                    printf("恭喜通關\n");
                    break;
                }
            }
        }
        else{
            printf("超出邊界,請重新輸入\n");
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

void menu(){
    printf( "-----------------------------\n"\
            "          1 開始遊戲\n"\
            "          0 退出遊戲\n"\
            "-----------------------------\n");
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

void chain(char map[height][width], int mines[height][width], int row, int col, int Height, int Width){
    int count = 0;
    for(int i=row-1 ; i<=row+1 ; i++){
        for(int j=col-1 ; j<=col+1 ; j++){
            if(i<0 || i> Height-1 || j<0 || j >Width-1){
                continue;
            }
            if(mines[i][j] == 1){
                count++;
            }
        }
    }
    if(count == 0){
        map[row][col] = '0';
        if(row-1 >= 0 && map[row-1][col] == '*'){
            chain(map, mines, row-1, col, Height, Width);
        }
        if(row+1 < Height && map[row+1][col] == '*'){
            chain(map, mines, row+1, col, Height, Width);
        }
        if(col-1 >= 0 && map[row][col-1] == '*'){
            chain(map, mines, row, col-1, Height, Width);
        }
        if(col+1 >= 0 && map[row][col+1] == '*'){
            chain(map, mines, row, col+1, Height, Width);
        }
    }
    else{
        map[row][col] = '0' + count;
    }
}
void check(char map[height][width], int mines[height][width], int Height, int Width){
    int row, col;
    printf("輸入座標：");
    scanf("%d%d", &row, &col);


}
int remain(char map[height][width], int Height, int Width){
    int count = 0 ;
    for(int i=0 ; i < Height ; i++){
        for(int j=0 ; j < Width ; j++){
            if(map[i][j] == '*'){
                count++ ;
            }
        }
    }
    return count;
}

void printmap(char map[height][width], int Height, int Width){
    printf("—");
    for(int i=0 ; i <= Width ; i++){
        printf("——————");
    }
    printf("—\n");

    for(int i=0 ; i <= Width ; i++){
        printf("| %3d ", i);
    }
    printf("|\n");
    for(int i=0 ; i <Height ; i++){
        for(int j=0 ; j <= Width+1 ; j++){
            printf("|");
            if(j <= Width){
                printf("—————");
            }
        }
        printf("\n");
        printf("| %3d ", i+1);
        for(int j=0 ; j < Width ; j++){
            printf("|");
            printf("  %c  ", map[i][j]);
        }
        printf("|\n");
    }
    printf("—");
    for(int i=0 ; i <= Width ; i++){
        printf("——————");
    }
    printf("—");
}
