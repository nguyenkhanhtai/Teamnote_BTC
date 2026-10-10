#include <bits/stdc++.h>
#define int long long
#include "../source/cpp/data_structure/arpa_trick.cpp"
#include "../source/cpp/data_structure/binary_trie.cpp"
#include "../source/cpp/data_structure/block_array_mo.cpp"
#include "../source/cpp/data_structure/erasable_priority_queue.cpp"
#include "../source/cpp/data_structure/expandable.cpp"
#include "../source/cpp/data_structure/fenwick_2d.cpp"
#include "../source/cpp/data_structure/hash_map.cpp"
#include "../source/cpp/data_structure/implicit_treap.cpp"
#include "../source/cpp/data_structure/interval_set.cpp"
#include "../source/cpp/data_structure/iterative_segment_tree.cpp"
#include "../source/cpp/data_structure/kd_tree.cpp"
#include "../source/cpp/data_structure/li_chao.cpp"
#include "../source/cpp/data_structure/line_container.cpp"
#include "../source/cpp/data_structure/link_cut_tree.cpp"
#include "../source/cpp/data_structure/parallel_binary_search.cpp"
#include "../source/cpp/data_structure/persistent_segment_tree.cpp"
#include "../source/cpp/data_structure/segment_tree_beats.cpp"
#include "../source/cpp/data_structure/sparse_segment_tree.cpp"
#include "../source/cpp/data_structure/wavelet_tree.cpp"
#include "../source/cpp/dp/alien_dp.cpp"
#include "../source/cpp/dp/convex_hull_trick.cpp"
#include "../source/cpp/dp/dnc_dp.cpp"
#include "../source/cpp/dp/expected_value_dp.cpp"
#include "../source/cpp/dp/monotonic_queue.cpp"
#include "../source/cpp/dp/one_d_one_d_dp.cpp"
#include "../source/cpp/dp/reroot_dp.cpp"
#include "../source/cpp/dp/slope_trick.cpp"
#include "../source/cpp/dp/sos_dp.cpp"
#include "../source/cpp/geometry/area_union_rectangles.cpp"
#include "../source/cpp/geometry/circle_tangents.cpp"
#include "../source/cpp/geometry/convex_hull.cpp"
#include "../source/cpp/geometry/halfplane_intersection.cpp"
#include "../source/cpp/geometry/line_hull_intersection.cpp"
#include "../source/cpp/geometry/manhattan_mst.cpp"
#include "../source/cpp/geometry/minkowski_sum.cpp"
#include "../source/cpp/geometry/planar_dual.cpp"
#include "../source/cpp/geometry/point_in_convex.cpp"
#include "../source/cpp/geometry/polygon_raycast.cpp"
#include "../source/cpp/geometry/primitive_geometry.cpp"
#include "../source/cpp/geometry/rotating_calipers.cpp"
#include "../source/cpp/geometry/smallest_enclosing_circle.cpp"
#include "../source/cpp/graph/bcc.cpp"
#include "../source/cpp/graph/dominator_tree.cpp"
#include "../source/cpp/graph/dsu_rollback.cpp"
#include "../source/cpp/graph/euler_path.cpp"
#include "../source/cpp/graph/floyd_warshall.cpp"
#include "../source/cpp/graph/functional_cycle.cpp"
#include "../source/cpp/graph/general_matching.cpp"
#include "../source/cpp/graph/gomory_hu.cpp"
#include "../source/cpp/graph/hopcroft_karp.cpp"
#include "../source/cpp/graph/hungarian.cpp"
#include "../source/cpp/graph/matroid_intersection.cpp"
#include "../source/cpp/graph/max_flow_dinic.cpp"
#include "../source/cpp/graph/min_cost_flow.cpp"
#include "../source/cpp/graph/online_bipartite.cpp"
#include "../source/cpp/graph/prufer.cpp"
#include "../source/cpp/graph/scc_tarjan.cpp"
#include "../source/cpp/graph/stable_marriage.cpp"
#include "../source/cpp/graph/steiner_tree.cpp"
#include "../source/cpp/graph/two_sat.cpp"
#include "../source/cpp/graph/vizing.cpp"
#include "../source/cpp/math/berlekamp_massey.cpp"
#include "../source/cpp/math/big_integer.cpp"
#include "../source/cpp/math/diophantine.cpp"
#include "../source/cpp/math/discrete_log_bsgs.cpp"
#include "../source/cpp/math/extended_gcd.cpp"
#include "../source/cpp/math/fast_sieve.cpp"
#include "../source/cpp/math/fft.cpp"
#include "../source/cpp/math/floor_sum.cpp"
#include "../source/cpp/math/fwht.cpp"
#include "../source/cpp/math/game_strategy.cpp"
#include "../source/cpp/math/lagrange.cpp"
#include "../source/cpp/math/linalg_gauss.cpp"
#include "../source/cpp/math/ntt.cpp"
#include "../source/cpp/math/pollard_rho.cpp"
#include "../source/cpp/math/prime_counter.cpp"
#include "../source/cpp/math/primitive_root.cpp"
#include "../source/cpp/math/rabin_miller.cpp"
#include "../source/cpp/math/sqrt_mod.cpp"
#include "../source/cpp/math/stern_brocot.cpp"
#include "../source/cpp/math/xor_basis.cpp"
#include "../source/cpp/string/aho_corasick.cpp"
#include "../source/cpp/string/debruijn.cpp"
#include "../source/cpp/string/kmp.cpp"
#include "../source/cpp/string/lyndon.cpp"
#include "../source/cpp/string/manacher.cpp"
#include "../source/cpp/string/palindrome_tree.cpp"
#include "../source/cpp/string/rolling_hash.cpp"
#include "../source/cpp/string/suffix_array.cpp"
#include "../source/cpp/string/suffix_automaton.cpp"
#include "../source/cpp/string/z_algorithm.cpp"
#include "../source/cpp/tree/centroid_decomposition.cpp"
#include "../source/cpp/tree/hld.cpp"
#include "../source/cpp/tree/tree_isomorphism.cpp"
#include "../source/cpp/utility/calendar.cpp"
#include "../source/cpp/utility/expression.cpp"
#include "../source/cpp/utility/johnson.cpp"
#include "../source/cpp/utility/josephus.cpp"
#include "../source/cpp/utility/interactive.cpp"
#include "../source/cpp/utility/bit_tricks.cpp"
using namespace std;
void notebook_usage_examples() {
 {
using namespace notebook::data_structure;

auto ids = range_max_indices({3,1},{{0,2}});
 }
 {
using namespace notebook::data_structure;

BinaryTrie tr; tr.insert(7); auto best = tr.max_xor(3);
 }
 {
using namespace notebook::data_structure;

BlockArray a({1,2,3});
 }
 {
using namespace notebook::data_structure;

ErasablePriorityQueue q; q.insert(3); // max-heap
 }
 {
using namespace notebook::data_structure;
vector<int> buildIndex(const vector<int>&);
ExpandableIndex idx(buildIndex); idx.insert(3);
// buildIndex(const vector<int>&): vector<int>.
 }
 {
using namespace notebook::data_structure;

Fenwick2D fw(3,4); fw.add(0,1,5); auto s = fw.sum(0,0,3,4);
 }
 {
using namespace notebook::data_structure;

HashMap cnt; cnt.reserve(1000); ++cnt[42];
 }
 {
using namespace notebook::data_structure;

ImplicitTreap tr(123456); tr.insert(0,7); tr.reverse(0,1);
 }
 {
using namespace notebook::data_structure;

IntervalSet seg(0,10,0); seg.assign(2,5,7);
 }
 {
using namespace notebook::data_structure;
int mergeSum(int,int);
// int mergeSum(int a,int b) { return a+b; }
SegmentTree st({1,2,3},0,mergeSum); auto s = st.fold(0,3);
RangeAddPointQuery lazy(3); lazy.add(0,2,4);
 }
 {
using namespace notebook::data_structure;

KDTree kd({{0.,0.},{1.,2.}}); auto p = kd.nearest({0.,1.});
 }
 {
using namespace notebook::data_structure;

LiChao lc(-100,101); lc.add(2,3); auto y = lc.minimum(5);
 }
 {
using namespace notebook::data_structure;

LineContainer lc; lc.add(2,3); auto y = lc.maximum(5);
 }
 {
using namespace notebook::data_structure;

LinkCutTree lct({1,2,3}); lct.link(0,1);
 }
 {
using namespace notebook::data_structure;
void reset(); void apply(int); bool test(int);
auto ans = parallel_binary_search(3,2,reset,apply,test);
// reset(): void; apply(eventID): void; test(queryID): bool.
 }
 {
using namespace notebook::data_structure;

PersistentRangeSum pst(3); int root = pst.add(0,1,5);
auto s = pst.sum(root,0,3); // root 0: all zeros
 }
 {
using namespace notebook::data_structure;

SegmentTreeBeats st({1,2,3}); st.chmin(0,3,2);
 }
 {
using namespace notebook::data_structure;

SparseRangeSum st(0,1000000000LL); st.add(42,5);
 }
 {
using namespace notebook::data_structure;

WaveletTree wt({3,1,2}); auto x = wt.kth(0,3,0);
 }
 {
using namespace notebook::dp;
int k=2; int lo=0,hi=10; PenalizedResult oracle(int);
auto ans = aliens_exact(k,lo,hi,oracle);
// oracle(lambda): PenalizedResult{minCost, count}.
 }
 {
using namespace notebook::dp;

MonotoneMinHull cht; cht.add(3,1); auto y = cht.query(2);
 }
 {
using namespace notebook::dp;
int n=3; vector<int> previous(4); int cost(int,int);
auto next = divide_conquer_layer(previous,cost);
auto ans = knuth_partition(n,cost); // cost(l,r): int
 }
 {
using namespace notebook::dp;

mt19937_64 rng(123456);
auto ans = banded_pick_k(vector<int>{1,2,3},2,3,rng);
 }
 {
using namespace notebook::dp;

MonotoneMinQueue q; q.push(0,5); q.expire(0);
 }
 {
using namespace notebook::dp;
int n=3; int cost(int,int);
auto dp = monotone_partition_dp(n,cost); // cost(j,i): int
 }
 {
using namespace notebook::dp;
vector<vector<int>> g{{1},{0}}; RerootState identity{0,0}; RerootState merge(RerootState,RerootState); RerootState finish(RerootState,int); RerootState lift(RerootState,int,int);
auto ans = reroot(g,identity,merge,finish,lift);
// RerootState: edit state type and write three named functions.
 }
 {
using namespace notebook::dp;

SlopeTrick f; f.add_abs(3); auto ans = f.minimum();
 }
 {
using namespace notebook::dp;

vector<int> f(1<<3,1); subset_transform(f);
 }
 {
using namespace notebook::geometry;

auto area = rectangle_union_area({{0,0,2,3}});
 }
 {
using namespace notebook::geometry;

auto tangents = circle_tangents({0,0},1,{4,0},1);
 }
 {
using namespace notebook::geometry;

auto hull = convex_hull({{0,0},{2,0},{0,2}});
 }
 {
using namespace notebook::geometry;
vector<Line> lines{{{0,0},{1,0}}};
auto polygon = halfplane_intersection(lines,1000000.L);
// lines: vector<Line>; keeps left side, clips to bounding square.
 }
 {
using namespace notebook::geometry;

LineHullIntersection idx({{0,0},{2,0},{0,2}});
auto hits = idx.intersect(Line{{0,1},{1,0}});
 }
 {
using namespace notebook::geometry;

auto [cost,edges] = manhattan_mst({{0,0},{2,3}});
 }
 {
using namespace notebook::geometry;
vector<Point> hullA{{0,0},{2,0},{0,2}},hullB=hullA;
auto sum = minkowski_sum(hullA,hullB); // vector<Point>, CCW
 }
 {
using namespace notebook::geometry;
vector<Point> points{{0,0},{2,0},{0,2}}; vector<pair<int,int>> edges{{0,1},{1,2},{2,0}};
auto dual = planar_dual(points,edges);
// points: vector<Point>; edges: vector<pair<int,int>>.
 }
 {
using namespace notebook::geometry;

int where = point_in_convex({{0,0},{2,0},{0,2}},{1,0});
 }
 {
using namespace notebook::geometry;

int where = point_in_polygon({{0,0},{2,0},{0,2}},{1,0});
 }
 {
using namespace notebook::geometry;

Point a{0,0}, b{2,1}; Line l{a,b-a}; // point + direction
 }
 {
using namespace notebook::geometry;

auto d2 = diameter_squared({{0,0},{2,0},{0,2}});
 }
 {
using namespace notebook::geometry;

mt19937_64 rng(123456);
auto c = smallest_enclosing_circle({{0,0},{2,0},{0,2}},rng);
 }
 {
using namespace notebook::graph;

auto bcc = biconnected_components(3,{{0,1},{1,2}});
 }
 {
using namespace notebook::graph;

auto idom = immediate_dominators({{1},{2},{}},0);
 }
 {
using namespace notebook::graph;

RollbackDSU dsu(3); auto snap = dsu.snapshot();
dsu.unite(0,1); dsu.rollback(snap);
 }
 {
using namespace notebook::graph;

auto trail = euler_trail(3,{{0,1},{1,2}},false);
 }
 {
using namespace notebook::graph;
vector<vector<int>> dist{{0,1},{1,0}};
bool ok = floyd_warshall(dist); // vector<vector<int>>
 }
 {
using namespace notebook::graph;
int nextState(int);
// int nextState(int x) { return (x+1)%3; }
auto cycle = find_cycle(0,nextState);
 }
 {
using namespace notebook::graph;

auto mate = general_matching({{1},{0,2},{1}});
 }
 {
using namespace notebook::graph;

auto tree = gomory_hu(3,{{0,1,5},{1,2,7}});
 }
 {
using namespace notebook::graph;

HopcroftKarp hk(2,3); hk.add_edge(0,1); int k = hk.solve();
// hk.left[u], hk.right[v]: matched ID; -1 if unmatched.
 }
 {
using namespace notebook::graph;

auto ans = hungarian({{3,1},{2,4}}); // ans.cost, ans.column
 }
 {
using namespace notebook::graph;
int n=3; bool oracle1(const vector<int>&); bool oracle2(const vector<int>&);
MatroidIntersection mi(n,oracle1,oracle2); auto ids = mi.solve();
// Each oracle: bool(const vector<int>& selectedIDs).
 }
 {
using namespace notebook::graph;

Dinic flow(3); flow.add_edge(0,1,5); flow.add_edge(1,2,5);
auto f = flow.max_flow(0,2);
 }
 {
using namespace notebook::graph;

MinCostFlow flow(3); flow.add_edge(0,1,5,2);
auto ans = flow.send(0,1,3); // ans.flow, ans.cost
 }
 {
using namespace notebook::graph;

BipartiteDSU dsu(3); dsu.add_edge(0,1);
 }
 {
using namespace notebook::graph;

auto edges = prufer_decode({0,1}); // n = code.size()+2
 }
 {
using namespace notebook::graph;

auto scc = strongly_connected_components({{1},{0,2},{}});
 }
 {
using namespace notebook::graph;

auto wives = stable_marriage({{0,1},{1,0}},{{0,1},{1,0}});
 }
 {
using namespace notebook::graph;
vector<vector<pair<int,int>>> g{{{1,1}},{{0,1},{2,1}},{{1,1}}};
auto cost = steiner_tree(g,{0,2});
// g: vector<vector<pair<int,int>>>, undirected.
 }
 {
using namespace notebook::graph;

TwoSAT sat(3); sat.add_or(sat.literal(0,true),
                                sat.literal(1,false));
auto ans = sat.solve(); // optional<vector<bool>>
 }
 {
using namespace notebook::graph;

auto colors = vizing_coloring(3,{{0,1},{1,2},{0,2}});
 }
 {
using namespace notebook::math;

vector<int> a = {0,1,1,2,3,5};
auto rec = berlekamp_massey(a); int x = recurrence_term(a,rec,10);
 }
 {
using namespace notebook::math;

bignum a{42,1}; print(a); // 1000000042
 }
 {
using namespace notebook::math;

auto sol = diophantine(3,5,7);
 }
 {
using namespace notebook::math;

auto exponent = discrete_log(2,8,13);
 }
 {
using namespace notebook::math;

auto b = extended_gcd(12,18); // b.gcd, b.x, b.y
 }
 {
using namespace notebook::math;

auto primes = segmented_sieve(2,1000000000,5000000);
 }
 {
using namespace notebook::math;

auto c = convolution_fft({1,2},{3,4});
 }
 {
using namespace notebook::math;

auto s = floor_sum(10,7,3,2); // sum floor((3*i+2)/7)
 }
 {
using namespace notebook::math;

vector<int> a(8,1); fwht(a,Walsh::Xor,998244353);
 }
 {
using namespace notebook::math;

auto state = retrograde_analysis(3,{{1},{2},{}});
 }
 {
using namespace notebook::math;

auto y = lagrange(vector<int>{0,1,4},5,998244353);
 }
 {
using namespace notebook::math;

auto sol = gauss({{1,2,3},{2,1,3}},2,1000000007);
 }
 {
using namespace notebook::math;

auto c = convolution_ntt({1,2},{3,4});
 }
 {
using namespace notebook::math;

mt19937 rng(123456); auto factors = factorize(360,rng);
 }
 {
using namespace notebook::math;

auto count = prime_count(1000000);
 }
 {
using namespace notebook::math;

mt19937 rng(123456); auto g = primitive_root(17,rng);
 }
 {
using namespace notebook::math;

bool prime = is_prime(1000000007);
 }
 {
using namespace notebook::math;

auto root = sqrt_mod(4,17);
 }
 {
using namespace notebook::math;

auto path = stern_encode(3,5); auto fraction = stern_decode(path);
 }
 {
using namespace notebook::math;

XorBasis basis; basis.insert(7); auto best = basis.maximum();
 }
 {
using namespace notebook::strings;
void onMatch(int,int);
AhoCorasick ac; ac.add("aba",0); ac.build();
ac.scan("ababa",onMatch); // void onMatch(int end,int id)
 }
 {
using namespace notebook::strings;
void onDigit(int);
de_bruijn(2,3,onDigit); // void onDigit(int digit)
 }
 {
using namespace notebook::strings;

auto positions = kmp_matches("ababa","aba");
 }
 {
using namespace notebook::strings;

int start = minimum_rotation("baca");
 }
 {
using namespace notebook::strings;

auto radii = manacher("ababa"); // radii.odd, radii.even
 }
 {
using namespace notebook::strings;

PalindromeTree pt; for (char c : string("aba")) pt.append(c);
auto counts = pt.occurrences();
 }
 {
using namespace notebook::strings;

RollingHash h("abc"); auto hash = h.get(0,2);
 }
 {
using namespace notebook::strings;

SuffixArray sa("banana"); // sa.sa, sa.lcp
 }
 {
using namespace notebook::strings;

SuffixAutomaton sam("banana");
 }
 {
using namespace notebook::strings;

auto z = z_function("ababa");
 }
 {
using namespace notebook::tree;
vector<vector<int>> g{{1},{0}}; void onCentroid(int,int,const vector<bool>&);
CentroidDecomposition cd(g,onCentroid);
// void onCentroid(int c,int parent,const vector<bool>& blocked)
 }
 {
using namespace notebook::tree;

HeavyLight hld({{1},{0,2},{1}},0); auto seg = hld.subtree(1);
// Store vertex values at hld.pos[u]; seg = [l,r).
 }
 {
using namespace notebook::tree;

TreeIsomorphism iso; bool same = iso.isomorphic({{1},{0}},
                                                            {{1},{0}});
 }
 {

int weekday = day_of_week(2026,10,8);
 }
 {

auto value = evaluate_expression("2*(3+4)");
 }
 {

auto schedule = johnson_schedule({{0,2,3},{1,4,1}});
 }
 {

auto survivor = josephus_fast(10,3); // zero-based
 }
 {

InteractiveSession judge(cin,cout,100);
 }
 {
void onMask(int);
for_each_submask(13,onMask); for_each_k_subset(5,2,onMask);
// void onMask(int mask)
 }
}
