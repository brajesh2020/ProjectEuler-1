from fractions import Fraction
import sys

class Problem():
    def solve(self):
        self.benchmark()
        print(self.E(100, 10))
    
    def benchmark(self):
        for N, M in [(3, 1), (3, 2), (10, 4), (100, 10)]:
            E = self.E_exactly(N, M)
            print(N, M, "=>", E, float(E))
    
    def E_exactly(self, N, M):
        expected_number = Fraction()
        for i in range(1, N + 1):
            q = Fraction((i - 1)**2 + (N - i)**2, N**2)
            P = Fraction(1 + (2*q - 1)**M, 2)
            expected_number += P
        return expected_number

    def E(self, N, M):
        expected_number = 0.0
        for i in range(1, N + 1):
            q = ((i - 1)**2 + (N - i)**2) / N**2
            P = (1 + (2*q - 1)**M) / 2
            expected_number += P
        return expected_number

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
