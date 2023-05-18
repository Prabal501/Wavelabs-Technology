#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void distance(int node, int parent, int& time, vector<vector<int>>& graph, vector<int>& discovery, vector<int>& low, vector<vector<int>>& criticalConnections) {
    discovery[node] = time;
    low[node] = time;
    time++;

    for (int neighbor : graph[node]) {
        if (neighbor == parent)
            continue;

        if (discovery[neighbor] == -1) {
            distance(neighbor, node, time, graph, discovery, low, criticalConnections);
            low[node] = min(low[node], low[neighbor]);
            if (low[neighbor] > discovery[node])
                criticalConnections.push_back({node, neighbor});
        }
        else {
            low[node] = min(low[node], discovery[neighbor]);
        }
    }
}

vector<vector<int>> findCriticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph(n);
    for (const auto& connection : connections) {
        int u = connection[0];
        int v = connection[1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> discovery(n, -1);
    vector<int> low(n, -1);
    vector<vector<int>> criticalConnections;
    int time = 0;

    distance(0, -1, time, graph, discovery, low, criticalConnections);

    return criticalConnections;
}

int main() {
    int n ;
    vector<vector<int>> connections ;

    cin >> n;

    for(int i = 0; i < n; i++ )
    {
       vector<int> temp(2 , 0);
        for(int j = 0; j < 2; j++)
        {
               cin >> temp[ j ];
        }

        connections.push_back(temp);

        temp.clear();
    }

    vector<vector<int>> criticalConnections = findCriticalConnections(n, connections);

    for (const auto& connection : criticalConnections) {
        cout << connection[0] <<" , " << connection[1] << endl;
    }

    return 0;
}
