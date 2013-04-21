from collections import deque

f = open(argv[1], 'r')
A = deque()
for i in range(100):
	A.append(int(f.readline()))

A.sort()

while len(A) > 1:
	A.append(abs(A.popleft() - A.popleft()))

print A[0]