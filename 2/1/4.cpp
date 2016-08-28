#include <array>
#include <cstdio>

using namespace std;

const int MAX = 1000000;

void init(array<int, MAX> &prime){
    int cnt = 1;
    prime.fill(0);
    for(int i = 2; i < MAX; ++i){
        if(prime[i] != 0) continue;
        for(int j = i; j < MAX; j += i){
            prime[j] = cnt; 
        }
        ++cnt;
    }
}

int main(){
    array<int, MAX> prime;
    init(prime);
    
    int n;
    while(scanf("%d", &n) != EOF){
        printf("%d\n", prime[n]);
    }
    return 0;
}
