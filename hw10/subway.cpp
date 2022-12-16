#include "subway.h"

Station::Station(int n)
{
    this->num = n;
    adj = new vector<pair<int, int> >[n];
}

void Station::insertEdge(int u, int v, int w)
{
    this->adj[u].push_back(make_pair(v, w));
    this->adj[v].push_back(make_pair(u, w));
}

vector<int> Station::dijkstra(int start)
{
    vector<bool> found(this->num, false);
    vector<int> distance(this->num, MAX);
    vector<int> from(this->num);

    priority_queue<pair<int, int>, vector<pair<int, int> >, Compare> pq;

    found[start] = true;
    distance[start] = 0;
    pq.push(make_pair(start, 0));

    while(!pq.empty()) {
        int u = pq.top().first;
        pq.pop();
        found[u] = true;

        for (int j = 0; j < (this->adj[u]).size(); j++) {
            pair<int, int> v = this->adj[u][j];
            if (!found[v.first]) {
                if (distance[u] + v.second < distance[v.first]) {
                    distance[v.first] = distance[u] + v.second;
                    from[v.first] = u;
                    pq.push(make_pair(v.first, distance[v.first]));
                }
            }
        }
    }
    return from;
}

void Station::path(int start, int end, vector<int> from)
{
    if (from[end] == start) {
        // cout << start << endl;
        pathId.push_back(start);
        return;
    }

    path(start, from[end], from); // 출발역 ~
    pathId.push_back(from[end]);
}