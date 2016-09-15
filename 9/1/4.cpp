#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

struct Node{
    int x[4], y[4], step;
};

int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
map<int, int> vis;
bool maze[8][8], flag;

void init(){
    flag = false;
    vis.clear();
}

Node decode(int x){
    Node node;
    for(int i = 0; i < 4; ++i){
        node.x[i] = x & 7;
        x >>= 3;
        node.y[i] = x & 7;
        x >>= 3;
    }
    node.step = x & 7;
    return node;
}

int encode(Node node){
    int ret = 0;
    ret |= node.step;
    for(int i = 0; i < 4; ++i){
        for(int j = i + 1; j < 4; ++j){
            if(node.x[i] > node.x[j]){
                int temp;
                temp= node.x[i]; node.x[i] = node.x[j]; node.x[j] = temp;
                temp = node.y[i]; node.y[i] = node.y[j]; node.y[j] = temp;
            }else if(node.x[i] == node.x[j]){
                if(node.y[i] > node.y[j]){
                    int temp = node.y[i];
                    node.y[i] = node.y[j];
                    node.y[j] = temp;
                }
            }
        }
    }
    for(int i = 3; i >= 0; --i){
        ret <<= 3;
        ret |= node.y[i];
        ret <<= 3;
        ret |= node.x[i];
    }
    return ret;
}

void bfs(int st, int s){
    queue<int> que;
    que.push(st);
    vis[st] = s;
    while(!que.empty()){
        Node now = decode(que.front());
        que.pop();
        memset(maze, 0, sizeof(maze));
        for(int i = 0; i < 4; ++i){
            maze[now.x[i]][now.y[i]] = true;
        }
        for(int i = 0; i < 4; ++i){
            Node next; memcpy(&next, &now, sizeof(Node));
            next.step += 1;
            for(int j = 0; j < 4; ++j){
                next.x[i] = now.x[i] + dir[j][0];
                next.y[i] = now.y[i] + dir[j][1];
                int code = -1;
                if(next.x[i] >= 0 && next.x[i] < 8 && next.y[i] >= 0 && next.y[i] < 8){
                    if(!maze[next.x[i]][next.y[i]]){
                        int temp = next.step;
                        next.step = 0;
                        code = encode(next);
                        next.step = temp;
                    }else{
                        next.x[i] += dir[j][0];
                        next.y[i] += dir[j][1];
                        if(next.x[i] >= 0 && next.x[i] < 8 && next.y[i] >= 0 && next.y[i] < 8){
                            if(!maze[next.x[i]][next.y[i]]){
                                int temp = next.step;
                                next.step = 0;
                                code = encode(next);
                                next.step = temp;
                            }
                        }
                    }
                }
                if(code != -1){
                    if(vis[code] == 0){
                        vis[code] = s;
                        if(next.step < 4){
                            que.push(encode(next));
                        }
                    }else if(vis[code] != s){
                        flag = true;
                        return;
                    }
                }
            }
        }
    }
}

int main(){
    Node st;
    while(scanf("%d%d", &st.x[0], &st.y[0]) != EOF){
        init();
        st.step = 0;
        for(int i = 1; i < 4; ++i){
            scanf("%d%d", &st.x[i], &st.y[i]);
        }
        for(int i = 0; i < 4; ++i){
            --st.x[i], --st.y[i];
        }
        bfs(encode(st), 1);
        for(int i = 0; i < 4; ++i){
            scanf("%d%d", &st.x[i], &st.y[i]);
        }
        for(int i = 0; i < 4; ++i){
            --st.x[i], --st.y[i];
        }
        bfs(encode(st), 2);
        if(flag){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
