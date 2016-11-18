#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 7;
int maze[MAX][MAX], step, dir[8] = {2, 4, 2, 4, 4, 2, 4, 2};
char path[100];
bool dflag[8] = {true, true, false, false, false, false, true, true};

int getH(){
    int num[4] = {0};
    for(int i = 2; i < 5; ++i){
        ++num[maze[i][2]];
        ++num[maze[i][4]];
    }
    ++num[maze[2][3]];
    ++num[maze[4][3]];
    return max(num[1], max(num[2], num[3]));
}

/* true: 向上; false: 向下 */
void tranCol(int col, bool flag){
    int temp;
    if(flag){
        temp = maze[0][col];
        for(int i = 0; i < 6; ++i){
            maze[i][col] = maze[i + 1][col];
        }
        maze[6][col] = temp;
    }else{
        temp = maze[6][col];
        for(int i = 6; i > 0; --i){
            maze[i][col] = maze[i - 1][col];
        }
        maze[0][col] = temp;
    }
}

/* true: 向左; false: 向右 */
void tranRow(int row, bool flag){
    int temp;
    if(flag){
        temp = maze[row][0];
        for(int i = 0; i < 6; ++i){
            maze[row][i] = maze[row][i + 1];
        }
        maze[row][6] = temp;
    }else{
        temp = maze[row][6];
        for(int i = 6; i > 0; --i){
            maze[row][i] = maze[row][i - 1];
        }
        maze[row][0] = temp;
    }
}

bool dfs(int cnt){
    int temp = getH();
    if(cnt == step && temp == 8) return true;
    if(cnt + (8 - temp) > step) return false;
    for(int i = 0; i < 8; ++i){
        char comm = i + 'A';
        path[cnt] = comm;
        if(comm == 'A' || comm == 'B' || comm == 'E' || comm == 'F'){
            tranCol(dir[i], dflag[i]);
            if(dfs(cnt + 1)) return true;
            tranCol(dir[i], !dflag[i]);
        }else{
            tranRow(dir[i], dflag[i]);
            if(dfs(cnt + 1)) return true;
            tranRow(dir[i], !dflag[i]);
        }
    }
    return false;
}

int main(){
    while(scanf("%d", &maze[0][2]) != EOF && maze[0][2]){
        scanf("%d", &maze[0][4]);
        for(int i = 1; i < 7; ++i){
            if(i == 2 || i == 4){
                for(int j = 0; j < 7; ++j){
                    scanf("%d", &maze[i][j]);
                }
            }else{
                scanf("%d%d", &maze[i][2], &maze[i][4]);
            }
        }
        if(getH() == 8){
            printf("No moves needed\n%d\n", maze[2][2]);
            continue;
        }
        step = 0;
        while(!dfs(0)){
            ++step;
        }
        path[step] = '\0';
        printf("%s\n%d\n", path, maze[2][2]);
    }
    return 0;
}
