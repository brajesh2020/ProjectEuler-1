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
        self.chinese_remainder_theorem = ChineseRemainderTheorem()
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

    """
    Solve the congruence ax^2 + bx + c = 0 (mod m).
    Let m = p_1^n_1 * p_2^n_2 * ... * p_k^n_k be the factorization of m.
    Solve ax^2 + bx + c = 0 (mod p_i^n_i) for each p_i, n_i.
    Then we can get the final solutions by Chinese remainder theorem.
    """
    def solve_quadratic_congruence_equation(self, a, b, c, m):
        g = gcd(gcd(a, b), gcd(c, m))
        primitive_solution = self.__solve_primitive_quadratic_congruence_equation(a // g, b // g, c // g, m // g)
        final_solution = []
        for i in range(g):
            final_solution += [root + i * (m // g) for root in primitive_solution]
        return final_solution

    def __solve_primitive_quadratic_congruence_equation(self, a, b, c, m):
        system_of_equations = []
        m_factorization = self.factorize(m)
        for p in m_factorization: 
            e = m_factorization[p]
            solution = self.__solve_quadratic_congruence_equation_prime(a, b, c, p, e)
            if not solution:
                return []
            system_of_equations.append([p**e, solution])
        return self.__solve_system_of_equations(system_of_equations)

    def __solve_system_of_equations(self, system_of_equations):
        if not system_of_equations:
            return []
        #print(system_of_equations)
        m, a_list = system_of_equations.pop()
        #print(m, a_list)
        while system_of_equations:
            n, b_list = system_of_equations.pop()
            next_m = m * n
            next_a_list = []
            for a in a_list:
                for b in b_list:
                    next_a = self.chinese_remainder_theorem.solve(a, m, b, n)
                    next_a_list.append(next_a)
            m = next_m
            a_list = next_a_list
            #print(m, a_list)
        return sorted(a_list)

    def __solve_quadratic_congruence_equation_prime(self, a, b, c, p, n=1):
        if p == 2:
            return self.__solve_quadratic_congruence_equation_even_prime(a, b, c, n)
        else:
            return self.__solve_quadratic_congruence_equation_odd_prime(a, b, c, p, n)
        
    """
    Solve the congruence ax^2 + bx + c = 0 (mod 2^n) by brute force. 
    """
    def __solve_quadratic_congruence_equation_even_prime(self, a, b, c, n):
        assert(n <= 14)
        m = 2**n
        result = []
        for x in range(2**(n-1) + 1):
            if (a * x**2 + b * x + c) % m == 0:
                result.append(x)
                if x != 0 and 2 * x != m:
                    result.append(m - x)
        return sorted(result)

    """
    Solve the congruence ax^2 + bx + c = 0 (mod p^n) where a != 0 (mod p^n) and p is odd prime.
    So, 4a^2 x^2 + 4ab x + 4ac = 0 (mod p), or (2ax + b)^2 = b^2 - 4ac (mod p^n).  
    Apply Cipolla's algorithm and Hensel's Lemma.
    """
    def __solve_quadratic_congruence_equation_odd_prime(self, a, b, c, p, n):
        #print("__solve_quadratic_congruence_equation_odd_prime =>", a, b, c, p, n, self.__solve_quadratic_residue(b**2 - 4*a*c, p, n))
        result = []
        for y in self.__solve_quadratic_residue(b**2 - 4*a*c, p, n):
            z = self.solve_linear_congruence_equations(2 * a, b - y, p**n)
            result += z
        return sorted(list(set(result)))

    """
    Solve the quadratic residue x^2 = q (mod p^n).
    If p is odd prime: 
        Solve x^2 = q (mod p) by Cipolla's algorithm. 
        Solve x^q = q (mod p^n) by using above result and Hensel’s Lemma.
    """
    def __solve_quadratic_residue(self, q, p, n):
        assert(p % 2 == 1)
        if q % p == 0:
            root_generator = p**((n+1) // 2)
            return list(range(0, p**n, root_generator))

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
        # ignore a = 0 (mod m)
        if a % m == 0:
            if b % m == 0:
                return list(range(m))
            else:
                return []

        g = gcd(a, gcd(b, m))
        primitive_solution = self.__solve_primitive_linear_congruence_equations(a // g, b // g, m // g)
        final_solution = []
        for i in range(g):
            final_solution += [root + i * (m // g) for root in primitive_solution]
        return final_solution

    def __solve_primitive_linear_congruence_equations(self, a, b, m):
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
        if self.__legendre_symbol(n, p) == p - 1:
            return []
        a = self.__find_a(n, p)
        x = self.__compute_x(a, n, p)
        if x == 0:
            return [x]
        else:
            return sorted([x, p - x])
            
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

class ChineseRemainderTheorem():
    """
    Solve
        x = a (mod m)
        x = b (mod n)
    where m and n are coprime.
    """
    def solve(self, a, m, b, n):
        x, y = self.__extended_gcd(m, n)
        return (a + (b - a) * x * m) % (m * n)
    
    def __extended_gcd(self, a, b):
        x, y = 0, 1
        last_x, last_y = 1, 0
        while b != 0:
            q, r = divmod(a, b)
            a, b = b, r
            x, last_x = last_x - q * x, x
            y, last_y = last_y - q * y, y
        return (last_x, last_y)

class Problem():
    def __init__(self):
        self.theory = NumberTheory()

    def solve(self):
        #print(self.theory.solve_linear_congruence_equations(6, 3, 9))
        #print(self.theory.solve_quadratic_congruence_equation(3, 4, 2, 9))
        #print(self.get_n_at_maximum(2, 8))
        #print(self.get_sum(5, 5))
        for b in range(101, 201):
            print(11, b, self.get_n_at_maximum(11, b))
        #print(self.get_sum(11, 100))
        #print(self.get_sum(10, 10))
        #print(self.get_sum(18, 1900))

    def get_sum(self, m, n):
        result = 0
        for a in range(1, m + 1):
            print("internal =>", a, result)
            for b in range(1, n + 1):
                n_at_maximum = self.get_n_at_maximum(a, b)
                #print(a, b, n_at_maximum)
                result += n_at_maximum
        return result

    def get_n_at_maximum(self, a, b):
        g = self.__get_g(a, b)
        g_factorization = self.theory.factorize(g)
        g_divisors = self.theory.get_all_divisors(g_factorization)[::-1]
        #print(a, b, g, g_factorization, g_divisors)
        #print("================================================================================")
        #print("get_n_at_maximum =>", a, b)
        first_found = False
        brute_force_answer = None
        for divisor in g_divisors:
            
            roots = [a for a in range(divisor) if (a**3 + b) % divisor == 0]
            root_count = len(roots)
            for i in range(root_count - 1):
                if first_found:
                    break
                if roots[i + 1] - roots[i] == a:
                    if not first_found:
                        first_found = True
                        brute_force_answer = roots[i]
                        break
                        #print("found =>", divisor, "=>", roots, roots[i])
                    #return roots[i]
            roots = self.__solve_equation(a, divisor)
            for root in roots:
                if (root**3 + b) % divisor == 0:
                    if brute_force_answer != root:
                        print("fatal error =>", a, b, divisor, brute_force_answer, root)
                        assert(False)
                    #print("new =>", divisor, "=>", roots)
                    return root
        return 0

    def __get_g(self, a, b):
        n = gcd(3 * a**3 + 9 * b, 2 * a**3 * gcd(a, 9))
        d = a**7 + 27 * a * b**2
        assert(d % n == 0)
        return d // n

        """
        Solve 3a x^2 + 3a^2 x + a^3 = 0 mod m
        """
    def __solve_equation(self, a, m):
        return self.theory.solve_quadratic_congruence_equation(3 * a, 3 * a**2, a**3, m)

def main():
    problem = Problem()
    problem.solve()
    
if __name__ == '__main__':
    sys.exit(main())
