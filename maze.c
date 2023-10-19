#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_SIZE 2250

// 效率更低
//int dir[4][2] = {
//        {-1, 0},  // 上
//        {0, -1},  // 左
//        {1, 0},   // 下
//        {0, 1},    // 右
//};

// 效率更高
int dir[4][2] = {
        {1, 0},   // 下
        {0, 1},    // 右
        {-1, 0},  // 上
        {0, -1},  // 左
};

typedef struct {
    int data[MAX_SIZE][2];
    int top;
} Stack;
void HideM();
void SetPosition(int x, int y);
void Menu();
void MakeWay(int** map, int x, int y, int size);
int** DefaultMap();
int** InitMap(int size);
int** FixMap(int** map, int size);
void PrintMap(int** map, int size);
void FreeMap(int** map, int size);
void MapChoice();
void initialize(Stack* stack);
int isEmpty(Stack* stack);
int isFull(Stack* stack);
void push(Stack* stack, int item1, int item2);
void pop(Stack* stack, int* item1, int* item2);
int AutoPlay(int** map, int size);
int Check(int** map, int x, int y);



int main() {
    HideM();
    Menu();
    return 0;
}

void Menu() {
    int maze, size;
    int** map;
    MapChoice();
    printf("\nPlease input your choice [1]/2:");
    scanf("%d", &maze);
    rewind(stdin);
    if (maze != 1 && maze != 2) {
        printf("Illegal input !!!\n");
        printf("It will be the default choice: 1\n");
        maze = 1;
    }
    if (maze == 1) {
        map = DefaultMap();
        size = 15;
    } else {
        printf("\nPlease input the size of maze:");
        scanf("%d", &size);
        rewind(stdin);
        if (size < 15) {
            printf("It's too small !!!\n");
            printf("It will be the default size: 15\n");
            size = 15;
            Sleep(2000);
        }else if (size > 50) {
            printf("It's too big !!!\n");
            printf("It will be the default size: 15\n");
            size = 15;
            Sleep(2000);
        }
        map = InitMap(size);
    }
    system("cls");
    PrintMap(map, size);
    int step = AutoPlay(map, size);
    SetPosition(size + 5, 0);
    printf("Congratulations! Completed the maze in a total of %d steps!\n", step);
}

int AutoPlay(int** map, int size) {
    Stack way;
    initialize(&way);
    int x = 1, y = 1, step = 0;
    push(&way, 1, 0);
    SetPosition(1, 1);
    printf("㊣");
    while (!isEmpty(&way)) {
        step ++;
        int nx, ny;
        int status = Check(map, x, y);
        if (status == -1) {
            pop(&way, &x, &y);
            pop(&way, &x, &y);
        } else {
            nx = x + dir[status][0];
            ny = y + dir[status][1];
            push(&way, x, y);
            push(&way, nx, ny);
            SetPosition(x, y);
            switch (status) {
//                case 0:
//                    printf("↑");
//                    break;
//                case 1:
//                    printf("←");
//                    break;
//                case 2:
//                    printf("↓");
//                    break;
//                case 3:
//                    printf("→");
//                    break;
                case 0:
                    printf("↓");
                    break;
                case 1:
                    printf("→");
                    break;
                case 2:
                    printf("↑");
                    break;
                case 3:
                    printf("←");
                    break;
                default:
                    break;
            }
            SetPosition(nx, ny);
            printf("㊣");
            x = nx;
            y = ny;
            if (nx == size && ny == size){
                break;
            }
        }
        Sleep(10);
    }
    FreeMap(map, size);
    return step;
}

int Check(int** map, int x, int y) {
    for (int i = 0; i < 4; i++) {
        if (map[x + dir[i][0]][y + dir[i][1]] == 1) {
            // 走过的
            map[x][y] = 2;
            return i;
        }
    }
    // 死路的
    map[x][y] = 3;
    SetPosition(x, y);
    printf("Ｘ");
    return -1;
}

void MapChoice() {
    printf("-----------------------------------------------------------------\n");
    printf("--                                                             --\n");
    printf("--                          Map                                --\n");
    printf("--                                                             --\n");
    printf("--                      1. Default                             --\n");
    printf("--                      2. Random                              --\n");
    printf("--                                                             --\n");
    printf("--                                                             --\n");
    printf("-----------------------------------------------------------------\n");

}

