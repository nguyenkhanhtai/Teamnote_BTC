# Notebook C++ interfaces

## Simple contest interfaces

The printed notebook now uses concrete structs and named helper functions:
no user-defined templates, lambda expressions, or `explicit` constructors.
The previous typename tutorial has been replaced by a declaration/callback guide.

- Declare `SegmentTree st(a, 0, mergeSum);`, where `mergeSum` is an ordinary
  `int mergeSum(int a, int b)` function.
- Declare `IntervalSet`, `ErasablePriorityQueue`, `MonotoneMinQueue`, and
  `HashMap` without template arguments; their values are `int`.
  The erasable queue is a max-heap; negate keys for minimum queries.
- `KDTree` has a `D = 2` constant to edit for another dimension.
- `RerootState`, `CycleState`, and `ExpandableIndex::Index` are concrete type
  aliases to edit when adapting the algorithm to a problem.
- Required callbacks accept named functions through `std::function`; the
  examples do not require lambdas. This can add dispatch overhead compared
  with the former templated callbacks.
- `tests/notebook_usage.cpp` compiles the declarations/calls in the examples;
  the runtime suite uses the new interfaces and checks the algorithms against
  independent implementations. Old generic interfaces are no longer supported.

The descriptions and page counts below record earlier versions of the notebook.

Parts 1–7 use 94 self-contained C++17 listings: 74 pseudocode replacements and 20 repaired or wrapped legacy C++ listings. Each file is an includable snippet with `#pragma once`, standard-library includes, and a `notebook::<section>` namespace (`notebook::strings` for string algorithms). Files that reuse another snippet include it explicitly. GNU C++17 is required (`bits/stdc++.h`, 128-bit integers).

```cpp
#include <bits/stdc++.h>
#define int long long
#include "source/cpp/data_structure/segment_tree_beats.cpp"
#include "source/cpp/tree/hld.cpp"

signed main() {
    notebook::data_structure::SegmentTreeBeats a({4, 1, 7});
    a.chmin(0, 3, 5);
    assert(a.sum(0, 3) == 10);
}
```

## Conventions

- Snippets use `int` with the notebook template's `#define int long long`.
  Include standard-library headers before the macro; use `signed main()`.
  Remove the macro only after adjusting constants and arithmetic for 32-bit values.
- Numeric values, indices, capacities, masks, and callbacks use `int`.
  Wide intermediate products and exact results use `__int128` where needed.
  Byte characters remain `unsigned char`.
- XOR basis, binary trie, and subset masks accept nonnegative signed values:
  bits 0 through 62 with the template above. Gosper allows `n <= 63`.
  `IntegerHash` uses masked wide products, so it does not rely on signed overflow.
- Fixed lists in range-for loops are declared as named arrays beforehand.

- Stateful algorithms use plain `struct` with directly accessible fields and methods.
- Vertices, array positions, edge IDs, and ranks are zero-based. Array ranges are `[l,r)`. Wavelet-tree value ranges are inclusive; `kth` takes a zero-based rank.
- Constructors own their state. Functions receive their graph/data explicitly. Missing solutions use `optional`; returned structs name outputs such as cost, flow, components, or edge IDs.
- Tree routines require a connected tree. Graph adjacency lists use the direction stated by each routine; undirected adjacency must contain both directions.
- HLD returns segments in source-to-destination order. `reversed` tells a caller how to fold each segment; `edges=true` excludes the LCA's vertex position.
- Rerooting receives an associative `merge`, identity, vertex `finish`, and edge `lift`. Centroid decomposition receives a processing callback and passes the current blocked set after blocking the centroid.
- Aho-Corasick accepts nonempty lowercase patterns. `scan` reports the exclusive match end and pattern ID. Suffix/palindrome automata accept byte characters; palindrome-tree nodes 0 and 1 are sentinel roots.
- Suffix-array `lcp[i]` compares `sa[i-1]` and `sa[i]`; `lcp[0]=0`. Manacher's odd radius includes the center; the even radius is centered between `i-1` and `i`.
- Exact DP optimizations require their documented monotonicity/convexity conditions. Aliens DP needs an exact penalized oracle that breaks ties toward larger counts. Randomized band DP can miss the optimum. Integer FWHT inverse XOR requires exact divisibility.
- Geometry uses `long double` and absolute tolerance `EPS`; scale coordinates/tolerance for the task. Convex polygon routines require strict CCW hulls. Half-plane intersection explicitly clips to a chosen bounding square and returns empty for zero-area intersections. Planar dual requires a connected, noncrossing straight-line embedding.
- Arithmetic must fit the declared types, including intermediate products, costs, offsets, and accumulated results. Routines using `1LL<<60` sentinels require finite values strictly inside that range. The floor sum must fit signed 128 bits. Floating-point linear algebra uses caller-adjustable tolerance.
- Recursive graph searches, blossom helpers, and game Grundy evaluation need adequate stack space on deep inputs. Grundy evaluation requires a DAG. Miller–Rabin is deterministic for nonnegative signed 64-bit inputs; factorization and enclosing circles take a caller-owned RNG. Rolling-hash equality is probabilistic; comparisons require the same base.

## Validation

From the repository root:

```sh
python3 tests/check_notebook_cpp.py --standalone
# Optional memory/undefined-behavior checks:
python3 tests/check_notebook_cpp.py --sanitizers
latexmk -pdf -interaction=nonstopmode -halt-on-error main.tex
```

`tests/notebook_cpp.cpp` includes every replacement together and compares algorithms against independent small exhaustive/direct implementations. It also checks graph certificates, ordered HLD paths, multigraphs, empty inputs, and numeric boundaries. These checks establish the tested input ranges; they are not large-instance performance benchmarks.

Additional interfaces: segment-tree folds preserve order and expose predicate boundary search; sparse/persistent trees provide point-add/range-sum; parallel binary search receives reset/apply/test callbacks; k-d trees return original point IDs and squared distances; the link-cut tree provides guarded link/cut, connectivity, rooted LCA, and vertex path sums. NTT and recurrence routines use modulus 998244353; FFT convolution relies on double-precision rounding. Interval assignment costs depend on the number of overwritten intervals. Big-integer printing accepts an output stream.

In environments traced with `ptrace`, LeakSanitizer is unsupported; run the sanitizer command with `ASAN_OPTIONS=detect_leaks=0` to retain AddressSanitizer and UBSan checks.

Current validation: 94/94 independent builds; the combined suite passes 1,058,532 assertions under AddressSanitizer and UBSan with leak detection disabled as described above. The Vietnamese notebook with its original transformations and selected additions has 25 pages.

## Compact print layout

`python3 tests/compact_notebook.py` packs short statements and complete helper blocks while verifying that C++ tokens remain identical. `NOTEBOOK_BEGIN` / `NOTEBOOK_END` comments delimit the printable body; `compactcpp` listings omit repeated includes, `using namespace std`, and section namespace wrappers. The full files still compile independently. The PDF retains its original font size and all 94 listings, reduced from 31 to 24 pages.

## Readable spacing

After compaction, run `python3 tests/space_notebook.py` to expand operator, comma, and control-flow spacing on lines with spare room. The formatter uses a 72-character display budget, preserves literals and C++ tokens, and keeps source line counts unchanged. Long lines remain compact to avoid extra wrapping; the notebook remains 24 pages at the original font size.

The Vietnamese edition translates explanatory prose and document labels while retaining familiar English algorithm names, technical terms, and the C++ listings. Translation alone produced 25 pages; `Transformations.tex` retains all 34 original entries and 20 selected additions; the current PDF has 25 pages at the same font size.
