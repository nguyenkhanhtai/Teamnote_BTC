#!/usr/bin/env python3
"""Add readable C++ spacing where it fits the notebook's existing line budget."""
import re
from compact_notebook import ROOT

# Keep numeric literals (including signed exponents), strings, and comments intact.
TOKEN = re.compile(
    r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    r'|(?:0[xX][\da-fA-F]+(?:\.[\da-fA-F]*)?(?:[pP][+-]?\d+)?'
    r'|(?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?)[uUlLfF]*'
    r'|[A-Za-z_]\w*|>>=|<<=|<=>|->\*|::|->|\+\+|--|&&|\|\|'
    r'|==|!=|<=|>=|\+=|-=|\*=|/=|%=|&=|\|=|\^=|<<|>>|\.\.\.|\S'
)
ASSIGN = {'=', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>='}
RELATIONAL = {'==', '!=', '<=', '>=', '&&', '||'}
ARITHMETIC = {'+', '-', '*', '/', '%', '&', '|', '^'}
CONTROL = {'if', 'for', 'while', 'switch', 'catch'}
PREFIX = {'return', 'throw', 'case', 'else', 'delete', 'new', 'sizeof', 'alignof'}
ACCESS = {'public', 'private', 'protected'}
TYPES = {'int','long','short','char','bool','float','double','auto','void','size_t',
         'T','U','Value','Point','State','Line','Node','iterator','const_iterator'}
TEMPLATES = {'template','vector','array','pair','tuple','map','set','multiset',
             'deque','queue','priority_queue','optional','unordered_map','function',
             'less','greater','equal_to','decay_t','invoke_result_t','complex',
             'numeric_limits','static_cast','reinterpret_cast','const_cast','min','max'}
# Leave room inside the actual three-column printed width, including indentation.
DISPLAY_WIDTH = 72


def tokens(text):
    return [m.group() for m in TOKEN.finditer(text)]

def space_line(line):
    if line.lstrip().startswith(('#', '//')) or '/*' in line or '*/' in line:
        return line
    matches = list(TOKEN.finditer(line))
    if not matches:
        return line
    values = [m.group() for m in matches]
    binary = set()
    references = set()
    template_edges = set()
    angles = 0
    for i, value in enumerate(values):
        if value == '<' and i and values[i-1] in TEMPLATES:
            angles += 1
            template_edges.add(i)
        elif value in {'>','>>'} and angles:
            angles = max(0, angles-(2 if value=='>>' else 1))
            template_edges.add(i)
        elif value in {'<','>','<<','>>'} and (not i or values[i-1] != 'operator'):
            binary.add(i)
        elif value in {'&','*','&&'} and i and (values[i-1] in TYPES or i-1 in template_edges):
            references.add(i)
        elif value in ASSIGN | RELATIONAL:
            binary.add(i)
        elif value in ARITHMETIC and i:
            previous = values[i-1]
            if previous not in PREFIX and (re.fullmatch(r'[A-Za-z_]\w*|\d.*', previous) or previous in {')', ']'}):
                binary.add(i)
        elif value == '?':
            binary.add(i)
        elif value == ':' and i and values[i-1] not in ACCESS:
            binary.add(i)
    out = line[:matches[0].start()] + values[0]
    for i in range(1, len(matches)):
        previous, current = values[i-1], values[i]
        gap = line[matches[i-1].end():matches[i].start()]
        if current.startswith('//'):
            gap = ' '
        elif i in references:
            gap = ''
        elif i-1 in references:
            gap = ' ' if current not in {',',')',';'} else ''
        elif i in binary or i-1 in binary:
            gap = ' '
        elif i in template_edges:
            gap = ''
        elif i-1 in template_edges:
            if previous == '<':
                gap = ''
            elif re.fullmatch(r'[A-Za-z_]\w*', current):
                gap = ' '
        elif previous == ',':
            gap = ' '
        elif current in {',', ';'}:
            gap = ''
        elif previous == ';' and current not in {')', ';'}:
            gap = ' '
        elif previous in CONTROL and current == '(':
            gap = ' '
        elif previous == ')' and (re.fullmatch(r'[A-Za-z_]\w*', current) or current in {'++', '--'}):
            gap = ' '
        elif previous == '}' and current == 'else':
            gap = ' '
        elif previous == ':' and values[i-2] in ACCESS:
            gap = ' '
        out += gap + current
    out += line[matches[-1].end():]
    assert tokens(out) == values
    # Display omits two spaces of namespace indentation. Never add wrapped lines.
    available = DISPLAY_WIDTH + 2
    if len(out) <= available or len(out) <= len(line):
        return out
    return tighten_line(line)

def tighten_line(line):
    matches = list(TOKEN.finditer(line))
    if not matches:
        return line
    values = [m.group() for m in matches]
    out = line[:matches[0].start()] + values[0]
    punctuation = ASSIGN | RELATIONAL | ARITHMETIC | {'<','>','<<','>>','?',':'}
    for i in range(1,len(matches)):
        previous,current = values[i-1],values[i]
        gap = line[matches[i-1].end():matches[i].start()]
        if not current.startswith('//') and (previous in punctuation or current in punctuation
            or previous == ',' or previous == ')' or previous in CONTROL and current == '('):
            gap = ''
        out += gap + current
    out += line[matches[-1].end():]
    return out if tokens(out)==values else line

if __name__ == '__main__':
    changed = count = 0
    for path in (ROOT/'source/cpp').glob('*/*.cpp'):
        source=path.read_text()
        classes=re.findall(r'\b(?:class|struct)\s+(\w+)', source)
        TYPES.update(classes)
        TEMPLATES.update(classes)
        aliases=re.findall(r'\busing\s+(\w+)\s*=', source)
        TYPES.update(aliases)
        TEMPLATES.update(aliases)
    for path in sorted((ROOT/'source/cpp').glob('*/*.cpp')):
        if path.parent.name == 'utility':
            continue
        original = path.read_text()
        lines = original.splitlines()
        spaced = [space_line(tighten_line(line)) if len(line)>DISPLAY_WIDTH+2 and not line.lstrip().startswith(('#','//')) else space_line(line) for line in lines]
        replacement = '\n'.join(spaced)+'\n'
        assert tokens(original) == tokens(replacement), path
        assert len(lines) == len(spaced)
        changed += sum(a != b for a,b in zip(lines,spaced))
        count += 1
        path.write_text(replacement)
    print(f'{count} listings: spaced {changed} lines; C++ tokens and line counts unchanged')
