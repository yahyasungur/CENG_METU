# Write a function named "breadthFirst" which will take an n-ary tree as argument and
# find the order of nodes according to the breadth-first traversal.
# examples:
# >>> breadthFirst([1,[2,[4],[5]],[3,[6],[7]]])
# [1, 2, 3, 4, 5, 6, 7]

from narytreefunctions import *
from stacknqueue import *

def breadthFirst(tree):
    result = []
    queue = CreateQueue() 
    result.append(datum(tree))
    for child in children(tree):
        Enqueue(child, queue)
    while not IsEmptyQueue(queue):
        item = Dequeue(queue)
        result.append(datum(item))
        for child in children(item):
            if child:
                Enqueue(child, queue)
    return result
 
print(breadthFirst([1,[2,[4],[5]],[3,[6],[7]]]))