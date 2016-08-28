#include <iostream>
#include <bitset>

using namespace std;

int main(){
    unsigned int A;
    while(cin >> A, A != 0){
        bitset<8> save(A);
        auto end = save.size();
        for(decltype(end) i = 0; i < end; ++i){
            if(save.test(i)){
                save &= (1UL << i);
                break;
            }
        }
        cout << save.to_ulong() << endl;
    }
}
