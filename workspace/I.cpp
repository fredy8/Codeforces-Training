//610 A
#include <bits/stdc++.h>
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

int op(int a, int b) {
	return a + b;
}

struct LazySegmentTree {
	vi t, d; int n, h;
	LazySegmentTree(vi &values) {
		n = values.size();
		h = sizeof(int) * 8 - __builtin_clz(n);
		t.assign(n<<1, 0), d.assign(n, 0);
		for(int i = 0; i < n; i++) t[i+n] = values[i];
		build(0, n);
	}
	void calc(int p, int k) {
		if (d[p] == 0) t[p] = t[p<<1] + t[p<<1|1];
		else t[p] = k - t[p<<1] - t[p<<1|1];
	}
	void apply(int p, int value, int k) {
		t[p] = k - t[p];
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
	void flip(int l, int r) {
		push(l, l + 1); push(r - 1, r);
		int l0 = l, r0 = r, k = 1;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
			if (l&1) apply(l++, 1, k);
			if (r&1) apply(--r, 1, k);
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

struct HeavyLightDecomposition {
	vector<LazySegmentTree> sts;
	vi whichList, posInList, treeSize, parent, listDepth;
	vvi lists;
	HeavyLightDecomposition(vvi &g, vi &values) {
		whichList = posInList = treeSize = parent = vi(g.size(), -1);
		getTreeSize(g, 0);
		makeLists(g, 0, -1, -1);
		for(auto &list: lists) {
			vi v;
			for(auto i: list) v.pb(values[i]);
			sts.pb(LazySegmentTree(v));
		}
	}
	int getTreeSize(vvi &g, int v) {
		treeSize[v] = 1;
		for(auto u: g[v]) if (u != parent[v])
			parent[u] = v, treeSize[v] += getTreeSize(g, u);
		return treeSize[v];
	}
	void makeLists(vvi &g, int v, int listIndex, int depth) {
		if(listIndex == -1) listIndex = lists.size(), lists.pb(vi()), listDepth.pb(++depth);
		whichList[v] = listIndex;
		posInList[v] = lists[listIndex].size();
		lists[listIndex].pb(v);
		int heavyChild = -1;
		for(auto u: g[v]) if (u != parent[v] && (heavyChild == -1 || treeSize[u] > treeSize[heavyChild]))
			heavyChild = u;
		for(auto u: g[v]) if (u != parent[v])
			makeLists(g, u, u == heavyChild ? listIndex : -1, depth);
	}
	int query(int l, int r) {
		if (listDepth[whichList[l]] < listDepth[whichList[r]]) swap(l, r);
		int ans = 0, lList;
		while(listDepth[lList = whichList[l]] > listDepth[whichList[r]])
			ans = op(ans, posInList[l] == 0 ? 0 : sts[lList].query(1, posInList[l])), l = parent[lists[lList][0]];
		while(whichList[l] != whichList[r]) {
			ans = op(ans, posInList[l] == 0 ? 0 : sts[whichList[l]].query(1, posInList[l]));
			ans = op(ans, posInList[r] == 0 ? 0 : sts[whichList[r]].query(1, posInList[r]));
			l = parent[lists[whichList[l]][0]], r = parent[lists[whichList[r]][0]];
		}
		if (posInList[l] < posInList[r]) swap(l, r);
		if (posInList[l] == posInList[r]) return ans;
		return op(ans, sts[whichList[l]].query(posInList[r] + 1, posInList[l]));
	}
	void flip(int l, int r) {
		if (listDepth[whichList[l]] < listDepth[whichList[r]]) swap(l, r);
		int lList;
		while(listDepth[lList = whichList[l]] > listDepth[whichList[r]]) {
			if(posInList[l]) sts[lList].flip(1, posInList[l]);
			l = parent[lists[lList][0]];
		}
		while(whichList[l] != whichList[r]) {
			if (posInList[l]) sts[whichList[l]].flip(1, posInList[l]);
			if (posInList[r]) sts[whichList[r]].flip(1, posInList[r]);
			l = parent[lists[whichList[l]][0]], r = parent[lists[whichList[r]][0]];
		}
		if (posInList[l] < posInList[r]) swap(l, r);
		if (posInList[l] == posInList[r]) return;
		sts[whichList[l]].flip(posInList[r] + 1, posInList[l]);
	}
};

int cycleSize = 1;

int dfs(vvi &g, int v, vi &visited, vi &parent, vi &cycle) {
	cout << v << endl;
	for(auto u: g[v]) if (parent[v] != u) {
		if (!visited[u]) {
			visited[u] = 1;
			parent[u] = v;
			int inCycle = dfs(g, u, visited, parent, cycle);
			if (inCycle == -2) return -2;
			if (inCycle != -1) {
				cycle[v] = cycleSize++;
				if (inCycle == v) {
					return -2;
				}
			}
		} else {
			cycle[v] = cycleSize++;
			return u;
		}
	}

	return -1;
}

int main() { _
	int N, M;
	cin >> N >> M;
	vvi g(N, vi());
	FOR(i, 0, N) {
		int a, b;
		cin >> a >> b;
		g[a - 1].pb(b-1);
		g[b - 1].pb(a-1);
	}

	vi visited(N, 0), parent(N, -1), inCycle(N, 0);
	visited[0] = 1;
	dfs(g, 0, visited, parent, inCycle);

	set<int> rootEdges;
	FOR(v, 0, N) if (inCycle[v])
		for(auto u: g[v]) if (!inCycle[u])
			rootEdges.insert(u);
	
	vvi tree(1, vi());
	map<int, int> gNodeToTNode;
	map<int, int> tNodeToGNode;
	FOR(i, 0, N)
		if (!inCycle[i]) {
			gNodeToTNode[i] = tree.size();
			tNodeToGNode[tree.size()] = i;
			tree.pb(vi());
		}
	
	for(auto u: rootEdges) {
		tree[0].pb(u);
		tree[u].pb(u);
	}

	FOR(i, 1, tree.size())
		for(auto u: g[tNodeToGNode[i]])
			tree[i].pb(u), tree[u].pb(i);
			cout << endl;
	
	map<int, int> gNodeToCNode;
	map<int, int> cNodeToGNode;

	HeavyLightDecomposition hld(tree);
	FOR(i, 0, M) {
		int a, b;
		cin >> a >> b;
		a--, b--;

		a = gNodeToTNode[a];
		b = gNodeToTNode[b];
		hld.flip(a, b);
		cout << N - hld.query(a, b) << endl;

		//if pasa por la root
	}
}
