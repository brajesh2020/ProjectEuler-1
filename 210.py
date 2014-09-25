import sys

class PrimeTable():
    def __init__(self, bound):
        self.bound = bound
        self.primes = []
        self._sieve()
    
    def _sieve(self):
        visited = [False] * (self.bound + 1)
        visited[0] = visited[1] = True
        for i in range(2, self.bound + 1):
            if not visited[i]:
                self.primes.append(i)
            for j in range(i + i, self.bound + 1, i):
                visited[j] = True
        print('Prime count:', len(self.primes))

class Factorization():
    def __init__(self):
        self.prime_table = PrimeTable(100)
    
    def get(self, n):
        d = n
        rv = []
        for i in range(len(self.prime_table.primes)):
            p = self.prime_table.primes[i]
            if d == 1 or p > d:
                break
            count = 0
            while d % p == 0:
                d = d // p
                count += 1
            if count > 0:
                rv += [(p, count)]
        if d > 1:
            raise Exception('prime factor should be small')
        return rv

class ProjectEulerProblem233():
    def __init__(self):
        self.factorization = Factorization()

    def get(self, n):
        rv = 4
        factors = self.factorization.get(n)
        print(factors)
        for p, e in factors:
            if p % 4 == 1:
                rv *= (2 * e + 1)
        return rv

class GaussCircleProblem():
    def get(self, n):
        sum = 0
        i = 0
        while True:
            a, b = n // (4*i + 1), n // (4*i + 3)
            if a == 0 and b == 0:
                break
            i += 1
            sum += (a - b)
        return 1 + 4 * sum

class Problem():
    def __init__(self):
        self.gauss_circle_problem = GaussCircleProblem()
        self.project_euler_problem = ProjectEulerProblem233()
    
    def solve(self):
        for n in [8, 1000000000]:
            self.get(n)

    def get(self, n):
        #print(self.gauss_circle_problem.get(n // 8))
        print(self.project_euler_problem.get(n // 4))
        print(n)

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
