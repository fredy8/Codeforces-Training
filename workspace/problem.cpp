#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0), cout.precision(15);
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(decltype((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define RFORC(cont, it) for(decltype((cont).rbegin()) it=(cont).rbegin(); it!=(cont).rend(); it++)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

struct Edge {
  ll to, weight;
  Edge(ll to, ll weight = 1) : to(to), weight(weight) {}
};
struct Graph {
  ll V; bool undirected;
  vector<vector<Edge> > edges;
  Graph(ll v, bool undirected) : V(v), undirected(undirected) { edges.assign(V, vector<Edge>()); }
  void connect(ll from, Edge edge) {
    edges[from].pb(edge);
    if(undirected) {
      ll aux = edge.to;
      edge.to = from;
      edges[aux].pb(edge);
    }
  }
};

struct LCA {
  vi order, height, index, st;
  int minIndex(int i, int j) {
    return height[i] < height[j] ? i : j;
  }
  LCA(Graph &g, ll root) {
    index.assign(g.V, -1);
    dfs(g, root, 0);
    st.assign(height.size()*2, 0);
    FOR(i, 0, height.size())
      st[height.size() + i] = i;
    for(int i = height.size()-1; i; i--)
      st[i] = minIndex(st[i<<1], st[i<<1|1]);
  }
  void dfs(Graph &g, ll cv, ll h) {
    index[cv] = order.size();
    order.pb(cv), height.pb(h);
    FORC(g.edges[cv], edge)
      if(index[edge->to] == -1) {
        dfs(g, edge->to, height.back() + 1);
        order.pb(cv), height.pb(h);
      }
  }
  ll query(ll i, ll j) {
    int from = index[i], to = index[j];
    if (from > to) swap(from, to);
    int idx = from;
    for(int l = from + height.size(), r = to + height.size() + 1; l < r; l >>= 1, r >>= 1) {
      if (l&1) idx = minIndex(idx, st[l++]);
      if (r&1) idx = minIndex(idx, st[--r]);
    }
    return order[idx];
  }
};

#define e18 1000000000000000000ll

ii orderii(ii a) { return ii(min(a.first, a.second), max(a.first, a.second)); }
const double EPS = 1e-9;

inline int digits(ll n) {
  int ans = 0;
  while(n) n/=10, ans++;
  return ans;
}

inline ll multiply2(ll a, ll b) {
  ll ans = a*b;
  if (ans == e18) return e18;
  if (digits(a) + digits(b) >= 20)
    return e18+1;
  return ans > e18 ? e18+1 : ans;
}

inline void multiply(ll &a, ll b) { a = multiply2(a, b); }

struct SegmentTree {
  vi tree;
  ll N;
  SegmentTree(vi &values) {
    tree.assign(values.size()*2, 0);
    N = values.size();
    FOR(i, 0, N)
      tree[i + N] = values[i];
    for(ll i = N - 1; i; i--)
      tree[i] = multiply2(tree[i<<1], tree[i<<1|1]);
  }
  void set(ll index, ll value) {
    tree[index + N] = value;
    for(ll i = (index + N)>>1; i; i >>= 1)
      tree[i] = multiply2(tree[i<<1], tree[i<<1|1]);
  }
  ll query(ll from, ll to) {
    ll ans = 1;
    for(ll l = N + from, r = N + to; l < r; l >>= 1, r >>= 1) {
      if (l&1) multiply(ans, tree[l++]);
      if (r&1) multiply(ans, tree[--r]);
    }
    return ans;
  }
};

vi parent;

struct HeavyLightDecomposition {
  vector<SegmentTree> sts;
  LCA *lca;
  vector<vi> lists;
  vi values, listIndex, posIndex, treeSizes;
  HeavyLightDecomposition(Graph &g) {
    lca = new LCA(g, 0);
    listIndex = posIndex = parent = treeSizes = vi(g.V, -1);
    getTreeSizes(g, 0);
    values.assign(g.V, 1);
    makeLists(g, 0, -1);
    FORC(lists, list) {
      vi v;
      FORC(*list, it) v.pb(values[*it]);
      sts.pb(SegmentTree(v));
    }
  }
  ~HeavyLightDecomposition() { delete lca; }
  int getTreeSizes(Graph &g, int cv) {
    treeSizes[cv] = 1;
    FORC(g.edges[cv], edge) if(edge->to != parent[cv])
      parent[edge->to] = cv, treeSizes[cv] += getTreeSizes(g, edge->to);  
    return treeSizes[cv];
  }
  void makeLists(Graph &g, ll cv, ll listNum) {
    if(listNum == -1)
      listNum = lists.size(), lists.pb(vi());
    listIndex[cv] = listNum;
    posIndex[cv] = lists[listNum].size();
    lists[listNum].pb(cv);
    ll MAX = -1;
    FORC(g.edges[cv], edge) if(edge->to != parent[cv]) {
      if(MAX == -1 || treeSizes[edge->to] > treeSizes[MAX]) MAX = edge->to;
    } else values[cv] = edge->weight;
    FORC(g.edges[cv], edge) if(edge->to != parent[cv])
      makeLists(g, edge->to, edge->to == MAX ? listNum : -1); 
  }
  ll query(ll from, ll to) {
    if (from == to) return 1;
    ll anc = lca->query(from, to), posLeft, posRight;
    ll result = multiply2(queryToAncestor(from, anc, posLeft), queryToAncestor(to, anc, posRight));
    if(posLeft < posRight) swap(posLeft, posRight);
    if (posRight != posIndex[anc])
      multiply(result, sts[listIndex[anc]].query(posIndex[anc]+1, posRight+1));
    if(posRight != posLeft)
      multiply(result, sts[listIndex[anc]].query(posRight+1, posLeft+1));
    return result;
  }
  ll queryToAncestor(ll from, ll anc, ll &posInAncestorList) {
    ll result = 1, left = from;
    vi vv;
    int rr = from;
    while(listIndex[left] != listIndex[anc]) {
      vv.pb(lists[listIndex[left]][0]);
      multiply(result, sts[listIndex[left]].query(0, posIndex[left]+1));
      left = parent[lists[listIndex[left]][0]];
    }
    posInAncestorList = posIndex[left];
    return result;
  }
  void set(ll index, ll value) {
    sts[listIndex[index]].set(posIndex[index], value);
  }
};

inline int edgeToNode(ii edge) {
  return parent[edge.first] == edge.second ? edge.first : edge.second;
}

int main() {_
  ll N, M;
  cin >> N >> M;
  vii edgeIndexToValue(1, ii());

  Graph g(N, true);
  FOR(i, 0, N-1) {
    ll a, b, c;
    cin >> a >> b >> c;
    g.connect(a-1, Edge(b-1, c));
    edgeIndexToValue.pb(orderii(ii(a-1, b-1)));
  }

  HeavyLightDecomposition hld(g);  

  FOR(i, 0, M) {
    ll type;
    cin >> type;
    if (--type) {
      ll edgeIndex, val;
      cin >> edgeIndex >> val;
      hld.set(edgeToNode(edgeIndexToValue[edgeIndex]), val);
    } else {
      ll from, to, y;
      cin >> from >> to >> y;
      cout << y / (hld.query(from-1, to-1)) << endl;
    }
  }
}