struct line{
    int a, b;
    line(int _a = 0, int _b = 0){
        a = _a;
        b = _b;
    }
    int getVal(int x){
        return a * x + b;
    }

    bool operator < (const line &other) const{
        return ((a == other.a) ? (b < other.b) : (a < other.a));
    }
};

//chuyen sang -ax - b: thi se thanh bai toan tim max.
struct CHT{
    vector<line> opt;

    bool bad(line l1, line l2, line l3){
        return 1.0 * (l2.b - l1.b) / (l1.a - l2.a)  > 1.0 * (l3.b - l1.b) / (l1.a - l3.a);
    }

    void addLine(line li){
        while(opt.size() > 1 and bad(opt[opt.size() - 2], opt.back(), li)) opt.pop_back();
        opt.pb(li);
    }

    int getMax(int x){
        int l = 0, r = opt.size() - 1;
        int res = -inf;
        while(l <= r){
            int mid = (l + r) >> 1;
            int cur = opt[mid].getVal(x);
            maximize(res, cur);

            if (mid != 0 and opt[mid - 1].getVal(x) > cur) r = mid - 1;
            else if (mid != opt.size() - 1 and opt[mid + 1].getVal(x) > cur) l = mid + 1;
            else break;
        }
        return res;
    }
};