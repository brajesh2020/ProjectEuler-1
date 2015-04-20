from fractions import Fraction
import itertools
import sys

class BruteForceMethod():
    def get(self, r):
        interior_points = self.__get_interior_points(r)

        partition = self.__partition(interior_points)
        print(r, '=>', interior_points, '=>', partition)

        count = 0
        for i in range(8):
            for j in range(i, 8):
                RR_count = 0
                for p1 in partition[i]:
                    for p2 in partition[j]:
                        for k in range(j, 8):
                            for p3 in partition[k]:
                                if self.__contains_origin(p1, p2, p3):
                                    #print(k)
                                    RR_count += 1
                print(i, j, 'RR_count =>', RR_count)
                count += RR_count
        print('RR =>', count)    



        count = 0
        for p1, p2, p3 in itertools.combinations(interior_points, 3):
            if self.__contains_origin(p1, p2, p3):
                count += 1
                #print(p1, p2, p3)
        return count

    def __partition(self, interior_points):
        partition = [[] for i in range(8)]
        for p in interior_points:
            x, y = p
            if x > 0 and y == 0:
                partition[0].append(p)
            elif x > 0 and y > 0:
                partition[1].append(p)
            if x == 0 and y > 0:
                partition[2].append(p)
            elif x < 0 and y > 0:
                partition[3].append(p)
            if x < 0 and y == 0:
                partition[4].append(p)
            elif x < 0 and y < 0:
                partition[5].append(p)
            if x == 0 and y < 0:
                partition[6].append(p)
            elif x > 0 and y < 0:
                partition[7].append(p)
        return partition

    def __get_interior_points(self, r):
        result = set() 
        result |= self.__get_points_on_line(1, 0, r) 
        result |= self.__get_points_on_line(0, 1, r) 
        result |= self.__get_points_on_line(1, 1, r)
        stack = [(0, 1, 1, 1)]
        while stack:
            a, b, c, d = stack.pop()
            n = a + c
            m = b + d
            if m > r or n > r:
                continue
            result |= self.__get_points_on_line(m, n, r)
            result |= self.__get_points_on_line(n, m, r)
            stack.append((a, b, n, m))
            stack.append((n, m, c, d))
        return result

    def __get_points_on_line(self, x, y, r):
        result = []
        c = x**2 + y**2
        r2 = r**2
        for i in range(1, r):
            if c * i**2 >= r2:
                break
            result.append((i * x, i * y))
            result.append((-i * x, i * y))
            result.append((-i * x, -i * y))
            result.append((i * x, -i * y))
        return set(result)

    def __contains_origin(self, p1, p2, p3):
        x1, y1 = p1
        x2, y2 = p2
        x3, y3 = p3
        x, y = 0, 0
        a = self.__double_area(x1, y1, x2, y2, x3, y3)
        a1 = self.__double_area(x, y, x2, y2, x3, y3)
        a2 = self.__double_area(x1, y1, x, y, x3, y3)
        a3 = self.__double_area(x1, y1, x2, y2, x, y)
        if a1 == 0 or a2 == 0 or a3 == 0:
            return False
        return (a == a1 + a2 + a3)

    def __double_area(self, x1, y1, x2, y2, x3, y3):
       return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)))



