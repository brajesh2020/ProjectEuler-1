import sys

class HeighwayDragon():
    def __init__(self, order):
        self.order = order

    def simulate(self, step):
        dragon = "Fa"
        rule_a = "ARBFR"
        rule_b = "LFALB"
        for i in range(self.order):
            dragon = dragon.replace("a", rule_a).replace("b", rule_b).replace("A", "a").replace("B", "b")
        curr_step = 0
        curr_pos = 0
        spot, direction = [0, 0], [0, 1]
        while curr_step < step:
            c0 = dragon[curr_pos]
            if c0 == "F":
                spot[0] += direction[0]
                spot[1] += direction[1]
                curr_step += 1
            elif c0 == "L":
                direction[0], direction[1] = -direction[1], direction[0]
            elif c0 == "R":
                direction[0], direction[1] = direction[1], -direction[0]
            curr_pos += 1
        return spot

class Problem():
    def __init__(self):
        self.spot_lg_map = {}
        self.spot_lg_map[0] = [0, 1]
        for i in range(1, 100):
            self.spot_lg_map[i] = [
                    self.spot_lg_map[i-1][0] + self.spot_lg_map[i-1][1],
                    self.spot_lg_map[i-1][1] - self.spot_lg_map[i-1][0]
            ]

    def solve(self):
        self.benchmark()
        #print(self.get(50, 10**12))
    
    def benchmark(self):
        heighway_dragon = HeighwayDragon(10)
        for step in [22]:
            print(step, heighway_dragon.simulate(step), self.get(10, step), "{0:b}".format(step))

    def get(self, order, step):
        assert(step % 2 == 0)
        bin_rep = "{0:b}".format(step)
        bin_rep_len = len(bin_rep)
        spot = list(self.spot_lg_map[bin_rep_len - 1])
        for i in range(1, bin_rep_len - 1):
            if bin_rep[i] == "1":
                print(spot, self.spot_lg_map[bin_rep_len - i - 1])
                spot[0] -= self.spot_lg_map[bin_rep_len - i - 1][0]
                spot[1] -= self.spot_lg_map[bin_rep_len - i - 1][1]
            #else:
            #    spot[0] -= self.spot_lg_map[bin_rep_len - i - 1][0]
            #    spot[1] -= self.spot_lg_map[bin_rep_len - i - 1][1]
        return spot

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
