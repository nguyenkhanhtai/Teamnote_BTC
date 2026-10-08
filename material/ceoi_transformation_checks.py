from random import Random
from collections import deque
from math import log2
r=Random(7)
count=0;worst=0
for n in range(2,41):
 for _ in range(100):
  edges={(r.randrange(v),v) for v in range(1,n)}
  edges|={tuple(sorted(r.sample(range(n),2))) for _ in range(n)}
  edges=sorted(edges);g=[[] for _ in range(n)]
  for u,v in edges:g[u].append(v);g[v].append(u)
  root=r.randrange(n);d=[-1]*n;d[root]=0;q=deque([root])
  while q:
   u=q.popleft()
   for v in g[u]:
    if d[v]<0:d[v]=d[u]+1;q.append(v)
  mass=[1]*n;out=[[] for _ in range(n)]
  for u,v in sorted(edges,key=lambda e:(max(d[e[0]],d[e[1]]),n*e[0]+e[1]),reverse=True):
   if d[u]<d[v] or (d[u]==d[v] and mass[u]>mass[v]):a,b=v,u
   else:a,b=u,v
   out[a].append(b);mass[b]+=mass[a];mass[a]=0
  for s in range(n):
   u=s;steps=0
   while u!=root:
    assert out[u]
    u=max(out[u],key=lambda v:n*min(u,v)+max(u,v));steps+=1
    assert steps<=n
   extra=steps-d[s];assert extra<=int(log2(n))+1,(n,extra)
   worst=max(worst,extra);count+=1
print('Theseus:',count,'start states passed; maximum detour',worst)
from itertools import product, permutations, combinations
# Equalmex: enumerate all partitions, compare number of feasible k and max k.
def mex(a):
 s=set(a);x=1
 while x in s:x+=1
 return x
count=0
for n in range(1,7):
 for a in product(range(1,4),repeat=n):
  feasible=set()
  for cuts in range(1<<(n-1)):
   chunks=[];start=0
   for i in range(n-1):
    if cuts>>i&1:chunks.append(a[start:i+1]);start=i+1
   chunks.append(a[start:]);ms=[mex(c) for c in chunks]
   if len(set(ms))==1:feasible.add(len(chunks))
  x=mex(a);seen=set();k=0
  for v in a:
   if v<x:seen.add(v)
   if len(seen)==x-1:k+=1;seen=set()
  assert feasible==set(range(1,k+1))
  count+=1
print('Equalmex:',count,'arrays, all partitions checked')
# Splits: enumerate all binary assignments to the two subsequences.
count=0
for n in range(1,6):
 for p in permutations(range(n)):
  generated={tuple([p[i] for i in range(n) if mask>>i&1]+[p[i] for i in range(n) if not(mask>>i&1)]) for mask in range(1<<n)}
  pos={x:i for i,x in enumerate(p)}
  for q in permutations(range(n)):
   desc=sum(pos[q[i]]>pos[q[i+1]] for i in range(n-1))
   assert (q in generated)==(desc<=1);count+=1
print('Splits:',count,'permutation pairs checked')
# DFS: enumerate every connected labeled graph n<=5 and group identical traces.
count=0
for n in range(1,6):
 edges=list(combinations(range(n),2));by_trace={}
 for mask in range(1<<len(edges)):
  g=[[] for _ in range(n)]
  for i,(u,v) in enumerate(edges):
   if mask>>i&1:g[u].append(v);g[v].append(u)
  seen=set();trace=[]
  def visit(u,depth):
   seen.add(u);trace.append((u,depth))
   for v in sorted(g[u]):
    if v not in seen:visit(v,depth+1)
  visit(0,0)
  if len(seen)==n:
   t=tuple(trace);by_trace[t]=by_trace.get(t,0)+1
 for trace,actual in by_trace.items():
  parent={};stack=[]
  for u,depth in trace:
   stack=stack[:depth]
   if stack:parent[u]=stack[-1]
   stack.append(u)
  k=0
  for x in range(n):
   child=x
   while child in parent:
    y=parent[child]
    if child!=x and x>child:k+=1
    child=y
  assert actual==1<<k,(trace,actual,k);count+=1
print('DFS:',count,'traces, all connected graphs n<=5 checked')
