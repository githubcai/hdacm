#include <iostream>

using namespace std;

unsigned int gcd(unsigned int n, unsigned int m){
    unsigned int r;
    r = n % m;
    while(0 != r){
        n = m;
        m = r;
        r = n % m;
    }
    return m;
}

int main(){
    unsigned int N, M;
    while(cin >> N >> M, N != -1 || M != -1){
        if(gcd(N, M) == 1){
            cout << "YES" << endl;
        }else{
            cout << "POOR Haha" << endl;
        }
    }
    return 0;
}
