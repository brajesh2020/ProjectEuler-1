from fractions import gcd
import sys

class PrimeList():
    def get(self, n):
        result = []
        visited = [False for _ in range(n + 1)]
        for i in range(2, n + 1):
            if visited[i]:
                continue
            result.append(i)
            for j in range(i + i, n + 1, i):
                visited[j] = True
        return result

class FactorialFactorization():
    def get(self, n):
        result = []
        prime_list = PrimeList().get(n)
        for prime in prime_list:
            e = 0
            d = prime
            while d <= n:
                e += n // d
                d *= prime
            result.append((prime, e))
        return result

class Problem():
    def solve(self):
        #self.benchmark()
        self.get()

    def get(self):
        mod = 10**16 + 61
        print('F(10^6!, 65432) mod (10^16 + 61)', self.__get_factorial(10**6, 65432) % mod)

    def benchmark(self):
        assert(self.__get_factorization([(2, 2), (3, 1), (7, 1)], 4) == 3)
        assert(self.__get_factorial(12, 12) == 11)
        assert(self.__get_factorial(50, 123) == 17888)

    def __get_factorial(self, n, last_digits):
        factorization = FactorialFactorization().get(n)
        return self.__get_factorization(factorization, last_digits)
        
    def __get_factorization(self, factorization, last_digits):
        mod = 10**len(str(last_digits))
        count_map = { last_digits : 1 }
        for p, e in factorization:
            print('current (p, e) =>', p, e)
            if p in [2, 5] and last_digits % p != 0:
                continue            
            if p < 500:
                count_map = self.__count_prime_factor_with_big_exponent(count_map, p, e, mod)
            else:
                count_map = self.__count_prime_factor(count_map, p, e, mod)
        return count_map[1]

    def __count_prime_factor_with_big_exponent(self, old_count, prime, exponent, mod):
        result = {}
        power_list, repeated_pos = self.__get_power_list(prime, mod)

        print('count_prime_factor_with_big_exponent =>', prime, exponent, '=>', len(power_list), repeated_pos)
        for i in range(repeated_pos):
            print('non repeated exponent i =>', i)
            solution_map = self.__solve_linear_equations(pow(prime, i, mod), old_count, mod)
            for d in solution_map:
                for x in solution_map[d]:
                    if x not in result:
                        result[x] = 0
                    result[x] += old_count[d]

        cycle_len = len(power_list) - repeated_pos
        for i in range(cycle_len):
            if i % 100 == 0:
                print('repeated exponent i =>', i, 'current result size =>', len(result))
            q, r = divmod(exponent - repeated_pos + 1, cycle_len)
            frequency = q + (1 if i < r else 0)
            if frequency == 0:
                break
            solution_map = self.__solve_linear_equations(power_list[repeated_pos + i], old_count, mod)
            for d in solution_map:
                for x in solution_map[d]:
                    if x not in result:
                        result[x] = 0
                    result[x] += frequency * old_count[d]

        return result

    def __count_prime_factor(self, old_count, prime, exponent, mod):
        result = {}
        for i in range(exponent + 1):
            solution_map = self.__solve_linear_equations(pow(prime, i, mod), old_count, mod)
            for d in solution_map:
                for x in solution_map[d]:
                    if x not in result:
                        result[x] = 0
                    result[x] += old_count[d]
        return result

    def __get_power_list(self, n, mod):
        result = []
        d = 1
        while True:
            if d in result:
                return result, result.index(d)
            else:
                result.append(d)
                d = (d * n) % mod

    def __solve_linear_equations(self, a, b_list, m):
        g = gcd(a, m)
        a_reduced = a // g
        m_reduced = m // g
        u_0 = self.__mod_inverse(a_reduced, m_reduced) 

        result = {}
        for b in b_list:
            b_reduced, r = divmod(b, g)
            if r != 0:
                result[b] = []
            else:
                t = (u_0 * b_reduced) % m_reduced
                result[b] = [t + m_reduced * i for i in range(g)]
        return result

    def __mod_inverse(self, a, n):
        t, new_t = 0, 1
        r, new_r = n, a
        while new_r != 0:
            quotient = r // new_r
            t, new_t = new_t, t - quotient * new_t
            r, new_r = new_r, r - quotient * new_r
        if r > 1:
            return None
        if t < 0:
            t += n
        return t

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
