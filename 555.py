import sys

class DivisorStore():
    def __init__(self, n):
        self.values = self.__init_values(n)

    def __init_values(self, n):
        values = [[] for _ in range(n + 1)]
        for d in range(1, n + 1):
            for i in range(d, n + 1, d):
                values[i].append(d)
        return values

    def get(self, n):
        return self.values[n]

class Problem():
    def solve(self):
        print(self.get(10**6, 10**6))

    def benchmark(self):
        assert(self.get(10, 10) == 225)
        assert(self.get(1000, 1000) == 208724467)

    def get(self, p, m):
        total_sum = 0
        divisor_store = DivisorStore(p)
        for s in range(1, p):
            divisors = divisor_store.get(s)
            for d in divisors:
                k = d + s
                if k > p:
                    continue
                begin = m - s + 1
                end = min(m + k - 2 * s, m)
                total_sum += self.get_sum(begin, end)
                #print(m, k, s, '=>', begin, end, total_sum)
        return total_sum

    def get_sum(self, begin, end):
        return (begin + end) * (end - begin + 1) // 2

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())