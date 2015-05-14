import itertools
import math
import sys

class TrigonometricFunction():
    def __init__(self):
        self.sin = None
        self.cos = None
        self.__init_values()

    def __init_values(self):
        self.sin = [math.sin(math.pi * degree / 180.0) for degree in range(90 + 1)]
        self.cos = [math.cos(math.pi * degree / 180.0) for degree in range(90 + 1)]
        for degree in range(90 + 1, 180 + 1):
            self.sin.append(self.sin[180 - degree])
            self.cos.append(-self.cos[180 - degree])

    def asin(self, value):
        best_angle = 0
        best_tolerance = 100
        for degree in range(90 + 1):
            delta = abs(value - self.sin[degree])
            if delta < best_tolerance:
                best_angle = degree
                best_tolerance = delta
        return best_angle, best_tolerance

class Problem():
    def __init__(self):
        self.function = TrigonometricFunction()
        self.tolerance = 1e-9

    def solve(self):
        #self.benchmark()
        print(self.get())

    def benchmark(self):
        print(self.__is_integer_angled(90, 90, 90, 90, 45))
        print(self.__is_integer_angled(130, 80, 80, 70, 30))

    def get(self):
        count = 0
        visited = set()
        qauadrilateral_list = self.__get_qauadrilateral_list()
        print("qauadrilateral_list size =>", len(qauadrilateral_list))
        for A, B, C, D in qauadrilateral_list:
            for D_1 in range(1, D):
                B_1 = 180 - A - D_1
                if B_1 <= 0 or B_1 >= B:
                    continue
                result = self.__is_integer_angled(A, B, C, D, D_1)
                if result:
                    if result in visited:
                        #print("dup =>", result)
                        continue
                    visited |= self.__get_all_similar_qauadrilaterals(result)
                    count += 1
                    if count % 1000 == 1:
                        print(count, result, len(visited))
        return count

    def __is_integer_angled(self, A, B, C, D, D_1):
        D_2 = D - D_1
        B_1 = 180 - A - D_1
        B_2 = 180 - C - D_2

        AD = self.function.sin[B_1] / self.function.sin[A]
        CD = self.function.sin[B_2] / self.function.sin[C]
        AB = self.function.sin[D_1] / self.function.sin[A]
        CB = self.function.sin[D_2] / self.function.sin[C]
        AC = math.sqrt(AD**2 + CD**2 - 2 * AD * CD * self.function.cos[D])

        A_1, e_1 = self.function.asin(self.function.sin[D] * CD / AC)
        A_2, e_2 = self.function.asin(self.function.sin[B] * CB / AC)
        if CD**2 > AC**2 + AD**2:
            A_1 = 180 - A_1
        if CB**2 > AB**2 + AC**2:
            A_2 = 180 - A_2
        #C_1, e_3 = self.function.asin(self.function.sin[D] * AD / AC)
        #C_2, e_4 = self.function.asin(self.function.sin[B] * AB / AC)
        C_1 = 180 - D - A_1
        C_2 = 180 - B - A_2

        if e_1 < self.tolerance and e_2 < self.tolerance:# and e_3 < self.tolerance and e_4 < self.tolerance:
            assert(A_1 + A_2 == A)
            assert(C_1 + C_2 == C)
            #raise Exception()

            return A_1, D_1, D_2, C_1, C_2, B_2, B_1, A_2
            #print(A, B, C, D, "=>", A_1, D_1, D_2, C_1, C_2, B_2, B_1, A_2)
            #print("angle =>", A, B, C, D, D_1, D_2, B_1, B_2)
            #print("side =>", AD, CD, AB, CB, AC)
            #print("splitted A =>", (A_1, e_1), (A_2, e_2))
        else:
            return None

    def __get_qauadrilateral_list(self):
        result = set()
        for D in range(1, 180):
            for C in range(D, 180):
                for B in range(C, 180):
                    A = 360 - B - C - D
                    if A < B or A >= 180:
                        continue
                    result.add((A, B, C, D))
                    result.add((A, B, D, C))
                    result.add((A, C, B, D))
                    result.add((A, C, D, B))
        return result

    def __is_integer_angled_old(self, qauadrilateral):
        s_angles, t_angles = qauadrilateral
        alpha_1, beta_1, gamma_1 = s_angles
        alpha_2, beta_2, gamma_2 = t_angles
        #print(qauadrilateral)
        b_1 = self.function.sin[beta_1] / self.function.sin[alpha_1]
        b_2 = self.function.sin[beta_2] / self.function.sin[alpha_2]
        c_1 = self.function.sin[gamma_1] / self.function.sin[alpha_1]
        c_2 = self.function.sin[gamma_2] / self.function.sin[alpha_2]
        #print(b_1, b_2)
        x = math.sqrt(b_1**2 + b_2**2 - 2 * b_1 * b_2 * self.function.cos[gamma_1 + gamma_2])
        #print(x)
        alpha_1_prime, tolerance_1 = self.function.asin(self.function.sin[gamma_1 + gamma_2] * b_2 / x)
        alpha_2_prime, tolerance_2 = self.function.asin(self.function.sin[gamma_1 + gamma_2] * b_1 / x)
        alpha_1_double_prime, tolerance_3 = self.function.asin(self.function.sin[beta_1 + beta_2] * c_2 / x)
        alpha_2_double_prime, tolerance_4 = self.function.asin(self.function.sin[beta_1 + beta_2] * c_1 / x)
        
        #print(alpha_1_prime, tolerance_1)
        #print(alpha_2_prime, tolerance_2)
        #print(alpha_1_double_prime, tolerance_3)
        #print(alpha_2_double_prime, tolerance_4)

        if tolerance_1 > self.tolerance:
            return None
        if tolerance_2 > self.tolerance:
            return None
        if tolerance_3 > self.tolerance:
            return None
        if tolerance_4 > self.tolerance:
            return None
        if alpha_1 != alpha_1_prime + alpha_1_double_prime:
            return None
        if alpha_2 != alpha_2_prime + alpha_2_double_prime:
            return None
        return alpha_1_prime, gamma_1, gamma_2, alpha_2_prime, alpha_2_double_prime, beta_2, beta_1, alpha_1_double_prime
        
    def __get_all_similar_qauadrilaterals(self, qauadrilateral):
        result = set()
        #print("__get_all_similar_qauadrilaterals =>", qauadrilateral)
        reversed_qauadrilateral = qauadrilateral[::-1]
        for i in range(8):
            result.add(qauadrilateral[i:] + qauadrilateral[:i])
            result.add(reversed_qauadrilateral[i:] + reversed_qauadrilateral[:i])
        return result

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
