"""Small independent checks of surveyed transformations; not full AC solutions."""
from collections import defaultdict, deque
from itertools import combinations
from math import ceil, sqrt
import random

rng = random.Random(20261007)


def backup_greedy(weights, k):
    weights = list(weights)
    answer = 0
    for _ in range(k):
        i = min(range(len(weights)), key=weights.__getitem__)
        answer += weights[i]
        if 0 < i < len(weights) - 1:
            weights[i - 1:i + 2] = [weights[i - 1] + weights[i + 1] - weights[i]]
        elif i == 0:
            del weights[:2]
        else:
            del weights[-2:]
    return answer


def check_backup():
    checked = 0
    for n in range(2, 12):
        for _ in range(80):
            weights = [rng.randrange(1, 30) for _ in range(n - 1)]
            for k in range(1, n // 2 + 1):
                want = min(sum(weights[i] for i in choice)
                           for choice in combinations(range(n - 1), k)
                           if all(b - a > 1 for a, b in zip(choice, choice[1:])))
                assert backup_greedy(weights, k) == want, (weights, k)
                checked += 1
    return checked


def palindromes(s):
    return {(l, r) for l in range(len(s)) for r in range(l, len(s))
            if s[l:r + 1] == s[l:r + 1][::-1]}


def check_first_mismatch():
    checked = 0
    for n in range(1, 13):
        for _ in range(35):
            s = ''.join(rng.choice('ABC') for _ in range(n))
            gains = defaultdict(int)
            for center in range(2 * n - 1):
                l, r = center // 2, (center + 1) // 2
                while l >= 0 and r < n and s[l] == s[r]:
                    l -= 1
                    r += 1
                if l < 0 or r == n:
                    continue
                for pos, color in ((l, s[r]), (r, s[l])):
                    a, b = l, r
                    while a >= 0 and b < n:
                        ca = color if a == pos else s[a]
                        cb = color if b == pos else s[b]
                        if ca != cb:
                            break
                        gains[pos, color] += 1
                        a -= 1
                        b += 1
            before = palindromes(s)
            for pos in range(n):
                for color in 'ABC':
                    if color == s[pos]:
                        continue
                    changed = s[:pos] + color + s[pos + 1:]
                    assert gains[pos, color] == len(palindromes(changed) - before)
                    checked += 1
    return checked


def rainbow_formula(river, box):
    ar, ac, br, bc = box
    vertices, horizontal, vertical = set(), set(), set()
    for r, c in river:
        vertices.update(((r, c), (r + 1, c), (r, c + 1), (r + 1, c + 1)))
        horizontal.update(((r, c), (r + 1, c)))
        vertical.update(((r, c), (r, c + 1)))
    V = sum(ar < r <= br and ac < c <= bc for r, c in vertices)
    V += 4 + 2 * (br - ar + bc - ac)
    E = sum(ar < r <= br and ac <= c <= bc for r, c in horizontal)
    E += sum(ar <= r <= br and ac < c <= bc for r, c in vertical)
    E += 2 * (br - ar + 1 + bc - ac + 1)
    B = sum(ar <= r <= br and ac <= c <= bc for r, c in river)
    C = 2 if all(ar < r < br and ac < c < bc for r, c in river) else 1
    return C - V + E - B


def check_rainbow():
    checked = 0
    for _ in range(200):
        r, c = rng.randrange(6), rng.randrange(6)
        river = {(r, c)}
        for _ in range(rng.randrange(1, 45)):
            neighbors = [(r + dr, c + dc) for dr, dc in
                         ((1, 0), (-1, 0), (0, 1), (0, -1))
                         if 0 <= r + dr < 6 and 0 <= c + dc < 6]
            r, c = rng.choice(neighbors)
            river.add((r, c))
        for _ in range(15):
            ar, br = sorted((rng.randrange(6), rng.randrange(6)))
            ac, bc = sorted((rng.randrange(6), rng.randrange(6)))
            land = {(r, c) for r in range(ar, br + 1)
                    for c in range(ac, bc + 1)} - river
            components = 0
            while land:
                components += 1
                queue = deque([land.pop()])
                while queue:
                    r, c = queue.popleft()
                    for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                        p = r + dr, c + dc
                        if p in land:
                            land.remove(p)
                            queue.append(p)
            assert rainbow_formula(river, (ar, ac, br, bc)) == components
            checked += 1
    return checked


def check_burza_bound():
    checked = 0
    for n in range(1, 15):
        for _ in range(60):
            parent = [-1] + [rng.randrange(v) for v in range(1, n)]
            depth = [0] * n
            for v in range(1, n):
                depth[v] = depth[parent[v]] + 1
            k = ceil(sqrt(n))
            leaves = [v for v in range(n) if depth[v] == k]
            reachable = {0}
            for d in range(1, k + 1):
                covers = []
                for v in range(n):
                    if depth[v] != d:
                        continue
                    mask = 0
                    for i, leaf in enumerate(leaves):
                        a = leaf
                        while depth[a] > d:
                            a = parent[a]
                        if a == v:
                            mask |= 1 << i
                    covers.append(mask)
                reachable |= {mask | cover for mask in reachable for cover in covers}
            assert (1 << len(leaves)) - 1 in reachable
            checked += 1
    return checked


if __name__ == '__main__':
    for name, check in [('Backup contraction', check_backup),
                        ('Palinilap first mismatch', check_first_mismatch),
                        ('Rainbow Euler counting', check_rainbow),
                        ('Burza sufficient bound', check_burza_bound)]:
        print(f'{name}: {check()} checks passed')
