//
// Created by N on 2021/5/14.
//
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

//class HashTable {
//private:
//    vector<list<pair<int, int>>> data;
//    static const int base = 769;
//    static int hash(int key) {
//        return key % base;
//    }
//public:
//    /** Initialize your data structure here. */
//    HashTable(): data(base) {}
//
//    /** value will always be non-negative. */
//    void put(int key, int value) {
//        int h = hash(key);
//        for (auto it = data[h].begin(); it != data[h].end(); it++) {
//            if ((*it).first == key) {
//                (*it).second = value;
//                return;
//            }
//        }
//        data[h].push_back(make_pair(key, value));
//    }
//
//    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
//    int get(int key) {
//        int h = hash(key);
//        for (auto it = data[h].begin(); it != data[h].end(); it++) {
//            if ((*it).first == key) {
//                return (*it).second;
//            }
//        }
//        return -1;
//    }
//
//    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
//    void remove(int key) {
//        int h = hash(key);
//        for (auto it = data[h].begin(); it != data[h].end(); it++) {
//            if ((*it).first == key) {
//                data[h].erase(it);
//                return;
//            }
//        }
//    }
//};
/*
 * 输入一个无向图的所有边,以vector<vector<int>>表示,而边用长度为2的vector<int>表示,包含其两端顶点的编号.
 * 该图有n个节点和n个边,顶点编号从1到n. 它由一棵树以及一条附加的边组成.
 * 该附加边的两端点是点1到点n中的点,且两端点不相同,也不是树中已经存在的边.
 * 返回一条可以从图中删掉的边,用长度为2的vector<int>表示,使得该图成为一棵树.
 * 请完成findRedundantConnection函数的编写.
 * 示例:
 */
void print_vec(const vector<int> &p) {
    for (auto &i:p)
        cout << i << ' ';
    cout << endl;
}

int Find(vector<int> &parent, int node) {
    while (parent[node] != node)
        node = parent[node];
    return node;
}

void Union(vector<int> &parent, int pnode1, int pnode2) {
    parent[pnode1] = pnode2;
}

vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    int nodesCount = edges.size();
    vector<int> parent(nodesCount + 1);
    int pnode1, pnode2;

    for (int i = 1; i <= nodesCount; ++i) {
        parent[i] = i;
    }

    for (auto &edge: edges) {
        pnode1 = Find(parent, edge[0]);
        pnode2 = Find(parent, edge[1]);
        if (pnode1 != pnode2) {
            Union(parent, pnode1, pnode2);
        } else return edge;
    }
    return vector<int>{};
}


int main() {
    /*
     * 1 - 2 - 3
     *     |   |
     *     5 - 4
     */
    vector<vector<int>> edges = {{1, 2},
                                 {2, 3},
                                 {2, 5},
                                 {4, 5},
                                 {3, 4}};
    vector<int> edge = findRedundantConnection(edges);
    print_vec(edge);
} // 应当输出3 4

