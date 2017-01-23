import math
import sys

class Problem():
    def solve(self):
        self.get()

    def get(self):
        # manually binary search
        print(self.__get_ratio(2240)) # 0.0009996098921905572 (this one)
        print(self.__get_ratio(2239)) # 0.0010000474961915275

    def benchmark(self):
        print(self.__get_ratio(2)) # 0.3646261692917279
        print(self.__get_ratio(15)) # 0.09736936867646916
        print(self.__get_ratio(14)) # 0.10271528270608653

    def __get_ratio(self, n):
        sin_alpha = 1.0 / math.sqrt(n**2 + 1.0)
        cos_alpha = n / math.sqrt(n**2 + 1.0)

        radius = 0.5
        h = 1.0 / (2 * n)

        cos_beta = ((radius - h) * cos_alpha) / radius
        sin_beta = math.sqrt(1 - cos_beta**2)

        cos_gamma = cos_beta * cos_alpha + sin_beta * sin_alpha
        sin_gamma = sin_beta * cos_alpha - cos_beta * sin_alpha

        circular_sector_area = 0.5 * radius**2 * math.acos(cos_gamma)
        triangle_area = 0.5 * sin_gamma * radius * (radius - h)
        target_area = 0.5 * radius * h - (circular_sector_area - triangle_area)
        blue_area = 0.25 - 0.0625 * math.pi
        return target_area / blue_area

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())