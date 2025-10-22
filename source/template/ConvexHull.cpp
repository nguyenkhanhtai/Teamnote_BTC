struct Polygon{
    //Counter-clockwise convex hull
    vector<Point> P;  
    Polygon(){
        P = {};
    }
    Polygon(vector<Point> &_Polygon){
        P = _Polygon;
    }
    void addPoint(Point pt){ P.pb(pt);    }
    void refineCH(){ 
        //Turn the set of Points into Convex Hull
        //Eliminate all the triplets of collinear points
        sort(P.begin(), P.end());
        if (sz(P) < 3) return;
        Point E0 = P[0];
        Point E1 = P.back();
        vector<Point> upper, lower;
        upper.pb(E0);
        lower.pb(E0);
 
        FOR(i, 1, (int) sz(P) - 1){
            if (i == sz(P) - 1 or cross(E0, E1, P[i]) >= 0){
                while(upper.size() > 1 and cross(upper[upper.size() - 2], upper.back(), P[i]) >= 0) 
                    upper.pop_back();
                upper.pb(P[i]);
            }
 
            if (i == sz(P) - 1 or cross(E0, E1, P[i]) < 0){
                while(lower.size() > 1 and cross(lower[lower.size() - 2], lower.back(), P[i]) <= 0) lower.pop_back();
                lower.pb(P[i]);
            }
        }
        vector<Point> ConvexHull;
        FOR(i, 0, (int) lower.size() - 1){
            ConvexHull.pb(lower[i]);
        }
        FORD(i, (int) upper.size() - 2, 1){
            ConvexHull.pb(upper[i]);
        }
        P = ConvexHull;
    }
    bool onSegment(Point A, Point B, Point O){
        int mnX = min(A.x, B.x);
        int mxX = max(A.x, B.x);
        int mnY = min(A.y, B.y);
        int mxY = max(A.y, B.y);
        return (cross(A, B, O) == 0 and O.x >= mnX and O.x <= mxX && O.y >= mnY && O.y <= mxY);
    }
    bool insideTriangle(Point A, Point B, Point C, Point O){
        int S1 = abs(cross(O, A, B));
        int S2 = abs(cross(O, A, C));
        int S3 = abs(cross(O, B, C));
        int S = abs(cross(A, B, C));
        return (S == S1 + S2 + S3);
    }
    void print(){
        FOR(i, 0, (int) sz(P) - 1){
            cout << P[i].x << ' ' << P[i].y << endl;
        }
    }
    bool inside(Point O){ //check if Point O is inside the polygon
        if (sz(P) == 1) return false;
        if (sz(P) == 2) return onSegment(P[0], P[1], O);
        if (cross(P[0], P[1], O) < 0) return false; //nam ngoai
        if (onSegment(P[0], P[1], O)) return true; //nam tren segment
 
        if (cross(P[0], P.back(), O) > 0) return false; //nam ngoai
        if (onSegment(P[0], P.back(), O)) return true; //nam tren segment
 
 
        int lo = 1, hi = (int) sz(P) - 2, res = -1;
        while(lo <= hi){
            int mid = (lo + hi) >> 1;
            if (cross(P[0], P[mid], O) > 0){
                res = mid;
                lo = mid + 1;
            }
            else hi = mid - 1;
        }
        // cout << res << endl;
 
        return insideTriangle(P[0], P[res], P[res + 1], O);
    }
};