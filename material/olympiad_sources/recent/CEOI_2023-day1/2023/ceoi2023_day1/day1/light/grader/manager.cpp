// #define DEBUG

#include <managerframework.h>
#include <bits/stdc++.h>
#include "scoreinfo.h"

using namespace std;
typedef long long ll;

int FIRELIMIT;
ll MAX_N;

#ifdef DEBUG
	#define SECURITY_VIOLATION "Security violation!"
	#define NOT_ORDERED "Positions not ordered or not unique"
	#define TOO_MANY_FIRES "Too many fires"
	#define GONE_TOO_FAR "Too large t"
	#define CORRECT(x) "Correct: coefficient <= %lld", x
	#define NOT_LIT(x) "Torch %lld not lit (t too small)", x + 1
	#define OUT_OF_RANGE(x) "Runner %lld out of range", x + 1
	#define T_OUT_OF_RANGE "Invalid value for t (t < 0)"
	#define RIGHTMOST_NOT_LIT "Rightmost torch not lit"
#else
	#define SECURITY_VIOLATION "Security violation!"
	#define NOT_ORDERED "Not correct"
	#define TOO_MANY_FIRES "Not correct"
	#define GONE_TOO_FAR "Not correct"
	#define CORRECT(x) x == 1? "Correct" : "Partially correct"
	#define NOT_LIT(x) "Not correct"
	#define OUT_OF_RANGE(x) "Not correct"
	#define T_OUT_OF_RANGE "Not correct"
	#define RIGHTMOST_NOT_LIT "Not correct"
#endif

namespace {
	constexpr int ANSWER = 324137656;
}

#define write(x) _write_helper(__LINE__, x)
template<typename T> void _write_helper(int line, T t) {
    fwrite(&t, sizeof(t), 1, fcommout);
    fflush(fcommout);

    #ifdef DEBUG_
        cerr << "[line" << line << "] " << t << flush;
    #endif
}

template<typename T> T read_or_fail() {
	T x;
	if (fread(&x, sizeof(x), 1, fcommin) != 1)
		result(0.0, SECURITY_VIOLATION);
	return x;
}

pair<__int128_t, vector<ll>> read_fires() {
	int code = read_or_fail<int>();
	ll t = read_or_fail<ll>();
	int size = read_or_fail<int>();
	if(code != ANSWER)
		result(0.0, SECURITY_VIOLATION);
	if(t < 0)
		result(0.0, T_OUT_OF_RANGE);

	if(size < 0 or size > 2 * FIRELIMIT) result(0.0, SECURITY_VIOLATION);
	vector<ll> r(size);
	if(fread(r.data(), sizeof(ll), size, fcommin) != size)
		result(0.0, SECURITY_VIOLATION);
	if(size > FIRELIMIT) result(0.0, TOO_MANY_FIRES);
	for(int i = 1; i < size; ++i)
		if(r[i] <= r[i - 1]) result(0.0, NOT_ORDERED);
	for(auto x : r)
		if(x < 0) result(0.0, OUT_OF_RANGE(x));
	for(auto &x : r) --x;

	return {t, r};
}

mt19937_64 eng;

ll rnd(ll l, ll h) {
	uniform_int_distribution<ll> distr(l, h);
	return distr(eng);
}

class abstract_adversary {
  public:
    abstract_adversary() : N(0), fires(1, 0) {}
	virtual ~abstract_adversary() {}

	virtual ll next_act() = 0;

	virtual void light(const vector<ll> &new_fires, ll t) {
		check(new_fires, t);
		fires = new_fires;
	}

  protected:
	ll N;
	vector<ll> fires;

	virtual void check(const vector<ll> &new_fires, __int128_t t) {
		if(t < 0) result(0.0, T_OUT_OF_RANGE);

		size_t i = 0;
		for(auto x : new_fires) {
			if(x < 0 or x > N) result(0.0, OUT_OF_RANGE(x));

			for(;; ++i) {
				if(i >= fires.size() or fires[i] > x) result(0.0, NOT_LIT(x));
				if(fires[i] + t >= x) break;
			}
		}

		if(new_fires.empty() or new_fires.back() != N)
			result(0.0, RIGHTMOST_NOT_LIT);
	}
};

