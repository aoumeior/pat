#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
int main()
{
    int N, M, C1, C2;
    cin >> N >> M >> C1 >> C2;
    vector<int> teams(N, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> teams[i];
    }
    vector<vector<int>> g(N, vector<int>(N, INT_MAX));
    for (int i = 0; i < M; i++)
    {
        int a, b, l;
        cin >> a >> b >> l;
        g[a][b] = g[b][a] = l;
    }
    vector<int> dist(N, INT_MAX);
    vector<int> paths(N, 0);
    vector<int> maxTeam(N, 0);
    vector<bool> know(N, false);
    dist[C1] = 0;
    paths[C1] = 1;
    maxTeam[C1] = teams[C1];
    for (int i = 0; i < N; i++)
    {
        int curr = -1;
        int minDist = INT_MAX;
        for (int j = 0; j < N; j++)
        {
            if (!know[j] && minDist > dist[j])
            {
                curr = j;
                minDist = dist[j];
            }
        }
        know[curr] = true;
        for (int j = 0; j < N; j++)
        {
            if (!know[j] && g[curr][j] < INT_MAX && g[curr][j] + dist[curr] <= dist[j])
            {
                if (g[curr][j] + dist[curr] < dist[j])
                {
                    dist[j] = g[curr][j] + dist[curr];
                    paths[j] = paths[curr];
                    maxTeam[j] = teams[j] + maxTeam[curr];
                }
                else
                {
                    paths[j] += paths[curr];
                    maxTeam[j] = max(maxTeam[curr] + teams[j], maxTeam[j]);
                }
            }
        }
    }
    cout << paths[C2] << " " << maxTeam[C2];
    return 0;
}