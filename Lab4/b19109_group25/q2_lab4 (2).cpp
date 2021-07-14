/*
Author- S Samarth Reddy (b19109) Group 25
    Insert all the input first . Then the output is printed.
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long int
struct Node {
	int left, right;  // stores index of left and right child
	ll min, Lazy;  // stores the minimum of all the values in the range
	ll get() { return min - Lazy; }
};
typedef struct Node Node;
vector<Node> ST;   // Segment tree
vector<ll> A;
int N, Q;

void build(int curr, int n_l, int n_r)
{
	static int k = 0;
	if (n_l == n_r) { ST[curr].min = A[n_l]; return; }
	int mid = n_l + ((n_r - n_l) >> 1);
	build(ST[curr].left = ++k, n_l, mid);
	build(ST[curr].right = ++k, mid + 1, n_r);
	ST[curr].min = min(ST[ST[curr].left].min, ST[ST[curr].right].min);
}

void update(int curr, int n_l, int n_r, int l, int r, int v)
{
	if (l > r)return;
	if (n_l == l && r == n_r) { ST[curr].Lazy += v; return; }
	int mid = n_l + ((n_r - n_l) >> 1);
	if (r <= mid)update(ST[curr].left, n_l, mid, l, r, v);
	else if (mid < l)update(ST[curr].right, mid + 1, n_r, l, r, v);
	else {
		update(ST[curr].left, n_l, mid, l, mid, v);
		update(ST[curr].right, mid + 1, n_r, mid + 1, r, v);
	}
	ST[curr].min = min({ ST[ST[curr].left].get(), ST[ST[curr].right].get(), ST[curr].min });
}

int leftmostless(int curr, int n_l, int n_r, ll v, ll Lazy)
{
	if (n_l == n_r) { return n_l-1; }
	int mid = n_l + ((n_r - n_l) >> 1);
	if (ST[ST[curr].left].get() - Lazy < v)return leftmostless(ST[curr].left, n_l, mid, v, Lazy + ST[ST[curr].left].Lazy);
	return leftmostless(ST[curr].right, mid+1, n_r, v, Lazy + ST[ST[curr].right].Lazy);
}

int leftmostless(int v) {
	if (v <= ST[0].get())return -1;
	return leftmostless(0, 1, N, v, ST[0].Lazy);
}

void Query()
{
	while (Q--)
	{
		int t; cin >> t;
		if (t == 1) {
			int l, r, v; cin >> l >> r >> v;
			update(0, 1, N, ++l, ++r, v);
		}
		else {
			int v; cin >> v;
			cout << leftmostless(v) << "\n";
		}
	}
}
void print(int curr, int n_l, int n_r, ll Lazy)
{
	if (n_l == n_r) { cout<<ST[curr].get()-Lazy<<" "; return; }
	int mid = n_l + ((n_r - n_l) >> 1);
	print(ST[curr].left, n_l, mid, Lazy + ST[curr].Lazy);
	print(ST[curr].right, mid + 1, n_r, Lazy + ST[curr].Lazy);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> N >> Q;
	ST.resize(N << 1); A.resize(N + 1);
	for (int i = 1; i <= N; i++)cin >> A[i];
	build(0, 1, N);
	Query();
	return 0;
}
