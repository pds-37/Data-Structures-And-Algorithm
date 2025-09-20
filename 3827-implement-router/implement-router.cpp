#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n = 0;            // number of used elements
    int cap = 0;          // capacity of bit array
    vector<int> arr;      // 0-based raw counts, size == n
    vector<int> bit;      // 1-based BIT, size == cap+1 (bit[0] unused)

    Fenwick() { n = 0; cap = 0; bit.assign(1, 0); }

    // Ensure internal capacity >= idx. If capacity grows we rebuild bit (amortized).
    void ensure_capacity(int idx) {
        if (idx <= cap) return;
        int newcap = max(1, cap);
        while (newcap < idx) newcap *= 2;
        vector<int> newbit(newcap + 1, 0);
        // copy existing raw values into newbit and build the BIT partial sums
        for (int i = 1; i <= n; ++i) newbit[i] = arr[i - 1];
        for (int i = 1; i <= n; ++i) {
            int j = i + (i & -i);
            if (j <= newcap) newbit[j] += newbit[i];
        }
        bit.swap(newbit);
        cap = newcap;
    }

    // idx is 1-based
    void add(int idx, int val) {
        if (idx <= 0) return;
        ensure_capacity(idx);
        if (idx > n) {
            arr.resize(idx, 0);
            n = idx;
        }
        arr[idx - 1] += val;
        for (int i = idx; i <= cap; i += i & -i) bit[i] += val;
    }

    int sumPrefix(int idx) {
        if (idx <= 0) return 0;
        if (idx > n) idx = n;
        int res = 0;
        for (int i = idx; i > 0; i -= i & -i) res += bit[i];
        return res;
    }

    int rangeSum(int l, int r) {
        if (r < l) return 0;
        return sumPrefix(r) - sumPrefix(l - 1);
    }
};

class Router {
    int memoryLimit;

    struct Packet {
        int s, d, t;
        int idx; // 1-based index in dest_ts[d]
    };

    deque<Packet> q;
    unordered_set<string> seen; // current packets in router, simple textual key
    unordered_map<int, vector<int>> dest_ts; // destination -> append-only timestamps
    unordered_map<int, Fenwick> dest_bit;    // destination -> Fenwick (aligned to dest_ts indices)

    static string keyOf(int s, int d, int t) {
        return to_string(s) + "#" + to_string(d) + "#" + to_string(t);
    }

public:
    Router(int memoryLimit) : memoryLimit(memoryLimit) {
        seen.reserve(1 << 17);
    }

    bool addPacket(int source, int destination, int timestamp) {
        string k = keyOf(source, destination, timestamp);
        if (seen.count(k)) return false; // duplicate currently in router

        // Evict oldest if we're at capacity
        if ((int)q.size() == memoryLimit) {
            Packet old = q.front(); q.pop_front();
            string oldk = keyOf(old.s, old.d, old.t);
            seen.erase(oldk);
            auto it = dest_bit.find(old.d);
            if (it != dest_bit.end()) it->second.add(old.idx, -1);
        }

        // Append timestamp to destination's list; index is 1-based
        auto &vec = dest_ts[destination];
        vec.push_back(timestamp);
        int idx = (int)vec.size();

        // Ensure fenwick exists and update
        auto &fw = dest_bit[destination]; // creates if missing
        fw.add(idx, 1);

        q.push_back(Packet{source, destination, timestamp, idx});
        seen.insert(k);
        return true;
    }

    vector<int> forwardPacket() {
        if (q.empty()) return {};
        Packet p = q.front(); q.pop_front();
        string k = keyOf(p.s, p.d, p.t);
        seen.erase(k);
        auto it = dest_bit.find(p.d);
        if (it != dest_bit.end()) it->second.add(p.idx, -1);
        return {p.s, p.d, p.t};
    }

    int getCount(int destination, int startTime, int endTime) {
        auto it = dest_ts.find(destination);
        if (it == dest_ts.end()) return 0;
        auto &vec = it->second;
        // find 1-based index range
        int l = int(lower_bound(vec.begin(), vec.end(), startTime) - vec.begin()) + 1;
        int r = int(upper_bound(vec.begin(), vec.end(), endTime) - vec.begin()); // already counts <= endTime
        if (l > r) return 0;
        auto bitIt = dest_bit.find(destination);
        if (bitIt == dest_bit.end()) return 0;
        return bitIt->second.rangeSum(l, r);
    }
};
