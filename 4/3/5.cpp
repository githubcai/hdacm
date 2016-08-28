#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct Node{
    int x, y, num;
};

const int MAX = 9;
bool flag, col[MAX][MAX + 1], row[MAX][MAX + 1], block[MAX][MAX + 1];
char maze[MAX][MAX];
vector<Node> store;
int cnt;

void dfs(int c){
    if(flag) return;
    if(c == cnt){
        flag = true;
        auto iter = store.begin();
        for(int i = 0; i < MAX; ++i){
            if(maze[i][0] == '?'){
                printf("%d", iter->num);
                ++iter;
            }else{
                printf("%c", maze[i][0]);
            }
            for(int j = 1; j < MAX; ++j){
                if(maze[i][j] == '?'){
                    printf(" %d", iter->num);
                    ++iter;
               }else{
                    printf(" %c", maze[i][j]);
                }
            }
            printf("\n");
        }
        return;
    }
    for(int i = 1; i <= 9; ++i){
        if(!col[store[c].y][i] &&
            !row[store[c].x][i] &&
            !block[store[c].x / 3 * 3 + store[c].y / 3][i]){
            col[store[c].y][i] = block[store[c].x / 3 * 3 + store[c].y / 3][i] = row[store[c].x][i] = true;
            store[c].num = i;
            dfs(c + 1);
            col[store[c].y][i] = block[store[c].x / 3 * 3 + store[c].y / 3][i] = row[store[c].x][i] = false;
        }
    }
}

int main(){
    char ch[2];
    bool cf = false;
    while(scanf("%s", ch) != EOF){
        maze[0][0] = ch[0];
        for(int i = 1; i < MAX; ++i){
            scanf("%s", ch);
            maze[0][i] = ch[0];
        }
        for(int i = 1; i < MAX; ++i){
            for(int j = 0; j < MAX; ++j){
                scanf("%s", ch);
                maze[i][j] = ch[0];
            }
        }

        memset(col, 0, sizeof(col));
        memset(row, 0, sizeof(row));
        memset(block, 0, sizeof(block));
        store.clear(), cnt = 0;
        for(int i = 0; i < MAX; ++i){
            for(int j = 0; j < MAX; ++j){
                if(maze[i][j] == '?'){
                    Node t = {i, j, 0};
                    ++cnt;
                    store.push_back(t);
                }else{
                    col[j][maze[i][j] - '0'] = 
                    block[i / 3 * 3 + j / 3][maze[i][j] - '0'] = 
                    row[i][maze[i][j] - '0'] = true;
                }
            }
        }

        flag = false;
        if(cf){
            printf("\n");
        }else{
            cf = true;
        }
        dfs(0);
    }
}
