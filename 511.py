import sys

class Sequence():
    def __init__(self, number_list, k, mod):
        self.number_list = [number % k for number in number_list]
        self.k = k
        self.mod = mod
        self.one_map = self.__init_one_map()

    def __init_one_map(self):
        one_map = {}
        for number in self.number_list:
            one_map[number] = 1
        return one_map

    def count(self, n):
        if n == 1:
            return self.one_map

        half_count_map = self.count(n // 2)
        
        double_map = {}
        for left_key in half_count_map:
            left_count = half_count_map[left_key]
            for right_key in half_count_map:
                right_count = half_count_map[right_key]
                new_key = (left_key + right_key) % self.k
                if new_key not in double_map:
                    double_map[new_key] = 0
                double_map[new_key] = (double_map[new_key] + left_count * right_count) % self.mod
        if n & 1 == 0:
            print('current n =>', n)
            return double_map

        count_map = {}
        for double_key in double_map:
            double_count = double_map[double_key]
            for one_key in self.one_map:
                one_count = self.one_map[one_key]
                new_key = (double_key + one_key) % self.k
                if new_key not in count_map:
                    count_map[new_key] = 0
                count_map[new_key] = (count_map[new_key] + double_count * one_count) % self.mod
        print('current n =>', n)
        return count_map



class Problem():
    def __init__(self):
        self.factorization = {
            3: [1, 3],
            4: [1, 2, 4],
            1111: [1, 11, 101, 1111],
            1234567898765: [1, 5, 41, 205, 25343, 126715, 237631, 1039063, 1188155, 5195315, 9742871, 48714355, 6022282433, 30111412165, 246913579753, 1234567898765],
        }

    def solve(self):
        #self.benchmark()
        print(self.get(1234567898765, 4321))

    def benchmark(self):
        assert(self.get(3, 4) == 4)
        assert(self.get(4, 11) == 8)
        assert(self.get(1111, 24) == 840643584)

    def get(self, n, k):
        sequence = Sequence(self.factorization[n], k, 10**9)
        return sequence.count(n)[(-n) % k]



def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
