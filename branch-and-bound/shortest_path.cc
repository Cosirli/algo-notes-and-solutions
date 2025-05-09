#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <functional>  // For std::greater

const double INF = std::numeric_limits<double>::max();

using namespace std;

struct GraphNode {
    int i;
    int dist;

    GraphNode(int vertex, int distance) : i(vertex), dist(distance) {}

    // Comparator for min-heap
    bool operator>(const GraphNode& other) const { return dist > other.dist; }

    // bool operator<(const GraphNode& o) const { return path_len < o.path_len; }
    bool operator==(const GraphNode& o) const
    {
        return i == o.i && dist == o.dist;
    }
};

void dijkstra(int v, const std::vector<std::vector<double>>& graph,
              std::vector<double>& dist, std::vector<int>& prev) {
    using namespace std;

    int n = dist.size() - 1;
    prev.assign(n + 1, 0);
    dist.assign(n + 1, INF);
    dist[v] = 0;

    priority_queue<GraphNode, vector<GraphNode>, greater<GraphNode>> pq;
    pq.push(GraphNode(v, 0.0));

    for (;;) {
        GraphNode current = pq.top();
        pq.pop();
        int u = current.i, curr_dist = current.dist;
        if (curr_dist > dist[u])
            continue;
        for (int j = 1; j <= n; ++j) {
            // neighbors AND satifies bound()
            if (graph[u][j] < INF && curr_dist + graph[u][j] < dist[j]) {
                dist[j] = curr_dist + graph[u][j];
                pq.push(GraphNode(j, dist[j]));
            }
        }

        if (pq.empty()) break;
    }

    // Print the shortest distances
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) {
            cout << "Node " << i << " is unreachable from the source." << endl;
        } else {
            cout << "Shortest distance to node " << i << ": " << dist[i] << endl;
        }
    }
}

int main() {
    // Example graph represented as an adjacency list:
    // graph[u] = list of pairs (v, weight) for all edges u -> v with weight
    vector<vector<pair<int, int>>> graph = {
        {{1, 4}, {2, 1}},  // Node 0: edges to node 1 with weight 4, and node 2 with weight 1
        {{0, 4}, {2, 2}, {3, 5}},  // Node 1: edges to node 0, node 2, and node 3
        {{0, 1}, {1, 2}, {3, 8}},  // Node 2: edges to node 0, node 1, and node 3
        {{1, 5}, {2, 8}}   // Node 3: edges to node 1 and node 2
    };

    int start = 0;  // Starting node (0 in this case)
    dijkstra(graph, start);

    return 0;
}

