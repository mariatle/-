#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    long long n; std::cin >> n;
    std::vector<long long> dividers;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            dividers.push_back(i);
            if (i != n / i) {
                dividers.push_back(n / i);
            }
        }
    }
    std::sort(dividers.rbegin(), dividers.rend());
    std::cout << "graph {\n";
    for (auto v : dividers) {
        std::cout << v << "\n";
    }
    std::vector<std::pair<long long, long long>> edges;
    for (auto v : dividers) {
        long long d = v;
        for (long long i = 2; i * i <= d; i++) {
            if (d % i == 0) {
                while (d % i == 0) {
                    d /= i;
                }
                edges.emplace_back(v, v / i);
            }
        }
        if (d != 1) {
            edges.emplace_back(v, v / d);
        }
    }
    for (auto e : edges) {
        std::cout << e.first << "--" << e.second << "\n";
    }
    std::cout << "}\n";
    return 0;
}
