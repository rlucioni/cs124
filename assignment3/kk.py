import sys

f = open(sys.argv[1], 'r')
A = []
for line in f:
	A.append(int(line))

A.sort()

while len(A) > 1:
	A.insert(0,abs(A.pop() - A.pop()))

print A[0]