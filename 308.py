import math
import sys

class Problem():
    def solve(self):
        self.get(104743)

    def get(self, n):
        largest_proper_divisor_list = self.get_largest_proper_divisor_list(n)

        total_count = (n - 1) * (4 * n**2 + 13 * n + 14) // 2 + sum(largest_proper_divisor_list[1 : n])
        for i in range(2, n + 1):
            total_count -= (6 * i + 2) * largest_proper_divisor_list[i]
            total_count += self.__get_floor_sum(i, largest_proper_divisor_list[i], i - 1) * 2
        print(total_count)
        return total_count

    def get_largest_proper_divisor_list(self, n):
        output = [i for i in range(n + 1)]
        sqrt_n = int(math.sqrt(n)) + 1
        for i in range(2, sqrt_n + 1):
            if output[i] == i:
                for j in range(i, n + 1, i):
                    if output[j] == j:
                        output[j] = j // i
        for i in range(2, n + 1):
            if output[i] == i:
                output[i] = 1
        return output

    def __get_floor_sum(self, n, i_begin, i_end):
        output = 0
        i = i_begin
        while i <= i_end:
            x = n // i
            max_i = min(n // x, i_end)
            output += x * (max_i - i + 1)
            i = max_i + 1
        return output

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
