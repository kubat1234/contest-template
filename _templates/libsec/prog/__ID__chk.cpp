// Checker. Run by sinol-make: __ID__chk <in> <contestant's output> <model's output>
// The library prints "<KOD_OK> <answer>" or one of the error codes (__ID__lib.cpp).
// Anything else is a communication error: contestants do not know the codes, so they
// cannot print a verdict by themselves.
#include <bits/stdc++.h>
using namespace std;

// TEMPLATE: the same codes as in __ID__lib.cpp.
const string KOD_OK = "tnobiwedwnntlhbzfj";
const string KOD_NARUSZENIE = "bgqzfmzboudslqulwn";
const string KOD_KOMUNIKACJA = "yjuocvnqdkuhmpqfww";

[[noreturn]] void verdict(bool ok, const string& comment, double percent = 100) {
    if (ok) printf("OK\n%s\n%.4f\n", comment.c_str(), percent);
    else printf("WRONG\n%s\n", comment.c_str());
    exit(0);
}

string read_all(const char* path) {
    ifstream f(path, ios::binary);
    return string(istreambuf_iterator<char>(f), istreambuf_iterator<char>());
}

// "<KOD_OK> <answer>" and nothing more; otherwise nullopt.
optional<long long> parse(const string& text) {
    istringstream ss(text);
    string code, answer, rest;
    if (!(ss >> code >> answer) || code != KOD_OK || (ss >> rest)) return nullopt;
    if (answer.empty() || answer.size() > 20 ||
        !all_of(answer.begin() + (answer[0] == '-'), answer.end(), [](char c) { return isdigit(c); }))
        return nullopt;
    return stoll(answer);
}

int main(int argc, char* argv[]) {
    assert(argc == 4);
    auto model = parse(read_all(argv[3]));
    assert(model);

    string out = read_all(argv[2]);
    auto got = parse(out);
    if (!got) {
        istringstream ss(out);
        string first;
        ss >> first;
        if (first == KOD_NARUSZENIE) verdict(false, "Naruszenie zasad komunikacji z biblioteką");  // TEMPLATE
        if (first == KOD_KOMUNIKACJA) verdict(false, "Błąd związany z komunikacją");
        if (out.rfind("OK", 0) == 0) verdict(false, "Zakaz szponcenia!!!");
        verdict(false, "Błąd związany z komunikacją");
    }
    if (*got != *model) verdict(false, "Zła odpowiedź: " + to_string(*got) + ", oczekiwano " + to_string(*model));
    verdict(true, "");
}
