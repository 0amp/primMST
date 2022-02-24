#include <iostream>
#include <time.h>
#include <vector>
#include <iterator>
#include <bits/stdc++.h>
#include <queue>

using namespace std;

void addEdge(vector <pair<float, int> > adj_list[], int u, int v, float w) {
    adj_list[u].push_back(make_pair(w, v));
    adj_list[v].push_back(make_pair(w, u));
}
  
void printGraph(vector<pair<float, int>> adj_list[], int N) {
    int v; 
    float w;
    for (int u = 0; u < N; u++) {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj_list[u].begin(); it!=adj_list[u].end(); it++) {
            v = it->second;
            w = it->first;
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
        cout << "\n";
    }
}

void printMST(pair<vector<int>, vector<int>> tree) {
  for (int i = 0; i<size(tree.first); i++) { 
    cout << i << ": " << tree.first[i] << "# \n";
  }
}

pair<vector<int>, vector<int>> primMST(vector<pair<float, int>> adj_list[], int N, int s) {
  //implementing Prim's Algorithm with binary heap

  //declare holding variables
  int v,w; 
  int remaining = N;
  vector<int> S;
  vector<bool> in_set;
  pair<float, int> tmp_pair;
  in_set.reserve(N);
  for (int i = 0; i < N; i++) {
    in_set.push_back(false);
  }

  //store cheapest cost of connection to each vertex
  vector<float> dist;
  dist.reserve(N);

  vector<int> prev; 
  prev.reserve(N);

  for (int i = 0; i<N; i++) {
    dist[i] = 2; 
    prev[i] = 0;
  }

  //create min heap 
  priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> min_heap;

  // initialize distance of source vertex and add to heap
  dist[s] = 0;
  tmp_pair = make_pair(0.0, s);
  min_heap.push(tmp_pair);
  
  // run through heap contents
  while (!min_heap.empty() && remaining != 0) {
    //cout << "size: " << size(min_heap) << "\n";
    v = min_heap.top().second; 
    min_heap.pop();
    S.push_back(v);
    remaining -= 1;
    in_set[v] = true;
    for (int i = 0; i < size(S); i++) {
      //cout << S[i] << ":" << prev[S[i]] << ":" << in_set[S[i]] << " # ";
    }
    //cout << "/" << v << "/\n";

    for (auto edge = adj_list[v].begin(); edge!=adj_list[v].end(); edge++) {
      if (in_set[edge->second] == false) {
        if (dist[edge->second] > edge->first) {
          dist[edge->second] = edge->first; 
          prev[edge->second] = v;
          tmp_pair = make_pair(edge->first, edge->second);
          min_heap.push(tmp_pair);
        }
      }
    }
  }

  return make_pair(S, prev);

}

pair<vector<int>, vector<int>> modifiedPrimMST(vector<pair<float, int>> adj_list[], int N, int s) {
  //implementing Prim's Algorithm with binary heap

  //declare holding variables
  int v,w; 
  int remaining = N;
  vector<int> S;
  vector<bool> in_set;
  pair<float, int> tmp_pair;
  in_set.reserve(N);
  for (int i = 0; i < N; i++) {
    in_set.push_back(false);
  }

  //store cheapest cost of connection to each vertex
  vector<float> dist;
  dist.reserve(N);

  vector<int> prev; 
  prev.reserve(N);

  for (int i = 0; i<N; i++) {
    dist[i] = 2; 
    prev[i] = 0;
  }

  //create min heap 
  priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> min_heap;

  // initialize distance of source vertex and add to heap
  dist[s] = 0;
  tmp_pair = make_pair(0.0, s);
  min_heap.push(tmp_pair);

  //apply optimization threshold k (currently >0.9)
  vector<pair<float, int>> adj[N];

  for (int i = 0; i<N; i++) {
    for (auto edge = adj_list[i].begin(); edge != adj_list[i].end(); edge++) {
      if (edge->first < 0.8) {
        adj[i].push_back(make_pair(edge->first, edge->second));
      }
    }
  }
  

  // run through heap contents
  while (!min_heap.empty() && remaining != 0) {
    //cout << "size: " << size(min_heap) << "\n";
    v = min_heap.top().second; 
    min_heap.pop();
    S.push_back(v);
    remaining -= 1;
    in_set[v] = true;
    for (int i = 0; i < size(S); i++) {
      //cout << S[i] << ":" << prev[S[i]] << ":" << in_set[S[i]] << " # ";
    }
    //cout << "/" << v << "/\n";

    for (auto edge = adj[v].begin(); edge!=adj[v].end(); edge++) {
      if (in_set[edge->second] == false) {
        if (dist[edge->second] > edge->first) {
          dist[edge->second] = edge->first; 
          prev[edge->second] = v;
          tmp_pair = make_pair(edge->first, edge->second);
          min_heap.push(tmp_pair);
        }
      }
    }
  }

  return make_pair(S, prev);

}

int main()
{
  srand(0);
  int N;
  cout << "Choose an N: "; 
  cin >> N;
  vector<pair<float, int>> adj_list[N];
  
  // initialize graph 1 with edge weights in (0,1)
  for (int i = 0; i<N; i++) {
    for (int j = i+1; j<N; j++) {
      float rN = ((float) rand())/RAND_MAX;
      addEdge(adj_list, i, j, rN);
    }
  }

  printGraph(adj_list, N);

  pair<vector<int>, vector<int>> tree;
  tree = primMST(adj_list, N, 0);

  printMST(tree);

  return 0;
}