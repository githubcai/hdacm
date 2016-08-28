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
    int x, y;
    while(cin >> x >> y){
        cout << x * y / gcd(x, y) << endl;
    }
    return 0;
}
