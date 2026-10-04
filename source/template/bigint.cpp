// Nonnegative integer: base 10^9, least-significant block first.
// Zero = {0}; otherwise the last block must be nonzero.
// Example: 1234567890000000042 -> {42, 234567890, 1}.
using bignum = vector<uint32_t>;
constexpr uint32_t BASE = 1000000000;

void print(const bignum &a) { // nonempty, normalized
    cout << a.back();
    for (size_t i = a.size() - 1; i > 0; --i) {
        string block = to_string(a[i - 1]);
        cout << string(9 - block.size(), '0') << block;
    }
}
