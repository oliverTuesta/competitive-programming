// max flow algorithm

#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

const int INF = 1e9;

struct graph {
  typedef long long flow_type;
  struct edge {
    int src, dst;
    flow_type capacity, flow;
    size_t rev;
  };
  int n;
  vector<vector<edge>> adj;

  graph(int n) : n(n), adj(n) { }

  void add_edge(int src, int dst, flow_type capacity) {
    adj[src].push_back({src, dst, capacity, 0, adj[dst].size()});
    adj[dst].push_back({dst, src, 0, 0, adj[src].size() - 1});
  }

  int max_flow(int s, int t) {
    vector<bool> visited(n);
    function<flow_type(int, flow_type)> augment = [&](int u, flow_type cur) {
      if (u == t) return cur;
      visited[u] = true;
      for (auto &e : adj[u]) {
        if (!visited[e.dst] && e.capacity > e.flow) {
          flow_type f = augment(e.dst, min(e.capacity - e.flow, cur));
          if (f > 0) {
            e.flow += f;
            adj[e.dst][e.rev].flow -= f;
            return f;
          }
        }
      }
      return flow_type(0);
    };
    for (int u = 0; u < n; ++u)
      for (auto &e : adj[u]) e.flow = 0;

    flow_type flow = 0;
    while (1) {
      fill(all(visited), false);
      flow_type f = augment(s, INF);
      if (f == 0) break;
      flow += f;
    }
    return flow;
  }

  // test function to understand the code
  // Function to print the residual graph
  void print_residual_graph() {
    cout << "Residual Graph:" << endl;
    for (int u = 0; u < n; ++u) {
      for (const auto &e : adj[u]) {
        if (e.capacity > 0) {  // Ignore reverse edges with 0 original capacity
          cout << "Edge from " << e.src << " to " << e.dst
               << " | Capacity: " << e.capacity
               << " | Flow: " << e.flow
               << " | Residual Capacity: " << (e.capacity - e.flow) << endl;
        }
      }
    }
    cout << "------------------------" << endl;
  }

};

int main() {
  int n,m;
  cin >> n >> m;
  graph g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    g.add_edge(u, v, w);
  }
  cout << g.max_flow(0,n-1) << endl;
  g.print_residual_graph();
}
