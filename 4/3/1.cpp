#include <cstdio>
#include <cstring>
#include <cmath>

struct Node{
    int x, y;
};

const int MAX = 7;
int N, M, T, dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, count;
bool vis[MAX][MAX], flag;
Node st, ed;

int dist(const Node &s, const Node &e){
    return fabs(s.x - e.x) + fabs(s.y - e.y);
}

void dfs(Node p){
    if(flag) return;
    if(p.x == ed.x && p.y == ed.y){
        if(T == count){
            flag = true;
        }
        return;
    }
    for(int i = 0; i < 4; ++i){
        Node next;
        next.x = p.x + dir[i][0];
        next.y = p.y + dir[i][1];
        if(next.x >= 0 && next.x < N &&
            next.y >= 0 && next.y < M &&
            !vis[next.x][next.y]){
            vis[next.x][next.y] = true;
            ++count;
            dfs(next);
            --count;
            vis[next.x][next.y] = false;
        }
    }
}

int main(){
    while(scanf("%d%d%d", &N, &M, &T) == 3 &&
        !(N == 0 && M == 0 && T == 0)){
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < N; ++i){
            char temp[MAX];
            scanf("%s", temp);
            for(int j = 0; j < M; ++j){
                switch(temp[j]){
                    case 'X':{
                        vis[i][j] = true;
                        break;
                    }
                    case 'D':{
                        ed.x = i, ed.y = j;
                        break;
                    }
                    case 'S':{
                        st.x = i, st.y = j;
                        break;
                    }
                    default:{
                        break;
                    }
                }
            }
        }
        int temp = dist(st, ed);
        flag = false;
        count = 0;
        if((T - temp) % 2 == 0){
            vis[st.x][st.y] = true;
            dfs(st);
        }
        if(flag){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
}
