# ICPC Team Notebook Summary - UIT.BTC

Comprehensive documentation of algorithms, data structures, mathematics, geometry, string algorithms, dynamic programming, and competition checklists for team **UIT.BTC**.

---

## 📌 Team Information
- **Team Name**: UIT.BTC
- **Institution**: University of Information Technology, VNU-HCM
- **Members**: Vu Gia Bao, Nguyen Khanh Tai, Huynh Trung Cuong
- **Format**: Landscape A4, 3 columns LaTeX document (`main.tex`, compiled via `latexmk -pdf`).

---

## 1. Data Structure — `DataStructure.tex`

| Algorithm / Structure | Complexity | Description & Applications |
| :--- | :--- | :--- |
| **Iterative Segment Tree** | $O(\log n)$ / op, $O(n)$ build | Fast non-recursive segment tree with point update, range query, non-commutative operations, $O(\log n)$ tree walk (max\_right / min\_left), and Dual SegTree. |
| **Lazy Segment Tree (Tips)** | $O(\log n)$ / query | Implementation tips: push/pull discipline, tag composition (Affine $ax+b$, Range Set vs Add), and $O(\log n)$ Tree Walk. |

| **Sparse Segment Tree** | $O(\log n)$ / query | Dynamic segment tree with nodes allocated on demand. |
| **Cartesian Tree** | $O(n)$ build via Monotonic Stack | Min-Heap on values + BST on indices. Subtree = maximal range where $A[u]$ is min. RMQ $\iff$ LCA, Max rectangle in histogram, D&C to Tree DP. |
| **Persistent Segment Tree** | $O(\log n)$ / query | Versioned segment tree supporting point updates and historical range queries. |
| **Parallel Binary Search (PBS)** | $O(q \log (\text{range}) \log n)$ | Offline simultaneous binary search over monotonic queries after dynamic updates. |
| **Wavelet Tree** | $O(\log \Sigma)$ / query | Range $k$-th element, range frequency, and range counting in $[L, R]$. |
| **Segment Tree Beats** | $O(n \log n)$ amortized | Range chmin/chmax, historical min/max values with amortized bounds. |
| **Kd-Tree** | $O(\sqrt{n})$ / query | $k$-Nearest Neighbors and orthogonal range queries in 2D/3D. |
| **2D BIT (Fenwick)** | $O(\log^2 n)$ / query | 2D rectangular prefix sum updates and queries. |
| **Treap** | $O(\log n)$ amortized | Randomized BST supporting array splits, merges, and implicit key rotations. |
| **Splay Tree / Link-Cut Tree** | $O(\log n)$ / op | Dynamic forest connectivity (link, cut, path queries, subtree rerooting). |
| **Farach-Colton-Bender** | $O(1)$ / query | Lowest Common Ancestor (LCA) in $O(1)$ after $\pm 1$ RMQ preprocessing. |
| **Trie** | $O(\text{len})$ / query | Prefix tree for string matching and bitwise XOR maximum queries. |
| **Li Chao Tree** | $O(\log n)$ / op | Online dynamic line insertions and minimum/maximum evaluation at $x$. |
| **Line Container** | $O(\log n)$ amortized | Dynamic upper envelope of lines supporting arbitrary slopes queried at arbitrary $x$. |
| **Arpa Trick** | $O(n \alpha(n))$ | Fast offline range maximum/minimum query via DSU. |
| **Blocky Data Structure** | $O(n\sqrt{n})$ | Square root decomposition: Block Array and Hilbert-curve Mo's algorithm. |
| **Ultimate Hashmap** | $O(1)$ expected | High-performance custom hash table with `splitmix64` anti-hash randomization. |
| **Erasable Priority Queue** | $O(\log n)$ | Priority queue with lazy removal of arbitrary elements using 2 `std::priority_queue`. |
| **Expandable Data Structure** | $O(A \log n)$ | Converts static structures (Aho-Corasick, CHT) to support dynamic online insertions. |
| **Interval Set (ODT style)** | $O(\log n)$ amortized | Disjoint interval set with range assignment and adjacent merging via predicate `can_merge`. |

---

## 2. Graph — `Graph.tex`

