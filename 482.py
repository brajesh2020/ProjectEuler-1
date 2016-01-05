import fractions
import itertools
import sys

class PythagoreanTripleIterator():
    def get(perimeter):
        stack = [(3, 4, 5)]
        while stack:
            a, b, c = stack.pop()
            if a + b + c > perimeter:
                continue
            yield a, b, c
            stack.append(( a - 2 * b + 2 * c,  2 * a - b + 2 * c,  2 * a - 2 * b + 3 * c))
            stack.append(( a + 2 * b + 2 * c,  2 * a + b + 2 * c,  2 * a + 2 * b + 3 * c))
            stack.append((-a + 2 * b + 2 * c, -2 * a + b + 2 * c, -2 * a + 2 * b + 3 * c))

class Problem():
    def __init__(self):
        self.pythagorean_triple_map = None

    def solve(self):
        #assert(self.get(10**3) == 3619)
        print(self.get(10**7))

    def get(self, n):
        total_sum = 0
        visited_solution = set()
        for a, b, c, x, y, z in self.__iterate_solution(n):
            triangle_key = tuple(sorted((a, b, c)))
            if triangle_key in visited_solution:
                continue
            perimeter = a + b + c
            d = n // perimeter
            total_sum += (d * (d + 1) // 2) * (perimeter + x + y + z)
            visited_solution.add(triangle_key)
            print(a, b, c, x, y, z, total_sum)
        return total_sum

    def __iterate_solution(self, n):
        self.__init_pythagorean_triple(4 * n)
        total_progress = len(self.pythagorean_triple_map)
        progress = 0
        for k in self.pythagorean_triple_map:
            triple_set = self.pythagorean_triple_map[k]
            for t1, t2 in itertools.combinations(triple_set, 2):
                n, n_hypotenuse = t1
                m, m_hypotenuse = t2

                discriminant = m * n - k**2
                if discriminant <= 0:
                    continue

                a = n * m_hypotenuse**2
                b = m * n_hypotenuse**2
                c = (m + n) * discriminant
                x = n_hypotenuse * discriminant
                y = m_hypotenuse * discriminant
                z = k * m_hypotenuse * n_hypotenuse

                a, b, c, x, y, z = self.__get_primitive_solution(a, b, c, x, y, z)
                if a + b + c <= n:
                    yield a, b, c, x, y, z

            progress += 1
            if progress % 2000 == 0:
                print('========================================')
                print('Progress: {0}/{1}'.format(progress, total_progress))
                print('========================================')

    def __init_pythagorean_triple(self, n):
        triple_map = {}
        for primitive_a, primitive_b, primitive_c in PythagoreanTripleIterator.get(n):
            perimeter = primitive_a + primitive_b + primitive_c
            for d in range(1, n // perimeter + 1):
                a, b, c = primitive_a * d, primitive_b * d, primitive_c * d
                if a not in triple_map:
                    triple_map[a] = set()
                triple_map[a].add((b, c))
                if b not in triple_map:
                    triple_map[b] = set()
                triple_map[b].add((a, c))
        self.pythagorean_triple_map = triple_map

    def __get_primitive_solution(self, a, b, c, x, y, z):
        g = fractions.gcd(fractions.gcd(fractions.gcd(a, b), c), fractions.gcd(fractions.gcd(x, y), z))
        return a // g, b // g, c // g, x // g, y // g, z // g

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())