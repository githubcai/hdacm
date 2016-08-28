#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int NMAX = 10000, MMAX = 20000;
int pre[NMAX], n, m, A[MMAX], B[MMAX], rd[NMAX], total;
char oper[MMAX];
vector<int> vect[NMAX];

void init(){
    for(int i = 0; i < n; ++i){
        pre[i] = i;
        vect[i].clear();
    }
    memset(rd, 0, sizeof(rd));
}

int find(int x){
    if(x == pre[x]) return x;
    int temp = pre[x];
    pre[x] = find(pre[x]);
    return pre[x];
}

void merge(int a, int b){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar != br){
        pre[ar] = br;
        --total;
    }
}

void topoSort(){
    queue<int> que;
    bool uncertain = false;
    for(int i = 0; i < n; ++i){
        if(0 == rd[i] && i == find(i)){
            que.push(i);
        }
    }
    while(!que.empty()){
        if(que.size() > 1){
            uncertain = true;
        }
        int cur = que.front();
        que.pop();
        --total;
        for(auto iter = vect[cur].begin(); iter != vect[cur].end(); ++iter){
            if(--rd[*iter] == 0){
                que.push(*iter);
            }
        }
    }
    if(total > 0){
        printf("CONFLICT\n");
    }else if(uncertain){
        printf("UNCERTAIN\n");
    }else{
        printf("OK\n");
    }
}

int main(){
    while(scanf("%d%d", &n, &m) == 2){
        init();
        total = n;
        for(int i = 0; i < m; ++i){
            scanf("%d %c %d", &A[i], &oper[i], &B[i]);
            if('=' == oper[i]){
                merge(A[i], B[i]);
            }
        }
        for(int i = 0; i < m; ++i){
            if('=' == oper[i]) continue;
            int a, b;
            a = find(A[i]), b = find(B[i]);
            if('>' == oper[i]){
                vect[a].push_back(b);
                ++rd[b];
            }else{
                vect[b].push_back(a);
                ++rd[a];
            }
        }
        topoSort();
    }
    return 0;
}
