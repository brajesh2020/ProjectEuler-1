import sys

class GoodPrimeTable():
    def build(self, sieve_range):
        factor = 3**2 * 7 * 13 * 19
        print(factor)
        shrinked_sieve_range = sieve_range // factor
        print(shrinked_sieve_range)
        result = []
        visited = [False for _ in range(shrinked_sieve_range)]
        for i in range(2, shrinked_sieve_range):
            if visited[i] is True:
                continue
            if i % 3 == 1:
                result.append(i)
            for j in range(i + i, shrinked_sieve_range, i):
                visited[j] = True
        return result

class Problem():
    def __init__(self):
        self.sieve_range = None
        self.table = None

    def solve(self):
        self.sieve_range = 10**7
        print(self.sieve_range)
        self.table = GoodPrimeTable().build(self.sieve_range)
        x = self.get_sum_excluding_9()
        y = self.get_count_including_9()
        print('Ans:', x + y)
    
    def get_sum_excluding_9(self):
        sum = 0
        n = len(self.table)
        performance_counter = 0
        for i in range(n):
            p_i = self.table[i]
            for j in range(i + 1, n):
                p_j = self.table[j]
                p_ij = p_i * p_j
                if p_ij > self.sieve_range:
                    break
                for k in range(j + 1, n):
                    p_k = self.table[k]
                    p_ijk = p_ij * p_k
                    if p_ijk > self.sieve_range:
                        break
                    for h in range(k + 1, n):
                        p_h = self.table[h]
                        p_ijkh = p_ijk * p_h
                        if p_ijkh > self.sieve_range:
                            break
                        for t in range(h + 1, n):
                            p_t = self.table[t]
                            p_all = p_ijkh * p_t
                            if p_all > self.sieve_range:
                                break
                            q_sum = 0
                            for x in range(1, self.sieve_range // p_all + 1):
                                if x % 9 == 0 or x % p_i == 0 or p_j == 0 or p_k == 0 or p_h == 0 or p_t == 0:
                                    continue
                                q_sum += x
                            #print(x, p_all, p_i, p_j, p_k, p_h, p_t)
                            sum += q_sum * p_all
                            performance_counter += 1

                            #print('excluding 9:', p_all, self.sieve_range // p_all)
        print(sum)
        return sum

    def get_count_including_9(self):
        sum = 0
        n = len(self.table)
        #print(self.sieve_range)
        performance_counter = 0

        for i in range(n):
            p_i = self.table[i]
            p_i9 = p_i * 9
            if p_i9 > self.sieve_range:
                break
            for j in range(i + 1, n):
                p_j = self.table[j]
                p_ij = p_i9 * p_j
                if p_ij > self.sieve_range:
                    break
                for k in range(j + 1, n):
                    p_k = self.table[k]
                    p_ijk = p_ij * p_k
                    if p_ijk > self.sieve_range:
                        break
                    for h in range(k + 1, n):
                        p_h = self.table[h]
                        p_all = p_ijk * p_h
                        if p_all > self.sieve_range:
                            break
                        #print(p_all)
                        q_sum = 0
                        for x in range(1, self.sieve_range // p_all + 1):
                            if x % p_i == 0 or p_j == 0 or p_k == 0 or p_h == 0:
                                continue
                            q_sum += x
                            #print(x, p_all, p_i, p_j, p_k, p_h)
                        sum += q_sum * p_all


                        performance_counter += 1
                        #print(p_all)
        print(sum)
        return sum

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
