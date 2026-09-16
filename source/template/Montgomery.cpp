struct montgomery {
    uint64_t n, nr;

    constexpr montgomery(uint64_t n) : n(n), nr(1) {
        // log(2^64) = 6
        for (int i = 0; i < 6; i++)
            nr *= 2 - n * nr;
    }

    [[nodiscard]]
    uint64_t reduce(__uint128_t x) const {
        uint64_t q = __uint128_t(x) * nr;
        uint64_t m = ((__uint128_t) q * n) >> 64;
        uint64_t res = (x >> 64) + n - m;
        if (res >= n)
            res -= n;
        return res;
    }

    [[nodiscard]]
    uint64_t multiply(uint64_t x, uint64_t y) const {
        return reduce((__uint128_t) x * y);
    }

    [[nodiscard]]
    uint64_t transform(uint64_t x) const {
        return (__uint128_t(x) << 64) % n;
    }
};