#include <iostream>

using namespace std;

unsigned int getSum(unsigned int num, unsigned int base){
   unsigned int sum = 0;
   while(num > 0){
        sum += num % base;
        num /= base;
   }
   return sum; 
}

int main(){
    for(unsigned int i = 2992; i < 10000; ++i){
        unsigned int result;
        result = getSum(i, 10);
        if(result == getSum(i, 16) && result == getSum(i, 12)){
            cout << i << endl;
        }
    }
    return 0;
}
