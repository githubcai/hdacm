#include <vector>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct Node{
    int num;
    friend bool operator<(const Node &a, const Node &b){
        return a.num > b.num;
    }
};

const int MAX = 501;
int rd[MAX], N, M;
vector<int> vect[MAX];

void init(){
    memset(rd, 0, sizeof(rd));
    for(int i = 1; i <= N; ++i){
       vect[i].clear(); 
    }
}

void topoSort(){
    priority_queue<Node> que;
    bool isFirst = true;
    for(int i = 1; i <= N; ++i){
        if(rd[i] == 0){
            Node temp = {i};
            que.push(temp);
        }
    }
    while(!que.empty()){
        Node now = que.top();
        que.pop();
        if(isFirst){
            isFirst = false;
            printf("%d", now.num);
        }else{
            printf(" %d", now.num);
        }
        for(auto iter = vect[now.num].begin(); iter != vect[now.num].end(); ++iter){
            if(--rd[*iter] == 0){
                Node temp = {*iter};
                que.push(temp);
            }
        }
    }
    printf("\n");
}

int main(){
    while(scanf("%d%d", &N, &M) == 2){
        init();
        for(int i = 0; i < M; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            vect[a].push_back(b);
            ++rd[b];
        }
        topoSort();
    }
    return 0;
}
