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
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

struct MaxBipartiteMatching {
	int L, R;
	vvi edgesL;
	vi visitedL, matchR, matchL, inCoverL, inCoverR;
	MaxBipartiteMatching(int L, int R) : L(L), R(R) { edgesL.assign(L, vi()); }
	void addEdge(int l, int r) { edgesL[l].pb(r); }
	bool augment(int l) {
		if (visitedL[l]) return 0;
		visitedL[l] = 1;
		for (auto r: edgesL[l])
			if (matchR[r] == -1 || augment(matchR[r])) { matchR[r] = l; return 1; }
		return 0;
	}
	int maxMatching() {
		int ans = 0;
		matchR.assign(R, -1), matchL.assign(L, -1);
		for(int i = 0; i < L; i++)
			visitedL.assign(L, 0), ans += augment(i);
		for(int i = 0; i < R; i++) if (matchR[i] != -1) matchL[matchR[i]] = i;
		return ans;
	}
	void augment2(int l) {
		if (l == -1 || !inCoverL[l]) return;
		inCoverL[l] = 0;
		for (auto r: edgesL[l])
			if (!inCoverR[r]) inCoverR[r] = 1, augment2(matchR[r]);
	}
	void minCover() { // assuming matching found
		inCoverL.assign(L, 1), inCoverR.assign(R, 0);
		for(int i = 0; i < L; i++)
			if (matchL[i] == -1) augment2(i);
	}
};

int main() {
	int N, M;
	while (cin >> N >> M) {
		string arr[N];
		FOR(i, 0, N) cin >> arr[i];

		vvi posToNodeL(N, vi(M, 0)), posToNodeR(N, vi(M, 0));
		map<int, vii> nodeToPosL, nodeToPosR;
		int L = 0, R = 0;
		FOR(i, 0, N)
			FOR(j, 0, M)
				if (arr[i][j] == '*') {
					if ((j == 0 || arr[i][j] != arr[i][j-1])) L++;
					posToNodeL[i][j] = L-1;
					nodeToPosL[L-1].eb(i, j);
				}

		FOR(j, 0, M)
			FOR(i, 0, N)
				if (arr[i][j] == '*') {
					if (i == 0 || arr[i][j] != arr[i-1][j]) R++;
					posToNodeR[i][j] = R-1;
					nodeToPosR[R-1].eb(i, j);
				}

		MaxBipartiteMatching MBM(L, R);
		for(auto &lntp: nodeToPosL)
			for(auto pos: lntp.se)
				MBM.addEdge(lntp.fi, posToNodeR[pos.fi][pos.se]);

		for(auto &rntp: nodeToPosR)
			for(auto pos: rntp.se)
				MBM.addEdge(posToNodeL[pos.fi][pos.se], rntp.fi);

		cout << MBM.maxMatching() << endl;
		MBM.minCover();

		FOR(i, 0, R) if (MBM.inCoverR[i])
			cout << "vline " << nodeToPosR[i][0].se+1 << " " << nodeToPosR[i][0].fi+1 << " " << nodeToPosR[i].back().fi+1 << endl;
		FOR(i, 0, L) if (MBM.inCoverL[i])
			cout << "hline " << nodeToPosL[i][0].fi+1 << " " << nodeToPosL[i][0].se+1 << " " << nodeToPosL[i].back().se+1 << endl;
	}
}
