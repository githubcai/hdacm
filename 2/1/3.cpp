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
    int p, q;
    while(cin >> p >> q){
        cout << p + q - gcd(p, q) << endl;
    }
    return 0;
}
