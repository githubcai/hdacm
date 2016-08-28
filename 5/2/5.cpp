#include <cstdio>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        map<string, int> store;
        int edge = 1, rd[1200] = {0};
        for(int i = 0; i < n; ++i){
            string a, b;
            cin >> a >> b;
            if(store[a] == 0){
                store[a] = edge++;
            }
            if(store[b] == 0){
                store[b] = edge++;
            }
            ++rd[store[b]];
        }
        int temp = 0;
        for(int i = 1; i < edge; ++i){
            if(rd[i] == 0) ++temp;
        }
        if(temp == 1){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
