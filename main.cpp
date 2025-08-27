#include "LRUCache.cpp"
using namespace std;

int main() {
    LRUCache cache(2);

    cache.put(1, 100);
    cache.put(2, 200);
    cout << cache.get(1) << endl; // 100

    cache.put(3, 300); // removes key 2
    cout << cache.get(2) << endl; // -1

    cache.put(4, 400); // removes key 1
    cout << cache.get(1) << endl; // -1
    cout << cache.get(3) << endl; // 300
    cout << cache.get(4) << endl; // 400

    return 0;
}
