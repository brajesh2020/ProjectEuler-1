import sys

class Problem():
    def solve(self):
        self.get(10)
        #print([self.get(n) for n in range(1, 10 + 1)])

    def get(self, n):
        squares = {}
        for i in range(n + 2):
            squares[i**2] = i

        x_map = {}

        total_sum = 0
        for a in range(-n, n + 1):
            for b in range(-n, n + 1):
                discriminant = a**2 + 4 * b
                if discriminant in squares:
                    x_0 = (a - squares[discriminant]) // 2
                    x_1 = (a + squares[discriminant]) // 2

                    if x_0 not in x_map:
                        x_map[x_0] = []
                    x_map[x_0].append(x_1)

                    lattice_points = self.count_lattice_points(x_0, x_1)
                    total_sum += lattice_points
                    print(a, b, '=>', x_0, x_1, lattice_points)
        print('total_sum =>', total_sum)

        print(x_map)

        return total_sum
        
    def count_lattice_points(self, x_0, x_1):
        line = self.count_lattice_points_under_line(x_0, x_1)
        parabola = self.count_lattice_points_under_parabola(x_0, x_1)
        #print(x_0, x_1, '=>', line, parabola, '=>', line - parabola)
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
