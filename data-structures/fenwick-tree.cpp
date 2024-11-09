#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

int n, m;
int a[MAXN];
long long f[MAXN];
char q;
int l, r;

void update(int pos, int delta) {
  for (; pos <= n; pos = (pos | (pos + 1)))
    f[pos] += delta;
}

long long sum(int pos) {
  long long res = 0;
  for (; pos > 0; pos = (pos & (pos + 1)) - 1)
    res += f[pos];
  return res;
}

long long sum(int l, int r) {
  return sum(r) - sum(l - 1);
}

void solve() {

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    update(i, a[i]);
  }

  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> q >> l >> r;
    if (q == 's') {
      cout << sum(l, r) << " ";
    }
    else {
      int delta = r - a[l];
      a[l] = r;
      update(l, delta);
    } 
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}
