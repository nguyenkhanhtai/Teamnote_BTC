#include <bits/stdc++.h>
#include "../source/cpp/data_structure/arpa_trick.cpp"
#include "../source/cpp/data_structure/farach_colton_bender.cpp"
#include "../source/cpp/data_structure/segment_tree_beats.cpp"
#include "../source/cpp/data_structure/wavelet_tree.cpp"
#include "../source/cpp/dp/alien_dp.cpp"
#include "../source/cpp/dp/convex_hull_trick.cpp"
#include "../source/cpp/dp/dnc_dp.cpp"
#include "../source/cpp/dp/expected_value_dp.cpp"
#include "../source/cpp/dp/monotonic_queue.cpp"
#include "../source/cpp/dp/one_d_one_d_dp.cpp"
#include "../source/cpp/dp/reroot_dp.cpp"
#include "../source/cpp/dp/slope_trick.cpp"
#include "../source/cpp/dp/sos_dp.cpp"
#include "../source/cpp/geometry/area_union_rectangles.cpp"
#include "../source/cpp/geometry/circle_tangents.cpp"
#include "../source/cpp/geometry/convex_hull.cpp"
#include "../source/cpp/geometry/halfplane_intersection.cpp"
#include "../source/cpp/geometry/line_hull_intersection.cpp"
#include "../source/cpp/geometry/manhattan_mst.cpp"
#include "../source/cpp/geometry/minkowski_sum.cpp"
#include "../source/cpp/geometry/planar_dual.cpp"
#include "../source/cpp/geometry/point_in_convex.cpp"
#include "../source/cpp/geometry/polygon_raycast.cpp"
#include "../source/cpp/geometry/primitive_geometry.cpp"
#include "../source/cpp/geometry/rotating_calipers.cpp"
#include "../source/cpp/geometry/smallest_enclosing_circle.cpp"
#include "../source/cpp/graph/bcc.cpp"
#include "../source/cpp/graph/dominator_tree.cpp"
#include "../source/cpp/graph/dsu_rollback.cpp"
#include "../source/cpp/graph/euler_path.cpp"
#include "../source/cpp/graph/floyd_warshall.cpp"
#include "../source/cpp/graph/functional_cycle.cpp"
#include "../source/cpp/graph/general_matching.cpp"
#include "../source/cpp/graph/gomory_hu.cpp"
#include "../source/cpp/graph/hopcroft_karp.cpp"
#include "../source/cpp/graph/hungarian.cpp"
#include "../source/cpp/graph/max_flow_dinic.cpp"
#include "../source/cpp/graph/min_cost_flow.cpp"
#include "../source/cpp/graph/online_bipartite.cpp"
#include "../source/cpp/graph/prufer.cpp"
#include "../source/cpp/graph/scc_tarjan.cpp"
#include "../source/cpp/graph/stable_marriage.cpp"
#include "../source/cpp/graph/steiner_tree.cpp"
#include "../source/cpp/graph/two_sat.cpp"
#include "../source/cpp/graph/vizing.cpp"
#include "../source/cpp/math/diophantine.cpp"
#include "../source/cpp/math/discrete_log_bsgs.cpp"
#include "../source/cpp/math/extended_gcd.cpp"
#include "../source/cpp/math/fast_sieve.cpp"
#include "../source/cpp/math/floor_sum.cpp"
#include "../source/cpp/math/fwht.cpp"
#include "../source/cpp/math/game_strategy.cpp"
#include "../source/cpp/math/lagrange.cpp"
#include "../source/cpp/math/linalg_gauss.cpp"
#include "../source/cpp/math/pollard_rho.cpp"
#include "../source/cpp/math/prime_counter.cpp"
#include "../source/cpp/math/primitive_root.cpp"
#include "../source/cpp/math/rabin_miller.cpp"
#include "../source/cpp/math/sqrt_mod.cpp"
#include "../source/cpp/math/stern_brocot.cpp"
#include "../source/cpp/math/xor_basis.cpp"
#include "../source/cpp/string/aho_corasick.cpp"
#include "../source/cpp/string/debruijn.cpp"
#include "../source/cpp/string/kmp.cpp"
#include "../source/cpp/string/lyndon.cpp"
#include "../source/cpp/string/manacher.cpp"
#include "../source/cpp/string/palindrome_tree.cpp"
#include "../source/cpp/string/rolling_hash.cpp"
#include "../source/cpp/string/suffix_array.cpp"
#include "../source/cpp/string/suffix_automaton.cpp"
#include "../source/cpp/string/z_algorithm.cpp"
#include "../source/cpp/tree/centroid_decomposition.cpp"
#include "../source/cpp/tree/hld.cpp"
#include "../source/cpp/tree/tree_isomorphism.cpp"
#include "../source/cpp/data_structure/binary_trie.cpp"
#include "../source/cpp/data_structure/block_array_mo.cpp"
#include "../source/cpp/data_structure/erasable_priority_queue.cpp"
#include "../source/cpp/data_structure/expandable.cpp"
#include "../source/cpp/data_structure/fenwick_2d.cpp"
#include "../source/cpp/data_structure/hash_map.cpp"
#include "../source/cpp/data_structure/implicit_treap.cpp"
#include "../source/cpp/data_structure/interval_set.cpp"
#include "../source/cpp/data_structure/iterative_segment_tree.cpp"
#include "../source/cpp/data_structure/kd_tree.cpp"
#include "../source/cpp/data_structure/li_chao.cpp"
#include "../source/cpp/data_structure/line_container.cpp"
#include "../source/cpp/data_structure/link_cut_tree.cpp"
#include "../source/cpp/data_structure/parallel_binary_search.cpp"
#include "../source/cpp/data_structure/persistent_segment_tree.cpp"
#include "../source/cpp/data_structure/sparse_segment_tree.cpp"
#include "../source/cpp/math/berlekamp_massey.cpp"
#include "../source/cpp/math/big_integer.cpp"
#include "../source/cpp/math/fft.cpp"
#include "../source/cpp/math/ntt.cpp"
using namespace std;
mt19937_64 rng(712367);
long long checks=0;
void check(bool ok,int line) {
  ++checks;
  if(!ok)throw runtime_error("check failed #"+to_string(checks)+" at line "+to_string(line));
}
#define require(...) check((__VA_ARGS__),__LINE__)
int brute_matching(const vector<vector<int>>&g,int mask) {
  if(!mask)return 0;
  int u=__builtin_ctz((unsigned)mask);
  int best=brute_matching(g,mask^(1<<u));
  for(int v:g[u])if(mask>>v&1)best=max(best,1+brute_matching(g,mask^(1<<u)^(1<<v)));
  return best;
}
void test_structures() {
  using namespace notebook::data_structure;
  using namespace notebook::tree;
  for(int rep=0;rep<150;++rep) {
    int n=1+rng()%40;
    vector<long long>a(n);
    for(auto&v:a)v=(int)(rng()%101)-50;
    WaveletTree w(a);
    SegmentTreeBeats beats(a);
    for(int step=0;step<150;++step) {
      int l=rng()%n,r=l+1+rng()%(n-l);
      vector<long long>b(a.begin()+l,a.begin()+r);
      sort(b.begin(),b.end());
      if(step==0) {
        for(int k=0;k<r-l;++k)require(w.kth(l,r,k)==b[k]);
      }
      long long x=(int)(rng()%101)-50;
      switch(rng()%4) {
        case 0:beats.chmin(l,r,x);
        for(int i=l;i<r;++i)a[i]=min(a[i],x);
        break;
        case 1:beats.chmax(l,r,x);
        for(int i=l;i<r;++i)a[i]=max(a[i],x);
        break;
        case 2:beats.add(l,r,x);
        for(int i=l;i<r;++i)a[i]+=x;
        break;
        default:require(beats.sum(l,r)==accumulate(a.begin()+l,a.begin()+r,0LL));
      }
    }
    vector<vector<int>>g(n);
    for(int i=1;i<n;++i) {
      int p=rng()%i;
      g[i].push_back(p);
      g[p].push_back(i);
    }
    FCBLCA f(g);
    HeavyLight h(g);
    for(int i=0;i<n;++i)for(int j=0;j<n;++j) {
      int u=i,v=j;
      vector<int>left,right;
      while(h.depth[u]>h.depth[v])left.push_back(u),u=h.parent[u];
      while(h.depth[v]>h.depth[u])right.push_back(v),v=h.parent[v];
      while(u!=v) {
        left.push_back(u);
        right.push_back(v);
        u=h.parent[u];
        v=h.parent[v];
      }
      require(f.lca(i,j)==u&&h.lca(i,j)==u);
      left.push_back(u);
      reverse(right.begin(),right.end());
      left.insert(left.end(),right.begin(),right.end());
      vector<int>path;
      for(auto s:h.path_segments(i,j)) {
        if(s.reversed)for(int k=s.r-1;k>=s.l;--k)path.push_back(h.vertex[k]);
        else for(int k=s.l;k<s.r;++k)path.push_back(h.vertex[k]);
      }
      require(path==left);
    }
    TreeIsomorphism iso;
    require(iso.isomorphic(g,g));
  }
}
void test_strings() {
  using namespace notebook::strings;
  for(int rep=0;rep<250;++rep) {
    string s;
    int n=rng()%35;
    for(int i=0;i<n;++i)s+=char('a'+rng()%3);
    SuffixArray sa(s);
    vector<int>expected(n);
    iota(expected.begin(),expected.end(),0);
    sort(expected.begin(),expected.end(),[&](int a,int b) {
      return s.substr(a)<s.substr(b);
    });
    require(sa.sa==expected);
    for(int i=1;i<n;++i) {
      int a=sa.sa[i-1],b=sa.sa[i],k=0;
      while(a+k<n&&b+k<n&&s[a+k]==s[b+k])++k;
      require(sa.lcp[i]==k);
    }
    SuffixAutomaton sam(s);
    PalindromeTree pam;
    for(char c:s)pam.append(c);
    auto rad=manacher(s);
    set<string>sub,pal;
    auto z=z_function(s);
    RollingHash hash(s);
    for(int i=0;i<n;++i) {
      int k=0;
      while(i+k<n&&s[k]==s[i+k])++k;
      require(z[i]==k);
      for(int j=i+1;j<=n;++j) {
        string t=s.substr(i,j-i);
        sub.insert(t);
        require(sam.contains(t));
        string rev=t;
        reverse(rev.begin(),rev.end());
        if(t==rev)pal.insert(t);
        for(int a=0;a+j-i<=n;++a)if(s.substr(a,j-i)==t)require(hash.get(i,j)==hash.get(a,a+j-i));
      }
      int odd=1,even=0;
      while(i-odd>=0&&i+odd<n&&s[i-odd]==s[i+odd])++odd;
      while(i-even-1>=0&&i+even<n&&s[i-even-1]==s[i+even])++even;
      require(rad.odd[i]==odd&&rad.even[i]==even);
    }
    require(sam.distinct_substrings()==(long long)sub.size());
    require(pam.nodes.size()==pal.size()+2);
    string best=s;
    int idx=minimum_rotation(s);
    for(int i=0;i<n;++i)best=min(best,s.substr(i)+s.substr(0,i));
    require(s.substr(idx)+s.substr(0,idx)==best);
    string pattern="ab";
    vector<int>matches;
    for(int i=0;i+2<=n;++i)if(s.substr(i,2)==pattern)matches.push_back(i);
    require(kmp_matches(s,pattern)==matches);
    AhoCorasick ac;
    ac.add("ab",0);
    ac.add("a",1);
    ac.build();
    vector<pair<int,int>>got;
    ac.scan(s,[&](int end,int id) {
      got.push_back( {
        end,id
      });
    });
    vector<pair<int,int>>want;
    for(int i=0;i<n;++i) {
      if(s[i]=='a')want.push_back( {
        i+1,1
      });
      if(i&&s.substr(i-1,2)=="ab")want.push_back( {
        i+1,0
      });
    }
    sort(got.begin(),got.end());
    sort(want.begin(),want.end());
    require(got==want);
  }
  for(int k=1;k<=4;++k)for(int n=1;n<=5;++n) {
    vector<int>a;
    de_bruijn(k,n,[&](int x) {
      a.push_back(x);
    });
    int count=1;
    for(int i=0;i<n;++i)count*=k;
    require((int)a.size()==count);
    set<vector<int>>words;
    for(int i=0;i<count;++i) {
      vector<int>w;
      for(int j=0;j<n;++j)w.push_back(a[(i+j)%count]);
      words.insert(w);
    }
    require((int)words.size()==count);
  }
}
void test_math() {
  using namespace notebook::math;
  LinearSieve sieve(10000);
  for(int n=0;n<=10000;++n) {
    bool prime=n>=2;
    for(int d=2;d*d<=n;++d)if(n%d==0)prime=false;
    require(is_prime(n)==prime);
  }
  for(int n=0;n<=2000;++n)require(prime_count(n)==(uint64_t)count_if(sieve.primes.begin(),sieve.primes.end(),[&](int p) {
    return p<=n;
  }));
  for(int rep=0;rep<1000;++rep) {
    int n=rng()%50,m=1+rng()%50,a=rng()%100,b=rng()%100;
    long long sum=0;
    for(int i=0;i<n;++i)sum+=(a*i+b)/m;
    require(floor_sum(n,m,a,b)==sum);
    long long x=(int)(rng()%101)-50,y=(int)(rng()%101)-50;
    auto z=extended_gcd(x,y);
    require(z.gcd==gcd(x,y)&&x*z.x+y*z.y==z.gcd);
    uint64_t p=1+rng()%1000,q=1+rng()%1000,d=gcd(p,q);
    p/=d;
    q/=d;
    auto decoded=stern_decode(stern_encode(p,q));
    require(decoded.first==p&&decoded.second==q);
    uint64_t value=1+rng()%1000000000;
    auto factors=factorize(value,rng);
    __uint128_t product=1;
    for(auto f:factors) {
      require(is_prime(f));
      product*=f;
    }
    require(product==value);
    XorBasis basis;
    vector<uint64_t>span {
      0
    };
    for(int i=0;i<8;++i) {
      uint64_t v=rng()%256;
      basis.insert(v);
      int sz=span.size();
      for(int j=0;j<sz;++j)span.push_back(span[j]^v);
    }
    sort(span.begin(),span.end());
    span.erase(unique(span.begin(),span.end()),span.end());
    require(basis.maximum()==span.back());
    for(int i=0;i<(int)span.size();++i)require(basis.kth(i)==span[i]);
  }
  for(int m=1;m<=60;++m)for(int a=0;a<m;++a)for(int b=0;b<m;++b) {
    optional<uint64_t>want;
    uint64_t v=1%m;
    set<uint64_t>seen;
    for(int i=0;seen.insert(v).second;++i) {
      if(v==(uint64_t)b) {
        want=i;
        break;
      }
      v=v*a%m;
    }
    require(discrete_log(a,b,m)==want);
  }
  for(int p:sieve.primes) {
    if(p>150)break;
    uint64_t root=primitive_root(p,rng);
    set<uint64_t>powers;
    for(int i=0;i<p-1;++i)powers.insert(pow_mod(root,i,p));
    require((int)powers.size()==p-1);
    for(int a=0;a<p;++a) {
      auto x=sqrt_mod(a,p);
      bool possible=false;
      for(int i=0;i<p;++i)if(i*i%p==a)possible=true;
      require(bool(x)==possible);
      if(x)require(*x**x%p==(uint64_t)a);
    }
  }
  for(auto kind: {
    Walsh::Xor,Walsh::And,Walsh::Or
  })for(int rep=0;rep<30;++rep) {
    vector<long long>a(16),b(16),c(16);
    for(auto&x:a)x=rng()%10;
    for(auto&x:b)x=rng()%10;
    for(int i=0;i<16;++i)for(int j=0;j<16;++j)c[kind==Walsh::Xor?i^j:kind==Walsh::And?i&j:i|j]+=a[i]*b[j];
    fwht(a,kind);
    fwht(b,kind);
    for(int i=0;i<16;++i)a[i]*=b[i];
    fwht(a,kind,true);
    require(a==c);
  }
  for(int n=1;n<15;++n) {
    vector<uint64_t>y(n);
    for(int i=0;i<n;++i)y[i]=(3*i*i+5*i+7)%101;
    if(n<3)continue;
    for(int x=0;x<101;++x)require(lagrange(y,x,101)==(uint64_t)((3*x*x+5*x+7)%101));
  }
  auto sol=gauss( {
    {
      1,2,3
    }, {
      2,4,6
    }
  },2);
  require(sol.consistent&&sol.rank==1&&sol.nullspace.size()==1);
  require(!gauss( {
    {
      1,2,3
    }, {
      2,4,7
    }
  },2).consistent);
  require(abs(determinant( {
    {
      1,2
    }, {
      3,4
    }
  })+2)<1e-9);
}
void test_graphs() {
  using namespace notebook::graph;
  for(int rep=0;rep<300;++rep) {
    int n=2+rng()%8;
    vector<vector<int>>g(n);
    vector<pair<int,int>>edges;
    vector<CutTreeEdge>capacities;
    Dinic flow(n);
    for(int u=0;u<n;++u)for(int v=u+1;v<n;++v)if(rng()%2) {
      g[u].push_back(v);
      g[v].push_back(u);
      edges.push_back( {
        u,v
      });
      long long c=rng()%10;
      capacities.push_back( {
        u,v,c
      });
      flow.add_edge(u,v,c);
      flow.add_edge(v,u,c);
    }
    auto match=general_matching(g);
    int count=0;
    for(int u=0;u<n;++u)if(match[u]>=0) {
      ++count;
      require(match[match[u]]==u);
      require(find(g[u].begin(),g[u].end(),match[u])!=g[u].end());
    }
    require(count/2==brute_matching(g,(1<<n)-1));
    auto colors=vizing_coloring(n,edges);
    int delta=0;
    for(auto row:g)delta=max(delta,(int)row.size());
    vector<set<int>>used(n);
    for(int i=0;i<(int)edges.size();++i) {
      auto[u,v]=edges[i];
      require(colors[i]>=0&&colors[i]<=delta);
      require(used[u].insert(colors[i]).second&&used[v].insert(colors[i]).second);
    }
    auto tree=gomory_hu(n,capacities);
    vector<vector<pair<int,long long>>>t(n);
    for(auto e:tree) {
      t[e.u].push_back( {
        e.v,e.capacity
      });
      t[e.v].push_back( {
        e.u,e.capacity
      });
    }
    for(int a=0;a<n;++a)for(int b=a+1;b<n;++b) {
      long long best=LLONG_MAX;
      for(int mask=0;mask<(1<<n);++mask)if((mask>>a&1)&&!(mask>>b&1)) {
        long long sum=0;
        for(auto e:capacities)if((mask>>e.u&1)!=(mask>>e.v&1))sum+=e.capacity;
        best=min(best,sum);
      }
      function<long long(int,int,long long)>dfs=[&](int u,int p,long long value) {
        if(u==b)return value;
        for(auto[v,w]:t[u])if(v!=p) {
          auto x=dfs(v,u,min(value,w));
          if(x>=0)return x;
        }
        return -1LL;
      };
      require(dfs(a,-1,LLONG_MAX)==best);
      if(a==0&&b==n-1)require(flow.max_flow(a,b)==best);
    }
    vector<vector<int>>dg(n);
    for(int u=0;u<n;++u)for(int v=0;v<n;++v)if(rng()%4==0)dg[u].push_back(v);
    auto idom=immediate_dominators(dg,0);
    auto reach=[&](int blocked) {
      vector<bool>seen(n);
      if(blocked!=0) {
        seen[0]=true;
        vector<int>q {
          0
        };
        for(size_t i=0;i<q.size();++i)for(int v:dg[q[i]])if(v!=blocked&&!seen[v])seen[v]=true,q.push_back(v);
      }
      return seen;
    };
    auto base=reach(-1);
    vector<vector<bool>>without;
    for(int u=0;u<n;++u)without.push_back(reach(u));
    for(int v=1;v<n;++v) {
      if(!base[v]) {
        require(idom[v]==-1);
        continue;
      }
      vector<int>dom;
      for(int u=0;u<n;++u)if(u!=v&&!without[u][v])dom.push_back(u);
      int want=-1;
      for(int u:dom) {
        bool deepest=true;
        for(int w:dom)if(u!=w&&without[w][u])deepest=false;
        if(deepest)want=u;
      }
      require(idom[v]==want);
    }
    vector<vector<int>>tg(n);
    for(int i=1;i<n;++i) {
      int p=rng()%i;
      tg[i].push_back(p);
      tg[p].push_back(i);
    }
    vector<vector<int>>decoded(n);
    for(auto[u,v]:prufer_decode(prufer_encode(tg))) {
      decoded[u].push_back(v);
      decoded[v].push_back(u);
    }
    for(auto&row:tg)sort(row.begin(),row.end());
    for(auto&row:decoded)sort(row.begin(),row.end());
    require(tg==decoded);
  }
  for(int rep=0;rep<200;++rep) {
    int n=1+rng()%6,m=n+rng()%3;
    vector<vector<long long>>a(n,vector<long long>(m));
    for(auto&row:a)for(auto&x:row)x=(int)(rng()%31)-15;
    long long best=LLONG_MAX;
    function<void(int,int,long long)>dfs=[&](int i,int mask,long long value) {
      if(i==n) {
        best=min(best,value);
        return;
      }
      for(int j=0;j<m;++j)if(!(mask>>j&1))dfs(i+1,mask|(1<<j),value+a[i][j]);
    };
    dfs(0,0,0);
    auto assignment=hungarian(a);
    require(assignment.cost==best);
    MinCostFlow f(n+m+2);
    for(int i=0;i<n;++i) {
      f.add_edge(n+m,i,1,0);
      for(int j=0;j<m;++j)f.add_edge(i,n+j,1,a[i][j]);
    }
    for(int j=0;j<m;++j)f.add_edge(n+j,n+m+1,1,0);
    auto result=f.send(n+m,n+m+1,n);
    require(result.flow==n&&result.cost==best);
    HopcroftKarp hk(n,m);
    vector<vector<int>>bg(n+m);
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)if(rng()%2) {
      hk.add_edge(i,j);
      bg[i].push_back(n+j);
      bg[n+j].push_back(i);
    }
    require(hk.solve()==brute_matching(bg,(1<<(n+m))-1));
    auto cover=hk.min_vertex_cover();
    require(cover.first.size()+cover.second.size()==(size_t)hk.solve());
    int vars=1+rng()%5;
    TwoSAT sat(vars);
    vector<pair<int,int>>clauses;
    for(int i=0;i<15;++i) {
      int a=rng()%(2*vars),b=rng()%(2*vars);
      clauses.push_back( {
        a,b
      });
      sat.add_or(a,b);
    }
    bool possible=false;
    for(int mask=0;mask<(1<<vars);++mask) {
      bool ok=true;
      for(auto[a,b]:clauses)ok&=(((mask>>(a/2)&1)==!(a&1))||((mask>>(b/2)&1)==!(b&1)));
      possible|=ok;
    }
    auto sol=sat.solve();
    require(bool(sol)==possible);
    if(sol)for(auto[a,b]:clauses)require(((*sol)[a/2]==!(a&1))||((*sol)[b/2]==!(b&1)));
  }
}
void test_dp() {
  using namespace notebook::dp;
  for(int rep=0;rep<200;++rep) {
    int n=1+rng()%40;
    long long penalty=rng()%100;
    auto cost=[&](int j,int i) {
      return 1LL*(i-j)*(i-j)+penalty;
    };
    vector<long long>brute(n+1,1LL<<60);
    brute[0]=0;
    for(int i=1;i<=n;++i)for(int j=0;j<i;++j)brute[i]=min(brute[i],brute[j]+cost(j,i));
    require(monotone_partition_dp(n,cost)==brute);
    vector<long long>prev(n+1,1LL<<60);
    prev[0]=0;
    for(int layer=1;layer<=min(n,5);++layer) {
      vector<long long>want(n+1,1LL<<60);
      for(int i=1;i<=n;++i)for(int j=0;j<i;++j)if(prev[j]<(1LL<<60))want[i]=min(want[i],prev[j]+cost(j,i));
      require(divide_conquer_layer(prev,cost)==want);
      prev=want;
    }
    MonotoneMinHull hull;
    vector<pair<long long,long long>>lines;
    for(int i=50;i>=-50;--i) {
      long long b=(int)(rng()%1000)-500;
      hull.add(i,b);
      lines.push_back( {
        i,b
      });
    }
    for(int x=-50;x<=50;++x) {
      long long want=LLONG_MAX;
      for(auto[m,b]:lines)want=min(want,m*x+b);
      require(hull.query(x)==want);
    }
    vector<long long>a(n);
    for(auto&x:a)x=(int)(rng()%100)-50;
    int k=rng()%(n+1);
    auto answer=banded_pick_k(a,k,n,rng);
    sort(a.rbegin(),a.rend());
    require(answer==accumulate(a.begin(),a.begin()+k,0LL));
    vector<vector<int>>g(n);
    for(int i=1;i<n;++i) {
      int p=rng()%i;
      g[i].push_back(p);
      g[p].push_back(i);
    }
    using State=pair<long long,long long>;
    auto result=reroot(g,State {
      0,0
    },[](State a,State b) {
      return State {
        a.first+b.first,a.second+b.second
      };
    },[](State a,int) {
      return State {
        a.first+1,a.second
      };
    },[](State a,int,int) {
      return State {
        a.first,a.second+a.first
      };
    });
    for(int u=0;u<n;++u) {
      vector<int>d(n,-1),q {
        u
      };
      d[u]=0;
      for(size_t i=0;i<q.size();++i)for(int v:g[q[i]])if(d[v]<0)d[v]=d[q[i]]+1,q.push_back(v);
      require(result[u]==State {
        n,accumulate(d.begin(),d.end(),0LL)
      });
    }
    SlopeTrick st;
    vector<long long>f(401,0);
    for(int step=0;step<20;++step) {
      int a=(int)(rng()%41)-20;
      st.add_abs(a);
      for(int x=-200;x<=200;++x)f[x+200]+=abs(x-a);
      if(rng()%2) {
        int l=rng()%4,r=rng()%4;
        st.window_min(l,r);
        auto old=f;
        for(int x=-200;x<=200;++x) {
          f[x+200]=LLONG_MAX;
          for(int y=max(-200,x-r);y<=min(200,x+l);++y)f[x+200]=min(f[x+200],old[y+200]);
        }
      }
      require(st.minimum()==*min_element(f.begin(),f.end()));
    }
  }
}
void test_geometry() {
  using namespace notebook::geometry;
  for(int rep=0;rep<300;++rep) {
    int n=1+rng()%25;
    vector<Point>p;
    vector<pair<long long,long long>>ip;
    for(int i=0;i<n;++i) {
      long long x=(int)(rng()%41)-20,y=(int)(rng()%41)-20;
      p.push_back( {
        (long double)x,(long double)y
      });
      ip.push_back( {
        x,y
      });
    }
    auto h=convex_hull(p);
    long double diameter=0;
    for(auto a:p)for(auto b:p)diameter=max(diameter,norm2(a-b));
    require(abs(diameter_squared(h)-diameter)<1e-8);
    for(int step=0;step<30;++step) {
      Point q {
        (long double)((int)(rng()%61)-30),(long double)((int)(rng()%61)-30)
      };
      require(point_in_convex(h,q)==point_in_polygon(h,q));
    }
    auto mst=manhattan_mst(ip);
    vector<long long>d(n,LLONG_MAX);
    vector<bool>used(n);
    d[0]=0;
    long long total=0;
    for(int i=0;i<n;++i) {
      int u=-1;
      for(int v=0;v<n;++v)if(!used[v]&&(u<0||d[v]<d[u]))u=v;
      used[u]=true;
      total+=d[u];
      for(int v=0;v<n;++v)d[v]=min(d[v],llabs(ip[u].first-ip[v].first)+llabs(ip[u].second-ip[v].second));
    }
    require(mst.first==total);
    auto circle=smallest_enclosing_circle(p,rng);
    for(Point x:p)require(contains(circle,x));
    long double best=numeric_limits<long double>::infinity();
    auto attempt=[&](Circle c) {
      bool ok=true;
      for(auto x:p)ok&=contains(c,x);
      if(ok)best=min(best,c.radius);
    };
    for(int i=0;i<n;++i) {
      attempt( {
        p[i],0
      });
      for(int j=0;j<i;++j) {
        attempt(diameter_circle(p[i],p[j]));
        for(int k=0;k<j;++k)attempt(circle_through(p[i],p[j],p[k]));
      }
    }
    require(abs(circle.radius-best)<1e-7);
    if(h.size()>=3) {
      LineHullIntersection index(h);
      for(int step=0;step<30;++step) {
        Line l {
          {
            (long double)((int)(rng()%61)-30),(long double)((int)(rng()%61)-30)
          }, {
            1,(long double)((int)(rng()%11)-5)
          }
        };
        vector<Point>want;
        for(int i=0;i<(int)h.size();++i) {
          Point a=h[i],b=h[(i+1)%h.size()];
          auto hit=line_intersection(l, {
            a,b-a
          });
          if(hit&&on_segment(*hit,a,b))want.push_back(*hit);
        }
        auto got=index.intersect(l);
        require(got.empty()==want.empty());
        for(auto x:got) {
          require(abs(cross(l.d,x-l.p))<1e-7);
          require(point_in_convex(h,x)>=0);
        }
      }
      vector<Line>planes;
      for(int i=0;i<(int)h.size();++i)planes.push_back( {
        h[i],h[(i+1)%h.size()]-h[i]
      });
      auto clipped=halfplane_intersection(planes,100);
      long double a=0,b=0;
      for(int i=0;i<(int)h.size();++i)a+=cross(h[i],h[(i+1)%h.size()]);
      for(int i=0;i<(int)clipped.size();++i)b+=cross(clipped[i],clipped[(i+1)%clipped.size()]);
      require(abs(a-b)<1e-7);
    }
    vector<Rectangle>rects;
    set<pair<int,int>>cells;
    for(int i=0;i<10;++i) {
      int x=rng()%10,y=rng()%10,w=rng()%5,h=rng()%5;
      rects.push_back( {
        x,y,x+w,y+h
      });
      for(int a=x;a<x+w;++a)for(int b=y;b<y+h;++b)cells.insert( {
        a,b
      });
    }
    require(rectangle_union_area(rects)==(__int128)cells.size());
  }
  auto dual=planar_dual( {
    {
      0,0
    }, {
      1,0
    }, {
      1,1
    }, {
      0,1
    }
  }, {
    {
      0,1
    }, {
      1,2
    }, {
      2,3
    }, {
      3,0
    }, {
      0,2
    }
  });
  require(dual.face_darts.size()==3&&dual.outer_face>=0);
  require(circle_tangents( {
    0,0
  },1, {
    4,0
  },1)->size()==4);
  require(!circle_tangents( {
    0,0
  },1, {
    0,0
  },1));
}
void test_additional();
void test_boundaries();
void test_legacy();
void test_interface_boundaries();
int main() {
  try {
    test_structures();
    cerr<<"structures OK\n";
    test_strings();
    cerr<<"strings OK\n";
    test_math();
    cerr<<"math OK\n";
    test_graphs();
    cerr<<"graphs OK\n";
    test_dp();
    cerr<<"DP OK\n";
    test_interface_boundaries();
    test_legacy();
    cerr<<"legacy interfaces OK\n";
    test_boundaries();
    test_additional();
    cerr<<"additional OK\n";
    test_geometry();
    cerr<<"geometry OK\n";
    cout<<"PASS: "<<checks<<" checks\n";
  }
  catch(exception&e) {
    cerr<<e.what()<<'\n';
    return 1;
  }
}
void test_additional() {
  using namespace notebook::graph;
  {
    RollbackDSU d(5);
    auto a=d.snapshot();
    d.unite(0,1);
    d.unite(0,1);
    auto b=d.snapshot();
    d.unite(1,2);
    require(d.components==3);
    d.rollback(b);
    require(d.find(0)==d.find(1)&&d.find(0)!=d.find(2));
    d.rollback(a);
    require(d.components==5);
  }
  for(int rep=0;rep<100;++rep) {
    int n=2+rng()%7;
    vector<pair<int,int>>edges;
    vector<vector<int>>g(n);
    BipartiteDSU d(n);
    for(int step=0;step<15;++step) {
      int u=rng()%n,v=rng()%n;
      edges.push_back( {
        u,v
      });
      g[u].push_back(v);
      g[v].push_back(u);
      d.add_edge(u,v);
      for(int root=0;root<n;++root) {
        vector<int>c(n,-1),q {
          root
        };
        c[root]=0;
        bool ok=true;
        for(size_t i=0;i<q.size();++i)for(int w:g[q[i]]) {
          if(c[w]<0)c[w]=c[q[i]]^1,q.push_back(w);
          else if(c[w]==c[q[i]])ok=false;
        }
        require(d.is_bipartite(root)==ok);
      }
    }
    auto components=[&](int removed_vertex,int removed_edge) {
      vector<bool>seen(n);
      int count=0;
      for(int start=0;start<n;++start)if(start!=removed_vertex&&!seen[start]) {
        ++count;
        vector<int>q {
          start
        };
        seen[start]=true;
        for(size_t i=0;i<q.size();++i)for(int id=0;id<(int)edges.size();++id)if(id!=removed_edge) {
          auto[u,v]=edges[id];
          if(u!=q[i])swap(u,v);
          if(u==q[i]&&v!=removed_vertex&&!seen[v])seen[v]=true,q.push_back(v);
        }
      }
      return count;
    };
    int base=components(-1,-1);
    auto bcc=biconnected_components(n,edges);
    set<int>bridges(bcc.bridges.begin(),bcc.bridges.end());
    for(int i=0;i<(int)edges.size();++i)require(bridges.count(i)==(size_t)(components(-1,i)>base));
    for(int u=0;u<n;++u)require(bcc.articulation[u]==(components(u,-1)>base));
    vector<int>occ(edges.size());
    for(auto block:bcc.edge_blocks)for(int id:block)++occ[id];
    for(int x:occ)require(x==1);
    vector<pair<int,int>>walk;
    int last=rng()%n;
    for(int i=0;i<20;++i) {
      int next=rng()%n;
      walk.push_back( {
        last,next
      });
      last=next;
    }
    for(bool directed: {
      false,true
    }) {
      auto trail=euler_trail(n,walk,directed);
      require(bool(trail));
      vector<int>used(walk.size());
      for(int i=0;i<(int)walk.size();++i) {
        int id=trail->edge_ids[i];
        require(++used[id]==1);
        auto[u,v]=walk[id];
        int a=trail->vertices[i],b=trail->vertices[i+1];
        require((u==a&&v==b)||(!directed&&u==b&&v==a));
      }
    }
    vector<vector<int>>men(n),women(n);
    for(auto*side: {
      &men,&women
    })for(auto&row:*side) {
      row.resize(n);
      iota(row.begin(),row.end(),0);
      shuffle(row.begin(),row.end(),rng);
    }
    auto wife=stable_marriage(men,women);
    vector<int>husband(n);
    for(int m=0;m<n;++m)husband[wife[m]]=m;
    for(int m=0;m<n;++m)for(int w:men[m]) {
      if(w==wife[m])break;
      auto&pref=women[w];
      require(find(pref.begin(),pref.end(),husband[w])<find(pref.begin(),pref.end(),m));
    }
  }
  {
    auto cycle=find_cycle(0,[](int x) {
      return x<3?x+1:1;
    });
    require(cycle.entry==1&&cycle.prefix_length==1&&cycle.cycle_length==3);
    vector<vector<long long>>d {
      {
        0,3,1000
      }, {
        1000,0,4
      }, {
        2,1000,0
      }
    };
    require(!floyd_warshall(d,1000));
    require(d[0][2]==7&&d[1][0]==6);
  }
  for(int rep=0;rep<50;++rep) {
    int n=4,m=5;
    vector<tuple<int,int,long long>>e {
      {
        0,1,1+(long long)(rng()%8)
      }, {
        1,2,1+(long long)(rng()%8)
      }, {
        2,3,1+(long long)(rng()%8)
      }, {
        0,2,1+(long long)(rng()%8)
      }, {
        1,3,1+(long long)(rng()%8)
      }
    };
    vector<vector<pair<int,long long>>>g(n);
    for(auto[u,v,w]:e)g[u].push_back( {
      v,w
    }),g[v].push_back( {
      u,w
    });
    long long best=LLONG_MAX;
    for(int mask=0;mask<(1<<m);++mask) {
      RollbackDSU d(n);
      long long value=0;
      for(int i=0;i<m;++i)if(mask>>i&1) {
        auto[u,v,w]=e[i];
        d.unite(u,v);
        value+=w;
      }
      if(d.find(0)==d.find(2)&&d.find(0)==d.find(3))best=min(best,value);
    }
    require(steiner_tree(g, {
      0,2,3
    })==best);
  }
  for(int n=2;n<=25;++n) {
    vector<pair<int,int>>e;
    for(int i=0;i<n;++i)for(int j=0;j<i;++j)e.push_back( {
      i,j
    });
    auto colors=vizing_coloring(n,e);
    vector<set<int>>used(n);
    for(int i=0;i<(int)e.size();++i) {
      auto[u,v]=e[i];
      require(colors[i]>=0&&colors[i]<=n-1);
      require(used[u].insert(colors[i]).second&&used[v].insert(colors[i]).second);
    }
  }
  {
    Dinic d(3);
    d.add_edge(0,0,100);
    d.add_edge(0,1,3);
    d.add_edge(1,2,3);
    require(d.max_flow(0,2,1)==1&&d.max_flow(0,2)==2);
  }
  using namespace notebook::data_structure;
  for(int rep=0;rep<60;++rep) {
    int n=1+rng()%25;
    vector<long long>a(n);
    for(auto&x:a)x=(int)(rng()%21)-10;
    WaveletTree w(a);
    vector<pair<int,int>>queries;
    for(int l=0;l<n;++l)for(int r=l+1;r<=n;++r)queries.push_back( {
      l,r
    });
    auto indices=range_max_indices(a,queries);
    for(int i=0;i<(int)queries.size();++i) {
      auto[l,r]=queries[i];
      int want=l;
      for(int j=l;j<r;++j)if(a[j]>=a[want])want=j;
      require(indices[i]==want);
      require(w.count(l,r,-3,4)==count_if(a.begin()+l,a.begin()+r,[](long long x) {
        return -3<=x&&x<=4;
      }));
    }
  }
  using namespace notebook::dp;
  for(int rep=0;rep<100;++rep) {
    int n=1+rng()%20;
    vector<long long>a(n),prefix(n+1);
    for(int i=0;i<n;++i)a[i]=rng()%20,prefix[i+1]=prefix[i]+a[i];
    auto cost=[&](int l,int r) {
      return prefix[r]-prefix[l];
    };
    vector<vector<long long>>b(n,vector<long long>(n));
    for(int len=2;len<=n;++len)for(int l=0;l+len<=n;++l) {
      int r=l+len-1;
      b[l][r]=LLONG_MAX;
      for(int k=l;k<r;++k)b[l][r]=min(b[l][r],b[l][k]+b[k+1][r]+cost(l,r+1));
    }
    require(knuth_partition(n,cost)==b[0][n-1]);
    vector<long long>v(32);
    for(auto&x:v)x=(int)(rng()%100)-50;
    for(bool super: {
      false,true
    }) {
      auto orig=v;
      subset_transform(v,super);
      subset_transform(v,super,true);
      require(v==orig);
    }
    for(int k=0;k<=30;++k) {
      auto oracle=[](long long lambda) {
        PenalizedResult result {
          LLONG_MAX,0
        };
        for(int j=0;j<=30;++j) {
          long long val=1LL*j*j-lambda*j;
          if(val<=result.value)result= {
            val,j
          };
        }
        return result;
      };
      require(aliens_exact(k,-100,100,oracle)==1LL*k*k);
    }
  }
  {
    MonotoneMinQueue<int>q;
    q.push(0,4);
    q.push(1,3);
    q.push(2,5);
    require(q.minimum()==3);
    q.expire(2);
    require(q.minimum()==5);
    q.expire(3);
    require(q.empty());
  }
  using namespace notebook::tree;
  for(int rep=0;rep<60;++rep) {
    int n=1+rng()%50;
    vector<vector<int>>g(n),other(n);
    vector<int>perm(n);
    iota(perm.begin(),perm.end(),0);
    shuffle(perm.begin(),perm.end(),rng);
    for(int i=1;i<n;++i) {
      int p=rng()%i;
      g[p].push_back(i);
      g[i].push_back(p);
      other[perm[p]].push_back(perm[i]);
      other[perm[i]].push_back(perm[p]);
    }
    TreeIsomorphism iso;
    require(iso.isomorphic(g,other));
    vector<int>seen(n);
    CentroidDecomposition cd(g,[&](int c,int parent,const vector<bool>&blocked) {
      require(++seen[c]==1&&blocked[c]);if(parent>=0)require(blocked[parent]);int total=1,largest=0;for(int v:g[c])if(!blocked[v]) {
        vector<pair<int,int>>q {
          {
            v,c
          }
        };for(size_t i=0;i<q.size();++i)for(int w:g[q[i].first])if(!blocked[w]&&w!=q[i].second)q.push_back( {
          w,q[i].first
        });total+=q.size();largest=max(largest,(int)q.size());
      }
      require(largest<=total/2);
    });
    for(int x:seen)require(x==1);
  }
  using namespace notebook::geometry;
  for(int rep=0;rep<100;++rep) {
    vector<Point>a,b;
    for(int i=0;i<10;++i) {
      a.push_back( {
        (long double)(rng()%20),(long double)(rng()%20)
      });
      b.push_back( {
        (long double)(rng()%20),(long double)(rng()%20)
      });
    }
    a=convex_hull(a);
    b=convex_hull(b);
    vector<Point>all;
    for(auto x:a)for(auto y:b)all.push_back(x+y);
    auto expected=convex_hull(all),sum=minkowski_sum(a,b);
    auto area=[](const vector<Point>&p) {
      long double ans=0;
      for(int i=0;i<(int)p.size();++i)ans+=cross(p[i],p[(i+1)%p.size()]);
      return ans;
    };
    require(abs(area(expected)-area(sum))<1e-8);
    for(auto x:sum)require(point_in_convex(expected,x)>=0);
  }
  auto square=halfplane_intersection( {
  },10);
  require(square.size()==4);
  require(halfplane_intersection( {
    {
      {
        1,0
      }, {
        0,-1
      }
    }, {
      {
        0,0
      }, {
        0,1
      }
    }
  },10).empty());
  using namespace notebook::math;
  for(int a=-10;a<=10;++a)for(int b=-10;b<=10;++b)for(int c=-10;c<=10;++c) {
    auto s=diophantine(a,b,c);
    bool possible=(a==0&&b==0)?c==0:c%gcd(a,b)==0;
    require(bool(s)==possible);
    if(s&&!s->all_pairs) {
      require(a*s->x+b*s->y==c);
      require(a*s->dx+b*s->dy==0);
    }
  }
  require(retrograde_analysis(3, {
    {
      1
    }, {
      2
    }, {
    }
  })==vector<int>( {
    LOSE,WIN,LOSE
  }));
  vector<int>memo(3,-1);
  require(get_grundy(0,memo, {
    {
      1
    }, {
      2
    }, {
    }
  })==0);
}
void test_boundaries() {
  using namespace notebook::geometry;
  vector<Point>square {
    {
      0,0
    }, {
      1,0
    }, {
      1,1
    }, {
      0,1
    }
  };
  LineHullIntersection index(square);
  require(index.intersect( {
    {
      0,1
    }, {
      1,0
    }
  }).size()==2);
  require(index.intersect( {
    {
      0,0
    }, {
      1,-1
    }
  }).size()==1);
  require(index.intersect( {
    {
      0,0.5
    }, {
      1,0
    }
  }).size()==2);
  require(index.intersect( {
    {
      0,2
    }, {
      1,0
    }
  }).empty());
  for(int rep=0;rep<600;++rep) {
    vector<Line>lines;
    int k=rng()%8;
    for(int i=0;i<k;++i) {
      Point p {
        (long double)((int)(rng()%21)-10),(long double)((int)(rng()%21)-10)
      },d {
        (long double)((int)(rng()%7)-3),(long double)((int)(rng()%7)-3)
      };
      if(norm2(d)==0)d.x=1;
      lines.push_back( {
        p,d
      });
    }
    vector<Point>poly {
      {
        -10,-10
      }, {
        10,-10
      }, {
        10,10
      }, {
        -10,10
      }
    };
    for(Line l:lines) {
      vector<Point>next;
      for(int i=0;i<(int)poly.size();++i) {
        Point a=poly[i],b=poly[(i+1)%poly.size()];
        long double x=cross(l.d,a-l.p),y=cross(l.d,b-l.p);
        if(x>=-EPS)next.push_back(a);
        if((x>EPS&&y<-EPS)||(x<-EPS&&y>EPS)) {
          Point hit=a+(b-a)*(x/(x-y));
          next.push_back(hit);
        }
      }
      poly.swap(next);
    }
    auto actual=halfplane_intersection(lines,10);
    auto area=[](const vector<Point>&p) {
      long double a=0;
      for(int i=0;i<(int)p.size();++i)a+=cross(p[i],p[(i+1)%p.size()]);
      return abs(a);
    };
    require(abs(area(actual)-area(poly))<1e-7);
  }
  using namespace notebook::math;
  require(!is_prime(UINT64_MAX));
  require(is_prime(18446744073709551557ULL));
  require(pow_mod(UINT64_MAX-1,2,UINT64_MAX)==1);
  auto bezout=extended_gcd(LLONG_MIN,LLONG_MAX);
  require(bezout.gcd==1&&(__int128)LLONG_MIN*bezout.x+(__int128)LLONG_MAX*bezout.y==1);
  require(floor_sum(0,1,UINT64_MAX,UINT64_MAX)==0);
  require(prime_count(1000000)==78498);
  vector<uint64_t>linear {
    5,8,11
  };
  uint64_t p=18446744073709551557ULL,x=p-2;
  require(lagrange(linear,x,p)==p-1);
  using namespace notebook::data_structure;
  WaveletTree empty( {
  });
  require(empty.count(0,0,LLONG_MIN,LLONG_MAX)==0);
  SegmentTreeBeats beats( {
  });
  require(beats.sum(0,0)==0);
  using namespace notebook::graph;
  require(euler_trail(0, {
  })->vertices.empty());
  require(!euler_trail(4, {
    {
      0,1
    }, {
      2,3
    }
  }));
  require(stable_marriage( {
  }, {
  }).empty());
  require(gomory_hu(0, {
  }).empty());
  using namespace notebook::strings;
  require(prefix_function("").empty()&&z_function("").empty());
  require(kmp_matches("ab","")==vector<int>( {
    0,1,2
  }));
  require(SuffixArray("").sa.empty());
}
void test_legacy() {
  using namespace notebook::data_structure;
  for(int rep=0;rep<80;++rep) {
    int n=1+rng()%30;
    vector<long long>a(n);
    for(auto&x:a)x=rng()%10;
    auto merge=[](long long a,long long b) {
      return a+b;
    };
    SegmentTree<long long,decltype(merge)>tree(a,0,merge);
    SparseRangeSum sparse(0,n);
    PersistentRangeSum persistent(n);
    int root=0;
    vector<pair<int,vector<long long>>>versions {
      {
        0,vector<long long>(n)
      }
    };
    for(int i=0;i<n;++i) {
      sparse.add(i,a[i]);
      root=persistent.add(root,i,a[i]);
    }
    versions.push_back( {
      root,a
    });
    for(int step=0;step<80;++step) {
      int p=rng()%n;
      long long value=rng()%10,delta=value-a[p];
      a[p]=value;
      tree.set(p,value);
      sparse.add(p,delta);
      root=persistent.add(root,p,delta);
      versions.push_back( {
        root,a
      });
      int l=rng()%n,r=l+rng()%(n-l+1);
      long long expected=accumulate(a.begin()+l,a.begin()+r,0LL);
      require(tree.fold(l,r)==expected&&sparse.sum(l,r)==expected&&persistent.sum(root,l,r)==expected);
      long long bound=rng()%30;
      int end=l;
      long long total=0;
      while(end<n&&total+a[end]<=bound)total+=a[end++];
      require(tree.max_right(l,[&](long long sum) {
        return sum<=bound;
      })==end);
      auto[v,old]=versions[rng()%versions.size()];
      require(persistent.sum(v,l,r)==accumulate(old.begin()+l,old.begin()+r,0LL));
    }
    vector<long long>zeros(n);
    RangeAddPointQuery dual(n);
    BlockArray block(zeros);
    IntervalSet<int>intervals(0,n,0);
    vector<int>values(n);
    for(int step=0;step<100;++step) {
      int l=rng()%n,r=l+rng()%(n-l+1);
      long long x=(int)(rng()%21)-10;
      dual.add(l,r,x);
      block.add(l,r,x);
      intervals.assign(l,r,(int)x);
      for(int i=l;i<r;++i)zeros[i]+=x,values[i]=x;
      for(int i=0;i<n;++i)require(dual.get(i)==zeros[i]&&block.get(i)==zeros[i]&&intervals.get(i)==values[i]);
      auto parts=intervals.intervals();
      require(parts.front().l==0&&parts.back().r==n);
      for(int i=1;i<(int)parts.size();++i)require(parts[i-1].r==parts[i].l&&parts[i-1].value!=parts[i].value);
    }
    vector<int>threshold(n);
    for(auto&x:threshold)x=(int)(rng()%(n+4))-1;
    long long state=0;
    auto ans=parallel_binary_search(n,n,[&] {
      state=0;
    },[&](int) {
      ++state;
    },[&](int q) {
      return state>=threshold[q];
    });
    for(int i=0;i<n;++i)require(ans[i]==min(n+1,max(0,threshold[i])));
    ImplicitTreap treap(rng());
    vector<long long>sequence;
    for(int step=0;step<100;++step) {
      int size=sequence.size();
      if(!size||rng()%3==0) {
        int p=rng()%(size+1),value=(int)(rng()%30)-15;
        sequence.insert(sequence.begin()+p,value);
        treap.insert(p,value);
      }else {
        int l=rng()%size,r=l+rng()%(size-l+1);
        if(rng()%2) {
          reverse(sequence.begin()+l,sequence.begin()+r);
          treap.reverse(l,r);
        }else {
          sequence.erase(sequence.begin()+l,sequence.begin()+r);
          treap.erase(l,r);
        }
      }
      require(treap.size()==(int)sequence.size());
      for(int i=0;i<(int)sequence.size();++i)require(treap.sum(i,i+1)==sequence[i]);
      require(treap.sum(0,treap.size())==accumulate(sequence.begin(),sequence.end(),0LL));
    }
    vector<array<double,2>>points(n);
    for(auto&p:points)p= {
      (double)(rng()%40),(double)(rng()%40)
    };
    KDTree<2>kd(points);
    for(int step=0;step<20;++step) {
      array<double,2>q {
        (double)(rng()%40),(double)(rng()%40)
      };
      int excluded=rng()%(n+1)-1;
      double best=numeric_limits<double>::infinity();
      int id=-1;
      for(int i=0;i<n;++i)if(i!=excluded) {
        double d=0;
        for(int j=0;j<2;++j)d+=(points[i][j]-q[j])*(points[i][j]-q[j]);
        if(d<best)best=d,id=i;
      }
      auto got=kd.nearest(q,excluded);
      require(bool(got)==(id>=0));
      if(got)require(got->first==id&&got->second==best);
      array<double,2>low {
        10,5
      },high {
        25,20
      };
      vector<int>want;
      for(int i=0;i<n;++i)if(low[0]<=points[i][0]&&points[i][0]<=high[0]&&low[1]<=points[i][1]&&points[i][1]<=high[1])want.push_back(i);
      auto found=kd.range(low,high);
      sort(found.begin(),found.end());
      require(found==want);
    }
    vector<pair<int,int>>ranges;
    for(int i=0;i<30;++i) {
      int l=rng()%n,r=l+rng()%(n-l+1);
      ranges.push_back( {
        l,r
      });
    }
    long long sum=0;
    auto mo=mo_queries(n,ranges,[&](int i) {
      sum+=a[i];
    },[&](int i) {
      sum-=a[i];
    },[&](int) {
      return sum;
    });
    for(int i=0;i<(int)ranges.size();++i)require(mo[i]==accumulate(a.begin()+ranges[i].first,a.begin()+ranges[i].second,0LL));
  }
  for(int rep=0;rep<80;++rep) {
    BinaryTrie trie;
    multiset<uint64_t>keys;
    ErasablePriorityQueue<uint64_t>pq;
    LiChao lc(-100,101);
    LineContainer hull;
    vector<pair<long long,long long>>lines;
    for(int step=0;step<100;++step) {
      uint64_t key=rng()%256;
      if(rng()%3||keys.empty()) {
        keys.insert(key);
        trie.insert(key);
        pq.insert(key);
      }else {
        auto it=keys.begin();
        advance(it,rng()%keys.size());
        key=*it;
        keys.erase(it);
        require(trie.erase(key)&&pq.erase(key));
      }
      require(trie.size()==(int)keys.size()&&pq.size()==keys.size());
      if(!keys.empty()) {
        require(pq.top()==*keys.rbegin());
        uint64_t want=0;
        for(auto x:keys)want=max(want,x^key);
        require(trie.max_xor(key)==want);
      }
      long long m=(int)(rng()%101)-50,b=(int)(rng()%201)-100;
      lines.push_back( {
        m,b
      });
      lc.add(m,b);
      hull.add(m,b);
      long long x=(int)(rng()%201)-100,wantmin=LLONG_MAX,wantmax=LLONG_MIN;
      for(auto[m,b]:lines) {
        wantmin=min(wantmin,m*x+b);
        wantmax=max(wantmax,m*x+b);
      }
      require(lc.minimum(x)==wantmin&&hull.maximum(x)==wantmax);
    }
  }
  for(int rep=0;rep<80;++rep) {
    int n=10;
    vector<long long>values(n);
    for(auto&x:values)x=(int)(rng()%21)-10;
    LinkCutTree lct(values);
    vector<vector<bool>>edge(n,vector<bool>(n));
    auto path=[&](int a,int b) {
      vector<int>parent(n,-1),queue {
        a
      };
      parent[a]=a;
      for(size_t i=0;i<queue.size();++i)for(int v=0;v<n;++v)if(edge[queue[i]][v]&&parent[v]<0)parent[v]=queue[i],queue.push_back(v);
      vector<int>out;
      if(parent[b]<0)return out;
      for(int u=b;u!=a;u=parent[u])out.push_back(u);
      out.push_back(a);
      reverse(out.begin(),out.end());
      return out;
    };
    for(int step=0;step<200;++step) {
      int u=rng()%n,v=rng()%n;
      auto p=path(u,v);
      switch(rng()%4) {
        case 0: {
          bool ok=p.empty();
          require(lct.link(u,v)==ok);
          if(ok)edge[u][v]=edge[v][u]=true;
          break;
        }
        case 1: {
          bool ok=edge[u][v];
          require(lct.cut(u,v)==ok);
          if(ok)edge[u][v]=edge[v][u]=false;
          break;
        }
        case 2:values[u]=(int)(rng()%21)-10;
        lct.set(u,values[u]);
        break;
        default:require(lct.connected(u,v)==!p.empty());
        auto result=lct.path_sum(u,v);
        require(bool(result)==!p.empty());
        if(result) {
          long long want=0;
          for(int x:p)want+=values[x];
          require(*result==want);
          int root=p[rng()%p.size()];
          auto a=path(root,u),b=path(root,v);
          int ancestor=root;
          for(int i=0;i<(int)min(a.size(),b.size())&&a[i]==b[i];++i)ancestor=a[i];
          require(lct.lca(root,u,v)==ancestor);
        }
        break;
      }
    }
  }
  {
    Fenwick2D f(8,9);
    vector<vector<long long>>a(8,vector<long long>(9));
    for(int step=0;step<100;++step) {
      int x=rng()%8,y=rng()%9,value=(int)(rng()%31)-15;
      f.add(x,y,value);
      a[x][y]+=value;
      int x1=rng()%8,x2=x1+rng()%(9-x1),y1=rng()%9,y2=y1+rng()%(10-y1);
      long long want=0;
      for(int x=x1;x<x2;++x)for(int y=y1;y<y2;++y)want+=a[x][y];
      require(f.sum(x1,y1,x2,y2)==want);
    }
  }
  {
    auto builder=[](const vector<int>&a) {
      auto b=a;
      sort(b.begin(),b.end());
      return b;
    };
    ExpandableIndex<int,decltype(builder)>index(builder);
    vector<int>all;
    for(int i=0;i<100;++i) {
      int x=rng()%20;
      all.push_back(x);
      index.insert(x);
      int count=0;
      index.query([&](const vector<int>&bucket) {
        count+=upper_bound(bucket.begin(),bucket.end(),x)-lower_bound(bucket.begin(),bucket.end(),x);
      });
      require(count==std::count(all.begin(),all.end(),x));
    }
    HashMap<int>hash;
    hash[3]=7;
    require(hash.at(3)==7);
  }
  using namespace notebook::math;
  for(int rep=0;rep<80;++rep) {
    int n=rng()%30,m=rng()%30;
    vector<int>a(n),b(m);
    for(auto&x:a)x=(int)(rng()%21)-10;
    for(auto&x:b)x=(int)(rng()%21)-10;
    vector<long long>c(n&&m?n+m-1:0);
    for(int i=0;i<n;++i)for(int j=0;j<m;++j)c[i+j]+=1LL*a[i]*b[j];
    require(convolution_fft(a,b)==c);
    auto got=convolution_ntt(a,b);
    require(got.size()==c.size());
    for(int i=0;i<(int)c.size();++i)require(got[i]==(c[i]%MOD+MOD)%MOD);
  }
  for(int rep=0;rep<80;++rep) {
    int k=1+rng()%6;
    vector<int>rec(k),sequence(100);
    for(auto&x:rec)x=rng()%10;
    for(int i=0;i<k;++i)sequence[i]=rng()%10;
    for(int i=k;i<100;++i)for(int j=0;j<k;++j)sequence[i]=(sequence[i]+1LL*rec[j]*sequence[i-1-j])%MOD;
    vector<int>prefix(sequence.begin(),sequence.begin()+30);
    auto found=berlekamp_massey(prefix);
    for(int i=0;i<100;++i)require(recurrence_term(prefix,found,i)==sequence[i]);
  }
  require(berlekamp_massey( {
  }).empty());
}
void test_interface_boundaries() {
  for(int rep=0;rep<100;++rep) {
    std::string bytes;
    int n=1+rng()%30;
    for(int i=0;i<n;++i)bytes+=char(rng()%256);
    std::string best=bytes;
    for(int i=1;i<n;++i)best=min(best,bytes.substr(i)+bytes.substr(0,i));
    int index=notebook::strings::minimum_rotation(bytes);
    require(bytes.substr(index)+bytes.substr(0,index)==best);
    std::string rebuilt,previous;
    bool first=true;
    for(auto[l,r]:notebook::strings::lyndon_factors(bytes)) {
      auto word=bytes.substr(l,r-l);
      rebuilt+=word;
      require(first||previous>=word);
      first=false;
      previous=word;
      for(int i=1;i<(int)word.size();++i)require(word<word.substr(i)+word.substr(0,i));
    }
    require(rebuilt==bytes);
  }
  using namespace notebook::data_structure;
  auto concatenate=[](std::string a,std::string b) {
    return a+b;
  };
  SegmentTree<std::string,decltype(concatenate)>ordered( {
    "ab","cd","ef"
  },"",concatenate);
  require(ordered.fold(0,3)=="abcdef"&&ordered.fold(1,3)=="cdef");
  ordered.set(1,"z");
  require(ordered.fold(0,3)=="abzef");
  LiChao empty_lines(-1,2);
  LineContainer hull;
  require(!empty_lines.minimum(0)&&!hull.maximum(0));
  vector<pair<long long,long long>>lines {
    {
      LLONG_MIN,LLONG_MAX
    }, {
      LLONG_MAX,LLONG_MIN
    }, {
      0,0
    }, {
      LLONG_MAX,LLONG_MAX
    }
  };
  for(auto[m,b]:lines)hull.add(m,b);
  for(long long x: {
    LLONG_MIN,-1LL,0LL,1LL,LLONG_MAX
  }) {
    __int128 best=-((__int128)1<<126);
    for(auto[m,b]:lines)best=max(best,(__int128)m*x+b);
    require(hull.maximum(x)==best);
  }
  KDTree<3>kd( {
    array<double,3> {
      1,2,3
    }
  });
  require(!kd.nearest( {
    0,0,0
  },0));
  require(kd.nearest( {
    0,0,0
  })->second==14);
  PersistentRangeSum persistent(0);
  require(persistent.sum(0,0,0)==0);
  Fenwick2D fenwick(0,0);
  require(fenwick.sum(0,0,0,0)==0);
  ErasablePriorityQueue<int>q;
  require(!q.erase(1));
  q.insert(1);
  q.insert(1);
  q.erase(1);
  require(q.top()==1&&q.size()==1);
  q.pop();
  require(q.empty());
  using namespace notebook::math;
  ostringstream out;
  print( {
    42,234567890,1
  },out);
  require(out.str()=="1234567890000000042");
  vector<int>rec {
    1,1
  },fib {
    0,1
  };
  require(recurrence_term(fib,rec,50)==607336789);
  require(convolution_ntt( {
  }, {
    1
  }).empty()&&convolution_fft( {
    1
  }, {
  }).empty());
}
