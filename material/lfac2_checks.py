#!/usr/bin/env python3
"""Small independent oracles for LFAC2 transformations; not 44 judge solutions.
Run: python3 material/lfac2_checks.py
Uses only the Python standard library; deterministic seed 20261007.
"""
from collections import deque
from functools import lru_cache
from itertools import combinations, product
from math import gcd
from random import Random

RNG = Random(20261007)


def report(name, count):
    print(f'{name}: {count} comparisons passed')


def check_vending():
    count = 0
    for _ in range(150):
        n = RNG.randrange(1, 5)
        stocks = tuple(RNG.randrange(1, 4) for _ in range(n))
        prices = tuple(RNG.randrange(1, 5) for _ in range(n))
        budget = RNG.randrange(0, 12)

        @lru_cache(None)
        def brute(stock, money):
            ans = 0
            for i in range(n):
                if stock[i] and prices[i] <= money:
                    nxt = list(stock)
                    value = 0
                    for j in range(i + 1):
                        if nxt[j]:
                            nxt[j] -= 1
                            value += prices[j]
                    ans = max(ans, value + brute(tuple(nxt), money - prices[i]))
            return ans

        dp = {(0, 0): 0}
        limit = max(stocks)
        for i in reversed(range(n)):
            nxt = {}
            for (t, spent), value in dp.items():
                for x in range(min(stocks[i], limit - t) + 1):
                    b = spent + x * prices[i]
                    if b <= budget:
                        key = (t + x, b)
                        val = value + prices[i] * min(stocks[i], t + x)
                        nxt[key] = max(nxt.get(key, -1), val)
            dp = nxt
        assert max(dp.values()) == brute(stocks, budget), (stocks, prices, budget)
        count += 1
    report('2012A reverse planning vs inventory search', count)


def formula_criterion(a):
    prefix = 0
    critical = 0
    critical_prefix = 0
    for i, value in enumerate(a):
        if value >= prefix:
            critical, critical_prefix = i, prefix
        prefix += value + 1
    blockers = extra = 0
    for value in a[critical + 1:]:
        if value > blockers:
            extra += value - blockers
        else:
            blockers += 1
    return a[critical] <= critical_prefix + extra


def check_formula():
    count = 0
    for n, cap in [(2, 5), (3, 4), (4, 3), (5, 2)]:
        start = (tuple(range(n)), (0,) * n)
        seen = {start}
        queue = deque([start])
        reachable_counts = set()
        while queue:
            order, used = queue.popleft()
            reachable_counts.add(used)
            for i in range(1, n):
                car = order[i]
                if used[car] == cap:
                    continue
                new_order, new_used = list(order), list(used)
                new_order[i], new_order[i - 1] = new_order[i - 1], new_order[i]
                new_used[car] += 1
                state = (tuple(new_order), tuple(new_used))
                if state not in seen:
                    seen.add(state)
                    queue.append(state)
        for a in product(range(cap + 1), repeat=n):
            assert formula_criterion(a) == (a in reachable_counts), a
            count += 1
    report('2012F critical inequality vs all bounded swap histories', count)


