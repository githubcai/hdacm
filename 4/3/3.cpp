#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct Node{
    int n, step;
    vector<char> store;
};

const int MAX = 1000;
int N, K, M, KM, ed;
bool vis[MAX];

void bfs(int n){
    queue<Node> que;
    int temp = (n % KM + KM) % KM;
    memset(vis, 0, sizeof(vis));
    Node st = {temp, 0};
    vis[temp % K] = true;
    que.push(st);
    while(!que.empty()){
        st = que.front();
        que.pop();
        if(ed == (st.n % K)){
            printf("%d\n", st.step);
            for(auto iter = st.store.begin(); iter != st.store.end(); ++iter){
                printf("%c", *iter);
            }
            printf("\n");
            return;
        }
        for(int i = 0; i < 4; ++i){
            Node next;
            copy(st.store.begin(), st.store.end(), back_inserter(next.store));
            switch(i){
                case 0:{
                    next.n = (st.n + M) % KM;
                    next.store.push_back('+');
                    break;
                }
                case 1:{
                    next.n = ((st.n - M) % KM + KM) % KM;
                    next.store.push_back('-');
                    break;
                }
                case 2:{
                    next.n = st.n * M % KM;
                    next.store.push_back('*');
                    break;
                }
                case 3:{
                    next.n = (st.n % M + M) % M; 
                    next.store.push_back('%');
                    break;
                }
            }
            if(!vis[next.n % K]){
                next.step = st.step + 1;
                vis[next.n % K] = true;
                que.push(next);
            }
        }
    }
    printf("0\n");
}

int main(){
    while(scanf("%d%d%d", &N, &K, &M) == 3 &&
        !(N == 0 && K == 0 && M == 0)){
        ed = (((N + 1) % K) + K) % K;
        KM = K * M;
        bfs(N);
    }
    return 0;
}