### Network Flows & Matching
- **Min Cost Flow (Min-cost $k$-flow)** ($O(F m \log n)$): Minimum cost flow augmenting along shortest paths with potentials.
- **MinCut - MaxFlow (Dinic)** ($O(EV^2)$ / $O(E\sqrt{V})$ on unit nets): Blocking flow construction with level graphs.
- **Bipartite Matching (Hopcroft-Karp)** ($O(E\sqrt{V})$): Maximum matching, minimum vertex cover (König), maximum independent set, minimum path cover, maximum antichain (Dilworth).
- **Hungarian Algorithm** ($O(V^3)$): Minimum cost perfect matching on bipartite graphs.
- **General Matching (Edmonds Blossom \& Tutte / Rabin-Vazirani)** ($O(V^3)$): Maximum matching via Blossom or randomized Tutte Matrix Rank ($\frac{1}{2}\text{rank}(T)$). **Rabin-Vazirani Reconstruction**: Invert $T \to A$, pick edge $(u,v)$ with $A_{u,v} \ne 0$, update $A$ in $O(V^2)$ via Schur complement. **Max $b$-Matching**: Split $i \to a_i$ slots, $e=(u,v) \to L_e - R_e$ + connections to slots (aux $|V'| \le 4M$).
- **Gomory-Hu Tree** ($O(V \cdot \text{MaxFlow})$): Cut tree representing all-pairs max-flow and min-cut.

### Connectivity & Graph Structure
- **Biconnected Components (BCC)** ($O(V + E)$): Articulation points, bridges, block-cut trees.
- **Strongly Connected Components (Tarjan SCC)** ($O(V + E)$): Condensation DAG of directed graphs.
- **Functional Cycle (Floyd Tortoise & Hare)** ($O(\text{dist} + \text{len})$): Cycle detection in functional graphs $f(x)$.
- **Offline Deletion (DSU with Rollback)** ($O(q \log q \log n)$): Segment tree over time for dynamic connectivity.
- **2-SAT** ($O(n + m)$): Boolean satisfiability via SCC on implication graph.
- **Eulerian Path (Hierholzer)** ($O(m)$): Construct Eulerian trails on directed/undirected graphs.
- **Vizing's Theorem** ($O(n^2)$): Edge coloring with at most $\Delta + 1$ colors.
- **Online Bipartite Checking** ($O(\alpha(n))$): Dynamic 2-coloring maintenance via parity DSU.
- **Dominator Tree (Lengauer-Tarjan)** ($O(m \log n)$): Immediate dominator tree on directed flowgraphs.
- **Prufer Sequence** ($O(n \log n)$): Bijection between labeled trees and sequences of length $n-2$.
- **Steiner Tree** ($O(n \cdot 3^k + m \cdot 2^k \log m)$): Min-weight tree spanning $k$ terminal vertices.
- **Stable Marriage (Gale-Shapley)** ($O(n^2)$): Gale-Shapley stable matching algorithm.

---

## 3. Tree — `Tree.tex`

- **Tree Isomorphism** ($O(n \log n)$): Hash-based tree isomorphism for rooted/unrooted trees.
- **Centroid Decomposition** ($O(n \log n)$): $O(\log n)$ tree depth divide-and-conquer for path queries.
- **Heavy-Light Decomposition (HLD)** ($O(n \log^2 n)$): Decompose tree into heavy paths for path/subtree range queries.

---

## 4. String — `String.tex`

- **String Problem Solving Strategies**:
  - Problem taxonomy: Longest common prefix $\to$ Z/KMP; Multiple dictionary matching $\to$ Aho-Corasick; Distinct substrings/$k$-th substring $\to$ SAM/SA; Palindromes $\to$ Manacher/PAM; Fast $O(1)$ substring matching $\to$ Mersenne $2^{61}-1$ Hash.
  - Periodicity: Minimal period $p = n - \pi[n-1]$, Fine-Wilf periodicity lemma, logarithmic border series.
  - Theoretical bounds: Distinct palindromic substrings $\le n$, SAM has $\le 2n-1$ states and $\le 3n-4$ transitions.
- **Rolling Hash (61-bit Mersenne)**: Fast bitwise modulo $2^{61}-1$ with randomized base.
- **KMP** ($O(n)$): Prefix function $\pi$ and linear string matching.
- **Z-Algorithm** ($O(n)$): Compute $z[i] = \text{LCP}(S, S[i..n-1])$ and pattern matching via $P + \# + T$.
- **Aho-Corasick** ($O(\sum |P_i| + |T|)$): Trie with BFS failure/exit links for multi-pattern matching.
- **Suffix Array & LCP** ($O(n \log n)$ SA, $O(n)$ Kasai LCP): Doubling suffix array sorting with Kasai LCP algorithm.
  - *Arbitrary Suffix LCP*: $\text{LCP}(S[i..], S[j..]) = \min_{k=\min(pos[i], pos[j])+1}^{\max(pos[i], pos[j])} LCP[k]$ via RMQ in $O(1)$.
  - *Distinct Substrings*: $\frac{n(n+1)}{2} - \sum_{i=1}^{n-1} LCP[i]$.
  - *$k$-th Lexicographical Substring*: Suffix $SA[i]$ adds $n - SA[i] - LCP[i]$ new substrings.
  - *LCS of 2 / $K$ Strings*: Build SA on concatenated strings with unique delimiters; 2 strings $\to \max LCP[i]$ across different IDs; $K$ strings $\to$ sliding window covering all $K$ colors with range min LCP.
  - *Pattern Count & Range*: Suffixes with prefix $P$ form continuous $[L, R]$ in SA via binary search ($O(|P| \log n)$).
  - *Longest Substring Occurring $\ge K$ Times*: $\max_i(\min_{j=i+1}^{i+K-1} LCP[j])$ via sliding RMQ in $O(n)$.
- **Suffix Automaton (SAM)** ($O(n |\Sigma|)$): Minimal DAWG representing all substrings.
- **Lyndon Factorization (Duval)** ($O(n)$): Factorization into Lyndon words and minimal cyclic shift.
- **Manacher Algorithm** ($O(n)$): Palindromic radius centered at every index.
- **Palindrome Tree (EERTREE)** ($O(n)$): Explicit tree of all distinct palindromes in $S$.
- **De Bruijn Sequence** ($O(k^n)$): Cyclic sequence containing all $k$-ary words of length $n$.

---

## 5. Dynamic Programming — `DP.tex`

- **Reroot DP** ($O(n)$): Tree rerooting via 2-pass DFS with prefix/suffix transitions.
- **Divide-and-Conquer DP / Knuth Optimization** ($O(k n \log n)$ DnC / $O(n^2)$ Knuth):
  - *Quadrangle Inequality (QI / Monge)*: $\forall a \le b \le c \le d \implies C(a, c) + C(b, d) \le C(a, d) + C(b, c)$ ($\text{Cross} \le \text{Nest}$).
  - *Sufficient \& Necessary Local Test*: Checking adjacent $2 \times 2$ cells is sufficient (telescoping sum):
    $$C(i, j+1) - C(i, j) \ge C(i+1, j+1) - C(i+1, j) \quad (\forall i < j)$$
    (Equivalently, cost increase $\Delta_j(i) = C(i, j+1) - C(i, j)$ is non-increasing in $i$; or continuous 2nd derivative $\frac{\partial^2 C}{\partial x \partial y} \le 0$).
  - *Common Functions Satisfying QI*:
    - $C(l, r) = f(S_r - S_{l-1})$ for any convex $f$ ($f'' \ge 0$), e.g. $(S_r - S_{l-1})^2$, $(S_r - S_{l-1})^k$ ($k \ge 1$).
    - $C(l, r) = \sum_{k=l}^r w_k = W_r - W_{l-1}$ ($w_k \ge 0$, Knuth Optimal BST with exact equality $=$).
    - $C(l, r) = \text{inv}(l, r)$ (inversion count in subarray $[l, r]$, or any cross-pair property).
    - $C(l, r) = |x_r - x_l|^p$ ($p \ge 1$ on sorted $x$), or variance / sum of squared differences from mean.
  - *Monotonicity*: Monge property $\implies opt(i_1) \le opt(i_2)$ for $i_1 \le i_2$ (DnC: $O(k n \log n)$) and $opt[i][j-1] \le opt[i][j] \le opt[i+1][j]$ (Knuth: $O(n^2)$).
- **1D/1D DP Optimization** ($O(n \log n)$): Optimize $dp[i] = \min_{j < i} (dp[j] + cost(j, i))$ with quadrangle inequality via Deque of intervals + Binary Search.
- **Alien's Trick (WQS Binary Search)** ($O(n \log n)$): Binary search Lagrange penalty $\lambda$ to relax exact $k$-item constraint on convex objective functions.
- **Convex Hull Trick (CHT)** ($O(n \log n)$ or $O(n)$): Linear transition optimization $dp[i] = \min(a_j \cdot x_i + b_j)$.
- **Slope Trick** ($O(n \log n)$): Maintain continuous piecewise linear convex function $f(x)$ via 2 Priority Queues for $+ |x - a|$, prefix minimum, and domain shifts.
- **SOS DP (Sum Over Subsets / Fast Zeta Transform)** ($O(N \cdot 2^N)$): Subset/superset sums and bitwise AND/OR pair counting.
- **Bitmask DP State Reduction** ($O(2^N)$): In matching/permutation DP, step/count $i = \text{popcount}(mask)$ is uniquely determined by $mask$. Dimension $i$ and outer loop over bit counts can be completely omitted ($dp[i][mask] \to dp[mask]$), preserving topological order via natural loop `mask = 0..(1<<N)-1`.
- **Monotonic Queue Optimization** ($O(n)$): Sliding window minimum/maximum using monotonic deque or 2 stacks.
- **Expected Value Trick** ($O(n\sqrt{n})$): Limit DP state space to $[\frac{i \cdot k}{n} - \sqrt{n}, \frac{i \cdot k}{n} + \sqrt{n}]$ when picking $k$ items randomly.

---

## 6. Math — `Math.tex`

### Number Theory & Modular Arithmetic
- **Extended Euler Totient Power Reduction**: $a^b \equiv a^{(b \bmod \phi(m)) + \phi(m)} \pmod m$ for $b \ge \phi(m)$ ($\forall a, m$).
- **Floor Division Trick**: Traverse $O(\sqrt{n})$ distinct values of $\lfloor n/i \rfloor$ via `r = n / (n / l)`.
- **Like-Euclid `floor_sum`** ($O(\log m)$): Compute $\sum_{i=0}^{n-1} \lfloor \frac{ai+b}{m} \rfloor$ via coordinate rotation.
- **Legendre's Formula (de Polignac)**: $v_p(n!) = \sum \lfloor \frac{n}{p^k} \rfloor = \frac{n - S_p(n)}{p - 1}$.
- **Wilson's Theorem**: $(p-1)! \equiv -1 \pmod p \iff p$ prime.
- **Frobenius Coin Problem (Chicken McNugget)**: Max non-representable $ax + by$ ($x, y \ge 0$) is $ab - a - b$; total non-representable count is $\frac{(a-1)(b-1)}{2}$.
- **Primality & Factorization**: Deterministic Miller-Rabin ($n < 2^{64}$), Linear Sieve, Prime Counting (Meissel-Lehmer $O(N^{2/3})$), Pollard's Rho with Brent cycle finding ($O(\sqrt[4]{n} \log n)$).
- **Modular Inverses & Equations**: Extended GCD, Diophantine equations, Primitive Root, Discrete Log (Baby-step Giant-step), Modular Square Root (Tonelli-Shanks), Stern-Brocot Tree.

### Multiplicative Functions & Möbius Inversion
- **Dirichlet Convolution & Möbius Inversion**: $(f * g)(n) = \sum_{d \mid n} f(d) g(n/d)$, $f = g * 1 \iff g = f * \mu$.
- **GCD/LCM Summations**: $\sum_{i, j} [\gcd(i, j) = 1] = \sum \mu(d) \lfloor n/d \rfloor \lfloor m/d \rfloor$; $\sum \gcd(i, j) = \sum \phi(g) \lfloor n/g \rfloor \lfloor m/g \rfloor$.

### Combinatorics & Advanced Counting
- **Binomial Identities & Summations**:
  - *Symmetry & Pascal*: $\binom{n}{k} = \binom{n}{n-k} = \binom{n-1}{k-1} + \binom{n-1}{k}$.
  - *Absorption & Trident*: $k \binom{n}{k} = n \binom{n-1}{k-1}$, $\frac{1}{k+1}\binom{n}{k} = \frac{1}{n+1}\binom{n+1}{k+1}$, $\binom{n}{k}\binom{k}{m} = \binom{n}{m}\binom{n-m}{k-m}$.
  - *Row & Weighted Sums*: $\sum_{k=0}^n \binom{n}{k} = 2^n$, $\sum (-1)^k \binom{n}{k} = [n=0]$, $\sum_{k \text{ even}} = \sum_{k \text{ odd}} = 2^{n-1}$, $\sum k \binom{n}{k} = n 2^{n-1}$, $\sum k^2 \binom{n}{k} = n(n+1) 2^{n-2}$, $\sum \frac{\binom{n}{k}}{k+1} = \frac{2^{n+1}-1}{n+1}$.
  - *Hockey-Stick*: $\sum_{i=r}^n \binom{i}{r} = \binom{n+1}{r+1}$, $\sum_{i=0}^k \binom{n+i}{i} = \binom{n+k+1}{k}$.
  - *Vandermonde Convolution*: $\sum_{k=0}^r \binom{m}{k}\binom{n}{r-k} = \binom{m+n}{r} \implies \sum_{k=0}^n \binom{n}{k}^2 = \binom{2n}{n}$.
  - *Upper Negation*: $\binom{-n}{k} = (-1)^k \binom{n+k-1}{k}$.
  - *Binomial Inversion*: $f(n) = \sum_{k=0}^n \binom{n}{k} g(k) \iff g(n) = \sum_{k=0}^n (-1)^{n-k} \binom{n}{k} f(k)$. Upper: $f(n) = \sum_{k=n}^N \binom{k}{n} g(k) \iff g(n) = \sum_{k=n}^N (-1)^{k-n} \binom{k}{n} f(k)$.
  - *Finite Differences*: $\sum_{k=0}^n (-1)^{n-k} \binom{n}{k} k^m = n! \left\{ \begin{matrix} m \\ n \end{matrix} \right\}$ ($0$ for $m < n$, $n!$ for $m = n$).
- **Stars and Bars, Derangements** ($D_n = n D_{n-1} + (-1)^n \approx [n! / e]$).
- **Catalan Numbers** ($C_n = \frac{1}{n+1}\binom{2n}{n}$), **André's Reflection Principle**, **Balloting Theorem**.
- **Stirling Numbers (1st & 2nd Kind)**, **Principle of Inclusion-Exclusion (PIE)**, **Lucas' Theorem**.
- **Cayley's Tree Formula** ($n^{n-2}$ labeled trees), **Matrix Tree Theorem** ($\det(L_i)$), **Lindström-Gessel-Viennot (LGV) Lemma** ($\det(M)$).

### Polynomials & Transforms
- **Generating Functions (OGF/EGF)**, **Taylor Expansions**, **Simpson's Rule**.
- **Linear Recurrences (Berlekamp-Massey + Bostan-Mori / Kitamasa)** ($O(N^2 \log K)$).
- **Fast Walsh-Hadamard Transform (FWHT)** ($O(n \log n)$ for XOR, AND, OR convolutions).
- **Lagrange Interpolation** ($O(n)$ on equidistant points), **NTT & FFT** ($O(n \log n)$), **Formal Power Series (FPS) Formulas** (Inverse, Log, Exp, Sqrt, Pow, Division, Taylor Shift, MTT).

### Linear Algebra, Groups & Games
- **Gaussian Elimination** ($O(n^3)$ det, rank, linear solver), **XOR Linear Basis** ($O(B)$).
- **Burnside's Lemma & Pólya Enumeration Theorem** (Necklaces, Bracelets under symmetry).
- **Game Strategy & State Reasoning** ($O(V + E)$):
  - *Winning ($\mathcal{W}$ / N-pos) vs Losing ($\mathcal{L}$ / P-pos) State Axioms*: Terminal state rules (normal vs misère), $\exists \mathcal{L} \implies \mathcal{W}$, $\forall \mathcal{W} \implies \mathcal{L}$.
  - *Problem Solving Tactics*: Retrograde Analysis BFS on general graph with cycles/draws ($O(V + E)$), Symmetry / Mirroring strategy, Invariants & Parity arguments, Pairing / Matching strategy, Small-case brute-force & pattern discovery.
  - *Sprague-Grundy & Nim Variants*: SG-value $g(u) = \text{mex}(\{g(v)\})$ on independent subgames, Tree Hackenbush (Colon Principle), Standard Nim, Bounded Subtraction Nim, Moore's $\text{Nim}_k$, Staircase Nim, Misère Nim.
- **Probability & Expected Value**: Linearity of Expectation, Indicator Variables, Coupon Collector ($nH_n \approx n(\ln n + \gamma)$), Markov & Chebyshev inequalities.
- **Extreme Bignum**: Arbitrary precision arithmetic.

---

## 7. Geometry — `Geometry.tex`

### 2D Vectors & Primitives
- **Dot Product & Projections**: $A \cdot B = |A||B|\cos\theta$, projection $\text{proj}_B(A) = \frac{A \cdot B}{|B|^2} B$, angle $\theta = \text{atan2}(A \times B, A \cdot B)$.
- **Cross Product & Orientation**: $A \times B = x_1 y_2 - x_2 y_1$, $\text{ccw}(A, B, C)$, signed triangle area $S_{ABC} = \frac{1}{2}(B - A) \times (C - A)$.
- **Shoelace Formula**: $\text{Area}(P) = \frac{1}{2} |\sum P_i \times P_{i+1}|$ (positive $\implies$ CCW).
- **Primitive Geometry** (`primitive_geometry.txt`).

### Polygons, Convex Hulls & Sweeps
- **Convex Hull** ($O(n \log n)$): Monotone Chain / Graham Scan.
- **Rotating Calipers** ($O(n)$): Convex polygon diameter, minimum bounding rectangle.
- **Minkowski Sum** ($O(|P| + |Q|)$): Distance between convex polygons $\text{dist}(P, Q) = \text{dist}(O, P - Q)$.
- **Point in Convex Polygon** ($O(\log n)$): Binary search polar angle from $P_0$.
- **Line - Convex Hull Intersection** ($O(\log n)$): Binary search extreme vertices along normal vector.
- **Polygon Raycast** ($O(n)$): Point in general simple polygon test.
- **Half-plane Intersection** ($O(n \log n)$): Intersection of half-planes via Deque.

### Circles & Classical Geometry Theorems
- **Smallest Enclosing Circle** ($O(n)$): Welzl's randomized minimum bounding circle.
- **Circle Tangents**: Up to 4 common tangent lines between 2 circles.
- **Circle-Circle Intersection**, **Apollonius Circle** ($\frac{PA}{PB} = k$), circumradius $R = \frac{abc}{4S}$, inradius $r = \frac{S}{p}$.
- **Pick's Theorem**: $S = I + \frac{B}{2} - 1 \implies I = S - \frac{B}{2} + 1$.
- **Euler's Planar Formula**: $V - E + F = 1 + C$ ($V - E + F = 2$ for connected planar graphs).
- **Heron's Formula, Stewart's Theorem, Ptolemy's Theorem** ($AC \cdot BD = AB \cdot CD + BC \cdot AD$).
- **Brahmagupta's Formula** (cyclic quad) & **Bretschneider's Formula** (general quad).
- **Descartes' Theorem** (4 mutually tangent circles: $(\sum k_i)^2 = 2 \sum k_i^2$).
- **Circle Inversion**: $OP \cdot OP' = R^2$ (preserves angles and tangencies).
- **Triangle Centers**: Centroid $G$, Incenter $I$, Circumcenter $O$, Orthocenter $H$.

### Advanced Algorithms & 3D Geometry
- **Area of Union of Rectangles** ($O(n \log n)$): Sweep-line + Segment Tree.
- **Manhattan MST** ($O(n \log n)$): 8-octant sweep for Manhattan MST.
- **Planar Dual Graph** ($O(E \log E)$): Construct planar dual, extract all bounded/unbounded faces and dual edges via angular sorting on half-edges (`PlanarDual.cpp` / `planar_dual.txt`).
- **Delaunay Triangulation & Voronoi Diagram** ($O(n \log n)$).
- **3D Primitives**: 3D Cross Product $\vec{A} \times \vec{B}$, Tetrahedron volume $V = \frac{1}{6}|((\vec{B}-\vec{A})\times(\vec{C}-\vec{A}))\cdot(\vec{D}-\vec{A})|$, Plane equation and point-plane distance.

---

## 8. Misc & Strategy — `main.tex`

### Templates & Utilities
- `Template`: Base competitive programming setup (`template.cpp` / `templates.cpp`) with fast I/O, modular addition/subtraction, bitmask utilities, and `maximize`/`minimize`.
- `Debugging Magic`: Macro printer for competitive debugging (`debug.cpp`).
- `Expression Parsing`: Arithmetic expression evaluation AST parser.
- `Johnson Scheduling`: Johnson's rule for optimal 2-machine scheduling.
- `Matrix Multiplication Check`: Freivalds' randomized algorithm for checking $AB = C$.
- `Calendar`, `Josephus Problem`, `Bit Tricks & Bitset`, `Enum & Bitmask Flags`.

### Transformations (Approaches as Problem-Solving Transforms)
- **When Stuck**: Re-read statement! Formulate small cases ($N \le 6$) to find patterns/invariants; deduce complexity ($N \le 20 \to 2^N, 500 \to N^3, 5000 \to N^2, 2\cdot 10^5 \to N \log N$).
1. **Optimization $\to$ Decision (Binary Search)**: If predicate $P(X)$ is monotonic, binary search over $X$ to solve decision/feasibility instead of directly finding the optimum.
2. **Global Permutation $\to$ Local Swap (Greedy Exchange Argument)**: Invert global sorting: swapping $(i, j) \to (j, i)$ strictly improves the objective $\iff f(i, j) < f(j, i)$.
3. **Constraints $\to$ Graph / Network Flow / Cut**: 2-SAT, difference constraints ($x_j - x_i \le w$), Project Selection (Min-Cut), Hall's Marriage, Dilworth (DAG path cover $=$ $|V| - \text{MaxMatching}$).
4. **Algebraic / Cost Function $\to$ Geometry / Convexity**: Upper/lower envelopes, Convex Hull, Slope Trick, Minkowski sum, CHT.
5. **Global Range $\to$ Divide \& Conquer**: Split $[l, r] \to [l, m]$ and $[m+1, r]$ + cross contributions (CDQ D\&C, D\&C DP).
6. **Offline Deletions $\to$ Incremental Additions (Time Reversal)**: Invert query timeline $Q \to 1$ to turn edge deletions into DSU additions. In game theory / DP, work backward from target/terminal state.
7. **Search Space Split (Meet-in-the-Middle)**: Split $N = N/2 + N/2$, reducing $2^N \to 2^{N/2}$ via hash table / two pointers.
8. **Exact $(= k) \to$ Lagrange Penalty $(\ge k)$**: Alien's Trick (WQS Binary Search) relaxes exact $k$-item constraint on convex DP; Binomial Inversion / PIE converts exact $k$ to $\ge k$.
9. **Total Evaluation $\to$ Element Contribution (Fubini)**: Invert perspective: instead of evaluating $f(S)$ per subset/permutation, sum the contribution of each element/edge/pair $(u, v)$ over all valid states.
10. **Threshold Partitioning ($\sqrt{N}$ Heavy/Light)**: Elements $\le B$ updated statically/cached; elements $> B$ (at most $N/B$) processed dynamically (Mo's algorithm, heavy/light trees).
11. **State Compression**: In matching/permutation DP, step count $i = \text{popcount}(mask)$ is determined by $mask \implies dp[i][mask] \to dp[mask]$, preserving topological order.
12. **Exact Count $\to$ Complementary / PIE**: Count valid states via $\text{Total} - \text{Invalid}$, Stars \& Bars, PIE, or Generating Functions.
13. **Impartial Game $\to$ Nim Sum**: Transform impartial games on DAGs into XOR sum of Sprague-Grundy values ($SG(u) = \text{mex}\{SG(v)\}$).
14. **General Complex Case $\to$ Simplified Special Case**: Solve easier restrictions first ($A_i \in \{0, 1\}$, trees, small $N \le 6$) to reveal invariants before generalizing.
15. **Exhaustive Search $\to$ Branch and Bound**: Transform brute force into pruned DFS by bounding potential branch answers with admissible heuristics.
16. **Manhattan $\leftrightarrow$ Chebyshev Transform ($45^\circ$ Rotation)**: $(x, y) \mapsto (x + y, x - y) \implies |x_1 - x_2| + |y_1 - y_2| = \max(|x'_1 - x'_2|, |y'_1 - y'_2|)$. Decouples 2D distances into independent 1D axes!
17. **Max/Min \& Absolute Value Decomposition**: $\max(A, B) = \frac{A + B + |A - B|}{2}$, $\min(A, B) = \frac{A + B - |A - B|}{2}$; $|x - a| = \max(x - a, a - x)$. To minimize $\sum |x - a_i| + |y - b_i|$, split by 4 sign combinations $(\pm x \pm y)$.
18. **Threshold / Layer Counting (Fubini)**: $\sum_{i=1}^n A_i = \sum_{v=1}^{\max A} \text{count}(A_i \ge v)$ (Summing values $\longleftrightarrow$ Counting elements $\ge v$).
19. **Range Add $\to$ Difference Array / Prefix Sums**: $A_i = \sum_{j=1}^i D_j$ ($D_i = A_i - A_{i-1}$); Range add $[l, r] \to 2$ point updates on $D$. Prefix sums decouple static range sums into $S_r - S_{l-1}$.
20. **Range / All-Pairs $\to$ Adjacent Condition**: $\min_{i \ne j} |A_i - A_j| = \min_i (A_{i+1} - A_i)$ after sort; $A_j - A_i \ge (j-i)D \iff A'_{i+1} \ge A'_i$ ($A'_i = A_i - iD$); Majority ($> 50\%$) subsegment $\ge 2$ always contains length 2 ($x, x$) or 3 ($x, y, x$) witness.
21. **Product to Sum**: $ab = \binom{a + b}{2} - \binom{a}{2} - \binom{b}{2}$; $\prod A_i \to \sum \log A_i$ (or log-probabilities).
22. **Bitwise Identities**: $A + B = (A \oplus B) + 2(A \text{ AND } B) = (A \text{ OR } B) + (A \text{ AND } B)$; $A \oplus B = (A \text{ OR } B) - (A \text{ AND } B)$; Adjacent bit flips: $\sum_{i=1}^n \text{popcount}((i-1) \oplus i) = 2n - \text{popcount}(n)$.
23. **Multiset / Permutation $\to$ XOR Hashing**: Assign random 64-bit $r_v$ to value $v$. Subarray $A[l..r]$ is permutation of $1..k \iff \bigoplus_{i=l}^r r_{A[i]} == \bigoplus_{i=1}^k r_i$.
24. **Grid Path Blocking $\longleftrightarrow$ Dual Cut**: Blocking 4-dir path $(1, 1) \to (n, n)$ on grid is dual to finding an 8-dir connected barrier from left/bottom to top/right (or Min-Cut).
25. **Color Coding ($k \le 5$)**: Randomly color $N$ vertices with $k$ colors. Prob optimal $k$ items get $k$ distinct colors is $k! / k^k$. Repeat $O(k^k / k!) \approx 300$ times for error $< \epsilon$.
26. **Dirichlet / Pigeonhole (4-Sum $a_x + a_y = a_z + a_w$)**: When $N > \sqrt{2 \max A}$, 2 pairs with equal sums always exist since $\binom{N}{2} > 2\max A$. Find in $O(N^2)$ by hashing pairs.
27. **Boyer-Moore Majority Vote**: Find majority element ($> n/2$ occurrences) in $O(n)$ time and $O(1)$ space with a single counter. Sperner's antichain max size: $\binom{n}{\lfloor n/2 \rfloor}$.

### Checked (Pre-Submit Checklist)
- 📌 **Read constraints and edge cases ($N=0, 1$, negative numbers, disconnected graphs)?**
- Multiple test cases: clear/reset all global data structures properly?
- Array bounds and 0-based vs 1-based indexing?
- Integer overflow: use `long long` / `__int128`?
- Missing `return` statements in non-void functions (UB)?
- Floating point precision / epsilon comparisons (`eps = 1e-9`)?
- Fast I/O included (`cin.tie(NULL)`, `'\n'` instead of `endl`)?
