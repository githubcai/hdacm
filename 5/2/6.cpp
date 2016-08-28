#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 2000;
vector<int> vect[3][MAX];
int rd[3][MAX], n, R, result[3][MAX];

void init(){
    memset(rd, 0, sizeof(rd));
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 2 * n; ++j){
            vect[i][j].clear();
        }
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < n; ++j){
            vect[i][2 * j + 1].push_back(2 * j);
            ++rd[i][2 * j];
        }
    }
}

bool topoSort(int s){
    queue<int> que;
    int total = 2 * n;
    for(int i = 0; i < 2 * n; ++i){
        if(rd[s][i] == 0) que.push(i);
    }
    while(!que.empty()){
        int now = que.front();
        que.pop();
        result[s][now] = total--;
        for(auto iter = vect[s][now].begin(); iter != vect[s][now].end(); ++iter){
            if(--rd[s][*iter] == 0) que.push(*iter);
        }
    }
    if(total > 0){
        return false;
    }else{
        return true;
    }
}

int main(){
    int cnt = 0;
    while(scanf("%d %d\n", &n, &R) == 2 && !(n == 0 && R == 0)){
        ++cnt;
        init();
        for(int i = 0; i < R; ++i){
            char c;
            int a, b;
            scanf("%c %d %d\n", &c, &a, &b);
            switch(c){
                case 'I':{
                    for(int i = 0; i < 3; ++i){
                        vect[i][2 * (a - 1) + 1].push_back(2 * (b - 1));
                        ++rd[i][2 * (b - 1)];
                        vect[i][2 * (b- 1) + 1].push_back(2 * (a - 1));
                        ++rd[i][2 * (a - 1)];
                    }
                    break;
                }
                case 'X':{
                    vect[0][2 * (b - 1)].push_back(2 * (a - 1) + 1);
                    ++rd[0][2 * (a - 1) + 1];
                    break;
                }
                case 'Y':{
                    vect[1][2 * (b - 1)].push_back(2 * (a - 1) + 1);
                    ++rd[1][2 * (a - 1) + 1];
                    break;
                }
                case 'Z':{
                    vect[2][2 * (b - 1)].push_back(2 * (a - 1) + 1);
                    ++rd[2][2 * (a - 1) + 1];
                    break;
                }
            }
        }
        bool flag = true;
        for(int i = 0; i < 3; ++i){
            flag = topoSort(i);
            if(!flag) break;
        }
        if(flag){
            printf("Case %d: POSSIBLE\n", cnt);
            for(int i = 0; i < n; ++i){
                printf("%d %d %d %d %d %d\n", result[0][2 * i], result[1][2 * i], result[2][2 * i],
                    result[0][2 * i + 1], result[1][2 * i + 1], result[2][2 * i + 1]);
            }
        }else{
            printf("Case %d: IMPOSSIBLE\n", cnt);
        }
        printf("\n");
    }
    return 0;
}
