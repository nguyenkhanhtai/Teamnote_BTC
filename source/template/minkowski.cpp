    Polygon Minkowski(Polygon Poly1, Polygon Poly2){
        int ptr1 = 0;
        int ptr2 = 0;
        FOR(i, 1, (int) sz(Poly1.P) - 1){
            if ((Poly1.P[i].y == Poly1.P[ptr1].y and Poly1.P[i].x < Poly1.P[ptr1].x) or (Poly1.P[i].y < Poly1.P[ptr1].y)) ptr1 = i;
        }
        rotate(Poly1.P.begin(), Poly1.P.begin() + ptr1, Poly1.P.end());
 
        FOR(i, 1, (int) sz(Poly2.P) - 1){
            if ((Poly2.P[i].y == Poly2.P[ptr2].y and Poly2.P[i].x < Poly2.P[ptr2].x) or (Poly2.P[i].y < Poly2.P[ptr2].y)) ptr2 = i;
        }
 
        rotate(Poly2.P.begin(), Poly2.P.begin() + ptr2, Poly2.P.end());
        Poly1.addPoint(Poly1.P[0]);
        Poly2.addPoint(Poly2.P[0]);
        ptr1 = 0, ptr2 = 0;
        Polygon res;
        while(ptr1 < sz(Poly1.P) - 1 or ptr2 < sz(Poly2.P) - 1){
            res.addPoint(Poly1.P[ptr1] + Poly2.P[ptr2]);
            if (ptr1 == (int) sz(Poly1.P) - 1) ptr2++;
            else if (ptr2 == (int) sz(Poly2.P) - 1) ptr1++;
            else{
                int dir = (Poly1.P[ptr1 + 1] - Poly1.P[ptr1]).cross(Poly2.P[ptr2 + 1] - Poly2.P[ptr2]);
                if (dir > 0) ptr1++;
                else if (dir < 0) ptr2++;
                else ptr1++, ptr2++;
            }
        }
        res.refineCH();
        return res;
    }