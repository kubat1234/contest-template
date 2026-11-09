// Library: reads the encrypted test, runs the contestant's maks_suma() and prints one code:
//   KOD_OK <answer>     __ID__chk compares the answer with the model's output
//   KOD_NARUSZENIE      a rule of the statement was broken
//   KOD_KOMUNIKACJA     wrong guard word or a broken input
// The codes are random words, so a solution cannot print a verdict by itself.
//
// Encrypted test: the first line is STRAZNIK, every number is written as value ^ KLUCZ.
// A solution that reads stdin before the library (e.g. in a constructor of a global
// variable) gets only encrypted numbers, and the library then reports KOD_KOMUNIKACJA.
// Decrypted format: n, then n numbers.
//
// main() and maks_suma() are weak: sio2 links the library also into the ingen, the inwer
// and the checker, and their own main() has to win there.
#include <bits/stdc++.h>
#include "__ID__lib.h"
using namespace std;

__attribute__((weak)) long long maks_suma();

namespace {

// TEMPLATE: draw new secrets for every package (python3 -c "import secrets,string;
// print(''.join(secrets.choice(string.ascii_lowercase) for _ in range(18)), secrets.randbits(31))")
// and copy them to __ID__chk.cpp, __ID__ingen.cpp and __ID__inwer.cpp. Never move them to a
// shared header: files from extra_compilation_files lie next to the solution when it is compiled.
const char* const STRAZNIK = "yaxnmjizyhwiwudozq";
const long long KLUCZ = 281558958;
const char* const KOD_OK = "tnobiwedwnntlhbzfj";
const char* const KOD_NARUSZENIE = "bgqzfmzboudslqulwn";
const char* const KOD_KOMUNIKACJA = "yjuocvnqdkuhmpqfww";

// TEMPLATE: replace the interface.
int n;
vector<long long> a;
vector<int> reads;

[[noreturn]] void koniec(const char* kod) {
    printf("%s\n", kod);
    fflush(stdout);
    exit(0);
}

// The next number of the test, decrypted.
long long liczba() {
    long long v;
    if (scanf("%lld", &v) != 1) koniec(KOD_KOMUNIKACJA);
    return v ^ KLUCZ;
}

}  // namespace

int dlugosc() { return n; }

long long element(int i) {
    if (i < 1 || i > n || ++reads[size_t(i)] > 2) koniec(KOD_NARUSZENIE);
    return a[size_t(i)];
}

__attribute__((weak)) int main() {
    char straznik[64];
    if (scanf("%63s", straznik) != 1 || strcmp(straznik, STRAZNIK) != 0) koniec(KOD_KOMUNIKACJA);
    n = int(liczba());
    a.assign(size_t(n) + 1, 0);
    reads.assign(size_t(n) + 1, 0);
    for (int i = 1; i <= n; ++i) a[size_t(i)] = liczba();
    // No fclose(stdin): sio2jail on SIO forbids close(0), which gives RV on every test.
    // The whole test is already read, so the contestant has nothing left to read.
    long long answer = maks_suma();
    printf("%s %lld\n", KOD_OK, answer);
    fflush(stdout);
}
