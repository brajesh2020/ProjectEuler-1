import math
import sys

class Problem():
    def solve(self):
        #self.get(5)
        print([self.get(n) for n in range(1, 100 + 1)])

    def get(self, n):
        total_sum = 0

        for x_1 in range(n + 1):
            lattice_points = self.count_lattice_points(0, x_1)
            total_sum += lattice_points

        for x_1 in range(1, n):
            lattice_points = self.count_lattice_points(1, x_1)
            total_sum += lattice_points

        sqrt_n = int(math.sqrt(n))
        for x_0 in range(2, sqrt_n + 1):
            for x_1 in range(x_0, n // x_0 + 1):
                lattice_points = self.count_lattice_points(x_0, x_1)
                total_sum += lattice_points

        for x_0 in range(1, n + 1):
            for x_1 in range(n // x_0 + 1):
                lattice_points = self.count_lattice_points(-x_0, x_1)
                total_sum += lattice_points

        for x_0 in range(1, sqrt_n + 1):
            for x_1 in range(1, x_0 + 1):
                lattice_points = self.count_lattice_points(-x_0, -x_1)
                total_sum += lattice_points

        for x_0 in range(sqrt_n + 1, n):
            for x_1 in range(1, n // x_0 + 1):
                lattice_points = self.count_lattice_points(-x_0, -x_1)
                total_sum += lattice_points
        #print('total_sum =>', total_sum)
        return total_sum



    def count_lattice_points(self, x_0, x_1):
        line = self.count_lattice_points_under_line(x_0, x_1)
        parabola = self.count_lattice_points_under_parabola(x_0, x_1)
        return line - parabola

    def count_lattice_points_under_line(self, x_0, x_1):
        return (x_1 - x_0 + 1) * (x_0**2 + x_1**2 + 2) // 2

    def count_lattice_points_under_parabola(self, x_0, x_1):
        if x_0 >= 0:
            return x_1 * (x_1 + 1) * (2 * x_1 + 1) // 6 - x_0 * (x_0 - 1) * (2 * x_0 - 1) // 6
        elif x_1 >= 0:
            return x_1 * (x_1 + 1) * (2 * x_1 + 1) // 6 - x_0 * (-x_0 + 1) * (-2 * x_0 + 1) // 6
        else:
            return self.count_lattice_points_under_parabola(-x_1, -x_0)



def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
