#include <iostream>
#include <map>
#include <assert.h> 
#include <math.h>
#include <stdio.h>

class Problem {
public:
    void solve() {
        long long n = 10000000000LL;
        printf("B(%lld) = %lld\n", n, get(n));
    }

private:
    void benchmark() {
        assert(get(10000LL) == 49LL);
        assert(get(1000000LL) == 38239LL);        
    }

    long long get(long long n) {
        std::map<long long, long long> count_map;
        long long a_bound = integer_square_root(n / 4.0);
        printf("Bound: %lld\n", a_bound);
        for (long long a = 0; a < a_bound + 1; a++) {
            if (a % 100 == 0) {
                printf("Current a: %lld\n", a);
            }
            for (long long b = a + 2; ; b += 2) {
                long long x = a * a + b * b;
                if (2 * x > n) {
                    break;
                }
                count_map[x]++;
            }
        }

        long long output = 0;
        for (std::map<long long, long long>::iterator it = count_map.begin(); it != count_map.end(); ++it) {
            output += get_binomial_coefficient(it->second);
        }
        return output;
    }

    /* Floor[Sqrt[n]] */
    long long integer_square_root(double n) {
        long long output = (long long)(sqrt(n));
        assert(output * output <= n);
        assert((output + 1) * (output + 1) > n);
        return output;
    }

    /* BinomialCoefficient[n, 3] */
    long long get_binomial_coefficient(long long n) {
        if (n < 3) {
            return 0LL;
        }
        if (binomial_coefficient_cache[n] == 0) {
            binomial_coefficient_cache[n] = n * (n - 1) * (n - 2) / 6;
        }
        return binomial_coefficient_cache[n];
    }

    std::map<long long, long long> binomial_coefficient_cache;
};

int main() {
    Problem problem;
    problem.solve();
    return 0;
}
