#include <iostream>
#include <set>

using namespace std;

bool cal(int N, set<int> &result){
    for(int i = 1; i <= N; i *= 10){
        int a = N / (i * 11);
        int b1 = N / i - 11 * a;
        int b2 = b1 - 1;
        int c1 = (N - (11 * a + b1) * i) / 2;
        int c1mod = (N - (11 * a + b1) * i) % 2;
        int c2 = (N - (11 * a + b2) * i) / 2;
        int c2mod = (N - (11 * a + b2) * i) % 2;

        if(((0 == b1 && 0 != a) || (b1 > 0)) && b1 < 10 && 0 == c1mod){
            result.insert((10 * a + b1) * i + c1);
        }

        if(((0 == b2 && 0 != a) || (b2 > 0)) && b2 < 10 && 0 == c2mod){
            result.insert((10 * a + b2) * i + c2);
        }
    }
    if(result.size() > 0) return true;
    return false;
}

void print(const set<int> &result){
    auto iter = result.begin();
    cout << *iter;
    for(++iter; iter != result.end(); ++iter){
        cout << " " << *iter;
    }
    cout << endl;
}

int main(){
    int N;
    while(cin >> N, N != 0){
        set<int> result;
        if(cal(N, result)){
            print(result);
        }else{
            cout << "No solution." << endl;
        }
    }
    return 0;
}
