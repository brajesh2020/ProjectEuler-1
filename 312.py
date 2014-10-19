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
    
    def factorize(self, f):
        rv = {}
        for n in f:
            g = self.factorize_integer(n)
            for prime in g:
                if prime not in rv:
                    rv[prime] = 0
                rv[prime] += g[prime] * f[n]
        return rv
    
    def get_phi(self, f):
        rv = {}
        for prime in f:
            g = self.factorize_integer(prime - 1)
            e = f[prime]
            if e > 1:
                if prime not in rv:
                    rv[prime] = 0
                rv[prime] += e - 1
            for q in g:
                if q not in rv:
                    rv[q] = 0
                rv[q] += g[q]
        return rv

    def factorize_integer(self, n):
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
            raise Exception('prime factor should be small', d)
        return rv

class ExponentialTowerAlgorithm():
    def __init__(self):
        self.factorization = Factorization()
    
    def get(self, a, k, m):
        a = self.factorization.factorize(a)
        k = self.factorization.factorize(k)
        m = self.factorization.factorize(m)
        
        h, period = None, None
        g = self.convert_to_integer(self.get_gcd(a, m))
        print(a, m, g)
        if g > 1:
            h, period = self.get_period_not_coprime(a, k, m)
        else:
            h, period = self.get_period_coprime(a, k, m)
            mod_k = self.get_mod(k, period)
            return self.get_mod(self.get_power(a, mod_k), m)
            #print('a, mod_k, power, mod_a', a, mod_k, self.get_power(a, mod_k), mod_a)
            #print('power mod =>', k, period, mod_k, mod_a)
        print(h, period)

    def get_period_coprime(self, a, k, m):
        return 0, self.factorization.get_phi(m)

    def get_period_not_coprime(self, a, k, m):
        """
        Let d_h = gcd(a^h, m).  Then there exists the minimal h = h0 such that d_h = d_{h+1}.
        For such h = h0, let d = gcd(a^{h0}, m).  Then the period is phi(m/d).
        """
        h = 1
        d = None
        d_factorization = None
        while True:
            g_factorization = self.get_gcd(self.get_power(a, h), m)
            g = self.convert_to_integer(g_factorization)
            if d == g:
                d_factorization = g_factorization
                break
            else:
                h += 1
                d = g
        return h, self.factorization.get_phi(self.get_division(m, d_factorization))

    def get_gcd(self, f, g):
        h = {}
        for prime in f:
            if prime in g:
                h[prime] = min(f[prime], g[prime])
        return h
    
    def convert_to_integer(self, f):
        rv = 1
        for prime in f:
            rv *= prime**f[prime]
        return rv

    def get_power(self, f, e):
        rv = {}
        for prime in f:
            rv[prime] = f[prime] * e
        return rv

    def get_division(self, f, g):
        rv = {}
        for prime in f:
            if prime in g:
                e = f[prime] - g[prime]
                if e > 0:
                    rv[prime] = e
            else:
                rv[prime] = f[prime]
        return rv

    def get_mod(self, f, m):
        integer_m = self.convert_to_integer(m)
        rv = 1
        for prime in f:
            rv *= pow(prime, f[prime], integer_m)
        return rv % integer_m

    def get_mod_inverse(self, a, m):
        g, x, y = self._extended_gcd(a, m)
        if g != 1:
            raise Exception('modular inverse does not exist')
        else:
            return x % m

    def _extended_gcd(self, a, b):
        if a == 0:
            return (b, 0, 1)
        else:
            g, y, x = self._extended_gcd(b % a, a)
            return (g, x - (b // a) * y, y)

class Problem():
    def solve(self):
        algorithm = ExponentialTowerAlgorithm()
        a = algorithm.get({12: 1}, {3: 3}, {13: 3})
        b = algorithm.get({12: 1}, {3: 1}, {13: 3})
        b_inverse = algorithm.get_mod_inverse(b, 13**3)
        print(a, b, b_inverse, (a * b_inverse) % 13**3)
        print((a * b_inverse) * algorithm.get_mod_inverse(2, 13**3) % (13**3))
        

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    import sys
    sys.exit(main())
