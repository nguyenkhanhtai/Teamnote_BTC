#!/usr/bin/env python3
"""Compact notebook C++ without changing tokens; mark printable implementation bodies."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
WIDTH = 88
LEX = re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|\d+(?:\.\d+)?|\S')

def signature(text):
    return [t for t in LEX.findall(text) if not t.startswith(('//', '/*'))]

def masked(text):
    return re.sub(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', '', text)

def braced_controls(text):
    text = masked(text)
    for match in re.finditer(r'\b(?:if|for|while|switch)\s*\(', text):
        depth = 1
        j = match.end()
        while depth and j < len(text):
            depth += (text[j] == '(') - (text[j] == ')')
            j += 1
        if text[j:].lstrip()[:1] != '{':
            return False
    return True

def compact(lines):
    lines = [line.rstrip() for line in lines if line.strip()]
    # Collapse small complete blocks, including structs and one-line helpers.
    changed = True
    while changed:
        changed = False
        for start in range(len(lines)-1, -1, -1):
            if not lines[start].rstrip().endswith('{') or '//' in lines[start]:
                continue
            depth = 1
            for end in range(start+1, len(lines)):
                code = masked(lines[end])
                depth += code.count('{') - code.count('}')
                if depth <= 0:
                    break
            else:
                continue
            block = lines[start:end+1]
            if any('//' in line or '/*' in line for line in block):
                continue
            indent = len(lines[start]) - len(lines[start].lstrip())
            joined = ' '*indent + ' '.join(line.strip() for line in block)
            if len(joined) <= WIDTH and braced_controls(joined):
                lines[start:end+1] = [joined]
                changed = True
    # Pack adjacent ordinary statements; leave unbraced control flow on its own line.
    result = []
    for line in lines:
        if result:
            previous = result[-1]
            same_indent = len(previous)-len(previous.lstrip()) == len(line)-len(line.lstrip())
            balanced = all(masked(x).count('(') == masked(x).count(')') for x in (previous,line))
            plain = all(not re.search(r'\b(?:if|else|for|while|do|switch|case|default)\b|//|/\*', x)
                        for x in (previous,line))
            joined = previous + ' ' + line.strip()
            if same_indent and balanced and plain and previous.rstrip().endswith(';') and line.rstrip().endswith(';') and len(joined) <= WIDTH:
                result[-1] = joined
                continue
        result.append(line)
    return result

if __name__ == '__main__':
    before = after = count = 0
    for path in sorted((ROOT/'source/cpp').glob('*/*.cpp')):
        if path.parent.name == 'utility':
            continue
        original = path.read_text()
        lines = [line for line in original.splitlines() if line.strip() not in ('// NOTEBOOK_BEGIN','// NOTEBOOK_END','//NOTEBOOK_BEGIN','//NOTEBOOK_END')]
        first = next(i for i,line in enumerate(lines) if line.strip() == 'using namespace std;') + 1
        assert lines[-1].strip() == '}', path
        body = [line[2:] if line.startswith('  ') else line for line in lines[first:-1]]
        packed = compact(body)
        replacement = '\n'.join(lines[:first]+['//NOTEBOOK_BEGIN']+['  '+line for line in packed]+['//NOTEBOOK_END',lines[-1]])+'\n'
        assert signature(original) == signature(replacement), f'Token change: {path}'
        before += len(original.splitlines())
        after += len(replacement.splitlines())
        count += 1
        path.write_text(replacement)
    print(f'{count} listings: {before} -> {after} source lines; executable tokens unchanged')
