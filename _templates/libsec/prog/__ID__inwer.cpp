// Input verifier. Run: sinol-make inwer
// sinol-make passes the test file name (e.g. "__ID__2c.in") as argv[1] and the
// test on stdin, so every test is checked against the limits of ITS group.
// The test is encrypted: the first line is the guard word, every number is value ^ KLUCZ.
#include <bits/stdc++.h>
#include "oi.h"
using namespace std;

// TEMPLATE: the same STRAZNIK and KLUCZ as in __ID__lib.cpp.
const string STRAZNIK = "yaxnmjizyhwiwudozq";
const long long KLUCZ = 281558958;

// TEMPLATE: replace the limits and the reading code.

struct Limits {
    int max_n;
    long long max_abs;
};

// Group 0 = statement examples and ocen tests: only the global limits apply.
const map<int, Limits> GROUP = {
    {0, {200'000, 1'000'000'000}},
    {1, {1'000, 1'000'000}},
    {2, {200'000, 1'000'000'000}},
};

// "__ID__2c.in" -> 2, "__ID__1ocen.in" -> 0, "__ID__0a.in" -> 0
int group_of(string name) {
    name = name.substr(name.rfind('/') + 1);
    if (name.find("ocen") != string::npos) return 0;
    size_t i = 3, j = i;  // skip the task id
    while (j < name.size() && isdigit(name[j])) j++;
    return stoi(name.substr(i, j - i));
}

// The next number, decrypted, from [lo, hi].
long long rd(oi::Scanner& in, long long lo, long long hi) {
    long long v = in.readLL() ^ KLUCZ;
    assert(lo <= v && v <= hi);
    return v;
}

int main(int argc, char* argv[]) {
    int group = argc > 1 ? group_of(argv[1]) : 0;
    assert(GROUP.count(group));
    Limits L = GROUP.at(group);

    oi::Scanner in(stdin, oi::PL);
    char straznik[64];
    in.readString(straznik, sizeof straznik);
    assert(straznik == STRAZNIK);
    in.readEoln();
    int n = int(rd(in, 1, L.max_n));
    in.readEoln();
    long long mx = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        long long a = rd(in, -L.max_abs, L.max_abs);
        mx = max(mx, a);
        if (i + 1 < n) in.readSpace();
    }
    in.readEoln();
    in.readEof();

    cout << "OK group=" << group << " n=" << n << " max=" << mx << '\n';
}