class sample_adversary : public abstract_adversary {
  public:
	sample_adversary() : abstract_adversary(), counter(0) {}
	virtual ~sample_adversary() {}

	virtual ll next_act() {
		ll delta = ops[counter++];
		N += delta;
		return delta;
	}

  protected:
	int counter;

	static constexpr ll ops[] = {3, -2, 2, 3, 0};
};

class random_adversary : public abstract_adversary {
  public:
	random_adversary() : abstract_adversary() {}
	virtual ~random_adversary() {}

	virtual ll next_act() {
		ll new_N = next_act_internal();
		ll delta = new_N - N;
		N = new_N;
		assert(0 <= N and N < MAX_N);
		return delta;
	}

  protected:
	virtual ll next_act_internal() {
		ll new_N = N;
		while(new_N == N) new_N = rnd(0, MAX_N - 1);
		return new_N;
	}
};

class greedy_adversary : public random_adversary {
  public:
	greedy_adversary() : random_adversary() {}
	virtual ~greedy_adversary() {}

  protected:
	virtual ll next_act_internal() {
		if(rnd(1, 100) <= 42 or fires.size() < 10)
			return random_adversary::next_act_internal();

		int lower = rnd(0, 1)? 2 : (int) fires.size() / 2;
		int i = (int) rnd(lower, fires.size() - 2);
		return fires[i] - rnd(0, 2);
	}
};

class dismantle_adversary : public random_adversary {
  public:
	dismantle_adversary() : random_adversary() {}
	virtual ~dismantle_adversary() {}

  protected:
	virtual ll next_act_internal() {
		if(fires.size() <= 2)
			return random_adversary::next_act_internal();
		for(int i = (int) fires.size() - 1; i >= 0; --i)
			if(fires[i] < .95 * N) return max(0ll, fires[i] - rnd(1, 2));
		return random_adversary::next_act_internal();
	}
};

class babystep_adversary : public random_adversary {
  public:
	babystep_adversary() : random_adversary() {}
	virtual ~babystep_adversary() {}

  protected:
	virtual ll next_act_internal() {
		return rnd(0, 1) or N <= 1? random_adversary::next_act_internal() : N - 1;
	}
};

class precomputed_adversary : public abstract_adversary {
  public:
	precomputed_adversary(size_t Q) : abstract_adversary() {
		while(pos.size() < Q) pos.insert(rnd(1, MAX_N - 1));
	}
	virtual ~precomputed_adversary() {}

	virtual ll next_act() {
		ll x = next_act_internal() - N;
		N += x;
		assert(0 <= N and N < MAX_N);
		return x;
	}

  protected:
	virtual ll next_act_internal() = 0;
	set<ll> pos;
};

class one_leave_adversary : public precomputed_adversary {
  public:
	one_leave_adversary(size_t Q) : precomputed_adversary(Q - 1) {}
	virtual ~one_leave_adversary() {}

  protected:
	virtual ll next_act_internal() {
		if(pos.empty()) return rnd(1, N);
		ll next = *pos.begin(); pos.erase(pos.begin());
		assert(next > N);
		return next;
	}
};

class one_leave_extra_adversary : public one_leave_adversary {
  public:
	one_leave_extra_adversary(size_t Q) : one_leave_adversary(Q), Q(Q), called_leave(false) {}
	virtual ~one_leave_extra_adversary() {}

  protected:
	virtual ll next_act_internal() {
		if(pos.empty()) return rnd(1, N);
		if(not called_leave and pos.size() <= Q / 2) {
			ll x = rnd(1, MAX_N - 1);
			if(x < N) {
				called_leave = true;
				Q = min(Q, MAX_N - N - 1);
				while(pos.size() < Q) pos.insert(rnd(x + 1, MAX_N - 1));
				return x;
			}
		}

		ll next = *pos.begin(); pos.erase(pos.begin());
		assert(next > N);
		return next;
	}

	ll Q;
	bool called_leave;
};

class onezero_adversary : public random_adversary {
  public:
	onezero_adversary(int Q) : random_adversary(), Q(Q), counter(0) {}
	virtual ~onezero_adversary() {}

  protected:
	virtual ll next_act_internal() {
		++counter;
		if(counter == 1)     return rnd(MAX_N / 3, MAX_N / 2);
		if(counter == 2*Q/3) return 0;
		else                 return N + (rnd(0, 1)? 1 : rnd(1, 4711));
	}

