#include <iostream>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        int sum = 0, a;
        while(N--){
            cin >> a;
            sum += a;
        }
        cout << sum << endl;
    }
}
