struct DequeOptimization{ //For basic operation: min/max
deque<ii> dq;
void pushBack(int id, int num){
while(!dq.empty() and num >= dq.back().fi) dq.pop_back();
dq.pb(ii(num, id));
}
void popFront(int l){
if (dq.empty()) return;
while(!dq.empty() and dq.front().se <= l) dq.pop_front();
}
inline int getMax(){
int mx = -inf;
if (!dq.empty()) maximize(mx, dq.front().fi);
return mx;
}
} opt[MAXN];

struct DoublyStack{  //For Linear Operation 
vector<ii> stk1, stk2;
void pushBack(int num){
if (stk2.empty()) stk2.pb(ii(num, num));
else {
ii toAdd = ii(num, max(num, stk2.back().se));
stk2.pb(toAdd);
}
}
void popFront(){
if (stk1.size() == 0 and stk2.size() == 0) return;
if (stk1.size() > 0) stk1.pop_back();
else{
 FORD(i, (int) stk2.size() - 1, 0){
    int curNum = stk2[i].fi;
    if (stk1.size() == 0) stk1.pb(ii(curNum, curNum));
    else stk1.pb(ii(curNum, max(curNum, stk1.back().se)));
 }
 if (stk1.size() > 0) stk1.pop_back();
 stk2.clear();
 stk2.shrink_to_fit();
}
}
int getMax(){
int mx = -inf;
if (stk2.size()) maximize(mx, stk2.back().se);
if (stk1.size()) maximize(mx, stk1.back().se);
return mx;
}
} opt[MAXN];

