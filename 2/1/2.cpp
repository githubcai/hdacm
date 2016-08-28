#include <iostream>
#include <cmath>

using namespace std;

bool judge(int n){
    for(int i = 2; i <= sqrt(1.0 * n); ++i){
        if(i != n && n % i == 0){
            return false;
        }
    }
    return true;
}

int main(){
    int N;
    while(cin >> N){
        int cnt = 0;
        for(int i = 0; i < N; ++i){
            int tmp;
            cin >> tmp;
            if(judge(tmp)){
                cnt++;
            }
        }
        cout << cnt << endl;
    }
    return 0;
}
