#!/usr/bin/env python3
"""Build variants, compare against brute force, then time identical stress inputs."""
import argparse
import hashlib
import json
import random
import statistics
import subprocess
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parent
VARIANTS = {
    "simple": ("simple.cpp", ["-Wno-error=return-type", "-Wno-error=unused-result"]),
    "original_fastio": ("original.cpp", ["-DUSE_FAST_IO"]),
    "original": ("original.cpp", []),
    "fixed_fastio": ("solver.cpp", ["-DBASELINE_LAYOUT", "-DFIXED_STRIDE"]),
    "packed": ("solver.cpp", ["-DBASELINE_LAYOUT"]),
    "transposed": ("solver.cpp", ["-DSTREAMING"]),
    "transposed_pragma": ("solver.cpp", ["-DSTREAMING", "-DUSE_PRAGMA"]),
    "batched": ("solver.cpp", ["-DBATCHED"]),
    "batched_pragma": ("solver.cpp", ["-DBATCHED", "-DUSE_PRAGMA"]),
}


def run(binary, data):
    return subprocess.run([str(binary)], input=data, capture_output=True,
                          cwd=binary.parent, check=True).stdout


def check(binaries):
    generator = random.Random(20261022)
    for case in range(180):
        dimensions = [generator.randint(1, 6) for _ in range(3)]
        updates = []
        cells = {}
        for _ in range(generator.randint(1, 25)):
            lower = [generator.randint(1, size) for size in dimensions]
            upper = [generator.randint(low, size) for low, size in zip(lower, dimensions)]
            coefficients = [generator.choice([0, -1000000, 1000000, generator.randint(-9, 9)])
                            for _ in range(4)]
            updates.append(lower + upper + coefficients)
            initial, slope_x, slope_y, slope_z = coefficients
            for x in range(lower[0], upper[0] + 1):
                for y in range(lower[1], upper[1] + 1):
                    for z in range(lower[2], upper[2] + 1):
                        cell = x, y, z
                        cells[cell] = cells.get(cell, 0) + initial + slope_x * (x - lower[0]) \
                            + slope_y * (y - lower[1]) + slope_z * (z - lower[2])
        queries = [(x, y, z) for x in range(1, dimensions[0] + 1)
                   for y in range(1, dimensions[1] + 1) for z in range(1, dimensions[2] + 1)]
        queries += [queries[0], queries[-1]]
        lines = [dimensions + [len(updates), len(queries)]] + updates + queries
        data = ("\n".join(" ".join(map(str, line)) for line in lines) + "\n").encode()
        expected = ("\n".join(str(cells.get(query, 0)) for query in queries) + "\n").encode()
        for name, binary in binaries.items():
            assert run(binary, data) == expected, (case, name)
    print(f"PASS: 180 brute-force cases x {len(binaries)} variants", flush=True)


def stress(dimensions, mode, path):
    generator = random.Random(20261022)
    updates, queries = 400000, 1000000
    with path.open("w") as stream:
        stream.write(" ".join(map(str, dimensions + [updates, queries])) + "\n")
        for _ in range(updates):
            if mode == "full":
                lower, upper = [1, 1, 1], dimensions
            elif mode == "long":
                lower = [generator.randint(1, max(1, size // 4)) for size in dimensions]
                upper = [generator.randint(max(1, 3 * size // 4), size) for size in dimensions]
            else:
                lower = [generator.randint(1, size) for size in dimensions]
                upper = [generator.randint(low, size) for low, size in zip(lower, dimensions)]
            values = lower + upper + [generator.randint(-1000000, 1000000) for _ in range(4)]
            stream.write(" ".join(map(str, values)) + "\n")
        for _ in range(queries):
            stream.write(" ".join(str(generator.randint(1, size)) for size in dimensions) + "\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repeats", type=int, default=3)
    parser.add_argument("--output", type=Path, default=ROOT / "results.json")
    parser.add_argument("--variants", nargs="+", choices=list(VARIANTS), default=list(VARIANTS))
    args = parser.parse_args()
    results = {"compiler": subprocess.check_output(["g++", "--version"], text=True).splitlines()[0],
               "repeats": args.repeats, "cases": []}
    with tempfile.TemporaryDirectory(prefix="reactor-") as scratch:
        scratch = Path(scratch)
        binaries = {}
        for name, (source, flags) in VARIANTS.items():
            if name not in args.variants:
                continue
            binary = scratch / name
            subprocess.run(["g++", "-std=c++17", "-O2", "-Wall", "-Wextra", "-Werror",
                            *flags, str(ROOT / source), "-o", str(binary)], check=True)
            binaries[name] = binary
        check(binaries)
        for dimensions, mode in [([200, 200, 50], "long"), ([50, 200, 200], "long"),
                                 ([125, 125, 125], "random"), ([200, 200, 50], "full"),
                                 ([1, 200, 200], "long")]:
            path = scratch / "input.txt"
            stress(dimensions, mode, path)
            record = {"dimensions": dimensions, "mode": mode, "variants": {}}
            expected_hash = None
            for repeat in range(args.repeats):
                order = list(binaries)
                random.Random(repeat).shuffle(order)
                for name in order:
                    output = scratch / "output.txt"
                    with path.open("rb") as source, output.open("wb") as destination:
                        begin = time.perf_counter()
                        subprocess.run([str(binaries[name])], stdin=source, stdout=destination,
                                       cwd=binaries[name].parent, check=True)
                        elapsed = time.perf_counter() - begin
                    digest = hashlib.sha256(output.read_bytes()).hexdigest()
                    if expected_hash is None:
                        expected_hash = digest
                    assert digest == expected_hash, (dimensions, mode, name)
                    record["variants"].setdefault(name, []).append(round(elapsed, 4))
            results["cases"].append(record)
            print(dimensions, mode, {name: statistics.median(values)
                                    for name, values in record["variants"].items()}, flush=True)
            args.output.write_text(json.dumps(results, indent=2) + "\n")


if __name__ == "__main__":
    main()
