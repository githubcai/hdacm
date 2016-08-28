#include <iostream>

using namespace std;

int main(){
    int N;
    cin >> N;
    while(N--){
        int M, sum = 0, a;
        cin >> M;
        while(M--){
            cin >> a;
            sum += a;
        }
        cout << sum << endl;
    }
}
