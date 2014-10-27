import sys

class BlumBlumShub():
    def get(self, s0, mod):
        sequence = [s0]
        visited = set(sequence)
        s = s0
        n = 0
        while True:
            s = s**2 % mod
            n += 1
            if s in visited:
                break
            else:
                sequence.append(s)
                visited.add(s)
        return sequence

class Problem():
    def __init__(self):
        self.w = None
        self.partial_sums = None
        self.partial_sum_set = None
        
        self.__init_string()
        self.__init_partial_sums()
        self.__init_partial_sum_set()
    
    def __init_string(self):
        blum_blum_shub = BlumBlumShub()
        sequence = blum_blum_shub.get(14025256, 20300713)
        print("blum blum shub =>", len(sequence), sequence[:10], "...")
        self.w = [0]
        for s in sequence:
            self.w.extend([int(digit) for digit in str(s)])
        print("string =>", len(self.w), self.w[:10], "...")
        
    def __init_partial_sums(self):
        curr_partial_sum = self.w[0]
        self.partial_sums = [curr_partial_sum]
        for i in range(1, len(self.w)):
            curr_partial_sum += self.w[i]
            self.partial_sums.append(curr_partial_sum)
        print("partial_sums =>", len(self.partial_sums), self.partial_sums[:10], "...")

    def __init_partial_sum_set(self):
        self.partial_sum_set = set(self.partial_sums)
        print("partial_sum_set =>", len(self.partial_sum_set))
    
    def solve(self):
        self.benchmark()

    def benchmark(self):
        rv = 0
        for k in range(1, 1000 + 1):
            for z in range(1, 1000 + 1):
                if k + self.partial_sums[z - 1] in self.partial_sum_set:
                    rv += z
                    break
        print("sum =>", rv)

def main():
    problem = Problem()
    problem.solve()
    
if __name__ == '__main__':
    sys.exit(main())
