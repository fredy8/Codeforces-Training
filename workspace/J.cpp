//610 A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0), cout.precision(15);
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(decltype((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define RFORC(cont, it) for(decltype((cont).rbegin()) it=(cont).rbegin(); it!=(cont).rend(); it++)
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define mt make_tuple
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef sii set<ii>;

struct LazySegmentTree {
  vvi t, d, P, d2; int n, h;
  LazySegmentTree(vi &values) {
    n = values.size();
    h = sizeof(int) * 8 - __builtin_clz(n);
    t.assign(n<<1, vii(1, (0, 0))), d.assign(n, vii(1, (0, 0)));
    for(int i = 0; i < N; i++) t[i+N].back().se = values[i];
    build(i+N, n<<1);
  }
  void calc(int p, int k, int when) {
	int pastTime = *(--upper_bound(P[p].begin(), P[p].end(), when));
	int lazyVal = d[p][pastTime];
	int treeVal = t[p][pastTime];
	int lazyVal2 = d2[p][pastTime];

	if (lazyVal == 0) {
		t[p] = t[p<<1][pastTime] + t[p<<1|1][pastTime];
	} else if (lazyVal == 1) {
		t[p] = k - t[p<<1][pastTime] + t[p<<1|1][pastTime];
	} else if (lazyVal == 2) {
		t[p] = k;
	} else if (lazyVal ==  {
		t[p] = 0;
	} else {

	}
	
    if (d[p].back() == 0) t[p] = t[p<<1].back().se + t[p<<1|1].back().se;
	else if (dp[p] == 
    else t[p] = d[p] * k;
  }
  void apply(int p, int value, int k) {
    t[p] = value * k;
    if (p < n) d[p] = value;
  }
  void push(int l, int r) {
    int s = h, k = 1 << (h-1);
    for (l += n, r += n-1; s > 0; --s, k >>= 1)
      for (int i = l >> s; i <= r >> s; ++i) if (d[i]) {
        apply(i<<1, d[i], k);
        apply(i<<1|1, d[i], k);
        d[i] = 0;
      }
  }
  void build(int l, int r) {
    int k = 2;
    for (l += n, r += n-1; l; k <<= 1) {
      l >>= 1, r >>= 1;
      for (int i = r; i >= l; --i) calc(i, k);
    }
  }
  void modify(int l, int r, int value) {
    if (value == 0) return;
    push(l, l + 1); push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l&1) apply(l++, value, k);
      if (r&1) apply(--r, value, k);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
  }
  int query(int l, int r) {
    push(l, l + 1); push(r - 1, r);
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1) res += t[l++];
      if (r&1) res += t[--r];
    }
    return res;
  }
};

int main() { _
	
}
