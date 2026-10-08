#include "oi.h"
#include <bits/stdc++.h>
using namespace std;

constexpr auto scanner_lang = oi::Lang::PL;

[[noreturn]] void checker(
    [[maybe_unused]] oi::Scanner& tin,
    [[maybe_unused]] oi::Scanner& tout,
    oi::Scanner& user
) {
    const int max_t = 1e6;
    const int max_n = 1e6;
    const int max_m = 1e6;
    int t;
    tin >> oi::Num{t, 1, max_t} >> oi::nl;
    for (int tt = 0; tt < t; ++tt) {
        int n, m;
        tin >> oi::Num{n, 1, max_n} >> ' ' >> oi::Num{m, 1, max_m} >> oi::nl;
        vector<tuple<int, int, int>> edges(m);
        for (auto& [a, b, c] : edges) {
            tin >> oi::Num{a, 1, n} >> ' ' >> oi::Num{b, 1, n} >> ' ' >> oi::Num{c, 1, m} >> oi::nl;
        }

        string correct_out, user_out;
        tout >> oi::Str(correct_out, 4) >> oi::nl;
        user >> oi::Str(user_out, 4) >> oi::nl;
        if (correct_out != user_out) {
            oi::checker_verdict.exit_wrong();
        }
        oi_assert(correct_out == "YES" or correct_out == "NO");
        if (correct_out == "YES") {
            int k;
            user >> oi::Num{k, 1, m};
            vector<int> cycle(k);
            for (auto& id : cycle) {
                user >> oi::Num{id, 1, m};
            }
            user >> oi::nl;
            for (int i = 0; i < k; ++i) {
                auto [a, b, c] = edges[cycle[i] - 1];
                auto [d, e, f] = edges[cycle[(i + 1) % k] - 1];
                if (b != d or c == f) {
                    oi::checker_verdict.exit_wrong();
                }
            }
            string h;
            tout >> oi::Line{h, numeric_limits<size_t>::max()} >> oi::nl;
        }
    }
    user >> oi::eof;
    tout >> oi::eof;
    oi::checker_verdict.exit_ok();
}

int main(int argc, char* argv[]) {
    oi_assert(argc == 4);
    auto test_in = oi::Scanner(argv[1], oi::Scanner::Mode::Lax, scanner_lang);
    auto user_out = oi::Scanner(argv[2], oi::Scanner::Mode::UserOutput, scanner_lang);
    auto test_out = oi::Scanner(argv[3], oi::Scanner::Mode::Lax, scanner_lang);
    checker(test_in, test_out, user_out);
}

// You can write checker tests in the following way:
// (They won't be executed in sio2, they only work locally)
//CHECKER_TEST(TestInput{"0 1\n1\n1\n"}, TestOutput{"does not matter"}, UserOutput{"1\n1\n"}, CheckerOutput{"OK\nPierwszy wiersz jest OK; Drugi wiersz jest OK\n100\n"})

// Or like this:
CHECKER_TEST(R"(
@test_in
1
2 1
1 2 1
@test_out
NO
@user
NO
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
2 1
1 2 1
@test_out
NO
@user
no
@checker
WRONG

0
)")

CHECKER_TEST(R"(
@test_in
1
2 1
1 2 1
@test_out
NO
@user
YES
1 1
@checker
WRONG

0
)")

CHECKER_TEST(R"(
@test_in
1
2 1
1 2 1
@test_out
NO
@user
   NO   
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
2 1
1 2 1
@test_out
NO
@user
NO
x
@checker
WRONG
Wiersz 2, pozycja 1: Wczytano 'x', oczekiwano EOF
0
)")

CHECKER_TEST(R"(
@test_in
2
2 1
1 2 1
2 1
1 2 1
@test_out
NO
NO
@user
NO

NO
@checker
WRONG
Wiersz 2, pozycja 1: Wczytano '\n', oczekiwano napisu
0
)")

CHECKER_TEST(R"(
@test_in
2
2 1
1 2 1
2 1
1 2 1
@test_out
NO
NO
@user
  NO   
   NO   
   
         
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
2 1
1 2 1
@test_out
NO
@user
NOx
@checker
WRONG

0
)")

CHECKER_TEST(R"(
@test_in
1
2 1
1 2 1
@test_out
NO
@user
NO    x
@checker
WRONG
Wiersz 1, pozycja 7: Wczytano 'x', oczekiwano EOF
0
)")

CHECKER_TEST(R"(
@test_in
1
3 3
1 2 1
2 3 2
3 2 3
@test_out
YES
2 2 3
@user
YES
2 2 3
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
3 3
1 2 1
2 3 2
3 2 3
@test_out
YES
2 2 3
@user
YES
2 3 2
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
3 3
1 2 1
2 3 2
3 2 3
@test_out
YES
2 2 3
@user
YES
2 1 2
@checker
WRONG

0
)")

CHECKER_TEST(R"(
@test_in
1
3 3
1 2 1
2 3 2
3 2 3
@test_out
YES
2 2 3
@user
YES
4 2 3 2 3
@checker
WRONG
Wiersz 2, pozycja 1: Liczba calkowita spoza zakresu
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES
4 2 3 2 3
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES
4 3 2 3 2
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
NO
@checker
WRONG

0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES
2 1 4
@checker
WRONG

0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES
2 0 3
@checker
WRONG
Wiersz 2, pozycja 3: Liczba calkowita spoza zakresu
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES
2 5 3
@checker
WRONG
Wiersz 2, pozycja 3: Liczba calkowita spoza zakresu
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES x
2 2 3
@checker
WRONG
Wiersz 1, pozycja 5: Wczytano 'x', oczekiwano '\n'
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
   YES 
   2   3   2   
     
        
@checker
OK

100
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES 2  
3 2   
@checker
WRONG
Wiersz 1, pozycja 5: Wczytano '2', oczekiwano '\n'
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES  
2 3 
2
@checker
WRONG
Wiersz 2, pozycja 5: Wczytano '\n', oczekiwano liczby
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user

YES  
2 3 2
@checker
WRONG
Wiersz 1, pozycja 1: Wczytano '\n', oczekiwano napisu
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES  
2
2 3
@checker
WRONG
Wiersz 2, pozycja 2: Wczytano '\n', oczekiwano liczby
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES  

@checker
WRONG
Wiersz 2, pozycja 1: Wczytano '\n', oczekiwano liczby
0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
yes
2 2 3
@checker
WRONG

0
)")

CHECKER_TEST(R"(
@test_in
1
3 4
1 2 1
2 3 2
3 2 3
2 1 1
@test_out
YES
2 2 3
@user
YES  
3 2 3
@checker
WRONG
Wiersz 2, pozycja 6: Wczytano '\n', oczekiwano liczby
0
)")
