#include <cstdio>
#include <vector>
using namespace std;

const int MAX = 12;
int t, n, x[MAX], cnt;
vector<int> store;

void dfs(int index, int sum){
    if(sum == t){
        ++cnt;
        auto iter = store.begin();
        printf("%d", *iter);
        for(++iter; iter != store.end(); ++iter){
            printf("+%d", *iter);
        }
        printf("\n");
        return;
    }
    for(int i = index; i < n; ++i){
        if(sum + x[i] <= t){
            store.push_back(x[i]);
            dfs(i + 1, sum + x[i]);
            store.pop_back();
        }
        while(i + 1 < n && x[i] == x[i + 1]) ++i;
    }
}

int main(){
    while(scanf("%d%d", &t, &n) == 2 && !(t == 0 && n == 0)){
        for(int i = 0; i < n; ++i){
            scanf("%d", &x[i]);
        }
        printf("Sums of %d:\n", t);
        store.clear(), cnt = 0;
        dfs(0, 0);
        if(cnt == 0){
            printf("NONE\n");
        }
    }
    return 0;
}
