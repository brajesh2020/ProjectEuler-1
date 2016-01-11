import sys

class FactorizationAlgorithm():
    def __init__(self, n):
        self.values = self.__get_values(n)

    def __get_values(self, n):
        values = [{} for i in range(n + 1)]
        for i in range(2, n + 1):
            if values[i]:
                continue
            for j in range(i, n + 1, i):
                values[j][i] = 1
            d = i * i
            while d <= n:
                for j in range(d, n + 1, d):
                    values[j][i] += 1
                d *= i
        return values

    """
    Factorize n
    """
    def get(self, n):
        return self.values[n]

class Problem():
    def __init__(self):
        self.mod = 101**4

    def solve(self):
        #self.benchmark()
        print(self.get(10**6, 10**12, 10**18))

    def benchmark(self):
        assert(self.get(10, 100, 1) == 91)
        assert(self.get(10, 100, 2) == 327)
        assert(self.get(10, 100, 3) == 1135)
        assert(self.get(10, 100, 1000) == 3286053)

    def get(self, a, b, n):
        c = b // a
        factorization_algorithm = FactorizationAlgorithm(c)
        result = 0
        for i in range(1, c + 1):
            factorization = factorization_algorithm.get(i)
            solution_count = self.__get_solution_count(factorization, n)
            gcd_value_count = b // i - a + 1
            result = (result + solution_count * gcd_value_count) % self.mod
        return result

    def __get_solution_count(self, factorization, n):
        result = 1
        for p in factorization:
            e = factorization[p]
            g = pow(e + 1, n, self.mod) - 2 * pow(e, n, self.mod) + pow(e - 1, n, self.mod)
            result = (result * g) % self.mod
        return result

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
