#include <cstdio>
#include <map>
using namespace std;

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        int temp;
        map<int, int> store;
        for(int i = 0; i < N; ++i){
            scanf("%d", &temp);
            ++store[temp];
        }
        int max = -1;
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            if(max < iter->second) max = iter->second;
        }
        printf("%d\n", max);
    }
    return 0;
}
