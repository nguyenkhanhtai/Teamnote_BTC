from itertools import permutations, product
from random import Random
rng=Random(20261007); counts={}
# Art: exhaustive true orders, all cyclic queries.
c=0
for n in range(1,8):
 for true in permutations(range(n)):
  rank={x:i for i,x in enumerate(true)}
  orders=[list(range(i,n))+list(range(i)) for i in range(n)]
  f=[sum(rank[a]>rank[b] for j,a in enumerate(o) for b in o[j+1:]) for o in orders]
  assert all((n-1+f[i]-f[(i+1)%n])//2==rank[i] for i in range(n))
  c+=1
counts['Art permutations']=c
# Jedinstven: random legal constraints, no full solver reused.
c=0
for n in range(1,31):
 for _ in range(100):
  edges=[(rng.randrange(n),0) for _ in range(n-1)]
  edges=[(l,rng.randrange(l+1,n+1)) for l,_ in edges]
  adj=[[] for _ in range(n+1)]
  for l,r in edges:adj[l].append(r);adj[r].append(l)
  seen={0};stack=[0]
  while stack:
   for v in adj[stack.pop()]:
    if v not in seen:seen.add(v);stack.append(v)
  seed=next(v for v in range(n+1) if v not in seen);component={seed};stack=[seed]
  while stack:
   for v in adj[stack.pop()]:
    if v not in component:component.add(v);stack.append(v)
  p=[int(i in component) for i in range(n+1)];d=[p[i+1]-p[i] for i in range(n)]
  a=[max(x,0) for x in d];b=[max(-x,0) for x in d]
  assert a!=b and all(sum(a[l:r])==sum(b[l:r]) for l,r in edges)
  c+=1
counts['Jedinstven instances']=c
# Homework: random expression trees; brute all leaf assignments, compare certificates.
def tree(n):
 if n==1:return None
 l=rng.randrange(1,n);return (rng.randrange(2),tree(l),tree(n-l)) # 0=min,1=max

def cert(t):
 if t is None:return (1,1)
 op,l,r=t;a,b=cert(l);c,d=cert(r)
 return (a+c,min(b,d)) if op==0 else (min(a,c),b+d) # c1,c0

def evaluate(t,it):
 if t is None:return next(it)
 op,l,r=t;a=evaluate(l,it);b=evaluate(r,it)
 return max(a,b) if op else min(a,b)
c=0
for n in range(1,8):
 for _ in range(25):
  t=tree(n);c1,c0=cert(t);values={evaluate(t,iter(p)) for p in permutations(range(1,n+1))}
  assert values==set(range(c0,n-c1+2)),(t,values,c0,c1)
  c+=1
counts['Homework trees']=c
# Sequence: all small ternary arrays; fixed occurrence block and all legal extensions.
c=0
for n in range(1,8):
 for arr in product(range(3),repeat=n):
  for x in set(arr):
   occ=[i for i,z in enumerate(arr) if z==x]
   for i in range(len(occ)):
    for j in range(i,len(occ)):
     left=occ[i-1]+1 if i else 0; right=occ[j+1]-1 if j+1<len(occ) else n-1
     ds=[];exists=False;num=j-i+1
     for l in range(left,occ[i]+1):
      for r in range(occ[j],right+1):
       vals=sorted(arr[l:r+1]);m=len(vals)
       exists |= x in (vals[(m-1)//2],vals[m//2])
       ds.append(sum((z>x)-(z<x) for z in arr[l:r+1]))
     assert exists==(min(ds)<=num and max(ds)>=-num)
     assert set(ds)==set(range(min(ds),max(ds)+1))
     c+=1
counts['Sequence occurrence blocks']=c
print(counts)
