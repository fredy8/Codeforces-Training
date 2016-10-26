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

#define LC(a) ((a) == ((a)->parent->left))
template<typename K>
struct Treap {
	struct Node {
		void print(vector<K> &out) {
			if (left) left->print(out);
			out.pb(key);
			if (right) right->print(out);
		}
		K key;
		int priority;
		Node *left, *right, *parent;};
	Node *root = 0;
	Treap(Node *root = 0) : root(root) { srand(time(0)); }
	Treap(Treap<K> t1, Treap<K> t2) {
		if (!t1.root || !t2.root) { root = (t1.root ? t1 : t2).root; return; }
		insert(t2.find(t1.root->key, 1, t2.root)->key, -INF);
		Node *n = root;
		root->left = t1.root, root->right = t2.root;
		root->left->parent = root->right->parent = root;
		fixDown(root);
		(LC(n) ? n->parent->left : n->parent->right) = 0;
		delete n; }
	void fixDown(Node *n) {
		bool a, b;
		while((a = (n->left && n->priority < n->left->priority)) || (b = (n->right && n->priority < n->right->priority))) rotate(n, a && b ? rand()%2 : b); }
	Node *find(K key, bool leaf, Node *start, bool onlyLeft = 0) {
		if (!start) return 0;
		Node *n = start, *next;
		while((next = (key < n->key || onlyLeft ? n->left : n->right)) && (leaf || key != n->key)) n = next;
		return n; }
	void insert(K key, int priority = -1) {
		Node *p = find(key, 1, root), *n = new Node { key, priority == -1 ? rand()%100000 : priority , 0, 0, p };
		if (!root) { root = n; return; }
		(key < p->key ? p->left : p->right) = n;
		while(p && n->priority > p->priority) rotate(p, !LC(n)), p = n->parent; }
	void erase(K key) {
		if (!root) return;
		Node *n = find(key, 0, root), *del = n;
		if (!n || n->key != key) return;
		if (n->left && n->right) {
			del = find(key, 1, n->right, 1);
			n->key = del->key, n->priority = del->priority;
			fixDown(n); }
		if (del->left || del->right) (del->left ? del->left : del->right)->parent = del->parent;
		if (del->parent) (LC(del) ? del->parent->left : del->parent->right) = del->left ? del->left : del->right;
		else root = del->left ? del->left : del->right;
		delete del; }
	void rotate(Node *n, bool left) {
		Node *u = (left ? n->right : n->left), *p = n->parent;
		if (p) (LC(n) ? p->left : p->right) = u;
		else root = u;
		Node *c = left ? u->left : u->right;
		(left ? n->right : n->left) = c;
		if (c) (left ? u->left : u->right)->parent = n;
		(left ? u->left : u->right) = n;
		u->parent = p, n->parent = u; }
	pair<Treap<K>, Treap<K>> split(K key) {
		insert(key, INF);
		if (root->left) root->left->parent = 0;
		if (root->right) root->right->parent = 0;
		delete root;
		return mp(Treap<K>(root->left), Treap<K>(root->right)); }
	void print(vector<K> &out) { if (root) root->print(out); }
};


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

