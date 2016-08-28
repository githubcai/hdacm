#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node{
    char lock[5];
    int step;
};
bool vis[10][10][10][10];
char dir1[8][4] = {
    {1, 0, 0, 0},
    {-1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, -1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, -1, 0},
    {0, 0, 0, 1},
    {0, 0, 0, -1}
};
int dir2[3][2] = {{0, 1}, {1, 2}, {2, 3}};
Node st, ed;

bool check(Node &n){
    bool flag = true;
    for(int i = 0; i < 4; ++i){
        if(n.lock[i] == 10) n.lock[i] = 1;
        if(n.lock[i] == 0) n.lock[i] = 9;
    }
    if(vis[n.lock[0]][n.lock[1]][n.lock[2]][n.lock[3]]){
        flag = false;
    }else{
        vis[n.lock[0]][n.lock[1]][n.lock[2]][n.lock[3]] = true;
    }
    return flag;
}

int bfs(){
    queue<Node> que;
    memset(vis, 0, sizeof(vis));
    vis[st.lock[0]][st.lock[1]][st.lock[2]][st.lock[3]] = true;
    
    st.step = 0;
    que.push(st);
    while(!que.empty()){
        Node now = que.front();
        que.pop();
        if(strcmp(now.lock, ed.lock) == 0){
            return now.step;
        }
        for(int i = 0; i < 8; ++i){
            Node next;
            next.lock[0] = now.lock[0] + dir1[i][0];
            next.lock[1] = now.lock[1] + dir1[i][1];
            next.lock[2] = now.lock[2] + dir1[i][2];
            next.lock[3] = now.lock[3] + dir1[i][3];
            if(check(next)){
                next.step = now.step + 1;
                que.push(next);
            }
        }
        for(int i = 0; i < 3; ++i){
            Node next;
            memcpy(next.lock, now.lock, sizeof(now.lock));
            char temp = next.lock[dir2[i][0]];
            next.lock[dir2[i][0]] = next.lock[dir2[i][1]];
            next.lock[dir2[i][1]] = temp;
            if(check(next)){
                next.step = now.step + 1;
                que.push(next);
            }
        }
    }
    return -1;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        char f[5], s[5];
        scanf("%s%s", f, s);
        for(int i = 0; i < 4; ++i){
            st.lock[i] = f[i] - '0';
            ed.lock[i] = s[i] - '0';
        }
        printf("%d\n", bfs());
    }
    return 0;
}
