#define eps 1e-7
template<typename T>
struct P{
    T x, y, id;  //Change to double if neccessary
    P(T _x = 0, T _y = 0): x(_x), y(_y) {}
    P operator + (const P &other) const{ return P(x + other.x, y + other.y);}
    void operator += (const P &other){  this->x += other.x; this->y += other.y; }
    P operator - (const P &other) const{ return P(x - other.x, y - other.y);}
    void operator -= (const P &other) { this->x -= other.x; this->y -= other.y;}
    P operator * (double coef) const {return P(this->x * coef, this->y * coef);}
    P operator / (double coef) const{return P(this->x / coef, this->y / coef);}
    T cross(const P &other) const{return (this->x * other.y - this->y * other.x);}
    T cross(const P &a, const P &b) const {return (a.x - this->x) * (b.y - this->y) - (a.y - this->y) * (b.x - this->x); }
    T dot(const P &other) const {return (this->x * other.x + this->y * other.y);}

    // P ShiftLength(double len) const{ //Use when Ps are double
    //     double cur_len = hypot(x, y);
    //     double new_x = 1.0 * x * len / cur_len;
    //     double new_y = 1.0 * y * len / cur_len;
    //     return P(new_x, new_y);
    // }

    double abs() const{
        return hypot(this->x, this->y);
    }
    T sqrLength() const{
        return (this->x * this->x + this->y * this->y);
    }

    int half () const {
        return (y < 0 || (y == 0 && x < 0));
    }
    friend ostream& operator << (ostream &out, P other){
        out << other.x << ' ' << other.y;
        return out;
    }
    bool operator == (const P &other) const {
        return (this->x == other.x && this->y == other.y);
    }
};

using Point = P<long double>;

struct Line{
    double a, b, c; //Ax + By + C = 0
    Line(double _a = 0, double _b = 0, double _c = 0){
        a = _a;
        b = _b;
        c = _c;
    }
    Line(Point A = Point(0, 0), Point B = Point(0, 0)){
        a = B.y - A.y;
        b = A.x - B.x;
        c = -A.x * a - A.y * b;
    }

    Point operator & (const Line &other) const{

        double deno = 1.0 * (a * other.b - b * other.a);
        if (abs(deno) < eps) return Point(-inf, -inf);

        return Point(1.0 * (-c * other.b + other.c * b) / deno,
                     1.0 * (c * other.a - other.c * a) / deno);
    }

    double distance(const Point &P) const{
        return 1.0 * abs(P.x * a + P.y * b + c) / hypot(a, b);
    }
};

struct Circle{
    Point O;
    double radius;

    Circle(Point _O = Point(0, 0), double _radius = 0){
        O = _O;
        radius = _radius;
    }

    vector<Point> IntersectWithLines (const Line &other) const{
        if ((other.distance(O) - radius) > eps) return {}; //Truong hop khong giao nhau

        Point H = other & Line(other.b, -other.a, -O.x * other.b + O.y * other.a);
        double d = other.distance(O);

        if (abs(d - radius) < 0) return {H};  //Trong hop ma khoang cach gan nhu la radius
        
        double len = sqrt(radius * radius - d * d);
        Point shift = Point(other.b, -other.a).ShiftLength(len);
        Point A = H - shift;
        Point B = H + shift;

        return {A, B};
    }

    int relativePosition(const Circle &other) const{
        double d = (this->O - other.O).abs();
        double r1 = max(this->radius, other.radius);
        double r2 = min(this->radius, other.radius);
        if (d + r2 <= r1 + eps) return 1; //Nam ben trong
        if (d + r2 > r1 + eps and d - r2 <= r1 + eps) return 2;  //Giao nhau
        if (d - r2 > r1 + eps) return 3; //Khong giao nhau
    }

    vector<Point> IntersectWithCircles(const Circle &other) const{
         double a = 2 * (O.x - other.O.x);
         double b = 2 * (O.y - other.O.y);
         double c = (other.O.x * other.O.x + other.O.y * other.O.y - other.radius * other.radius) - 
                    (O.x * O.x + O.y * O.y - radius * radius);

         Line L1 = Line(a, b, c);
         return IntersectWithLines(L1);
    }
};
