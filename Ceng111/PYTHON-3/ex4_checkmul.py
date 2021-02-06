# Write a function named "checkmul" which will take an *n-ary* tree as its
# argument and check the tree according to the following rule and return
# True (obeys the rule) or False (does not obey the rule).
# Rule: Each node (except leaf nodes) are equal to the product of values of
# its child nodes.
# Note: Each node holds a number and the tree is an *n-ary* tree.
# examples:
# >>> checkmul([300, [3], [5], [10], [2]])
# True
# >>> checkmul([-210, [7], [-10, [-1], [5], [2]], [3]])
# True
# >>> checkmul([-210, [7], [-10, [-2], [5], [2]], [3]])
# False
 
from narytreefunctions import *
 
def checkmul(tree):
    if isleaf(tree):
        return True
 
    mult_child = 1
    for e in children(tree):#calculate multiplication of children datum
            mult_child *= datum(e)
 
    if datum(tree) == mult_child:
        return checkmul_helper(children(tree))
    else:
        return False
 
def checkmul_helper(forest):
    result = True
    for e in forest:
        result = result and checkmul(e)
        if not result: # break if False is encountered
            break      # avoids unnecesary iteration
    return result
 

# Using iteration: 
def checkmul2(tree):
    if isleaf(tree):
        return True
    else:
        ret = 1
        for child in children(tree):
            ret *= datum(child)
        if ret == datum(tree):
            for child in children(tree):
                if not checkmul2(child):
                    return False
            return True
        else:
            return False
 
# Using recursion:
def checkmul3(tree):
    if isleaf(tree):
        return True
    elif children_mul(children(tree)) == datum(tree):
        return checkmul_forest(children(tree))
    else:
        return False
 
def children_mul(forest):
    if len(forest) == 0:
        return 1
    else:
        return datum(forest[0]) * children_mul(forest[1:])
 
def checkmul_forest(forest):
    if len(forest) == 0:
        return True
    else:
        return checkmul3(forest[0]) and checkmul_forest(forest[1:])