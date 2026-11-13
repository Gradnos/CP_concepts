#include <vector>
using namespace std;
using ll = long long;
const ll INF = 4e18;

// All-pairs shortest paths. dist: n x n, INF for missing edges, 0 on diagonal.
// Handles negative edges (assuming no negative cycles).
void floydWarshall(vector<vector<ll>>& dist) {
    int n = (int)dist.size();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
