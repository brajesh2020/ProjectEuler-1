import sys

class Folding():
    def build(self, dim):
        vaild_foldings = []
        initial_state = ([(0, 0), (0, 1)], False)
        dfs_stack = [initial_state]
        directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        while dfs_stack:
            top_folding, top_turn = dfs_stack[-1]
            dfs_stack.pop()
            if self.__is_overlapping(top_folding):
                continue
            if len(top_folding) == dim:
                if not self.__is_bendable(top_folding):
                    vaild_foldings.append(top_folding)
                #if len(vaild_foldings) % 1000 == 0:
                print("vaild path", len(vaild_foldings), top_folding)
                continue
            last_x, last_y = top_folding[-1]
            for direction_x, direction_y in directions:
                next_turn = top_turn
                if top_turn is False:
                    if direction_x == -1 and direction_y == 0:
                        continue
                    elif direction_x == 1 and direction_y == 0:
                        next_turn = True
                next_spot = (last_x + direction_x, last_y + direction_y)
                next_state = (top_folding + [next_spot], next_turn)
                dfs_stack.append(next_state)
                #print(next_state)
        return vaild_foldings

    def __is_overlapping(self, folding):
        visited_spots = set([str(_) for _ in folding])
        return len(folding) != len(visited_spots)

    def __is_bendable(self, folding):
        N = len(folding)
        for i in range(1, N-1):
            print(folding[i])
        raise NotImplementedError()
        return False

class Problem():
    def solve(self):
        folding = Folding()
        vaild_foldings = folding.build(4)
        #print(vaild_foldings)

def main():
    problem = Problem()
    problem.solve()
    
if __name__ == '__main__':
    sys.exit(main())
