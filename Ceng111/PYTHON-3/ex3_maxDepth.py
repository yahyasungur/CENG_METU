# Define a function named "maxdepth" which takes an *n-ary* tree as an argument
# and returns the depth of the deepest leaf.
# examples:
# >>> maxdepth([1, [2], [3]])
# 1
# >>> maxdepth([1, [2], [3, [4]]])
# 2
# >>> maxdepth([1, [2], [3, [4, [5]]]])
# 3
# >>> maxdepth([1, [2, [100], [1001]], [3, [4, [5]]]])
# 3
# >>> maxdepth([1, [2, [100], [1001, [3]]], [3, [4, [5]]]])
# 3
# >>> maxdepth([1, [2, [100], [1001, [3, [5]]]], [3, [4, [5]]]])
# 4
 
from narytreefunctions import *
 
def maxdepth(tree):
        if isleaf(tree):
                return 0
        else:
                return max(maxdepth_forest(children(tree))) + 1 
def maxdepth_forest(forest):
        if len(forest) == 0:
                return []
        else:
                return [maxdepth(forest[0])] + maxdepth_forest(forest[1:])
 
# Solution using iteration:
def maxdepth2(tree):
    if isleaf(tree):
        return 0
    else:
        maximum = -1
        for child in children(tree):
            cur = 1 + maxdepth2(child)
            if cur > maximum:
                maximum = cur

        return maximum