	int Q;
	int counter;
};

class up_down_adversary : public abstract_adversary {
  public:
	up_down_adversary() : abstract_adversary(), todo(), phase(DOWN) {}
	virtual ~up_down_adversary() {}

	virtual ll next_act() {
		if(todo.empty()) toggle_phase();
		assert(not todo.empty());
		ll r = todo.back(); todo.pop_back();
		N += r;
		assert(0 <= N and N < MAX_N);
		return r;
	}

  protected:
	virtual void toggle_phase() {
		assert(todo.empty());
		if(phase == UP) phase = DOWN, init_down();
		else            phase = UP,   init_up();
	}

	virtual void init_up() = 0;
	virtual void init_down() = 0;

	vector<ll> todo;
	enum {UP, DOWN} phase;
};

class step_up_down_adversary : public up_down_adversary {
  public:
	step_up_down_adversary(int perc) : up_down_adversary(), perc(perc) {}
	virtual ~step_up_down_adversary() {}

  protected:
	virtual void init_up() {
		if(uniform_int_distribution<>(1, 100)(eng) <= perc) {
			ll low = max(MAX_N - 100000, MAX_N / 2);
			todo.push_back(rnd(low, MAX_N - 1) - N);
		}
		else {
			ll high = min(471142ll, MAX_N / 2);
			assert(high > 1);
			todo.push_back(rnd(1, high) - N);
		}
	}

	virtual void init_down() {
		ll steps = rnd(1, 1337);
		ll X = N;

		for(int i = 0; i < steps; ++i) {
			int upper = 42;
			if(N <= 5000) upper = 5;
			todo.push_back(-rnd(1, upper));
			X += todo.back();

			if(X < 0) {
				todo.pop_back();
				return;
			}
		}

		for(int i = 0; i < steps; ++i) todo.push_back(-(X / steps));

		shuffle(todo.begin(), todo.end(), eng);
		todo.resize(2 * todo.size() / 3);
	}

	int perc;
};

class countdown_adversary : public up_down_adversary {
  public:
	countdown_adversary() : up_down_adversary() {}
	virtual ~countdown_adversary() {}

  protected:
	virtual void init_up() {
		ll x; for(x = N; x == N; x = rnd(MAX_N/2, MAX_N - 1));
		todo.push_back(x - N);
	}

	virtual void init_down() {
		ll steps = min(471ll, N);
		ll upper = rnd(1, 100) <= 42? min(10ll, N / steps) : 1;
		for(ll i = 0; i < steps; ++i) todo.push_back(-rnd(1, upper));
	}
};

class revstep_up_down_adversary : public up_down_adversary {
  public:
	revstep_up_down_adversary() : up_down_adversary() {}
	virtual ~revstep_up_down_adversary() {}

  protected:
  	virtual void init_down() {
		ll low = min(100000ll, MAX_N / 10);
		todo.push_back(rnd(0, low) - N);
	}

	virtual void init_up() {
		ll steps = rnd(1, 1337);
		ll X = N;

		for(int i = 0; i < steps; ++i) {
			todo.push_back(rnd(1, 5));
			X += todo.back();

			if(X >= MAX_N) {
				todo.pop_back();
				if(todo.empty()) todo.push_back(-1);
				return;
			}
		}

		for(int i = 0; i < steps; ++i) todo.push_back((MAX_N - 1 - X) / steps);

		shuffle(todo.begin(), todo.end(), eng);
		todo.resize(2 * todo.size() / 3);
	}
};

class one_join_adversary : public precomputed_adversary {
  public:
	one_join_adversary(size_t Q) : precomputed_adversary(Q) {}
	virtual ~one_join_adversary() {}

  protected:
	virtual ll next_act_internal() {
		auto it = pos.end(); --it;
		ll x = *it; pos.erase(it);
		assert(N == 0 or x < N);
		return x;
	}
};

class kill_adversary : public random_adversary {
  public:
	kill_adversary(int factor, abstract_adversary *adv, bool stop_after_kill) :
		random_adversary(), factor(factor), internal_adv(adv),
		random_phase(false), stop_after_kill(stop_after_kill) {}
	virtual ~kill_adversary() { delete internal_adv; }

