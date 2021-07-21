//
// Created by N on 2021/5/6.
//

//PREPEND BEGIN
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <pthread.h>

using namespace std;
//PREPEND END

//TEMPLATE BEGIN
class Triple {
private:
    int n;
    mutex z, o, t, tr;

public:
    explicit Triple(int n) {
        this->n = n;
        o.lock();
        t.lock();
        tr.lock();
    }

    void zero() {
        for (int i = 1; i <= n; ++i) {
            z.lock();
            cout << 0;
            if (i % 3 == 0)
                tr.unlock();
            else if (i % 3 == 1)
                o.unlock();
            else
                t.unlock();
        }
    }

    void one() {
        for (int i = 1; i <= n; i += 3) {
            o.lock();
            cout << i;
            z.unlock();
        }
    }

    void two() {
        for (int i = 2; i <= n; i += 3) {
            t.lock();
            cout << i;
            z.unlock();
        }
    }

    void three() {
        for (int i = 3; i <= n; i += 3) {
            tr.lock();
            cout << i;
            z.unlock();
        }
    }

};
//TEMPLATE END

//APPEND BEGIN


int main() {
    int n;
    cin >> n;
    Triple t(n);

    vector<thread> threads;
    threads.reserve(4);

    threads.emplace_back([&]() -> void { t.zero(); });
    threads.emplace_back([&]() -> void { t.one(); });
    threads.emplace_back([&]() -> void { t.two(); });
    threads.emplace_back([&]() -> void { t.three(); });

    for (auto &thread:threads)
        thread.join();
}