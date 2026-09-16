void PBS(int l, int r, vector<int>& candi) {
if(l + 1 == r || candi.empty()) { //trivial case.
for(auto c : candi) ans[c] = l;
return;
}
int mid = (l + r) >> 1;
// do things: events from [l, mid)

// split candi into two parts
vector<int> ok, not_ok;
for(auto c : candi) {
ull sum = 0;
//Query information

if(target[c] <= sum /* Ok Condition */) ok.push_back(c);
else {
  target[c] -= sum; //Reduce the condition
  not_ok.push_back(c);
}
}
// undo things: events from [l, mid)

// continue binary search and free memory
PBS(l, mid, ok); vector<int> ().swap(ok);
PBS(mid, r, not_ok); vector<int> ().swap(not_ok);
}