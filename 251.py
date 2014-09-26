import math
import sys

class Problem():
    def __init__(self):
        pass

    def solve(self):
        self.get_count(1000)
        #self.get_count_benchmark(1000)
    
    def get_count(self, bound):
        count = 0
        for k in range((bound - 2)//3 + 1):
            a = 2 + 3*k
            x = (1 + 2*k)**3 + (2 + 3*k)**2 # where x = b^2 c
            if 4 * (bound - a)**3 < 27 * x:
                break
            max_b = min(bound + 1 - a, self._int_sqrt(x))
            for b in range(1, max_b + 1):
                c, r = divmod(x, b**2)
                if r == 0 and a + b + c <= bound:
                    count += 1
                    print(count, "=>", a, b, c)

    def get_count_benchmark(self, bound):
        count = 0
        for k in range((bound-2)//3 + 1):
            a = 2 + 3*k
            for b in range(1, bound + 1 - a):
                for c in range(1, bound + 1 - a - b):
                    if self.is_cardano_triplet(a, b, c):
                        count += 1
                        print(count, "=>", a, b, c)

    def is_cardano_triplet(self, a, b, c):
        sum = 0
        for x in [a + b * math.sqrt(c), a - b * math.sqrt(c)]:
            if x >= 0:
                sum += x**(1/3)
            else:
                sum -= (-x)**(1/3)
        return abs(sum - 1) < 1e-9

    def _int_sqrt(self, n):
        guess = (n >> n.bit_length() // 2) + 1
        result = (guess + n // guess) // 2
        while abs(result - guess) > 1:
            guess = result
            result = (guess + n // guess) // 2
        while result * result > n:
            result -= 1
        return result


def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
