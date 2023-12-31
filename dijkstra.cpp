// https://www.youtube.com/watch?v=7oUt0zhv2sA
// https://www.youtube.com/watch?v=J-7MzbEtTR0&list=PLGhUJWLZ8uQ4EWdQwVyUFnz82kbeGRP97&index=5

// Dijkstra algo
// Doesnt work with negative weights
// Can work with oriented and unoriented graphs
// Work with weighted graphs (note that BFS doesn't work with weighte graphs)

// INIT step: mark all edge to be infitinity (as those are not visited yet)
//            mark first (source) edge as 0
// ALGO: in each step get node with smallest value and update all unvisited neighbours
// Do this for each node

// O(V*V + e)

#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

// returns array with distances from given (start/source) node
vector<int> dijkstra(vector<vector<pair<int, int>>> &graph, int start) {
    vector<int> dist(graph.size(), INF); // contains distances from start to all nodes; infinity at the beginning
    dist[start] = 0;
    vector<bool> visited(graph.size()); //contains visited nodes (true/false)
    
    // main loop
    for (int i = 0; i < graph.size(); i++) {
        int nearest = -1;
        //find nearest unvisited node;
        // nearest means with smallest dist value
        for (int v = 0; v < graph.size(); v++) {
            if (!visited[v] && (nearest == -1 || dist[nearest] > dist[v])) {
                nearest = v;
            }
        }

        /*
        // extra situation when graph is disconnected        
        if (dist[nearest] == INF) {
            break;
        }*/
        
        visited[nearest] = true;
        
        // update all unvisited neighbours of given node
        
       // Works only from 17v
       /* for (auto &[to, weight] : graph[nearest]) {
            if (dist[to] > dist[nearest] + weight) {
                dist[to] = dist[nearest] + weight;
            }
        }*/
        for (auto &p : graph[nearest]) {
            int to = p.first;
            int weight = p.second;
            if (dist[to] > dist[nearest] + weight) {
                dist[to] = dist[nearest] + weight;
            }
        }
    }
    
    return dist;
}

vector<int> dijkstra_with_path(vector<vector<pair<int, int>>> &graph, int start) {
    vector<int> dist(graph.size(), INF); // contains distances from start to all nodes; infinity at the beginning
    dist[start] = 0;
    vector<int> from(graph.size(), -1);
    
    vector<bool> visited(graph.size()); //contains visited nodes (true/false)
    
    // main loop
    for (int i = 0; i < graph.size(); i++) {
        int nearest = -1;
        //find nearest unvisited node;
        // nearest means with smallest dist value
        for (int v = 0; v < graph.size(); v++) {
            if (!visited[v] && (nearest == -1 || dist[nearest] > dist[v])) {
                nearest = v;
            }
        }

        visited[nearest] = true;
        
        // update all unvisited neighbours of given node
        for (auto &p : graph[nearest]) {
            int to = p.first;
            int weight = p.second;
            if (dist[to] > dist[nearest] + weight) {
                dist[to] = dist[nearest] + weight;
                from[to] = nearest;
            }
        }
    }

    // all path from end to beginning
    vector<int> path;
    for (int v = finish; v != -1; v = from[v])
        path.push_back(v);
    reverse(path.begin(), path.en());
    
    return dist;
}

//NAV PABEIGTS
vector<int> dijkstra_improved(vector<vector<pair<int, int>>> &graph, int start) {
    vector<int> dist(graph.size(), INF); // contains distances from start to all nodes; infinity at the beginning
    dist[start] = 0;
    set<pair<int, int>> unvisitedVertices; //contains only unvisited vertices (distance to node and its number)
    for (int v = 0; v < graph.size(); v++) {
        unvisitedVertices.insert({dist[v], v});
    }

    // main loop
    for (int i = 0; i < graph.size(); i++) {
        int nearest = unvisitedVertices.begin()->second;
        
        // find nearest unvisited node;
        // nearest means with smallest dist value
        unvisitedVertices.erase(unvisitedVertices.begin());

        for (auto &p : graph[nearest]) {
            int to = p.first;
            int weight = p.second;
            if (dist[to] > dist[nearest] + weight) {
                unvisitedVertices.erase({dist[to], to});
                dist[to] = dist[nearest] + weight;
                unvisitedVertices.insert({dist[to], to});                
            }
        }
    }
    
    return dist;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;
    
    vector<vector<pair<int, int>>> graph(vertexCount);
    for (int i = 0; i < edgeCount; i++) {
        int a,b,weight;
        cin >> a >> b >> weight;
        
        graph[a].push_back({b, weight});
        graph[b].push_back({a, weight}); // not needed for oriented graph, only for non-oriented
    }
    
    int start; //source node
    cin >> start;
    
    // cout << start;
    
    vector <int> dist = dijkstra(graph, start);
    
    for (int d: dist) {
        if (d != INF) {
            cout << d << " ";
        } else {
            cout << "X ";
        }
    }
    
    return 0;
}
