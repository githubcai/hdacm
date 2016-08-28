#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node{
    int i, step;
};

const int MAX = 201;
int N, A, B, Ki[MAX], dir[2] = {1, -1};
bool vis[MAX];

int bfs(){
    Node st = {A, 0};
    queue<Node> que;
    memset(vis, 0, sizeof(vis));
    que.push(st);
    vis[A] = true;
    while(!que.empty()){
        Node next;
        st = que.front();
        que.pop();
        if(st.i == B){
            return st.step;
        }
        for(int i = 0; i < 2; ++i){
            next.i = st.i + Ki[st.i] * dir[i];
            if(!vis[next.i] && next.i >= 1 && next.i <= N){
                next.step = st.step + 1;
                vis[next.i] = true;
                que.push(next);
            }
        }
    }
    return -1;
}

int main(){
    while(scanf("%d", &N) == 1 && N != 0){
        scanf("%d%d", &A, &B);
        for(int i = 1; i <= N; ++i){
           scanf("%d", &Ki[i]); 
        }
        int step = bfs();
        printf("%d\n", step);
    }
    return 0;
}
