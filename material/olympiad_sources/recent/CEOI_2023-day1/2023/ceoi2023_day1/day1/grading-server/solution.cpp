#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll S;

struct State{
    ll a1, d1, a2, d2;
    bool operator==(const State& other) const {return a1==other.a1 && a2 == other.a2 && d1 == other.d1 && d2 == other.d2;}
};

State sab(State state){
    return {state.a2, max(0ll, state.d2 - 1), state.a1, state.d1};
}
State att(State state){
    return {state.a2 - (state.a1 - S*state.d2), state.d2, state.a1, state.d1};
}

vector<vector<vector<int>>> dp;

bool half_sab_win(State state){
    ll sab_cnt = state.d2 / 2;
    state.a1 -= sab_cnt * (state.a2 - S*state.d1);
    state.d2 -= sab_cnt;
    state = att(state);
    state.a1 -= state.d2 * (state.a2 - S*state.d1);
    state.d2 = 0;
    state = att(state);

    ll alpha1 = state.a1 - S*state.d2;
    ll beta2 = S - state.a2;
    return alpha1 + state.d2 * beta2 >= S;
}

ll calc(ll d1, ll d2, ll a2);

int calls = 0;

bool wins(State state){
    // trivial cases
    if(state.a1 <= 0) return false;
    if(state.a2 <= 0) return true;
    // no one can attack
    ll sab_rounds = (max(0ll, min(state.d2*S - state.a1, state.d1*S - state.a2)) + S-1) / S;
    state.d1 -= sab_rounds;
    state.d2 -= sab_rounds;
    // player 1 can't attack and player 2 can't sabotage
    if(state.a1 <= state.d2*S && state.d1 == 0 && state.a2 < S){
        ll beta2 = S - state.a2;
        ll rounds = (state.d2*S - state.a1 + beta2-1) / beta2;
        state.d2 -= rounds;
        state.a1 -= rounds * state.a2;
        if(state.d2 < 0 || state.a1 <= 0) return false;
    }
    // player 1 can't attack
    if(state.a1 <= state.d2*S) return !wins(sab(state));
    // helpful values
    ll alpha1 = state.a1 - S*state.d2;
    ll alpha2 = state.a2 - S*state.d1;
    ll beta2 = min(S, S - alpha2);
    // player 1 must attack
    if(alpha1 >= S && alpha2 <= S) return true;
    if(alpha2 >= S){
        // calls++;
        return !wins(att(state));
    }
    if(state.d2 == 0) return !wins(att(state));
    // Can player 1 win by repeated sabotage?
    if(state.d2 >= S) return true; // prevent overflow!
    if(alpha1 + state.d2 * beta2 >= S) return true;
    // Prevent opponent win by repeated sabotage:
    if(state.d1 > 0){
        ll minAlpha1 = (S * (state.d1 - 1) + alpha2) / (state.d1 + 1);
        ll sabs_todo = min(state.d2, (max(0ll, minAlpha1 - alpha1) + beta2-1) / beta2);
        state.d2 -= sabs_todo;
        state.a1 -= sabs_todo * alpha2;
    }
    if(state.d2 == 0) return !wins(att(state));
    // Can player 1 win by using half of his sabotages?
    if(half_sab_win(state)) return true;
    // Now we need dp.
    ll minA1 = calc(state.d1, state.d2, state.a2);
    return state.a1 >= minA1;
}

// It can be proven that we need O(1) iterations when min(d1, d2) > 1
bool winsSafe(State state){
    if(state.a1 <= state.d2*S) return !wins(sab(state));
    if(state.d2 == 0) return !winsSafe(att(state));
    return !wins(sab(state)) || !winsSafe(att(state));
}

ll calc(ll d1, ll d2, ll a2){
    ll beta2 = S*(d1+1) - a2;

    if(dp[d2][d1][beta2] != -1) return dp[d2][d1][beta2] + S*d2;
    ll lo = d2*S+1, hi = (d2+1)*S;
    for(ll a1 = (lo+hi)/2; lo<hi; a1 = (lo+hi)/2){
        State state = {a1, d1, a2, d2};
        bool good = !wins(sab(state)) || !winsSafe(att(state));
        if(good) hi = a1;
        else lo = a1+1;
    }
    dp[d2][d1][beta2] = lo - S*d2;
    calls++;
    return lo;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int Q;
    cin >> S >> Q;
    ll totalSize = 0;
    dp.resize(1);
    for(ll d2 = 1; d2*d2 <= 8*S; d2++){
        vector<vector<int>> inner(min(S, 1 + 8*S/(max(1ll, d2*d2))));
        for(ll d1 = 0; d1 < S && d1*d2*d2 <= 8*S; d1++){
            ll mySize = min(S, 1 + 8*S/max(1ll, d1)/(d2*d2));
            totalSize += mySize;
            inner[d1].assign(mySize, -1);
        }
        dp.push_back(inner);
    }
    for(ll d2 = 1; d2*d2 <= 8*S; d2++){
        for(ll d1 = 0; d1 < S && d1*d2*d2 <= 8*S; d1++){
            ll mySize = min(S, 1 + 8*S/max(1ll, d1)/max(1ll, d2*d2));
            for(ll b2 = 1; b2 < mySize; b2++){
                ll minAlpha1 = (S * d1 - b2) / (d1 + 1);
                State state{S*d2+minAlpha1, d1, S*(d1+1)-b2, d2};
                if(minAlpha1 > 0 && minAlpha1 + d2*b2 < S && !half_sab_win(state)){
                    calc(d1, d2, S*(d1+1) - b2);
                };
            }
        }
    }

    for(int q = 0; q < Q; q++){
        ll a1, d1, a2, d2;
        cin >> a1 >> d1 >> a2 >> d2;
        cout << (wins({a1, d1, a2, d2}) ? "YES" : "NO") << "\n";
    }
}