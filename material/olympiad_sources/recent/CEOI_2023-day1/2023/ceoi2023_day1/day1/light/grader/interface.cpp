#include <vector>
#include <cstdio>
#include <cstdlib>
#include <optional>
#include "light.h"

using namespace std;

namespace {
	constexpr int ANSWER = 324137656;
}

template<typename T> void write(T t) {
    fwrite(&t, sizeof(t), 1, stdout);
}

template<typename T> optional<T> read() {
	T x;
	if(fread(&x, sizeof(x), 1, stdin) != 1)
		return nullopt;
	return x;
}

void output(pair<long long, vector<long long>> res) {
	write<int>(ANSWER);
	write<long long>(res.first);
	int size = min(300, (int) res.second.size());
	write<int>(size);
	fwrite(res.second.data(), sizeof(long long), size, stdout);
	fflush(stdout);
}

int main() {
	prepare();
	while(true) {
		optional<long long> d = read<long long>();
		if(not d or *d == 0)
			break;
		else if (*d > 0)
			output(join(*d));
		else
			output(leave(-(*d)));
	}
	return 0;
}
