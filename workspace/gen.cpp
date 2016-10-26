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
#define aint(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<int, int> ii; typedef vector<int> vi; typedef vector<ii> vii; typedef vector<vi> vvi;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
	srand(time(NULL));
	int N = 2000;
	cout << N << endl;
	FOR(i, 0, N) {
		cout << rand()%10000 + 1 << " ";
	}
	cout << endl;

	FOR(i, 1, N) {
		cout << i << " " << rand()%i << endl;
	}

	int Q = 2000;
	cout << Q << endl;
	FOR(i, 0, Q) {
		if (rand()%2) {
			cout << 1 << " " << rand()%N << " " << rand()%N << endl;
		} else {
			cout << 2 << " " << rand()%N << " " << rand()%10000 + 1 << endl;
		}
	}
}
