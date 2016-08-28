#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 20;
int n, ct;
bool vis[MAX], prime[MAX * 2];
vector<int> store;

void init(){
    fill(prime, prime + MAX * 2, true);
    prime[0] = prime[1] = false;
    for(int i = 2; i < MAX * 2; ++i){
        if(prime[i]){
            for(int j = i * 2; j < MAX * 2; j += i){
                prime[j] = false;
            }
        }
    }
}

void dfs(int now){
    if(ct == n && prime[now + 1]){
        auto iter = store.begin();
        printf("%d", *iter);
        for(++iter; iter != store.end(); ++iter){
            printf(" %d", *iter);
        }
        printf("\n");
        return;
    }
    for(int i = 2; i <= n; ++i){
        if(!vis[i] && prime[i + now]){
            vis[i] = true;
            store.push_back(i);
            ++ct;
            dfs(i);
            --ct;
            store.pop_back();
            vis[i] = false;
        }
    }
}

int main(){
    int cnt = 0;
    init();
    while(scanf("%d", &n) == 1){
        printf("Case %d:\n", ++cnt);
        if(n % 2 == 0){
            memset(vis, 0, sizeof(vis));
            vis[1] = true;
            ct = 1;
            store.clear();
            store.push_back(1);
            dfs(1);
        }
        printf("\n");
    }
    return 0;
}
