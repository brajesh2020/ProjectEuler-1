from fractions import Fraction
import itertools
import sys

class NumberTheory():
    def __init__(self, n):
        self.n = n
        self.prime_list = self.__init_prime_list(n // 2)[::-1]
        self.largest_prime_divisor_list = self.__init_largest_prime_divisor_list(n)

    def __init_prime_list(self, n):
        output = []
        visited = [False for i in range(n + 1)]
        visited[0] = visited[1] = True
        for i in range(2, n + 1):
            if not visited[i]:
                output.append(i)
                for j in range(i**2, n + 1, i):
                    visited[j] = True
        return output

    def __init_largest_prime_divisor_list(self, n):
        output = [None for i in range(n + 1)]
        visited = [False for i in range(n + 1)]
        visited[0] = visited[1] = True
        for i in range(2, n + 1):
            if not visited[i]:
                for j in range(i, n + 1, i):
                    output[j] = i
                    visited[j] = True
        return output

    def get_largest_prime_divisor(self, n):
        for prime in self.prime_list:
            if n % prime == 0:
                return prime
        return 1

class Problem():
    def __init__(self):
        self.number_theory = None
        self.free_elements = None

    def solve(self):
        self.get(80)

    def get(self, n):
        self.number_theory = NumberTheory(n)
        self.free_elements_map = self.__init_free_elements_map()

        prime = self.number_theory.prime_list[0]
        free_elements = self.free_elements_map[prime]
        restricted_elements = self.__get_elements(free_elements, [(0, 1)], prime)
        
        decreasing_prime_list = self.number_theory.prime_list[1:] 
        for prime in decreasing_prime_list:
            print('current prime =>', prime)
            free_elements = self.free_elements_map[prime]
            next_elements = self.__get_elements(free_elements, restricted_elements, prime)
            restricted_elements = next_elements

        for total_sum, total_frequency in restricted_elements:
            if total_sum == Fraction(1, 2):
                print('answer =>', total_frequency)

    def __init_free_elements_map(self):
        free_elements = {}
        for i in range(2, self.number_theory.n + 1): 
            divisor = self.number_theory.largest_prime_divisor_list[i]
            if divisor not in free_elements:
                free_elements[divisor] = []
            free_elements[divisor].append((Fraction(1, i**2), 1))
        return free_elements

    def __get_elements(self, free_elements, restricted_elements, largest_prime):
        element_dict = {}
        for restricted_total_sum, restricted_total_frequency in restricted_elements:
            for sub_free_elements in self.__subsets_iterator(free_elements):
                free_total_sum, free_total_frequency = self.__get_sum_and_frequency(sub_free_elements)
                total_sum = restricted_total_sum + free_total_sum
                total_frequency = restricted_total_frequency * free_total_frequency

                largest_prime_divisor = self.number_theory.get_largest_prime_divisor(total_sum.denominator)
                if largest_prime == 2 or largest_prime_divisor < largest_prime:
                    if total_sum not in element_dict:
                        element_dict[total_sum] = 0
                    element_dict[total_sum] += total_frequency 
        return self.__dict_to_list(element_dict)

    def __subsets_iterator(self, universal_set):
        universal_size = len(universal_set)
        for subset_size in range(universal_size + 1):
            for subset in itertools.combinations(universal_set, subset_size):
                yield subset

    def __get_sum_and_frequency(self, elements):
        total_sum = 0
        total_frequency = 1
        for element, frequency in elements:
            total_sum += element
            total_frequency *= frequency
        return total_sum, total_frequency

    def __dict_to_list(self, input_dict):
        return [(key, input_dict[key]) for key in input_dict]

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
