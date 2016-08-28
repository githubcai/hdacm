#include <iostream>

using namespace std;

int gcd(int x, int y){
    int r;
    r = x % y;
    while(r != 0){
        x = y;
        y = r;
        r = x % y;
    }
    return y;
}

int main(){
    int n, a, b;
    cin >> n;
    while(n-- > 0){
        cin >> a >> b;
        int i;
        for(i = 2; gcd(a, i * b) != b; ++i){}
        cout << i * b<< endl;
    }
    return 0;
}
