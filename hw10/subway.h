#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>

#define MAX 99999

using namespace std;

class Station {
public:
    int num; // 개수
    vector<pair<int, int> >* adj; // first: node, second: cost
    vector<int> pathId; // 최단경로의 id

    Station(int n); // 생성자
    void insertEdge(int u, int v, int w); // 간선 추가
    vector<int> dijkstra(int start); // 다익스트라 함수
    void path(int start, int end, vector<int> from); // pathId에 삽입
};

class Compare { // 우선순위 큐의 비교 연산자
public:
    bool operator() (pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};
