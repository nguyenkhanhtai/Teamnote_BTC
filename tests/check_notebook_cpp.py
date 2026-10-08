#!/usr/bin/env python3
"""Compile and exercise notebook listings; optional independent/sanitizer checks."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--standalone', action='store_true', help='compile each listing independently')
parser.add_argument('--sanitizers', action='store_true', help='enable AddressSanitizer and UBSan')
args = parser.parse_args()
with tempfile.TemporaryDirectory(prefix='notebook-cpp-') as directory:
    scratch = Path(directory)
    if args.standalone:
        files = sorted(p for p in (ROOT / 'source/cpp').glob('*/*.cpp') if p.parent.name != 'utility')
        def compile_one(source):
            wrapper = scratch / (source.parent.name + '_' + source.stem + '.cpp')
            wrapper.write_text(f'#include "{source}"\n')
            result = subprocess.run(['g++', '-std=c++17', '-Wall', '-Wextra', '-Werror',
                                     '-fsyntax-only', str(wrapper)], capture_output=True, text=True)
            return source, result
        with ThreadPoolExecutor(max_workers=4) as pool:
            results = list(pool.map(compile_one, files))
        failures = [(source, result) for source, result in results if result.returncode]
        for source, result in failures:
            print(source.relative_to(ROOT), result.stderr)
        print(f'Standalone: {len(files)-len(failures)}/{len(files)} passed', flush=True)
        if failures:
            raise SystemExit(1)
    binary = scratch / 'checks'
    # Compile the exact declarations and calls shown in the usage comments.
    subprocess.run(['g++', '-std=c++17', '-fsyntax-only',
                    str(ROOT / 'tests/notebook_usage.cpp')], check=True)
    command = ['g++', '-std=c++17', '-O1', '-Wall', '-Wextra', '-Werror']
    if args.sanitizers:
        command += ['-g1', '-fsanitize=address,undefined', '-fno-omit-frame-pointer']
    subprocess.run(command + [str(ROOT / 'tests/notebook_cpp.cpp'), '-o', str(binary)], check=True)
    subprocess.run([str(binary)], check=True)
