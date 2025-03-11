
import time
import random


def makeMatrix(n):
    return [[random.random() for _ in range(n)] for _ in range(n) ]

def makeZeroMatrix(n):
    return [[0.0 for _ in range(n)] for _ in range(n) ]

def mulMatrix(n,a,b,c):
    for i in range(n):
        for j in range(n):
            for k in range(n):
                c[i][j] += a[i][k]*b[k][j]


if __name__ == '__main__':
    # N = 500

    for N in range(1,101):
        avdtime = 0.0
        for _ in range(10):
            a = makeMatrix(N)
            b = makeMatrix(N)
            c = makeZeroMatrix(N)
            
            start = time.time()
            mulMatrix(N,a,b,c)
            end = time.time()
            avdtime += 0.1*(end-start)
        print(N,"\t",avdtime)