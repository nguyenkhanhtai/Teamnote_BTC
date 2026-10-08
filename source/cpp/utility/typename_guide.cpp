// C++17; requires <array> and <vector>.
template<typename T>
T bigger(T a, T b) { return a > b ? a : b; }

template<typename T>
struct Sum {
    T value{};
    void add(T x) { value += x; }
};

template<typename T, int N>
struct Buffer {
    std::array<T, N> data{};
};

template<typename C>
typename C::value_type total(const C& a) {
    typename C::value_type answer{};
    for (const auto& x : a) answer += x;
    return answer;
}

inline void typename_examples() {
    auto a = bigger(3, 5); // T = int
    auto b = bigger<int>(1, 2LL);
    Sum<int> s;
    s.add(a); s.add(b); // s.value = 7
    Buffer<int, 4> buf;
    buf.data[0] = a;
    auto c = total(std::vector<int>{1, 2, 3});
    (void)c; // c = 6
}
