import random

MAX_ITER = 25000

def gen_std(n):
	S = []
	for i in range(n):
		if random.random() < 0.5:
			S[i] = 1
		else:
			S[i] = -1
	return S

def neighbor_std(S):
	i,j = 0,0
	while i = j:
		i,j = random.randrange(0,len(S)),random.randrange(0,len(S))
	S[i] = -S[i]
	if random.random() < 0.5:
		S[j] = -S[j]
	return S

def residue_std(A,S):
	return sum([(a*b) for a,b in zip(A,S)])

def gen_pp(n):
	S = []
	for i in range(n):
		S[i] = random.randrange(0,n)
	return S

def neighbor_pp(S):
	i,j = 0,0
	while S[i] = j:
		i,j = random.randrange(0,len(S)),random.randrange(0,len(S))
	S[i] = j
	return S

def residue_pp(A,S):
	Ap = [0] * len(A)
	for i in range(len(A)):
		Ap[S[i]] += A[i]
	return kk(Ap)

def kk(A):
	A.sort()
	while len(A) > 1:
		A.insert(0,abs(A.pop() - A.pop()))
	return A[0]

def rep_random(A):
	pass

def hill_climb(A):
	pass

def anneal(A):
	pass

for i in range(50):
	# generate random instance
	A = []
	for j in range(100):
		A.append(random.randrange(0,10**12))

	# run kk
	kk_result = kk(A)

	# run repeated random

	# run hill climbing

	# run simulated annealing