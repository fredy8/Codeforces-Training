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




struct CartesianTree {
	typedef Treap<ii> tii;
	tii treap;
	CartesianTree(vi &values) {
		int N = values.size();
		vii order(N, ii());
		for(int i = 0; i < N; i++)
			order[i] = ii(values[i], i);
		sort(all(order));
		for(int i = 0; i < N; i++)
			treap.insert(ii(order[i].se, order[i].fi));
	}
	void insert(int pos, int val) {
		pair<tii, tii> ts = treap.split(ii(pos, 0));

	}
	void erase(int pos) {
		
	}
	void print(vi &out) {

	}
};

int main() { _
	Treap<ii> t;
	vector<ii> v1, v2;
	multiset<ii> m;

	FOR(i, 0, 1000000) {
		ii k = ii(rand()%100, rand()%100);
		if (rand()%2) {
			t.insert(k);
			m.insert(k);
		} else {
			if (m.find(k) != m.end()) {
				m.erase(m.find(k));
				t.erase(k);
			}
		}
		ii m = ii(rand()%100, rand()%100);
		pair<Treap<ii>, Treap<ii>> tp = t.split(m);
		t = Treap<ii>(tp.fi, tp.se);
	}

	for(auto i: m) v1.pb(i);
	t.print(v2);

	cout << (v1 == v2) << endl;
}

