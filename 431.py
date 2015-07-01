import math
import sys

class RombergIntegration():
    def __init__(self, J):
        self.J = J
        self.T = [[None for j in range(i + 1)] for i in range(self.J + 1)]

    def get(self, f, a, b):
        self.__apply_composite_trapezoidal_rule(f, a, b) 
        self.__apply_richardson_extrapolation()
        return self.T[self.J][self.J]

    def __apply_composite_trapezoidal_rule(self, f, a, b):
        self.T[1][1] = (b - a) * (f.get(a) + f.get(b)) / 2
        for j in range(2, self.J + 1):
            h = (b - a) / 2**(j - 1)
            f_k = sum(f.get(a + (2 * k - 1) * h) for k in range(1, 2**(j - 2) + 1))
            self.T[j][1] = self.T[j - 1][1] / 2 + h * f_k

    def __apply_richardson_extrapolation(self):
        for j in range(1, self.J + 1):
            for k in range(2, j + 1):
                self.T[j][k] = self.T[j][k - 1] + (self.T[j][k - 1] - self.T[j - 1][k - 1]) / (4**(k - 1) - 1)

class Function():
    def __init__(self, silo_radius, delivered_point):
        self.silo_radius = silo_radius
        self.delivered_point = delivered_point

    def get(self, x):
        y2 = self.silo_radius**2 - x**2
        y = math.sqrt(y2)
        d = math.sqrt((x - self.delivered_point)**2 + y2)
        return y * d + (x - self.delivered_point)**2 * math.log(d + y)

class Problem():
    def __init__(self):
        self.EPSILON = 1e-12

    def solve(self):
        self.get()

    def get(self): 
        silo_radius = 6.0
        angle_of_repose = 40.0

        output = 0.0
        suggested_list = [
            1.609758501243779,
            2.806011946731256,
            3.6783279155789383, 
            4.426403291908572,
            5.109420207555078,
            5.7561071896021945,
        ]
        space_list = self.__get_square_space_list(silo_radius, angle_of_repose)
        for i in range(len(space_list)):
            space = space_list[i]
            suggested_a = suggested_list[i] - 1e-8
            suggested_b = suggested_list[i] + 1e-8
            delivered_point = self.__search_delivered_point(silo_radius, angle_of_repose, space, suggested_a, suggested_b)
            output += delivered_point
            print(space, '=>', delivered_point)
        print(output)

    def __get_square_space_list(self, silo_radius, angle_of_repose):
        min_volume = self.__get_by_romberg_integration(silo_radius, 0.0, angle_of_repose, 10)
        max_volume = self.__get_by_romberg_integration(silo_radius, silo_radius - self.EPSILON, angle_of_repose, 10)
        begin = int(math.sqrt(min_volume)) + 1
        end = int(math.sqrt(max_volume))
        return [i**2 for i in range(begin, end + 1)]

    def __search_delivered_point(self, silo_radius, angle_of_repose, space, suggested_a, suggested_b):
        a = suggested_a
        b = suggested_b
        f_a = self.__get_by_romberg_integration(silo_radius, a, angle_of_repose, 10) - space
        f_b = self.__get_by_romberg_integration(silo_radius, b, angle_of_repose, 10) - space
        for i in range(100):
            c = (a + b) / 2
            f_c = self.__get_by_romberg_integration(silo_radius, c, angle_of_repose, 25) - space
            if abs(f_c) < self.EPSILON or (b - a) / 2 < self.EPSILON:
                return c
            if f_c * f_a > 0:
                a = c
                f_a = f_c
            else:
                b = c
                f_b = f_c
        print('Method failed =>', a, b)
        return (a + b) / 2

    def __get_by_romberg_integration(self, silo_radius, delivered_point, angle_of_repose, J): 
        function = Function(silo_radius, delivered_point)
        f_integral = RombergIntegration(J).get(function, -silo_radius, silo_radius)
        g_integral = self.__get_g(silo_radius, delivered_point) + self.__get_g(-silo_radius, delivered_point)
        return (f_integral - g_integral) * math.tan(math.pi / 180 * angle_of_repose)

    def __get_g(self, x, delivered_point):
        dx = abs(x - delivered_point)
        return dx**3 * (3 * math.log(dx) - 1) / 9

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())