	virtual ll next_act() {
		// did we kill the solution?
		if(random_phase and stop_after_kill)
			return 0;

		// can we?
		ll to_leave = attempt_kill();
		if(to_leave) {
			#ifdef DEBUG
				if(not random_phase) fprintf(stderr,"<kill!>");
			#endif

			N -= to_leave;
			random_phase = true;
			return -to_leave;
		}

		// ... no, we can't :(
		if(random_phase) return random_adversary::next_act();

		ll r = internal_adv->next_act();
		N += r;
		return r;
	}

	virtual void light(const vector<ll> &new_fires, ll t) {
		if(random_phase) random_adversary::light(new_fires, t);
		else             internal_adv->light(new_fires, t);

		fires = new_fires;
	}

  protected:
	ll attempt_kill() {
		pair<__int128_t, ll> opt(0, 0);

		for(size_t i = 1; i < fires.size(); ++i) {
			ll to_leave = N + 1 - fires[i];
			__int128_t cost = fires[i] - fires[i - 1] - 1;

			if(cost > factor * to_leave)
				opt = max(opt, make_pair((cost + to_leave - 1) / to_leave, -to_leave));
		}

		return -opt.second;
	}

	__int128_t factor;
	abstract_adversary *internal_adv;
	bool random_phase;
	bool stop_after_kill;
};

void check() {
	assert(fscanf(fin, "%d %lld", &FIRELIMIT, &MAX_N) == 2);

	int Q; char buffer[512];
	assert(fscanf(fin, "%d %s", &Q, buffer) == 2);

	string strategy(buffer);
	int kill = 0, stop_after_kill;
	if(strategy == "kill")
		assert(fscanf(fin, "%d %d %s", &kill, &stop_after_kill, buffer) == 3);
	strategy = buffer;

	ll seed; assert(fscanf(fin, "%lld", &seed) == 1);
	eng.seed(seed); eng.discard(133742);

	abstract_adversary *adv;
	     if(strategy == "rand")            adv = new random_adversary();
	else if(strategy == "greedy")          adv = new greedy_adversary();
	else if(strategy == "dism")            adv = new dismantle_adversary();
	else if(strategy == "one-zero")        adv = new onezero_adversary(Q);
	else if(strategy == "one-leave")       adv = new one_leave_adversary(Q);
	else if(strategy == "one-leave-extra") adv = new one_leave_extra_adversary(Q);
	else if(strategy == "one-join")        adv = new one_join_adversary(Q);
	else if(strategy == "baby")            adv = new babystep_adversary();
	else if(strategy == "step")            adv = new step_up_down_adversary(100);
	else if(strategy == "step2")           adv = new step_up_down_adversary(25);
	else if(strategy == "revs")            adv = new revstep_up_down_adversary();
	else if(strategy == "doom")            adv = new countdown_adversary();
	else if(strategy == "sample")          adv = new sample_adversary();
	else                                   throw -41;

	if(kill) adv = new kill_adversary(kill, adv, stop_after_kill);

	assert(strategy != "one-leave" or not kill or stop_after_kill);
	assert(strategy != "one-leave-extra" or not kill);

	bool only_one_leave = (strategy == "one-leave" or strategy == "one-leave-extra");
	int num_neg = 0;

	size_t max_fires = 1;
	__int128_t worst_coeff = 1;
	for(int act = 0; act < Q; ++act) {
		ll d = adv->next_act();
		if(d == 0) break;
		if(d < 0) ++num_neg;
		assert(num_neg <= 1 or not only_one_leave);
		if(num_neg > 1 and only_one_leave) break;
		write(d);

		auto [t, fires] = read_fires();
		max_fires = max(max_fires, fires.size());
		adv->light(fires, t);

		if(d < 0) d = -d;
		worst_coeff = max(worst_coeff, (t + d - 1) / d);
		if(worst_coeff > TCOEFF) result(0.0, GONE_TOO_FAR);
	}

	#ifdef DEBUG
		fprintf(stderr, "(%d)", (int) max_fires);
		fprintf(stderr, "[%lld]", worst_coeff);
	#endif

	sprintf(buffer, CORRECT(worst_coeff));
	result(vector<float>({1.0f, _score[worst_coeff]}), vector<string>({"Correct", buffer}));
}
