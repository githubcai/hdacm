#include <map>
#include <vector>
#include <cstdio>
using namespace std;

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int C; scanf("%d", &C);
        multimap<int, vector<int>> store;
        for(int i = 0; i < C; ++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            vector<int> temp;
            temp.push_back(b);
            temp.push_back(a);
            store.insert(pair<int, vector<int>>(c, temp));
        }
        scanf("%d", &C);
        for(int i = 0; i < C; ++i){
            int a; scanf("%d", &a);
            auto iter = store.begin();
            for(; iter != store.end(); ++iter){
                if((iter->second)[0] >= a){
                    printf("%d\n", (iter->second)[1]);
                    (iter->second)[0] -= a;
                    break;
                }
            }
            if(iter == store.end()){
                printf("sorry\n");
            }
        }
    }
    return 0;
}
