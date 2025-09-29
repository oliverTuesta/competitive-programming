#include <bits/stdc++.h>
using namespace std;

#define endl '\n';

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

struct node {
  int value;
  int priority;
  node* left;
  node* right;
  int cnt;
  node(int v) : value(v) {
    priority = random(0, 1e9);
    left = right = nullptr;
    cnt = 1;  // FIX: initialize cnt
  }
};

int cnt(node* t) {
  return t ? t->cnt : 0;
}

void upd_cnt(node* t) {
  if (t) t->cnt = 1 + cnt(t->left) + cnt(t->right);
}

node* merge(node* a, node* b) {
  if (!a) return b;
  if (!b) return a;
  if (a->priority > b->priority) {
    a->right = merge(a->right, b);
    upd_cnt(a);
    return a;
  } else {
    b->left = merge(a, b->left);
    upd_cnt(b);
    return b;
  }
}

pair<node*, node*> split(node* T, int k, int add = 0) {
  if (!T) return {nullptr, nullptr};
  int cur_key = add + cnt(T->left);
  if (k <= cur_key) {
    auto p = split(T->left, k, add);
    T->left = p.second;
    upd_cnt(T);
    return {p.first, T};
  } else {
    auto p = split(T->right, k, add + 1 + cnt(T->left));
    T->right = p.first;
    upd_cnt(T);
    return {T, p.second};
  }
}

node* insert(node* T, int pos, int value) {
  auto p = split(T, pos);
  T = merge(p.first, new node(value));
  T = merge(T, p.second);
  return T;
}

node* remove(node* T, int pos) {
  auto p1 = split(T, pos);        // [0..pos-1], [pos..end]
  auto p2 = split(p1.second, 1);  // [pos], [pos+1..end]
                                  // delete p2.first; // optional, free memory
  return merge(p1.first, p2.second);
}

void inorder(node* T) {
  if (!T) return;
  inorder(T->left);
  cout << T->value << " ";
  inorder(T->right);
}

void solve() {
  node* root = nullptr;

  root = insert(root, 0, 10);
  root = insert(root, 1, 20);
  root = insert(root, 2, 30);
  cout << "Initial array: ";
  inorder(root); cout << "\n";

  root = insert(root, 1, 15);
  cout << "After inserting 15 at pos 1: ";
  inorder(root); cout << endl;

  root = remove(root, 2);
  cout << "After removing element at pos 2: ";
  inorder(root); cout << endl;
}

int main() {
  solve();
}

