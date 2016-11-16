#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 362881, OBJ = 46234, fac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
struct Node{
    int s[9], loc, status, len;
};

char paths[MAX][40];
bool vis[MAX];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char cdir[5] = "durl";

int cantor(int s[9]){
    int sum = 0;
    for(int i = 0; i < 9; ++i){
        int num = 0;
        for(int j = i + 1; j < 9; ++j){
            if(s[i] > s[j]) ++num;
        }
        sum += num * fac[9 - i - 1];
    }
    return sum + 1;
}

void bfs(){
    queue<Node> que;
    Node now, next;
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i < 9; ++i){
        now.s[i - 1] = i;
    }
    now.s[8] = 0, now.loc = 8;
    now.status = OBJ, now.len = 0;
    paths[OBJ][0] = 0;
    vis[OBJ] = true;
    que.push(now);
    while(!que.empty()){
        now = que.front();
        que.pop();
        int x = now.loc / 3, y = now.loc % 3;
        for(int i = 0; i < 4; ++i){
            int tx = x + dir[i][0], ty = y + dir[i][1];
            if(tx >= 0 && tx < 3 && ty >= 0 && ty < 3){
                memcpy(next.s, now.s, sizeof(now.s));
                next.loc = tx * 3 + ty;
                next.s[now.loc] = now.s[next.loc];
                next.s[next.loc] = now.s[now.loc];
                next.status = cantor(next.s);
                if(!vis[next.status]){
                    vis[next.status] = true;
                    next.len = now.len + 1;
                    paths[next.status][0] = next.len;
                    for(int j = 1; j <= now.len; ++j){
                        paths[next.status][j] = paths[now.status][j];
                    }
                    paths[next.status][next.len] = cdir[i];
                    que.push(next);
                }
            }
        }
    }
}

int main(){
    char ch[2];
    int s[9];
    bfs();
    while(scanf("%s", ch) != EOF){
        s[0] = ((ch[0] == 'x') ? 0 : (ch[0] - '0'));
        for(int i = 1; i < 9; ++i){
            scanf("%s", ch);
            s[i] = ((ch[0] == 'x') ? 0 : (ch[0] - '0'));
        }
        int status = cantor(s);
        if(vis[status]){
            for(int i = paths[status][0]; i > 0; --i){
                printf("%c", paths[status][i]);
            }
            printf("\n");
        }else{
            printf("unsolvable\n");
        }
    }
    return 0;
}
