import random
import math
import copy

MAX_ITER = 25000
GRANULARITY = 100

def T(i): return (10**10) * ((0.8) ** math.floor(i / 300))

def gen_std(n):
	S = []
	for i in range(n):
		if random.random() < 0.5:
			S.append(1)
		else:
			S.append(-1)
	return S

def neighbor_std(S):
	i,j = 0,0
	while i == j:
		i,j = random.randrange(0,len(S)),random.randrange(0,len(S))
	S[i] = -S[i]
	if random.random() < 0.5:
		S[j] = -S[j]
	return S

def residue_std(A,S):
	return abs(sum([(a*b) for a,b in zip(A,S)]))

def gen_pp(n):
	S = []
	for i in range(n):
		S.append(random.randrange(1,n))
	return S

def neighbor_pp(S):
	i,j = 0,0
	while S[i] == j:
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

def rep_random_std(A):
	S = gen_std(len(A))
	for i in range(MAX_ITER):
		Sp = gen_std(len(A))
		if residue_std(A,Sp) < residue_std(A,S):
			S = copy.deepcopy(Sp)
		if i % GRANULARITY == 0:
			rep_random_std_lst[i / GRANULARITY] += residue_std(A,S)/50
	return residue_std(A,S)

def hill_climb_std(A):
	S = gen_std(len(A))
	for i in range(MAX_ITER):
		Sp = neighbor_std(copy.deepcopy(S))
		if residue_std(A,Sp) < residue_std(A,S):
			S = copy.deepcopy(Sp)
		if i % GRANULARITY == 0:
			hill_climb_std_lst[i / GRANULARITY] += residue_std(A,S)/50
	return residue_std(A,S)

def anneal_std(A):
	S = gen_std(len(A))
	Spp = copy.deepcopy(S)
	for i in range(MAX_ITER):
		Sp = neighbor_std(copy.deepcopy(S))
		if residue_std(A,Sp) < residue_std(A,S):
			S = copy.deepcopy(Sp)
		elif random.random() < math.exp(-(residue_std(A,Sp) - residue_std(A,S)) / T(i)):
			S = copy.deepcopy(Sp)
		if residue_std(A,S) < residue_std(A,Spp):
			Spp = copy.deepcopy(S)
		if i % GRANULARITY == 0:
			anneal_std_lst[i / GRANULARITY] += residue_std(A,Spp)/50
	return residue_std(A,Spp)

def rep_random_pp(A):
	S = gen_pp(len(A))
	for i in range(MAX_ITER):
		Sp = gen_pp(len(A))
		if residue_pp(A,Sp) < residue_pp(A,S):
			S = copy.deepcopy(Sp)
		if i % GRANULARITY == 0:
			rep_random_pp_lst[i / GRANULARITY] += residue_pp(A,S)/50
	return residue_pp(A,S)

def hill_climb_pp(A):
	S = gen_pp(len(A))
	for i in range(MAX_ITER):
		Sp = neighbor_pp(copy.deepcopy(S))
		if residue_pp(A,Sp) < residue_pp(A,S):
			S = copy.deepcopy(Sp)
		if i % GRANULARITY == 0:
			hill_climb_pp_lst[i / GRANULARITY] += residue_pp(A,S)/50
	return residue_pp(A,S)

def anneal_pp(A):
	S = gen_pp(len(A))
	Spp = copy.deepcopy(S)
	for i in range(MAX_ITER):
		Sp = neighbor_pp(copy.deepcopy(S))
		if residue_pp(A,Sp) < residue_pp(A,S):
			S = copy.deepcopy(Sp)
		elif random.random() < math.exp(-(residue_pp(A,Sp) - residue_pp(A,S)) / T(i)):
			S = copy.deepcopy(Sp)
		if residue_pp(A,S) < residue_pp(A,Spp):
			Spp = copy.deepcopy(S)
		if i % GRANULARITY == 0:
			anneal_pp_lst[i / GRANULARITY] += residue_pp(A,Spp)/50
	return residue_pp(A,Spp)

num_data_points = (MAX_ITER / GRANULARITY)
rep_random_std_lst = [0] * num_data_points
hill_climb_std_lst = [0] * num_data_points
anneal_std_lst = [0] * num_data_points
rep_random_pp_lst = [0] * num_data_points
hill_climb_pp_lst = [0] * num_data_points
anneal_pp_lst = [0] * num_data_points

for i in range(50):
	# generate random instance
	A = []
	for j in range(100):
		A.append(random.randrange(1,10**12))

	iter_result = []

	# run kk
	iter_result.append(kk(copy.deepcopy(A)))

	# run repeated random
	#print "rep_random"
	iter_result.append(rep_random_std(A))
	iter_result.append(rep_random_pp(A))

	# run hill climbing
	#print "hill_climb"
	iter_result.append(hill_climb_std(A))
	iter_result.append(hill_climb_pp(A))

	# run simulated annealing
	#print "anneal"
	iter_result.append(anneal_std(A))
	iter_result.append(anneal_pp(A))

	print " & ".join(map(lambda x: str(x),iter_result))

output_lst = [copy.deepcopy(rep_random_std_lst), copy.deepcopy(hill_climb_std_lst), copy.deepcopy(anneal_std_lst), copy.deepcopy(rep_random_pp_lst), copy.deepcopy(hill_climb_pp_lst), copy.deepcopy(anneal_pp_lst)]

f = open("graph_output.txt", "w")
for lst in output_lst:
	for i in lst:
		f.write(str(i)+"\n")
	f.write("###\n")
f.close()