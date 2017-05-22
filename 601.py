import sys

from fractions import gcd

class Problem():
    def solve(self):
        assert(self.get(3, 14) == 1)
        assert(self.get(6, 10**6) == 14286)
        print(sum([self.get(i, 4**i) for i in range(1, 31 + 1)]))

    def get(self, s, N):
        if s == 1:
            return (N - 1) // 2
        else:
            x0 = self.__lcm([_ for _ in range(2, s + 1)])
            x1 = self.__lcm([_ for _ in range(2, s + 2)])
            return (N - 2) // x0 - (N - 2) // x1

    def __lcm(self, number_list):
        output = number_list[0]
        for i in range(1, len(number_list)):
            number = number_list[i]
            output = output * number // gcd(output, number)
        return output

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
