//python3 run.py 1 \prog/wyssoc \prog/wys \in/wys0.in
#include <bits/stdc++.h>
#include <poll.h>

using namespace std;

mt19937 rng(2348325);

bool is_fd_writable(int fd) {
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLOUT;
    return poll(fds, 1, 0) == 1;
}

void check_if_writable_or_terminate(int fd) {
    if (!is_fd_writable(fd)) {
        cout << "WRONG\n";
        cout << "File descriptor " << fd << " is not writable\n";
        cout << "0\n";
        exit(0);
    }
}

void flush(FILE *file) {
    check_if_writable_or_terminate(fileno(file));
    fflush(file);
}

void write_no_flush(FILE *file, const char* format, ...) {
    va_list args;
    va_start(args, format);
    if (vfprintf(file, format, args) < 0) {
        cout << "WRONG\n";
        cout << "Error writing to file descriptor " << fileno(file) << "\n";
        cout << "0\n";
        exit(0);
    }
    va_end(args);
}

void write_and_flush(FILE *file, const char* format, ...) {
    va_list args;
    va_start(args, format);
    if (vfprintf(file, format, args) < 0) {
        cout << "WRONG\n";
        cout << "Error writing to file descriptor " << fileno(file) << "\n";
        cout << "0\n";
        exit(0);
    }
    flush(file);
    va_end(args);
}

void check_if_not_eof_or_terminate(FILE *file) {
    if (feof(file)) {
        cout << "WRONG\n";
        cout << "Unexpected EOF\n";
        cout << "0\n";
        exit(0);
    }
}

void read_and_check(FILE *file, const char* format, ...) {
    va_list args;
    va_start(args, format);
    check_if_not_eof_or_terminate(file);
    if (vfscanf(file, format, args) == 0) {
        cout << "WRONG\n";
        cout << "Error reading from file descriptor " << fileno(file) << "\n";
        cout << "0\n";
        exit(0);
    }
    check_if_not_eof_or_terminate(file);
    va_end(args);
}

void output_wrong_and_terminate(const string& message) {
    cout << "WRONG\n" << message << "\n0\n";
    exit(0);
}

char skip_whitespace(FILE* in) {
    char c = 0;
    while (c <= 32) {
        read_and_check(in, "%c", &c);
	}
    return c;
}

bool is_permutation(vector<int> v) {
    sort(v.begin(), v.end());
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i] != i)
            return false;
    return true;
}

int dist(int a, int b, vector<int> &where_is) {
    a = where_is[a];
    b = where_is[b];
    return min(abs(a - b), static_cast<int>(where_is.size()) - abs(a - b));
}

vector<pair<int, int>> get_shortest_edges(int a, int b, int c, vector<int> &where_is) {
    int n = static_cast<int>(where_is.size());
    vector<pair<int, int>> result;
    int d = n + 1;
    for (auto [x, y] : vector<pair<int, int>>{{a, b}, {a, c}, {b, c}}) {
        int dd = dist(x, y, where_is);
        if (dd < d) {
            d = dd;
            result = {{x, y}};
        } else if (dd == d) {
            result.push_back({x, y});
        }
    }
    for (auto &[x, y] : result)
        if (x > y)
            swap(x, y);
    return result;
}

bool is_correct_answer(const vector<int> &answer, const vector<int> &perm) {
    int n = static_cast<int>(perm.size());
    int i = 0;
    while (answer[i] != perm[0])
        i++;

    for (int j = -1; j <= 1; j += 2) {
        bool ok = true;
        for (int k = 0; k < n; k++) {
            int ind = (i + ((j + n) % n) * k) % n;
            if (answer[ind] != perm[k]) {
                ok = false;
                break;
            }
        }
        if (ok)
            return true;
    }
    return false;
}

int get_score(int K, double average_queries) {
    if (K == 12'000) // Different scoring for the 5th subtask
        return static_cast<int>(floor(100 * min(1.0, max(0.0, (12000 - average_queries) / 7700.0))));
    return average_queries <= static_cast<double>(K) ? 100 : 0;
}

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int num_processes = atoi(argv[1]);
    assert(num_processes == 1);
    FILE *in = fdopen(atoi(argv[2]), "r");
    assert(in);
    FILE *out = fdopen(atoi(argv[3]), "w");
    setvbuf(out, NULL, _IOFBF, 8192);
    int T, K;
    std::cin >> T >> K;
    vector<vector<int>> p(T);
    for (auto &v : p) {
        int n;
        std::cin >> n;
        v.resize(n);
        for (auto &x : v)
            std::cin >> x;
    }
    write_and_flush(out, "%d %d\n", T, K);

    long long total_queries = 0;
    int correct_test_cases = 0;

    for (const vector<int> &perm : p) {
        int n = static_cast<int>(perm.size());
        write_and_flush(out, "%d\n", n);
        vector<int> where_is(n);
        for (int i = 0; i < n; i++)
            where_is[perm[i]] = i;

        long long queries = 0;
        char c = skip_whitespace(in);
        while (c == '?') { // query
            queries++;
            int x, y, z;
            read_and_check(in, "%d %d %d", &x, &y, &z);
            if (x < 0 || x >= n || y < 0 || y >= n || z < 0 || z >= n)
                output_wrong_and_terminate("Invalid query - values out of range");
            if (x == y || x == z || y == z)
                output_wrong_and_terminate("Invalid query - two or more values are the same");
            
            vector<pair<int, int>> shortest_edges = get_shortest_edges(x, y, z, where_is);
            write_no_flush(out, "%u\n", shortest_edges.size());
            for (const auto &[s, t] : shortest_edges) {
                write_no_flush(out, "%d %d\n", s, t);
            }
            flush(out);

            c = skip_whitespace(in);
        }
        if (c != '!')
            output_wrong_and_terminate("Expected '!' or '?' but got something else");
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
            read_and_check(in, "%d", &ans[i]);
        
        if (!is_permutation(ans))
            output_wrong_and_terminate("Answer is not a permutation");
        
        if (is_correct_answer(ans, perm))
            correct_test_cases++;

        total_queries += queries;
    }

    if (correct_test_cases == T) {
        // All test cases are correct
        cout << "OK\n";
        double average_queries = static_cast<double>(total_queries) / T;
        int score = get_score(K, average_queries);
        cout << "Avg num of queries: " << average_queries << ", score = " << score << "\n";
        cout << score << "\n";
    } else {
        cout << "WRONG\n";
        int wrong_test_cases = T - correct_test_cases;
        cout << "Wrong answer in " << wrong_test_cases << " test case" << (wrong_test_cases == 1 ? "" : "s") << "\n";
        cout << "0\n";
    }

	return 0;
}