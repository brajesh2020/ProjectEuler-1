import math
import sys

class Prime():
    def get(n):
        primes = []
        visited = [False] * (n + 1)
        for i in range(2, n + 1):
            if not visited[i]:
                primes.append(i)
                for j in range(i * i, n + 1, i):
                    visited[j] = True
        return primes

class Problem():
    def __init__(self):
        self.basic_primes = None
        self.basic_prime_count = None
        self.prime_counting = None
        self.prime_sum = None

        self.a_cache = {} # A(p, n) = { 2 <= k <= n | smpf(k) = p }
        self.b_cache = {} # B(p, n) = { 2 <= k <= n | smpf(k) < p }

    def solve(self):
        print(self.get(10**12) % 10**9)

    def get(self, n):
        m = math.floor(math.sqrt(n))
        self.__init_values(m)
        
        total_count = self.prime_sum[n] - self.prime_sum[m]
        for p_pos in range(self.basic_prime_count):
            p = self.basic_primes[p_pos]
            count = self.__get_equal_inverse_smpf(p_pos, n)
            total_count += p * count
        return total_count

    def __init_values(self, n):
        self.basic_primes = Prime.get(n)
        self.basic_prime_count = len(self.basic_primes)

        self.prime_counting = [self.basic_prime_count for i in range(n + 1)]
        prev_pos, d = 0, 0
        for curr_pos in self.basic_primes:
            for i in range(prev_pos, curr_pos):
                self.prime_counting[i] = d
            prev_pos, d = curr_pos, d + 1

        # Reference: http://www.wolframalpha.com/input/?i=sum+of+all+the+primes+%3C%3D+10%5E12
        self.prime_sum = {
            10**1 : 17,
            10**2 : 1060,
            10**3 : 76127,
            10**4 : 5736396,
            10**6 : 37550402023,
            10**8 : 279209790387276,
            10**12 : 18435588552550705911377,
        }

    def __get_equal_inverse_smpf(self, p_pos, n):
        if p_pos < 0:
            return 0
        # prime is 2
        if p_pos == 0: 
            return n // 2

        p = self.basic_primes[p_pos]
        if p > n:
            return 0
        
        if p_pos not in self.a_cache:
            self.a_cache[p_pos] = {}
        if n not in self.a_cache[p_pos]:
            a = self.__get_less_inverse_smpf(p_pos, n // p)
            self.a_cache[p_pos][n] = n // p - a
        return self.a_cache[p_pos][n]

    def __get_less_inverse_smpf(self, p_pos, n):
        if p_pos < 0:
            return 0
        p = self.basic_primes[p_pos]
        if p > n:
            return n - 1

        if p_pos not in self.b_cache:
            self.b_cache[p_pos] = {}
        if n not in self.b_cache[p_pos]:
            m = math.floor(math.sqrt(n))
            q_pos = min(p_pos, self.prime_counting[m])
            q_count = sum([self.__get_equal_inverse_smpf(i, n) for i in range(q_pos)]) + p_pos - q_pos
            self.b_cache[p_pos][n] = q_count 
        return self.b_cache[p_pos][n]

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