class Problem():
    def solve(self):
        for n in [105]:
            #print(n, '=>', self.get_naive(n), self.get(n))
            print(n, '=>', self.get(n))
            #print(n, '=>', self.get_naive(n))

    def get_naive(self, n):
        return BruteForceMethod().get(n)

    def get(self, n):
        axis_class_count = n - 1
        count_map = self.__get_point_class_count_map(n)
        quadrant_total_count = sum(count_map.values())
        print('quadrant_total_count =>', quadrant_total_count)
        print('count_map size =>', len(count_map))


        point_class_list = sorted(list(count_map.keys()))
        point_class_list_len = len(point_class_list)
        #print(count_map)
        #print(point_class_list)
        quadrant_accumulated_count = [0]
        accumulated = 0
        for key in point_class_list:
            accumulated += count_map[key]
            quadrant_accumulated_count.append(accumulated)
        #print(quadrant_accumulated_count)


        # (R0, R1) => R5
        R0_R1_count = 0
        for i in range(point_class_list_len):
            c = axis_class_count * count_map[point_class_list[i]]
            f = quadrant_accumulated_count[i]
            R0_R1_count += c * f
        print('R0_R1_count =>', R0_R1_count)    

        # (R0, R2) => R5 exactly.
        R0_R2_count = axis_class_count * axis_class_count * quadrant_total_count
        print('R0_R2_count =>', R0_R2_count)

        # (R0, R3) => R5 exactly + R6 exactly + R7
        R0_R3_count = 0
        #R0_R3_count = quadrant_total_count * quadrant_total_count + R0_R1_count + quadrant_total_count * axis_class_count
        for i in range(point_class_list_len):
            c = axis_class_count * count_map[point_class_list[i]]
            f = (quadrant_total_count - quadrant_accumulated_count[i] - count_map[point_class_list[i]]) + quadrant_total_count + axis_class_count
            R0_R3_count += c * f
        print('R0_R3_count =>', R0_R3_count)

        # (R1, R1) => R5
        R1_R1_count = 0
        for i in range(point_class_list_len - 1):
            if i % 10 == 0:
                print(i, '=>', R1_R1_count)
            for j in range(i + 1, point_class_list_len):
                c = count_map[point_class_list[i]] * count_map[point_class_list[j]]
                f = quadrant_accumulated_count[j] - quadrant_accumulated_count[i + 1]
                R1_R1_count += c * f 
        print('R1_R1_count =>', R1_R1_count)

        # (R1, R2) => R5
        R1_R2_count = R0_R1_count
        print('R1_R2_count =>', R1_R2_count)

        # (R1, R3) => R5 + R6 exactly + R7
        R1_R3_count = 0
        for i in range(point_class_list_len):
            if i % 10 == 0:
                print(i, '=>', R1_R3_count)
            for j in range(point_class_list_len):
                c = count_map[point_class_list[i]] * count_map[point_class_list[j]]
                f = quadrant_accumulated_count[i] + axis_class_count + quadrant_accumulated_count[j]
                R1_R3_count += c * f
        print('R1_R3_count =>', R1_R3_count)

        # (R1, R4) => R5 + R6 exactly + R7 exactly
        R1_R4_count = R0_R3_count
        print('R1_R4_count =>', R1_R4_count)

        # (R1, R5) with angle(A) > angle(B) => R5 + R6 exactly + R7 exactly
        R1_R5_count = 0
        for i in range(point_class_list_len - 1):
            if i % 10 == 0:
                print(i, '=>', R1_R5_count)            
            for j in range(i + 1, point_class_list_len):
                c = count_map[point_class_list[i]] * count_map[point_class_list[j]]
                f = (quadrant_total_count - quadrant_accumulated_count[j] - count_map[point_class_list[j]]) + axis_class_count + quadrant_total_count
                R1_R5_count += c * f
        print('R1_R5_count =>', R1_R5_count)

        # (R2, R3) => R7
        R2_R3_count = R0_R1_count
        print('R2_R3_count =>', R2_R3_count)

        # (R2, R4) => R7 exactly
        R2_R4_count = R0_R2_count
        print('R2_R4_count =>', R2_R4_count)

        # (R2, R5) => R7 exactly (R0, R1 are ignored)
        R2_R5_count = axis_class_count * quadrant_total_count * quadrant_total_count
        print('R2_R5_count =>', R2_R5_count)

        # (R3, R3) => R7
        R3_R3_count = R1_R1_count
        print('R3_R3_count =>', R3_R3_count)

        # (R3, R4) => R7
        R3_R4_count = R0_R1_count
        print('R3_R4_count =>', R3_R4_count)

        # (R3, R5) => R7 (R0, R1 are ignored)
        R3_R5_count = 0
        for i in range(point_class_list_len):
            c = quadrant_total_count * count_map[point_class_list[i]]
            f = quadrant_accumulated_count[i]
            R3_R5_count += c * f
        print('R3_R5_count =>', R3_R5_count)    

        # (R3, R6) => R7
        R3_R6_count = R0_R1_count
        print('R3_R6_count =>', R3_R6_count)    

        # (R3, R7) => R7
        R3_R7_count = 0
        for i in range(point_class_list_len - 1):
            if i % 10 == 0:
                print(i, '=>', R3_R7_count)                        
            for j in range(i + 1, point_class_list_len):
                c = count_map[point_class_list[i]] * count_map[point_class_list[j]]
                f = quadrant_accumulated_count[i]
                R3_R7_count += c * f 
        print('R3_R7_count =>', R3_R7_count)    



        total_count = R0_R1_count + R0_R2_count + R0_R3_count \
                + R1_R1_count + R1_R2_count + R1_R3_count + R1_R4_count + R1_R5_count \
                + R2_R3_count + R2_R4_count + R2_R5_count \
                + R3_R3_count + R3_R4_count + R3_R5_count + R3_R6_count + R3_R7_count
        print('total_count =>', total_count)

        return total_count

    def __get_point_class_count_map(self, r):
        count_map = {}
        count_map[Fraction(1, 1)] = self.__get_count_on_line(1, 1, r)
        stack = [(0, 1, 1, 1)]
        while stack:
            a, b, c, d = stack.pop()
            n = a + c
            m = b + d
            if m > r or n > r:
                continue
            count = self.__get_count_on_line(n, m, r)
            if count != 0: 
                count_map[Fraction(n, m)] = count
                count_map[Fraction(m, n)] = count
            stack.append((a, b, n, m))
            stack.append((n, m, c, d))
        return count_map

    def __get_count_on_line(self, x, y, r):
        c = x**2 + y**2
        r2 = r**2
        for i in range(1, r):
            if c * i**2 >= r2:
                return i - 1
        return r - 1

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())
