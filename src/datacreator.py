import argparse
import random
import os
import time

def dump_list(l):
    res = ""
    for item in l:
        try:
            for subitem in item:
                res += str(subitem) + ","
            res = res[:-1]
        except:
            res += str(item)
        res += ";"
    return res

def generate_students(args):
    while True:
        students = [[random.randint(1, args.X) for j in range(args.E/args.X/2, args.E/args.X)] for i in range(args.E)]
        students_check = set()
        for student in students:
            for exam in student:
                students_check.add(exam)
        student_ok = True
        for i in range(1, args.X):
            if i not in students_check:
                student_ok = False
                break
        if student_ok:
            return students

def generate_profs(args):
    while True:
        profs = [[random.randint(1, args.X) for j in range(args.P/args.X/2, random.randint(1, args.X/4))] for i in range(args.P)]
        profs_check = set()
        for prof in profs:
            for exam in prof:
                profs_check.add(exam)
        prof_ok = True
        for i in range(1, args.X):
            if i not in profs_check:
                prof_ok = False
                break
        if prof_ok:
            return profs

def generate_data(args):
    res = str(args.T) + ";" + str(args.S) + ";"
    res += dump_list([random.randint(10, 200) for i in range(args.S)])
    res += str(args.E) + ";" + str(args.P) + ";" + str(args.X) + ";"
    res += dump_list(generate_students(args))
    res += dump_list(generate_profs(args))
    return res

if __name__ == '__main__':
    parser = argparse.ArgumentParser("Creates data for SAT solver")
    parser.add_argument("filename", type=str)
    parser.add_argument("T", type=int)
    parser.add_argument("S", type=int)
    parser.add_argument("E", type=int)
    parser.add_argument("P", type=int)
    parser.add_argument("X", type=int)

    args = parser.parse_args()


    data = generate_data(args)
    if os.system("./projq4.out \"" + data + "\"") == 0:
        with open(args.filename, "w") as f:
            f.write(data)