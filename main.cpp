#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

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

int main() {
    int n;
    cin >> n;
    Triple zeo(n);

    vector<thread> threads;
    threads.reserve(3);

    threads.emplace_back([&zeo]() -> void { zeo.zero(); });
    threads.emplace_back([&zeo]() -> void { zeo.one(); });
    threads.emplace_back([&zeo]() -> void { zeo.two(); });
    threads.emplace_back([&zeo]() -> void { zeo.three(); });

    for (auto &thread:threads)
        thread.join();
}
