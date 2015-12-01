#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0), cin.tie(0), cin.tie(0), cout.tie(0), cout.precision(15);
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(decltype((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define RFORC(cont, it) for(decltype((cont).rbegin()) it=(cont).rbegin(); it!=(cont).rend(); it++)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

const int MAXN = 200000;
ll N, B;

int main() { _
    while(cin >> N >> B)
     {
        ll a = 0, b = 0;
        int k;
        FOR(i, 0, N) {
            a *= B;  
            cin >> k;
            a += k;
        }






        cin >> N >> B;
        FOR(i, 0, N) {

            b *= B;
            



            cin >> k;
             b += k;
        }

        cout << (a == b ? '=' : a < b ? '<' : '>') << endl;
    }
} 
