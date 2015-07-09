import sys

class Problem():
    def __init__(self):
        self.mod = 10**9

    def solve(self):
        total_sum = 2517
        for n in [3, 4, 6, 8, 24, 64, 384, 2048]:
            g = self.get(n)
            total_sum = (total_sum + g) % self.mod
        print(total_sum)

    def get(self, n):
        a = n
        for i in range(n):
            a = (a * pow(2, a, self.mod)) % self.mod
        return (a - 3) % self.mod

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
