#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <cstdio>

using namespace std;

class Vertex;
class Edge;

class Vertex {
public:
  vector<Edge> edges;
};

class Edge {
public:
  long A;
  long B;
  long cost;

  friend bool operator<(const Edge& a, const Edge& b) {
    return a.cost > b.cost;
  }
};

long N;
Vertex V[1000000]; // 1e6
long M;
Edge E[1000000]; // 1e6

bool In[1000000]; // 1e6

// officially add the vertex to the main component
void add_vertex(priority_queue<Edge>& eheap, long vi) {
  In[vi] = true;
  for (auto ep = V[vi].edges.begin(); ep != V[vi].edges.end(); ep++) {
    if (In[ep->A] && In[ep->B])
      continue;

    eheap.push(*ep);
  }
}

void production() {
  cin >> N;
  cin >> M;

  Edge min_edge = Edge();
  min_edge.cost = 2000000000;

  for (long i=0; i<M; i++) {
    Edge& e = E[i];
    scanf("%ld %ld %ld", &e.A, &e.B, &e.cost);

    V[e.A].edges.push_back(e);
    V[e.B].edges.push_back(e);

    if (e.cost < min_edge.cost)
      min_edge = e;
  }

  priority_queue<Edge> eheap;
  add_vertex(eheap, min_edge.A);
  add_vertex(eheap, min_edge.B);

  long max_edge_cost = min_edge.cost;

  // flood
  while (!eheap.empty()) {
    min_edge = eheap.top(); eheap.pop();
    long A = min_edge.A;
    long B = min_edge.B;

    // throw out an edge if covered already
    if (In[A] && In[B])
      continue;

    long vi_new = In[A] ? B : A;
    add_vertex(eheap, vi_new);
    max_edge_cost = max(min_edge.cost, max_edge_cost);
  }

  // quick scan to see if we got everything;
  for (long i=0; i<N; i++) {
    if (!In[i]) {
      cout << "IMPOSSIBLE" << endl;
      return;
    }
  }

  // otherwise, we covered everything we minimal cost
  cout << max_edge_cost << endl;
  return;
}

int main() {
  production();
  return 0;
}
