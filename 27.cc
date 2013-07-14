#include <iostream>

#define UPPER_BOUND (999)
#define LOWER_BOUND (-999)

bool visited[100000] = {};
long long prime[9592] = {};

inline void InitPrimeTable() {
    int curr_pos = 0;
    for (long long i = 2; i < 100000; i++) {
        if (visited[i]) {
            continue;
        }
        prime[curr_pos] = i;
        curr_pos++;
        for (long long j = i + i; j < 100000; j += i) {
            visited[j] = true;
        }
    }
}

bool IsPrime(long long n) {
    if (n < 0) {
        n = -n;
    }
    for (long long i = 0; i < 9592 && (prime[i] * prime[i] <= n); i++) {
        if (n == prime[i]) {
            return true;
        }

        if (n % prime[i] == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, const char* argv[]) {
    InitPrimeTable();

    long long max_n_so_far = 0;
    long long a_when_max_n = LOWER_BOUND - 1;
    long long b_when_max_n = LOWER_BOUND - 1;
    for (long long a = LOWER_BOUND; a <= UPPER_BOUND; a++) {
        for (long long b = LOWER_BOUND; b <= UPPER_BOUND; b++) {
            long long n = 0;
            long long f;
            while (1) {
                f = n*n + a*n + b;
                if (!IsPrime(f)) {
                    break;
                }
                n++;
            }

            if (n > max_n_so_far) {
                max_n_so_far = n;
                a_when_max_n = a;
                b_when_max_n = b;
            }
        }
    }
    std::cout << a_when_max_n * b_when_max_n << std::endl;
    
    return 0;
}