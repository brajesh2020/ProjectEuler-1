import math
import sys

class Problem():
    def solve(self):
        N = 100
        result = 0
        xy_set = {}
        square_set = set([i**2 for i in range(N + 1)])
        for a in range(-N, N + 1):
            for b in range(-N, N + 1):
                found = False
                for x in range(-N, N + 1):
                    if found:
                        break
                    for y in range(-N, N + 1):
                        if found:
                            break
                        if a == x + y and b == - x * y:
                            print((a, b), "=>", (x, y), "=>", self.E(x, y))
                            if x not in xy_set:
                                xy_set[x] = []
                            xy_set[x].append(y)
                            result += self.E(x, y)
                            found = True
        print(result)
        print(xy_set)
        result = 0
        for x in xy_set:
            for y in xy_set[x]:
                result += self.E(x, y)
        print(result)
        return



        N = 100
        result = 0

        # passing (0, 0) and (y, y^2)
        result += self.E(0, 0)
        for y in range(1, N + 1):
            print((0, y), (0 + y, 0 * y), self.E(0, y))
            result += self.E(0, y) * 2
        print(result)

        # passing (1, 1) and (y, y^2)
        result += self.E(1, 1) * 2 + self.E(1, -1)
        print(result)
        for y in range(2, N):
            #print((1, y), (-1, -y), (-1, y), (1, -y), self.E(1, y), self.E(-1, -y), self.E(-1, y), self.E(1, -y))
            result += self.E(1, y) * 2 + self.E(1, -y) * 2
        print(result)

        max_x = int(math.sqrt(N))
        for x in range(2, max_x + 1):
            print((x, x), (-x, -x), (x, -x), self.E(x, x), self.E(x, -x))
            result += self.E(x, x) * 2 + self.E(x, -x)
            print(x)
            for y in range(x + 1, N // x + 1):
                print(x, y)
                #result += self.E(x, y) * 2 + self.E(x, -x) * 2

            #max_y = N // x
            #for y in range(1, max_y + 1):
            #    print((x, y), (-x, y), (-y, x), (-y, -x))
            #    print(self.E(x, y), self.E(-x, y), self.E(-y, x), self.E(-y, -x))
            #    if x != y:
            #        if x + y <= N:
            #            result = result + self.E(x, y) * 2
            #        result += self.E(-x, y) * 2
            #    else:
            #        result = result + self.E(x, y) + self.E(-x, y)

        print(result)


    def E(self, x, y):
        if x > y:
            return self.E(y, x)
        if x < 0 and y < 0:
            return self.E(-y, -x)
        assert(x <= y)
        assert(y >= 0)
        main_part = (x**2 + y**2 + 2) * (y - x + 1) // 2 - y * (y + 1) * (2 * y + 1) // 6
        #print("main_part =>", (x**2 + y**2 + 2) * (y - x + 1) // 2, y * (y + 1) * (2 * y + 1) // 6)
        x_part = None
        if x < 0:
            abs_x = abs(x)
            x_part = abs_x * (abs_x + 1) * (2 * abs_x + 1) // 6
        else:
            x_part = (x - 1) * x * (2 * x - 1) // 6
        return abs(main_part - x_part)

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
