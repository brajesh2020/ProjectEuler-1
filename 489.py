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
        self.cipolla_algorithm = CipollaAlgorithm()
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
        roots = [x for x in range(m) if (x**3 - a) % m == 0]
        #print(a, m, roots)
        #self.get_cube_roots(a, m)
        return roots 

    """
    Solve the congruence ax^2 + bx + c = 0 (mod p) where a != 0 (mod p).

    If p is odd prime, then 4a^2 x^2 + 4ab x + 4ac = 0 (mod p), or (2ax + b)^2 = b^2 - 4ac (mod p).  
    Apply Cipolla's algorithm.
    """
    def solve_quadratic_congruence_equation_prime(self, a, b, c, p):
        result = []
        if p == 2:
            if c % 2 == 0:
                result.append(0) 
            if (a + b + c) % 2 == 0:
                result.append(1)
        else:
            for y in self.solve_quadratic_residue(b**2 - 4*a*c, p):
                z = self.solve_linear_congruence_equations(2 * a, b - y, p)
                result += z
        return sorted(list(set(result)))

    """
    Solve the quadratic residue x^2 = q (mod p^n).
    If p is odd prime: 
        Solve x^2 = q (mod p) by Cipolla's algorithm. 
        Solve x^q = q (mod p^n) by using above result and Hensel’s Lemma.
    """
    def solve_quadratic_residue(self, q, p, n=1):
        if p % 2 == 1:
            x_list = self.cipolla_algorithm.execute(q, p)
            curr_list = list(x_list)
            for k in range(1, n):
                next_list = []
                for curr_x in curr_list:
                    y = self.solve_linear_congruence_equations(2 * curr_x, -1, p**k)
                    assert(len(y) > 0)
                    next_x = (curr_x - (curr_x**2 - q) * y[0]) % p**(k + 1)
                    next_list.append(next_x)
                curr_list = next_list
            return curr_list


    """
    Solve the congruence ax + b = 0 (mod m) where a != 0 (mod m).
    """
    def solve_linear_congruence_equations(self, a, b, m):
        result = []
        g, x, y = self.__extended_gcd(a, m)
        if g == 1:
            result.append((-b * x) % m)
        return result

    def __extended_gcd(self, a, b):
        if a == 0:
            return (b, 0, 1)
        else:
            g, y, x = self.__extended_gcd(b % a, a)
            return (g, x - (b // a) * y, y)

    def __product(self, sequence):
        rv = 1
        for number in sequence:
            rv *= number
        return rv
        
class CipollaAlgorithm():
    def execute(self, n, p):
        if p == 2:
            return []
        if self.__legendre_symbol(n, p) == -1:
            return []
        a = self.__find_a(n, p)
        x = self.__compute_x(a, n, p)
        return sorted(list(set([x, p - x])))
            
    def __legendre_symbol(self, a, p):
        return pow(a % p, (p - 1) // 2, p)    

    def __find_a(self, n, p):
        for a in range(p):
            if self.__legendre_symbol(a**2 - n, p) != 1:
                return a
        
    def __compute_x(self, a, n, p):
        d = a**2 - n
        q = (p+1) // 2        
        b = [a, 1]
        x = [1, 0]
        while q > 0:
            if q & 1 != 0:
                x = [(x[0]*b[0] + d*x[1]*b[1]) % p, (x[0]*b[1] + x[1]*b[0]) % p] 
            b = [(b[0]**2 + d * b[1]**2) % p, (2*b[0]*b[1]) % p]
            q >>= 1
        return x[0]  

class Problem():
    def __init__(self):
        self.theory = NumberTheory()

    def solve(self):
        for q, p, n in [(1, 3, 1), (1, 3, 4)]:
            print(q, p, n, "=>", self.theory.solve_quadratic_residue(q, p, n))
        for a, b, c, p in [(1, 4, 1, 13), (1, 1, 1, 3)]:
            print(a, b, c, p, "=>", self.theory.solve_quadratic_congruence_equation_prime(a, b, c, p))

        #print(self.get_n_at_maximum(1, 1))
        #print(self.get_sum(5, 5))
        #print(self.get_sum(10, 10))
        #print(self.get_sum(18, 1900))

    def get_n_at_maximum(self, a, b):
        g = self.__get_g(a, b)
        g_factorization = self.theory.factorize(g)
        g_divisors = self.theory.get_all_divisors(g_factorization)[::-1]
        #print(a, b, g, g_factorization, g_divisors)

        for divisor in g_divisors:
            roots = self.solve_equation(a, b, divisor)
            root_count = len(roots)
            for i in range(root_count - 1):
                if roots[i + 1] - roots[i] == a:
                    #print("found =>", a, b, divisor, roots[i], roots)
                    return roots[i]
        #print("0 =>", a, b, g_factorization)
        return 0

    def __get_g(self, a, b):
        n = gcd(3 * a**3 + 9 * b, 2 * a**3 * gcd(a, 9))
        d = a**7 + 27 * a * b**2
        assert(d % n == 0)
        return d // n

    def get_sum(self, m, n):
        result = 0
        for a in range(1, m + 1):
            #print("internal =>", a)
            for b in range(1, n + 1):
                result += self.get_n_at_maximum(a, b)
        return result

    def solve_equation(self, a, b, m):
        return self.theory.get_cube_roots_naive(m - b, m)

def main():
    problem = Problem()
    problem.solve()
    
if __name__ == '__main__':
    sys.exit(main())
