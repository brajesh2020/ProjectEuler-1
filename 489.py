from fractions import gcd
import itertools
import sys

class PrimeTable():
    def __init__(self, bound):
        self.primes = []
        self.__sieve(bound)
    
    def __sieve(self, bound):
        visited = [False] * (bound + 1)
        visited[0] = visited[1] = True
        for i in range(2, bound + 1):
            if not visited[i]:
                self.primes.append(i)
            for j in range(i + i, bound + 1, i):
                visited[j] = True
        print("Prime count:", len(self.primes))

class NumberTheory():
    def __init__(self):
        self.prime_table = PrimeTable(50000)
        self.max_n = self.prime_table.primes[-1]**2

    def factorize(self, n):
        assert(n < self.max_n)
        d = n
        rv = {}
        for i in range(len(self.prime_table.primes)):
            p = self.prime_table.primes[i]
            if d == 1 or p > d:
                break
            count = 0
            while d % p == 0:
                d = d // p
                count += 1
            if count > 0:
                rv[p] = count
        if d > 1:
            rv[d] = 1
        return rv

    def get_all_divisors(self, factorization):
        unpacking = [[p**e for e in range(factorization[p] + 1)] for p in factorization]
        return sorted([self.__product(divisor) for divisor in itertools.product(*unpacking)])

    def get_cube_roots_naive(self, a, m):
        return [0]
        roots = [x for x in range(m) if (x**3 - a) % m == 0]
        #print(a, m, roots)
        #self.get_cube_roots(a, m)
        return roots

    def get_cube_roots(self, a, m):
        m_factorization = self.factorize(m)
        print("get_cube_roots", a, m, m_factorization)
        for prime in m_factorization:
            self.get_cube_roots_prime(a % prime, prime)

    def get_cube_roots_prime(self, a, prime):
        print("get_cube_roots_prime =>", a, prime)    

    def __product(self, sequence):
        rv = 1
        for number in sequence:
            rv *= number
        return rv
        
class Problem():
    def __init__(self):
        self.theory = NumberTheory()
        self.problem_prime = set()

    def solve(self):
        #print(self.get_n_at_maximum(1, 1))
        print(self.get_sum(5, 5))
        #print(self.get_sum(10, 10))
        #print(self.get_sum(18, 1900))
        print(self.problem_prime, len(self.problem_prime), sum(self.problem_prime))

    def get_n_at_maximum(self, a, b):


        g = self.__get_g(a, b)
        g_factorization = self.theory.factorize(g)
        g_divisors = self.theory.get_all_divisors(g_factorization)[::-1]
        #print(a, b, g, g_factorization, g_divisors)
        for prime in g_factorization:
            self.problem_prime.add(prime)


        for divisor in g_divisors:
            roots = self.solve_equation(b, divisor)
            root_count = len(roots)
            for i in range(root_count - 1):
                if roots[i + 1] - roots[i] == a:
                    print("found =>", a, b, divisor, roots[i])
                    return roots[i]
        return 0

    def __get_g(self, a, b):
        n = gcd(3 * a**3 + 9 * b, 2 * a**3 * gcd(a, 9))
        d = a**7 + 27 * a * b**2
        assert(d % n == 0)
        return d // n

    def get_sum(self, m, n):
        result = 0
        for a in range(1, m + 1):
            print("internal =>", a)
            for b in range(1, n + 1):
                result += self.get_n_at_maximum(a, b)
        return result

    def solve_equation(self, b, m):
        return self.theory.get_cube_roots_naive(m - b, m)

def main():
    problem = Problem()
    problem.solve()
    
if __name__ == '__main__':
    sys.exit(main())