int** DefaultMap() {
    int size = 15;
    int data[][17] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {-1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
            {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
            {0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
            {0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0},
            {0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, -1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int **map = (int**)malloc((size + 2) * sizeof(int *));
    for (int i = 0; i < (size + 2); i++) {
        map[i] = (int*)calloc((size + 2), sizeof(int));
    }
    for (int i = 0; i < (size + 2); i++) {
        for (int j = 0; j < (size + 2); j++) {
            map[i][j] = data[i][j];
        }
    }
    return map;
}

int** InitMap(int size) {
    size += 4;
    srand(time(0));
    int **map = (int**)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        map[i] = (int*)calloc(size, sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            map[i][j] = 0;
        }
    }
    for (int i = 0; i < size; i++){
        map[i][0] = 1;
        map[0][i] = 1;
        map[i][size - 1] = 1;
        map[size - 1][i] = 1;
    }
    MakeWay(map, 2, 2, size);
    map[2][1] = 1;
    map[2][2] = 1;
    for (int i = size - 3; i >= 0; i--) {
        if (map[i][size - 3] == 1) {
            map[i][size - 2] = 1;
            break;
        }
    }
    map = FixMap(map, size);
    return map;
}

void PrintMap(int** map, int size) {
    size += 2;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (map[i][j] == 1) {
                printf("□");
            } else if (map[i][j] == 0){
                printf("■");
            }  else if (map[i][j] == -1){
                printf("〓");
            }
        }
        printf("\n");
    }
}

void MakeWay(int** map, int x, int y, int size) {
    int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = direction[0][0];
        direction[0][0] = direction[r][0];
        direction[r][0] = temp;

        temp = direction[0][1];
        direction[0][1] = direction[r][1];
        direction[r][1] = temp;
    }
    for (int i = 0; i < 4; i++) {
        int dx = x;
        int dy = y;

        int range = 1;
        while (range>0) {
            dx += direction[i][0];
            dy += direction[i][1];

            if (map[dx][dy] == 1) {
                break;
            }

            int count = 0;
            for (int j = dx - 1; j < dx + 2; j++) {
                for (int k = dy - 1; k < dy + 2; k++) {
                    //abs(j - dx) + abs(k - dy) == 1 确保只判断九宫格的四个特定位置
                    if (abs(j - dx) + abs(k - dy) == 1 && map[j][k] == 1) {
                        count++;
                    }
                }
            }

            if (count > 1) {
                break;
            }

            --range;
            map[dx][dy] = 1;
        }

        if (range <= 0) {
            MakeWay(map, dx, dy, size);
        }
    }
}

int** FixMap(int** map, int size) {
    int ns = size - 2;
    int **new = (int**)malloc(ns * sizeof(int *));
    for (int i = 0; i < ns; i++) {
        new[i] = (int*)calloc(ns, sizeof(int));
    }
    for (int i = 0; i < ns; i++) {
        for (int j = 0; j < ns; j++) {
            new[i][j] = map[i + 1][j + 1];
        }
    }
    for (int i = 0; i < size; i++) free(map[i]);
    free(map);
    for (int i = 0; i < ns; i++){
        new[i][0] = 0;
        new[0][i] = 0;
        new[i][ns - 1] = 0;
        new[ns - 1][i] = 0;
    }
    new[1][0] = -1;
    new[ns - 2][ns - 1] = -1;
    new[ns - 2][ns - 2] = 1;
    return new;
}

void FreeMap(int** map, int size) {
    for (int i = 0; i < size - 2; i++) free(map[i]);
    free(map);
}


void HideM() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = {1, 0};
    SetConsoleCursorInfo(hout, &cor_info);
}

void SetPosition(int x, int y) {
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = (short)(y * 2);
    cor.Y = (short)x;
    SetConsoleCursorPosition(hout, cor);
}

void initialize(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int item1, int item2) {
    if (isFull(stack)) {
        return;
    }
    stack->data[++stack->top][0] = item1;
    stack->data[stack->top][1] = item2;
}

void pop(Stack* stack, int* item1, int* item2) {
    if (isEmpty(stack)) {
        return;
    }
    *item1 = stack->data[stack->top][0];
    *item2 = stack->data[stack->top][1];
    stack->top--;
}