def check_rabbits():
    count = 0
    for n in range(3, 8):
        for k in range(1, (n + 1) // 2):
            for _ in range(12):
                a = tuple(RNG.randrange(5) for _ in range(n))
                best = 0
                for shots in product(range(n), repeat=k):
                    current = list(a)
                    for i in shots:
                        left, right = (i - 1) % n, (i + 1) % n
                        lval, rval = current[left], current[right]
                        current[i] = current[left] = current[right] = 0
                        current[(i - 2) % n] += lval
                        current[(i + 2) % n] += rval
                    best = max(best, sum(a) - sum(current))
                normal = 0
                for mask in range(1 << n):
                    if mask.bit_count() > k:
                        continue
                    x = [(mask >> i) & 1 for i in range(n)]
                    if any(x[i] and x[(i + 1) % n] for i in range(n)):
                        continue
                    normal = max(normal, sum(a[i] for i in range(n)
                                             if x[i] or (x[(i - 1) % n] and x[(i + 1) % n])))
                assert best == normal, (a, k, best, normal)
                count += 1
    report('2012K independent-shot normal form vs ordered simulations', count)


def tree_paths(adj):
    n = len(adj)
    paths = []
    for s in range(n):
        parent = [-1] * n
        parent[s] = s
        queue = deque([s])
        while queue:
            u = queue.popleft()
            for v in adj[u]:
                if parent[v] < 0:
                    parent[v] = u
                    queue.append(v)
        for t in range(s, n):
            path, u = 0, t
            while u != s:
                path |= 1 << u
                u = parent[u]
            paths.append(path | (1 << s))
    return paths


def check_cameras():
    count = 0
    for n in range(1, 8):
        # Every tree whose labels increase along root paths; many branching shapes.
        for parents in product(*(range(i) for i in range(1, n))):
            adj = [[] for _ in range(n)]
            for i, p in enumerate(parents, 1):
                adj[i].append(p)
                adj[p].append(i)
            paths = tree_paths(adj)
            for k in range(1, n + 1):
                best = max(mask.bit_count() for mask in range(1 << n)
                           if all((mask & path).bit_count() <= k for path in paths))
                alive = set(range(n))
                chosen = set()
                for _ in range(k // 2):
                    leaves = {u for u in alive if sum(v in alive for v in adj[u]) <= 1}
                    chosen.update(leaves)
                    alive -= leaves
                if k % 2 and alive:
                    chosen.add(min(alive))
                mask = sum(1 << u for u in chosen)
                assert len(chosen) == best and all((mask & p).bit_count() <= k for p in paths), (parents, k)
                count += 1
    report('2013F leaf peeling vs all subsets on increasing-parent trees n<=7', count)


def marbles_small(k):
    # k order: 1,2,3,4,6,8,9. A bounded-imbalance candidate, with 3 eliminated variables.
    for d4, d6, d8, d9 in product(*(range(-min(k[i], 6), min(k[i], 6) + 1)
                                   for i in (3, 4, 5, 6))):
        d2 = -2 * d4 - d6 - 3 * d8
        d3 = -d6 - 2 * d9
        d1 = d4 + d6 + 2 * d8 + d9
        d = (d1, d2, d3, d4, d6, d8, d9)
        if all(abs(x) <= min(c, 6) and (x - c) % 2 == 0 for x, c in zip(d, k)):
            return True
    return False


def check_marbles():
    digits = (1, 2, 3, 4, 6, 8, 9)
    count = 0
    for _ in range(250):
        k = tuple(RNG.randrange(3) for _ in digits)
        if sum(k) % 2:
            continue
        total_product = 1
        for digit, c in zip(digits, k):
            total_product *= digit ** c
        brute = False
        for allocation in product(*(range(c + 1) for c in k)):
            if sum(allocation) != sum(k) // 2:
                continue
            first = 1
            for digit, c in zip(digits, allocation):
                first *= digit ** c
            if first * first == total_product:
                brute = True
                break
        assert marbles_small(k) == brute, k
        count += 1
    report('2013G exponent equations vs exact integer products (not bound-6 certificate)', count)


def check_genetics():
    count = 0
    for _ in range(180):
        n = RNG.randrange(1, 11)
        a = [RNG.randrange(1, 4) for _ in range(n)]
        k = RNG.randrange(1, n + 1)
        brute = ()
        for mask in range(1 << n):
            seq = tuple(a[i] for i in range(n) if mask >> i & 1)
            if len(seq) % k or any(len(set(seq[j:j + k])) > 1 for j in range(0, len(seq), k)):
                continue
            if len(seq) > len(brute) or (len(seq) == len(brute) and seq < brute):
                brute = seq
        ends = [n] * n
        for i in range(n):
            occ = [j for j in range(i, n) if a[j] == a[i]]
            if len(occ) >= k:
                ends[i] = occ[k - 1]
        dp = [0] * (n + 1)
        for i in reversed(range(n)):
            dp[i] = max(dp[i + 1], 1 + dp[ends[i] + 1] if ends[i] < n else 0)
        s, blocks, result = 0, dp[0], []
        while blocks:
            value, i = min((a[i], i) for i in range(s, n)
                           if ends[i] < n and 1 + dp[ends[i] + 1] == blocks)
            result.extend([value] * k)
            s, blocks = ends[i] + 1, blocks - 1
        assert tuple(result) == brute, (a, k, result, brute)
        count += 1
    report('2013I certified lexicographic reconstruction vs all subsequences', count)


def check_prices():
    count = 0
    for _ in range(150):
        n, m = RNG.randrange(1, 5), RNG.randrange(1, 6)
        opening = [RNG.randrange(8) for _ in range(n)]
        prices = [[RNG.randrange(1, 8) for _ in range(m)] for _ in range(n)]
        brute = min(sum(prices[shop][j] for j, shop in enumerate(assignment))
                    + sum(opening[i] for i in set(assignment))
                    for assignment in product(range(n), repeat=m))
        old = [0] + [10**9] * ((1 << m) - 1)
        for i in range(n):
            opened = [v + opening[i] for v in old]
            for mask in range(1 << m):
                for j in range(m):
                    if mask >> j & 1:
                        opened[mask] = min(opened[mask], opened[mask ^ (1 << j)] + prices[i][j])
            old = [min(x, y) for x, y in zip(old, opened)]
        assert old[-1] == brute
        count += 1
    report('2014C open-shop DP vs all product-to-shop assignments', count)


def nim_case(n, first_step, second_step):
    d = gcd(first_step, second_step)
    if n % d:
        return 0  # draw
    n, first_step, second_step = n // d, first_step // d, second_step // d
    if first_step == second_step:
        return 1
    p, q = sorted((first_step, second_step))
    small_first = first_step == p
    if small_first:
        small_wins = n >= p or n % (q - p) != 0
    elif n < q:
        small_wins = True
    else:
        r = n % q
        small_wins = not (r < p and r % (q - p) == 0)
    return 1 if small_wins == small_first else -1


def check_nim():
    count = 0
    for p, q in product(range(1, 9), repeat=2):
        # For initial n<=30, forced add stays <=max(30,2*max(p,q)); removals decrease.
        bound = max(30, 2 * max(p, q))
        states = [(turn, n) for turn in range(2) for n in range(1, bound + 1)]
        successors = {}
        for turn, n in states:
            step = (p, q)[turn]
            moves = [n + step] if n < step else list(range(n - step, -1, -step))
            successors[turn, n] = [(1 - turn, x) for x in moves]
        outcome = {}  # winner relative to player to move: 1 win, -1 loss, absent draw
        changed = True
        while changed:
            changed = False
            for s in states:
                if s in outcome:
                    continue
                nxt = successors[s]
                if any(x == 0 or outcome.get((t, x)) == -1 for t, x in nxt):
                    outcome[s] = 1
                    changed = True
                elif all(outcome.get(v) == 1 for v in nxt):
                    outcome[s] = -1
                    changed = True
        for n in range(1, 31):
            assert nim_case(n, p, q) == outcome.get((0, n), 0), (n, p, q)
            count += 1
    report('2014E arithmetic cases vs retrograde finite game including draws', count)


def warming_candidate(a):
    n, best = len(a), (0, 0)
    for i, value in enumerate(a):
        l = max((j for j in range(i) if a[j] <= value), default=-1)
        r = min((j for j in range(i + 1, n) if a[j] <= value), default=n)
        if r == l + 2:
            candidates = [(i, i + 1)]
        else:
            maximum = max(a[l + 1:r])
            left = [j for j in range(l + 1, i) if a[j] == maximum]
            right = [j for j in range(i + 1, r) if a[j] == maximum]
            l2, l3 = (left[-1] if left else l), (left[-2] if len(left) > 1 else l)
            r2, r3 = (right[0] if right else r), (right[1] if len(right) > 1 else r)
            candidates = ([(l3 + 1, r2)] if left else []) + ([(l2 + 1, r3)] if right else [])
        for start, end in candidates:
            best = max(best, (end - start, -start))
    return best


def check_warming():
    count = 0
    for n in range(1, 9):
        for a in product(range(3), repeat=n):
            brute = max((r - l, -l) for l in range(n) for r in range(l + 1, n + 1)
                        if a[l:r].count(min(a[l:r])) == a[l:r].count(max(a[l:r])) == 1)
            assert warming_candidate(a) == brute, a
            count += 1
    report('2014G two candidates per minimum vs every subarray (alphabet 3, n<=8)', count)


def check_staging():
    count = 0
    for n in range(1, 7):
        for _ in range(120):
            target = list(range(n))
            RNG.shuffle(target)
            times = list(range(n))
            RNG.shuffle(times)
            alive = [True] * n
            for i in sorted(range(n), key=times.__getitem__):
                if alive[i]:
                    alive[target[i]] = False
            seen, survivors = set(), 0
            for start in range(n):
                if start in seen:
                    continue
                cycle, u = [], start
                while u not in seen:
                    seen.add(u)
                    cycle.append(u)
                    u = target[u]
                cuts = [i for i in range(len(cycle)) if times[cycle[i - 1]] >= times[cycle[i]]]
                lengths = [(cuts[(j + 1) % len(cuts)] - cut) % len(cycle) or len(cycle)
                           for j, cut in enumerate(cuts)]
                survivors += sum(x // 2 for x in lengths)
            assert survivors == sum(alive), (target, times)
            count += 1
    report('2014I cyclic increasing-run formula vs chronological event simulation', count)


def distances(adj, source):
    d = [10**9] * len(adj)
    d[source] = 0
    queue = deque([source])
    while queue:
        u = queue.popleft()
        for v in adj[u]:
            if d[v] == 10**9:
                d[v] = d[u] + 1
                queue.append(v)
    return d


def check_cave():
    count = 0
    for _ in range(300):
        n = RNG.randrange(1, 13)
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            p = RNG.randrange(i)
            adj[i].append(p)
            adj[p].append(i)
        all_dist = [distances(adj, s) for s in range(n)]
        regions = []
        for _ in range(RNG.randrange(1, 9)):
            a, b = RNG.randrange(n), RNG.randrange(n)
            limit = all_dist[a][b] + RNG.randrange(7)
            regions.append((a, b, limit))
        valid = [x for x in range(n) if all(all_dist[a][x] + all_dist[b][x] <= d for a, b, d in regions)]
        depths = all_dist[0]
        a, b, d = max(regions, key=lambda z: max(0, (depths[z[0]] + depths[z[1]] - z[2] + 1) // 2))
        area = [x for x in range(n) if all_dist[a][x] + all_dist[b][x] <= d]
        p = min(area, key=depths.__getitem__)
        assert bool(valid) == (p in valid), (regions, p, valid)
        count += 1
    report('2014J deepest projection witness vs explicit intersection', count)


def check_captain():
    count = 0
    for _ in range(220):
        n = RNG.randrange(2, 12)
        pts = [(RNG.randrange(15), RNG.randrange(15)) for _ in range(n)]
        dense = [[min(abs(x - xx), abs(y - yy)) for xx, yy in pts] for x, y in pts]
        sparse = [[0 if i == j else 10**9 for j in range(n)] for i in range(n)]
        for axis in range(2):
            order = sorted(range(n), key=lambda i: pts[i][axis])
            for i, j in zip(order, order[1:]):
                sparse[i][j] = sparse[j][i] = dense[i][j]
        for matrix in (dense, sparse):
            for k in range(n):
                for i in range(n):
                    for j in range(n):
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j])
        assert dense == sparse, pts
        count += 1
    report('2014K sorted-neighbor graph vs complete all-pairs distances', count)


def pillar_template(h, w):
    cells = [(r, c) for r in range(h) for c in range(w)
             if not (h // 2 - 1 <= r <= h // 2 and w // 2 - 1 <= c <= w // 2)]
    index = {v: i for i, v in enumerate(cells)}
    adj = [[index[v] for v in cells if abs(v[0] - r) + abs(v[1] - c) == 1] for r, c in cells]
    required = set()
    for r in (0, h - 1):
        for c in range(0, w, 2):
            required.add(frozenset((index[r, c], index[r, c + 1])))
    for c in (0, w - 1):
        for r in range(0, h, 2):
            required.add(frozenset((index[r, c], index[r + 1, c])))
    mandatory = [{next(iter(e - {i})) for e in required if i in e} for i in range(len(cells))]
    path, used = [0], {0}

    def search():
        u = path[-1]
        if len(path) == len(cells):
            edges = {frozenset((a, b)) for a, b in zip(path, path[1:] + path[:1])}
            return 0 in adj[u] and required <= edges
        options = [v for v in adj[u] if v not in used]
        if len(path) > 1:
            missing = mandatory[u] - {path[-2]}
            if len(missing) > 1:
                return False
            if missing:
                options = [v for v in options if v in missing]
        for v in sorted(options, key=lambda v: sum(x not in used for x in adj[v])):
            if any(x in used and x != u and x != 0 for x in mandatory[v]):
                continue
            path.append(v)
            used.add(v)
            if search():
                return True
            used.remove(v)
            path.pop()
        return False

    assert search(), (h, w)
    cycle = [cells[i] for i in path]
    assert len(set(cycle)) == h * w - 4
    assert all(abs(a[0] - b[0]) + abs(a[1] - b[1]) == 1
               for a, b in zip(cycle, cycle[1:] + cycle[:1]))
    return cycle


def check_pillars():
    for h, w in ((4, 4), (4, 6), (6, 4)):
        cycle = pillar_template(h, w)
        print(f'2014F {h}x{w} template: {cycle} (boundary-pair edges verified)')


def check_expression():
    count = 0
    for p in (2, 3, 5, 7, 11):
        g = next(g for g in range(1, p) if len({pow(g, e, p) for e in range(p - 1)}) == p - 1)
        logs = {pow(g, e, p): e for e in range(p - 1)}
        for _ in range(30):
            a, b = ([RNG.randrange(8) for _ in range(p)] for _ in range(2))
            direct = [0] * p
            transformed = [0] * p
            for x in range(p):
                for y in range(p):
                    direct[x * y % p] += a[x] * b[y]
            transformed[0] = a[0] * sum(b) + b[0] * sum(a) - a[0] * b[0]
            for x in range(1, p):
                for y in range(1, p):
                    transformed[pow(g, (logs[x] + logs[y]) % (p - 1), p)] += a[x] * b[y]
            assert direct == transformed
            # Independent enumeration of all assignments in the book's sample.
            count += 1
    assert sum(((a + y) * (z + 8)) ** 2 % 3 == 0 for a, y, z in product(range(3), repeat=3)) == 15
    report('2012E primitive-root histogram transform vs direct multiplication', count)


def check_demonstrations():
    count = 0
    for _ in range(160):
        n = RNG.randrange(2, 9)
        intervals = [tuple(sorted(RNG.sample(range(12), 2))) for _ in range(n)]
        u, pairs, initial = [0] * n, {}, 0
        for x in range(11):
            active = tuple(i for i, (l, r) in enumerate(intervals) if l <= x < r)
            initial += bool(active)
            if len(active) == 1:
                u[active[0]] += 1
            elif len(active) == 2:
                pairs[active] = pairs.get(active, 0) + 1
        gain = max(sum(sorted(u)[-2:]), max((u[i] + u[j] + w for (i, j), w in pairs.items()), default=0))
        brute = min(sum(any(l <= x < r for i, (l, r) in enumerate(intervals) if i not in removed)
                        for x in range(11)) for removed in combinations(range(n), 2))
        assert initial - gain == brute
        count += 1
    report('2013D sparse pair contributions vs deleting every pair', count)


def check_petrol():
    count = 0
    for _ in range(150):
        n = RNG.randrange(2, 10)
        matrix = [[0 if i == j else 10**9 for j in range(n)] for i in range(n)]
        edges = []
        for i in range(n):
            for j in range(i):
                if RNG.randrange(3) == 0 or j == i - 1:
                    w = RNG.randrange(1, 10)
                    edges.append((i, j, w))
                    matrix[i][j] = matrix[j][i] = w
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j])
        stations = sorted(RNG.sample(range(n), RNG.randrange(2, n + 1)))
        nearest = [min(matrix[v][s] for s in stations) for v in range(n)]
        for b in range(1, 20):
            def components(weighted_edges):
                sets = [{i} for i in range(n)]
                for i, j, w in weighted_edges:
                    if w <= b:
                        merged = sets[i] | sets[j]
                        for v in merged:
                            sets[v] = merged
                return sets
            dense = components((i, j, matrix[i][j]) for i in stations for j in stations)
            changed = components((i, j, nearest[i] + w + nearest[j]) for i, j, w in edges)
            assert all((j in dense[i]) == (j in changed[i]) for i in stations for j in stations)
        count += 1
    report('2014B road reweighting vs complete station-distance connectivity', count)


def check_hit():
    count = 0
    alphabet = 'RGB'

    def covers(stamp, text):
        length = len(stamp)
        starts = [i for i in range(len(text) - length + 1)
                  if all(t == '*' or s == t for s, t in zip(stamp, text[i:i + length]))]
        # Independent union-of-covered-cells check, rather than a gap predicate.
        covered = set()
        for i in starts:
            covered.update(range(i, i + length))
        return len(covered) == len(text)

    for _ in range(140):
        n = RNG.randrange(1, 8)
        text = ''.join(RNG.choice(alphabet + '*') for _ in range(n))
        brute = next(length for length in range(1, n + 1)
                     if any(covers(''.join(s), text) for s in product(alphabet, repeat=length)))
        oriented = text
        half = n // 2
        if text[:half].count('*') > text[n - half:].count('*'):
            oriented = text[::-1]
        short = n + 1
        for length in range(1, half + 1):
            prefix = oriented[:length]
            for filling in product(alphabet, repeat=prefix.count('*')):
                chars = iter(filling)
                stamp = ''.join(next(chars) if c == '*' else c for c in prefix)
                if covers(stamp, oriented):
                    short = min(short, length)
        long = next(length for length in range((n + 1) // 2, n + 1)
                    if all(a == '*' or b == '*' or a == b
                           for a, b in zip(text[:length], text[n - length:])))
        assert min(short, long) == brute, (text, brute, short, long)
        count += 1
    report('2014H short/long symmetry split vs every RGB stamp on n<=7', count)


if __name__ == '__main__':
    for check in (check_vending, check_formula, check_rabbits, check_cameras,
                  check_marbles, check_genetics, check_prices, check_nim,
                  check_warming, check_staging, check_cave, check_captain, check_pillars, check_expression,
                  check_demonstrations, check_petrol, check_hit):
        check()
