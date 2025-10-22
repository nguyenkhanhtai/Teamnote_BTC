int getSign(int x){
    if (x > 0) return 1;
    if (x == 0) return 0;
    if (x < 0) return -1;
}
int orientation(int a, int b, int c, point P){
    int value = a * P.x + b * P.y + c;
    return value;
}
bool checkCut(vector<point> &CH, int a, int b, int c){
    int l = 0, r = CH.size() - 1;
    if (orientation(a, b, c, CH[0]) == 0) return true;
    if (getSign(orientation(a, b, c, CH[0])) *
        getSign(orientation(a, b, c, CH.back())) <= 0) return true;
    int sign = getSign(orientation(a, b, c, CH[0]));
    while(l <= r){
        int mid = (l + r) >> 1;

        if (getSign(orientation(a, b, c,CH[0])) * getSign(orientation(a, b, c, CH[mid]))  <= 0) 
                return true;

        if (mid != 0 and getSign(orientation(a, b, c, CH[mid - 1]))
                       * getSign(orientation(a, b, c, CH[0])) <= 0) 
            return true;

        if (mid != CH.size() - 1 and getSign(orientation(a, b, c, CH[mid + 1]))
                                   * getSign(orientation(a, b, c, CH[0])) <= 0) 
            return true;
            
        if (mid != 0 and orientation(a, b, c, CH[mid]) * sign >
                         orientation(a, b, c, CH[mid - 1]) * sign){
            r = mid - 1;
        }
        else if (mid != CH.size() - 1 and 
                orientation(a, b, c, CH[mid]) * getSign(sign) > orientation(a, b, c, CH[mid + 1]) getSign(sign)){
            l = mid + 1;
        }
        else break;
    }
    return false;
}
if (!checkCut(upperHull, a, b, c) and !checkCut(lowerHull, a, b, c)) {
    ans++;