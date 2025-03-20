#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

struct Node {
  ll value;
  int start, end;
  Node* left;
  Node* right;

  Node(int start, int end) : 
    start(start), end(end), value(0), left(nullptr), right(nullptr) {}
};

ll aggregate_function(ll left, ll right){
  return left + right;
}

Node* build(vector<ll> &arr, int l, int r){
  Node* node = new Node(l,r);
  if(l == r) {
    node->value = arr[l];
    return node;
  }

  int m = (l + r) / 2;
  node->left = build(arr, l, m);
  node->right = build(arr, m+1, r);
  node->value = aggregate_function(node->left->value, node->right->value);
  return node;
}

ll query(Node* root, int start, int end) {
  if(start > end) return 0;
  if(root->start == start && root->end == end)
    return root->value;

  int m = (root->start+root->end)/2;
  ll ans = aggregate_function(query(root->left,start,min(m,end)), query(root->right,max(m+1,start),end));
  return ans;
}

Node* update(Node* root, int pos, ll value) {
  Node* node = new Node(root->start, root->end);
  if(root->start == root->end) {
    node->value = value;
    return node;
  }
  int m = (root->start + root->end) / 2;
  if(pos <= m) {
    node->left = update(root->left, pos, value);
    node->right = root->right;
  } else {
    node->right = update(root->right, pos, value);
    node->left = root->left;
  }
  node->value = aggregate_function(node->left->value, node->right->value);
  return node;
}

void solve() {
  vector<ll> arr = {1,1,1,1,1,1};
  int n = arr.size();
  Node* root = build(arr,0,n-1);
  cout << query(root,0,n-1) << endl; // 6
  Node* mod1 = update(root,0,2);
  cout << query(mod1,0,n-1) << endl; // 7
  Node* mod2 = update(mod1,0,10);
  cout << query(mod2,0,n-1) << endl; // 15
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}
