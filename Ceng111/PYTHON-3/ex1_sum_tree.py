# Define a function named "sum_tree" which sums all the numbers in an
# *n-ary* tree.
# examples:
# >>> print (sum_tree([1, [2, [3]], [4, [8], [9], [11]]]))
# 38
# >>> print( sum_tree([1, [2], [3], [4]]))
# 10
 
from narytreefunctions import *
 
def sum_tree(tree):

    if isleaf(tree):
        return datum(tree)
    else:
        return datum(tree) + sum_forest(children(tree))
 
def sum_forest(forest):
    if len(forest) == 0:
        return 0
    else:
        return sum_tree(forest[0]) + sum_forest(forest[1:])