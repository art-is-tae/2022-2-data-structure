#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <math.h>

#include "subway.h"
using namespace std;

int main(int argc, char *argv[]) {
    int num;
    int startLine, endLine;
    string startStation, endStation;

    int srcLine, dstLine;
    string srcStation, dstStation;

    if (argc != 3) {
        cerr << "Argument Count is" << argc << endl << "Argument must be" << argc << endl;
        return 1;
    }

    fstream fin(argv[1]);

    if (!fin) {
        cerr << argv[1] << "open failed" << endl;
        return 1;
    }

    // statins.txt
    fin >> num;

    map<int, pair<int, string> > startMap;
    map<int, pair<int, string> > endMap;
    map<pair<int, string>, int > idMap;

    int startId[num];
    int endId[num];
    double costArr[num];

    for (int i = 0; i < num; i++) {
        startId[i] = -1;
        endId[i] = -1;
    }

    // input
    for (int i = 0; i < num; i++)
    {
        fin >> startLine >> startStation >> endLine >> endStation;

        startMap[i] = (pair<int, string>(startLine, startStation));
        endMap[i] = (pair<int, string>(endLine, endStation));
    }

    // set ID map
    int id = 0;
    for (int i = 0; i < num; i++) {
        int tmp1 = startMap[i].first;
        string tmp2 = startMap[i].second;
        
        for (int j = 0; j < num; j++) {
            if ((startMap[j].first == tmp1 && startMap[j].second == tmp2) && startId[j] == -1) {
                startId[j] = id;
                // cout << id << ": " << tmp1 << " " << tmp2 << endl;
            }
            if ((endMap[j].first == tmp1 && endMap[j].second == tmp2) && endId[j] == -1) {
                endId[j] = id;
                // cout << id << ": " << tmp1 << " " << tmp2 << endl;
            }
        }
        id += 1;
    }
    for (int i = 0; i < num; i++) {
        if (endId[i] == -1) {
            for (int j = 0; j < num; j++) {
                if (startMap[j].first == endMap[i].first && startMap[j].second == endMap[i].second) {
                    // cout << j << endl;
                }
                else {
                    endId[i] = id;
                    id += 1;
                    // cout << id << ": " << startMap[j].first << " " << startMap[j].second << endl;
                    break;
                }
            }
        }
    }

    // cost
    for (int i = 0; i < num; i++) {
        if (startMap[i].first == endMap[i].first && startMap[i].second != endMap[i].second) {
            costArr[i] = 1.0;
        }
        else if (startMap[i].first != endMap[i].first && startMap[i].second == endMap[i].second) { // transfer
            costArr[i] = 0.5;
        } else {
            costArr[i] = 0.0;
        }
    }
    fin.close();

    Station* s = new Station(num*2);
    for (int i = 0; i < num; i++) {
        s->insertEdge(startId[i], endId[i], costArr[i]);
        s->insertEdge(endId[i], startId[i], costArr[i]);
        // cout << startId[i] << " " << endId[i] << " " << costArr[i] << endl;
    }

    // input.txt
    fstream fin2(argv[2]);

    if (!fin2) {
        cerr << argv[2] << " open failed" << endl;
        return 1;
    }
    
    fin2 >> srcLine >> srcStation;
    fin2 >> dstLine >> dstStation;
    

    //결과 출력

    // 1. 출발 & 도착 ID 변환
    int srcId = -1;
    int dstId = -1;
    for (int i=0; i<num; i++) {
        if ((startMap[i].first == srcLine && startMap[i].second == srcStation) || (endMap[i].first == srcLine && endMap[i].second == srcStation)) {
            srcId = startId[i]; // 56
            break;
        }
            
    }
    for (int i=0; i<num; i++) {
        if ((startMap[i].first == dstLine && startMap[i].second == dstStation) || (endMap[i].first == dstLine && endMap[i].second == dstStation)) {
            dstId = endId[i]; // 55
            break;
        }
    }

    fin2.close();

    // 2. 다익스트라 알고리즘 호출 및 pathId에 결과 입력
    vector<int> from = s->dijkstra(srcId);
    double pathCostAll = 0;
    s->path(srcId, dstId, from);
    s->pathId.push_back(dstId); // 도착역 입력

    // 최종 출력
    string pathName[s->pathId.size()];
    vector <string> resPath;
    double pathCostArr[s->pathId.size()];

    for (int i = 0; i < s->pathId.size(); i++) {
        pathName[i] = " ";
        pathName[i] = startMap[s->pathId.at(i)].second;
    }
    for (int i = 0; i < s->pathId.size(); i++) {
        if (pathName[i] == " ")
            pathName[i] = endMap[s->pathId.at(i)].second;
    }

    for (int i = 0; i < s->pathId.size(); i++) {
        resPath.push_back(pathName[i]);
    }
    resPath.erase(unique(resPath.begin(), resPath.end()), resPath.end()); // 중복 제거

    for (int i = 1; i < s->pathId.size(); i++) {
        pathCostAll += costArr[s->pathId.at(i) - 1];
    }

    for (int i = 0; i < resPath.size(); i++) { // 최종 역 출력
        cout << resPath.at(i) << endl;
    }

    // 중점
    string center = resPath.at(resPath.size()/2);
    
    // 시간
    for (int i = 0; i < s->pathId.size(); i++) {
        pathCostArr[i] = costArr[s->pathId.at(i) - 1]; // costArr
    }

    double costA = 0;
    double costB = 0;
    double costAll = 0;
    bool costFlag = false;

    for (int i = 1; i < s->pathId.size(); i++) { // 출발역 시간 고려 x
        pathCostArr[i] = costArr[s->pathId.at(i) - 1]; // costArr
        // cout << pathCostArr[i] << endl;

        if (costFlag == false) { // A
            costA += pathCostArr[i];
        } else { // B
            costB += pathCostArr[i];
        }

        if (pathName[i] == center) {
            costFlag = true;
        }
    }

    for (int i = 1; i < s->pathId.size(); i++)
        costAll += pathCostArr[i];

    double tmp;
    if (costA < costB) { // 큰 값 먼저 출력
        tmp = costA;
        costA = costB;
        costB = tmp;
    }

    cout << endl;
    // 총 시간 출력
    cout << int(costAll*10) / 10;
    if (int(costAll*10) % 10 == 5) {
        cout << ":30" << endl;
    } else {
        cout << ":00" << endl;
    }

    // 중점 출력
    cout << center << endl;

    // A의 시간 출력
    cout << int(costA*10) / 10;
    if (int(costA*10) % 10 == 5) {
        cout << ":30" << endl;
    } else {
        cout << ":00" << endl;
    }

    // A의 시간 출력
    cout << int(costB*10) / 10;
    if (int(costB*10) % 10 == 5) {
        cout << ":30" << endl;
    } else {
        cout << ":00" << endl;
    }




    delete s;
    return 0;
}