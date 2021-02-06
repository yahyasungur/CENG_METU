# Write a function named all_orderings which takes a list of size N and 
# returns all the permutations (orderings) of order N.

# >>> all_orderings([1,2,3])
# [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
# >>> all_orderings(['a','b', True, False])
# [['a', 'b', True, False], ['a', 'b', False, True], ['a', True, 'b', False], ['a', True, False, 'b'], ['a', False, 'b', True], ['a', False, True, 'b'], ['b', 'a', True, False], ['b', 'a', False, True], ['b', True, 'a', False], ['b', True, False, 'a'], ['b', False, 'a', True], ['b', False, True, 'a'], [True, 'a', 'b', False], [True, 'a', False, 'b'], [True, 'b', 'a', False], [True, 'b', False, 'a'], [True, False, 'a', 'b'], [True, False, 'b', 'a'], [False, 'a', 'b', True], [False, 'a', True, 'b'], [False, 'b', 'a', True], [False, 'b', True, 'a'], [False, True, 'a', 'b'], [False, True, 'b', 'a']]

def all_orderings(L):
	if len(L) == 1:
		return [L]
	R = []
	for i in range(len(L)):
		subR = all_orderings(L[:i] + L[i+1:])
		for e in subR:
			e.insert(0, L[i])	
			R.append(e)
	return R
