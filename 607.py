import math
import sys

class Problem():
    def solve(self):
        theta = self.search_theta()
        print(self.get_days(theta))
        #print(theta, self.__get_horizontal_shift_delta(theta))

    def search_theta(self):
        left = math.pi / 3.
        right = math.pi / 6.
        while abs(left - right) > 1e-15:
            middle = (left + right) / 2.
            delta = self.__get_horizontal_shift_delta(middle)
            if delta < 0:
                left = middle
            elif delta > 0:
                right = middle
        return left

    def get_days(self, init_theta):
        thickness_list = self.__get_thickness_list()
        n_list = self.__get_n_list()
        speed_list = self.__get_speed_list()

        days = (thickness_list[0] / math.cos(init_theta)) / speed_list[0]
        curr_theta = init_theta
        for i in range(len(n_list) - 1):
            n_1 = n_list[i]
            n_2 = n_list[i + 1]
            theta_1 = curr_theta
            theta_2 = math.asin(math.sin(theta_1) * n_1 / n_2)
            days += (thickness_list[i + 1] / math.cos(theta_2)) / speed_list[i + 1]
            curr_theta = theta_2
        return days

    def __get_horizontal_shift_delta(self, init_theta):
        return 100. / math.sqrt(2.) - self.__get_horizontal_shift(init_theta)

    def __get_horizontal_shift(self, init_theta):
        thickness_list = self.__get_thickness_list()
        n_list = self.__get_n_list()

        horizontal_shift = thickness_list[0] * math.tan(init_theta)
        curr_theta = init_theta
        for i in range(len(n_list) - 1):
            n_1 = n_list[i]
            n_2 = n_list[i + 1]
            theta_1 = curr_theta
            theta_2 = math.asin(math.sin(theta_1) * n_1 / n_2)
            horizontal_shift += thickness_list[i + 1] * math.tan(theta_2)
            curr_theta = theta_2
        return horizontal_shift

    def __get_thickness_list(self):
        normal_terrain = (100. / math.sqrt(2.) - 50) / 2.
        marsh = 10.
        return [ normal_terrain, marsh, marsh, marsh, marsh, marsh, normal_terrain ]

    def __get_n_list(self): 
        return [ 1., 10. / 9., 10. / 8., 10. / 7., 10. / 6., 10. / 5., 1. ]

    def __get_speed_list(self):
        return [ 10., 9., 8., 7., 6., 5., 10. ]

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
