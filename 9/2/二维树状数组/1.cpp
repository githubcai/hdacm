void Update(int x, int y, int val){
    while(x <= n){
        int y1 = y;
        while(y1 <= n){
            C[x][y1] += val;
            y1 += y1 & (-y1);
        }
            x += x & (-x);
    }
}

int GetSum(int x, int y){
    int sum = 0;
    while(x > 0){
        int y1 = y;
        while(y1 > 0){
            sum += C[x][y1];
            y1 -= y1 & (-y1);
        }
            x -= x & (-x);
    }
    return sum;
}


