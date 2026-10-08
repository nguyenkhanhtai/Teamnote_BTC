#include <cstdio>
#include <cmath>

using namespace std;

const int N = 1e5 + 500;

typedef long double ld;

ld r[N], S, P;
int n;

ld calc_x(ld t, ld a){
	return sqrt((4 * a - t * t - sqrt((t * t - 4 * a) * (t * t - 4 * a) - 16 * (a * a - t * t * a))) / 8);
}

bool check(ld t) {
	ld uk_x = 0;
	for(int i = 0;i < n;i++) {
		if(t > r[i]) continue;
		uk_x += calc_x(t, r[i] * r[i]);
	}
	return uk_x <= S;
}


int main(){
	scanf("%d%Lf", &n, &S);
	if(S < 1) {
		printf("%.10Lf\n", (ld)0);
		return 0;
	}
	ld bar = 0;
	for(int i = 0;i < n;i++) {
		int tmp; scanf("%d", &tmp);
		r[i] = tmp;
		bar += r[i] / sqrt(2); 
		P += r[i] * r[i] / 4;
	}
	if(bar < S) {
		printf("%.10Lf\n", P);
		return 0;
	}
	ld lo = 0, hi = 100011;
	for(int i = 0;i < 100;i++) {
		if(!check((lo + hi) / 2))
			lo = (lo + hi) / 2;
		else 
			hi = (lo + hi) / 2;
	}
	P = 0;
	for(int i = 0;i < n;i++) {
		if(lo > r[i]) continue;
		ld x = calc_x(lo, r[i] * r[i]);
		P += x * sqrt(r[i] * r[i] - x * x);
	}
	printf("%.10Lf\n", P / 2);
	return 0;
}
