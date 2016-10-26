//656 A
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
typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int ALPHA = 26;

//Space <= (35+4*ALPHA)*N
struct SuffixTree {
	string T;
	vvi child;
	int N, K;
	vector<bool> isLeaf;
	vi parent, depth, tdepth, start;
	vvi child;
	SuffixTree(string &T): T(T) {	
		N = s.size();
		K = 1;
		child.assign(N * 2, vi());
		parent.assign(N * 2, -1);
		depth.assign(N * 2, 0);
		tdepth.assign(N * 2, 0);
		start.assign(N * 2, 0);
		isLeaf.assign(N, 0);
		int u = 0;
		int d = 0;
		for(int i = 0; i < N; i++) {
			while(d == depth[u] && child[u][T[i+d]-'a'] != -1) {
				u = child[u][T[i+d]-'a'];
				d++;
				while(d < depth[u] && T[start[u] + d] == T[i+d]) d++;
			}
			if (d < depth[u]) u = createNode(u, d);
			createLeaf(i, u, d);
			u = d = 0;
		}
	}
	int createNode(int u, int d) {
		int i = start[u];
		int p = parent[u];
		int v = K++;
		start[v] = i;
		depth[v] = d;
		child[v].assign(ALPHA, -1);
		child[v][T[i+d]-'a'] = u;
		parent[u] = v;
		child[p][T[i+depth[p]]-'a'] = v;
		parent[v] = p;
		return v;
	}
	void createLeaf(int i, int u, int d) {
		int w = K++;
		isLeaf[w] = 1;
		start[w] = i;
		depth[w] = n - i + 1;
		child[u][T[i+d]-'a'] = w;
		parent[w] = u;
	}
};

int main() { _
	string P = "atcgat";
	string T = "atgatcgatc";
	for(auto match: duels(P, T))
		cout << match << endl;
}

