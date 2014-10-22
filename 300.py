import sys

class Folding():
    def build(self, dim):
        vaild_foldings = []
        initial_state = ([(0, 0), (0, 1)], False)
        dfs_stack = [initial_state]
        directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        while dfs_stack:
            top = dfs_stack[-1]
            dfs_stack.pop()
            if self.__is_overlapping(top):
                continue
            if len(top[0]) == dim:
                vaild_foldings.append(top[0])
                if len(vaild_foldings) % 1000 == 0:
                    print("vaild path", len(vaild_foldings), top[0])
                continue
            last_x, last_y = top[0][-1]
            for direction_x, direction_y in directions:
                next_turn = top[1]
                if top[1] is False:
                    if direction_x == -1 and direction_y == 0:
                        continue
                    elif direction_x == 1 and direction_y == 0:
                        next_turn = True
                next_spot = (last_x + direction_x, last_y + direction_y)
                next_state = (top[0] + [next_spot], next_turn)
                dfs_stack.append(next_state)
                #print(next_state)
        return vaild_foldings

    def __is_overlapping(self, state):
        folding = state[0]
        visited_spots = set([str(_) for _ in folding])
        return len(folding) != len(visited_spots)

class Problem():
    def solve(self):
        folding = Folding()
        vaild_foldings = folding.build(15)
        #print(vaild_foldings)

def main():
    problem = Problem()
    problem.solve()
    
if __name__ == '__main__':
    sys.exit(main())
