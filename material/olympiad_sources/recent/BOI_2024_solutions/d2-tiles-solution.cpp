/* TASK: Tiles (tiles)
 * Task proposal by: Mikkel Abrahamsen (DNK)
 * Task prepared by: Mikkel Abrahamsen (DNK), Dovydas Vadišius (LTU SC), Daumilas Ardickas (LTU SC)
 */

#include <bits/stdc++.h>

using namespace std;

int max_line(int N, int M, std::vector<int> X, std::vector<int> Y)
{
    X.push_back(X[0]);
    X.push_back(X[1]);
    Y.push_back(Y[0]);
    Y.push_back(Y[1]);
    map<int, set<int>> points; //sets of y coordinates sorted by x coordinates
    for (int i = 1; i <= N; i++)
    {
		//only interesting points are when direction changes
        if ((X[i - 1] != X[i] && X[i] == X[i + 1]) || (X[i - 1] == X[i] && X[i] != X[i + 1]))
        {
            points[X[i]].insert(Y[i]);
        }
    }
    int best = 0; //z
    int even_count = 0;
    int odd_count = 0;
    map<int, int> current; //intervals y coordinates mapped to interval type above it: -1 - empty, 0 - even, 1 - odd interval
    for (auto &line : points) //sweep from left to right
    {
        int x = line.first;
        if (even_count == 0)
        {
            best = max(best, (x - 1) | 1);
        }
        if (odd_count == 0)
        {
            best = max(best, x & ~1);
        }
        int shift = -1; //start of previous interval if it has odd size
        auto l = line.second.begin();
        while (l != line.second.end()) //check each vertical edge from bottom to top
        {
            int y1 = *l++;
            int y2 = *l++;
            auto it = current.upper_bound(y1);
            if (it != current.end() && it->first < y2) //edge is contained in more than one interval
                return best;
            if (it == current.begin() || prev(it)->second == -1) //interior of P is to the right of the edge
            {
                if (shift >= 0)
                {
                    if (prev(prev(it))->first != shift) //not continuing odd length interval
                        return best;
                }
                if (it == current.begin() || prev(it)->first != y1 || prev(prev(it))->second != x % 2) //start new interval
                {
                    current[y1] = x % 2;
                    (x % 2 ? odd_count : even_count)++;
                }
                else //merge with previous interval
                {
                    current.erase(prev(it));
                }
                if ((y1 % 2 == y2 % 2) ^ (shift >= 0)) //if together with previous interval have even size
                {
                    if (it == current.end() || it->first > y2) //close interval
                    {
                        current[y2] = -1;
                    }
                    else if (it->second == x % 2) //merge with next interval
                    {
                        current.erase(it);
                        (x % 2 ? odd_count : even_count)--;
                    }
                    shift = -1;
                }
                else
                {
                    if (it == current.end() || it->first != y2 || it->second != x % 2) //have odd length interval
                        return best;
					//merge with next interval
                    current.erase(it);
                    (x % 2 ? odd_count : even_count)--;
                    shift = y1;
                }
            }
            else //interior of P is to the left of the edge
            {
                if (shift >= 0)
                {
                    if (prev(it)->first != shift || y1 % 2 != shift % 2) //have odd length interval
                        return best;
                }
                else if (prev(it)->second != x % 2 || prev(it)->first % 2 != y1 % 2) //have odd length interval
                {
                    return best;
                }
                if (prev(it)->first == y1) //edge's bottom coincides with an interval's end
                {
                    if (prev(it) != current.begin() && prev(prev(it))->second != -1) //previous interval is empty
                    {
                        current[y1] = -1;
                    }
                    else
                    {
                        current.erase(prev(it));
                    }
                    (x % 2 ? odd_count : even_count)--;
                }
                else
                {
                    current[y1] = -1;
                }
                if (it->first % 2 == y2 % 2) //next interval has even length
                {
                    if (it->first != y2) //edge's top is not on interval's end
                    {
                        current[y2] = x % 2;
                        (x % 2 ? odd_count : even_count)++;
                    }
                    else if (it->second == -1) //next interval is empty
                    {
                        current.erase(it);
                    }
                    shift = -1;
                }
                else
                {
                    current[y2] = x % 2;
                    (x % 2 ? odd_count : even_count)++;
                    shift = y2;
                }
            }
        }
        if (shift >= 0)
            return best;
    }
    return best;
}

int main() {
	int N, M, x, y, k;
	vector<int> X, Y;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		X.push_back(x);
		Y.push_back(y);
	}
	k = max_line(N, M, X, Y);
	cout << k << endl;
}
