int gcded(int a,int b,int &x,int &y){
    if (a == 0){
        x = 0, y = 1;
        return b;
    }

    int g, x1, y1;
    g = gcded(b % a, a, x1, y1);
    y = x1;
    x = y1 - (b / a) * x1;
    return g;
}
