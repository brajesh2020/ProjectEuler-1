import itertools
import sys

class Problem():
    def solve(self):
        # real: 182m33.553s
        # user: 182m27.017s
        # sys: 0m0.280s
        print(self.get(12, 10))

    def get(self, base, smallest_count):
        total_sum = 0
        curr_smallest_count = 0
        for digit_array in itertools.permutations(range(base)):
            if digit_array[0] == 0:
                continue
            if curr_smallest_count == smallest_count:
                break
            
            number = self.digit_array_to_number(digit_array, base)
            if self.is_super_pandigital_number(number, base):
                print("[DEBUG]", digit_array, number)
                total_sum += number
                curr_smallest_count += 1
        return total_sum

    def is_super_pandigital_number(self, number, max_base):
        for base in range(2, max_base + 1):
            if not self.is_pandigital_number(number, base):
                return False
        return True

    def is_pandigital_number(self, number, base):
        digit_array = self.number_to_digit_array(number, base)
        for digit in range(base):
            if digit not in digit_array:
                return False
        return True

    def digit_array_to_number(self, digit_array, base):
        number = 0
        for digit in digit_array:
            number = number * base + digit
        return number

    def number_to_digit_array(self, number, base):
        digit_array = []
        curr_number = number
        while curr_number > 0:
            digit_array.insert(0, curr_number % base)
            curr_number = curr_number // base
        return digit_array

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
