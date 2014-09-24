#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#define SIEVE_RANGE (60000001)
#define MOD (1000000000000000000)
#define N (60000000)
#define K (3)

std::vector<int> divisor_function;

void InitDivisorFunction() {
    divisor_function = std::vector<int>(SIEVE_RANGE + 1, 1);
    for (int i = 2; i <= SIEVE_RANGE; i++) {
        if (divisor_function[i] == 1) {
            for (int j = i; j <= SIEVE_RANGE; j += i) {
                int e = 0;
                int d = j;
                while (d % i == 0) {
                    e++;
                    d /= i;
                }
                divisor_function[j] *= (e + 1);
            }
        }
    }
}

void DeinitDivisorFunction() {
    divisor_function.clear();
}

void DebugDivisorFunction() {
    for (int i = 1; i <= 20; i++) {
        std::cout << divisor_function[i];
        if (i != 20) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    
    int max_so_far = 1;
    for (int i = 1; i <= SIEVE_RANGE; i++) {
        if (divisor_function[i] > max_so_far) {
            max_so_far = divisor_function[i];
            std::cout << i << " " << max_so_far << std::endl;
        }
    }
}

// -------------------------------------------------------------------------------------------------

std::vector<int> triangle_number_divisor_function;

void InitTriangleNumberDivisorFunction() {
    InitDivisorFunction();
    triangle_number_divisor_function = std::vector<int>(SIEVE_RANGE + 1, 1);
    for (int i = 1; i <= SIEVE_RANGE; i += 2) {
        triangle_number_divisor_function[i] = divisor_function[i] * divisor_function[(i+1)/2];
    }
    
    for (int i = 2; i <= SIEVE_RANGE; i += 2) {
        triangle_number_divisor_function[i] = divisor_function[i/2] * divisor_function[i+1];
    }
    DeinitDivisorFunction();
}

void DebugTriangleNumberDivisorFunction() {
    for (int i = 1; i <= 20; i++) {
        std::cout << triangle_number_divisor_function[i];
        if (i != 20) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    
    int max_so_far = 1;
    for (int i = 1; i <= SIEVE_RANGE; i++) {
        if (triangle_number_divisor_function[i] > max_so_far) {
            max_so_far = triangle_number_divisor_function[i];
            std::cout << i << " " << max_so_far << std::endl;
        }
    }
}

// -------------------------------------------------------------------------------------------------

long long binary_indexed_tree[K + 1][SIEVE_RANGE + 1] = {};

void UpdateBinaryIndexedTree(int index, int k, int n, long long value) {
    while (index < n) {
        binary_indexed_tree[k][index] += value;
        index += (index & -index);
    }
}

long long GetBinaryIndexedTreeValue(int index, int k) {
    long long result = 0;
    while (index > 0) {
        result += binary_indexed_tree[k][index];
        index -= (index & -index);
    }
    return result;
}

std::map<int, int> GetSortedIndex(std::vector<int> array) {
    std::map<int, int> result;
    std::vector<int> sorted(array);
    sort(sorted.begin(), sorted.end(), std::greater<int>());
    result[sorted[0]] = 1;
    for (int i = 1; i < sorted.size(); i++) {
        if (sorted[i] != sorted[i-1]) {
            result[sorted[i]] = i+1;
        }
    }
    return result;
}

long long GetCount(std::vector<int> values) {
    std::vector< std::vector<long long> > counting(K + 1, std::vector<long long>(SIEVE_RANGE + 1, 0));
    std::map<int, int> sorted_index = GetSortedIndex(values);
    const int n = static_cast<const int>(values.size());
    long long result = 0;
    for (int i = 0; i < n; i++) {
        const int index = sorted_index[values[i]];
        counting[1][i] = 1;
        UpdateBinaryIndexedTree(index, 1, n, counting[1][i]);
        for(int j = 2 ; j <= K; j++) {
            counting[j][i] = GetBinaryIndexedTreeValue(index - 1, j - 1);
            UpdateBinaryIndexedTree(index, j, n, counting[j][i]);
        }
        result = (result + counting[K][i]) % MOD;
    }
    return result;
}

// -------------------------------------------------------------------------------------------------

long long Solve(int n) {
    std::vector<int> values = std::vector<int>(
            triangle_number_divisor_function.begin() + 1,
            triangle_number_divisor_function.begin() + n + 1);
    return GetCount(values);
}

int main(int argc, const char * argv[]) {
    InitTriangleNumberDivisorFunction();
    std::cout << Solve(N) << std::endl;
    return 0;
}

