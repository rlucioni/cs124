import sys
from bisect import insort_left

f = open(sys.argv[1], 'r')
A = []
for line in f:
	A.append(int(line))

A.sort()

while len(A) > 1:
	insort_left(A,abs(A.pop() - A.pop()))

print A[0]