import sys

class Problem():
    def __init__(self):
        self.goal = 100
        self.values = {}

    """
    The probability = 1/2 P(0, 0) + 1/2 P(1, 0)
    """
    def solve(self):
        prob = (self.get(0, 0) + self.get(1, 0)) / 2
        print('{0:.8f}'.format(prob))

    """
    returns the probability P(n, m) of Player #2 winning the game 
    where Player #1 gets n points and Player #2 gets m points.
    """
    def get(self, n, m):
        if m >= self.goal:
            return 1
        if n >= self.goal:
            return 0

        if n not in self.values:
            self.values[n] = {}
        if m not in self.values[n]:
            t = 1
            is_goaled = False
            max_so_far = 0
            while not is_goaled:
                next_n = n + 1
                next_m = m + 2**(t - 1)
                if next_m >= self.goal:
                    is_goaled = True
                prob = (self.get(next_n, next_m) + self.get(n, next_m) + (2**t - 1) * self.get(next_n, m)) / (2**t + 1) 
                max_so_far = max(max_so_far, prob)
                t += 1
            self.values[n][m] = max_so_far
        return self.values[n][m]

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())