# Write a function named kthNumber which takes a list and and a number k such that
# the list is unordered and the function returns the kth number of the list corresponding
# to its increasingly ordered version. 

# >>>  kthNumber([14, 5, 3, 7, -9, 0, 1, 3, 4, -3, -11, 6, 9, -1, -3, -12], 7)
# 0
# >>>  kthNumber([14, 5, 3, 7, -9, 0, 1, 3, 4, -3, -11, 6, 9, -1, -3, -12], 12)
# 5

def kthNumber(L, k):
	sNums = []	# smaller numbers than L[0]
	lNums = []	# larger numbers than L[0]
	
	if len(L) == 0:
		return -1

	if len(L) == 1:
		return L[0]
	
	for n in L[1:]:
		if n < L[0]:
			sNums.append(n)
		else:
			lNums.append(n)
	
	if len(sNums) >= k:
		return kthNumber(sNums, k)
	elif len(sNums) == k - 1:
		return L[0]
	else:
		return kthNumber(lNums, k - len(sNums) - 1)
