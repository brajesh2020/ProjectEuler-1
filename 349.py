class LangtonAntSimulator():
    def __init__(self):
        self.bound = 120
    
    def simulate(self, step=12000):
        board = [[True for _ in range(self.bound)] for _ in range(self.bound)]
        ant_pos = [self.bound * 3 // 4, self.bound // 2]
        ant_direction = [1, 0]
        for i in range(step):
            x, y = ant_pos
            assert(x >= 0 and x < self.bound and y >= 0 and y < self.bound)
            if board[x][y] is True:
                board[x][y] = False
                ant_direction = [ant_direction[1], -ant_direction[0]]
                ant_pos = [ant_pos[0] + ant_direction[0], ant_pos[1] + ant_direction[1]]
            else:
                board[x][y] = True
                ant_direction = [-ant_direction[1], ant_direction[0]]
                ant_pos = [ant_pos[0] + ant_direction[0], ant_pos[1] + ant_direction[1]]
            if i in [11000, 11208, 11416]:
                self.debug(board)
                print(i, self.count_black(board))

    def debug(self, board):
        print('+' + '-' * self.bound + '+')
        for row in board:
            row_string = ''
            has_black = False
            for cell in row:
                if cell is True:
                    row_string += ' '
                else:
                    row_string += '#'
                    has_black = True
            if has_black:
                print('|' + row_string + '|')
        print('+' + '-' * self.bound + '+')

    def count_black(self, board):
        count = 0
        for row in board:
            for cell in row:
                if cell is False:
                    count += 1
        return count

class Problem():
    def solve(self):
        simulator = LangtonAntSimulator()
        simulator.simulate()

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    import sys
    sys.exit(main())
