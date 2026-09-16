using ll = long long;
using i128 = __int128_t;

struct Point {
    ll x, y;
};

struct Edge {
    int u, v;
};

// ============================================================
// Planar Dual Graph: Faces & Dual Edges Construction
// Complexity: O(E log E) time, O(V + E) space
// ============================================================

struct PlanarDual {
    int faceCount;
    vector<Edge> edges; // Dual edges (faceOfDart[2i], faceOfDart[2i+1])

    vector<int> from, to;
    vector<vector<int>> adj;
    vector<int> position;
    vector<int> nextDart;
    vector<int> faceOfDart;

    const vector<Point>& points;
    const vector<Edge>& originalEdges;

    PlanarDual(
        const vector<Point>& points,
        const vector<Edge>& edges
    ) : points(points), originalEdges(edges) {
        buildHalfEdges();
        sortEdgesByAngle();
        buildNextDart();
        findFaces();
        buildDualEdges();
    }

private:
    int getHalf(ll x, ll y) {
        return y > 0 || (y == 0 && x > 0) ? 0 : 1;
    }

    void buildHalfEdges() {
        int n = points.size();
        int m = originalEdges.size();

        from.resize(2 * m);
        to.resize(2 * m);
        adj.resize(n);

        for (int i = 0; i < m; ++i) {
            auto [u, v] = originalEdges[i];

            from[2 * i] = u;
            to[2 * i] = v;

            from[2 * i + 1] = v;
            to[2 * i + 1] = u;

            adj[u].push_back(2 * i);
            adj[v].push_back(2 * i + 1);
        }
    }

    void sortEdgesByAngle() {
        position.resize(from.size());

        auto angleLess = [&](int a, int b) {
            int u = from[a];

            ll ax = points[to[a]].x - points[u].x;
            ll ay = points[to[a]].y - points[u].y;
            ll bx = points[to[b]].x - points[u].x;
            ll by = points[to[b]].y - points[u].y;

            int halfA = getHalf(ax, ay);
            int halfB = getHalf(bx, by);

            if (halfA != halfB) return halfA < halfB;

            i128 cross = (i128)ax * by - (i128)ay * bx;
            return cross > 0;
        };

        for (auto& darts : adj) {
            sort(darts.begin(), darts.end(), angleLess);

            for (int i = 0; i < (int)darts.size(); ++i) {
                position[darts[i]] = i;
            }
        }
    }

    void buildNextDart() {
        nextDart.resize(from.size());

        for (int dart = 0; dart < (int)from.size(); ++dart) {
            int v = to[dart];
            int reversePosition = position[dart ^ 1];
            int degree = adj[v].size();

            int nextPosition =
                (reversePosition - 1 + degree) % degree;

            nextDart[dart] = adj[v][nextPosition];
        }
    }

    void findFaces() {
        faceOfDart.assign(from.size(), -1);
        faceCount = 0;

        for (int start = 0; start < (int)from.size(); ++start) {
            if (faceOfDart[start] != -1) continue;

            int dart = start;

            do {
                faceOfDart[dart] = faceCount;
                dart = nextDart[dart];
            } while (dart != start);

            ++faceCount;
        }
    }

    void buildDualEdges() {
        int m = originalEdges.size();
        edges.resize(m);

        for (int i = 0; i < m; ++i) {
            edges[i] = {
                faceOfDart[2 * i],
                faceOfDart[2 * i + 1]
            };
        }
    }
};
