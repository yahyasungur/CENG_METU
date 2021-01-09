
# EXAMPLE-1

# Write a script which takes an input including a nested list. 
# By following the istructions(explained below), try to find the embedded word inside the nested list. 
# Instructions:
# - Starting from the root list, you need to visit some of the nested lists.
# - For each list you visit, you will read the first element of the list which is a number N.
# - After reading N, you need to go to Nth element of the list which is itself an other nested list. 
# - Apply the same procedure to newly visited list. After doing such 3 operations, you will reach the embedded word.
# - The embedded word is given such a way that the left half of the embedded word is in right side and the right half of the embedded word is in left side.
# - Correct the word by swapping its left and right halves, and print the corrected form of the embedded word.

# SAMPLE INPUT/OUTPUTs:

# == Input ==
# [2,[],[3,[],[[]],[1,'machinevirtual'],[[],[]]]]
# == Output ==
# virtualmachine

# == Input ==
# [3,[[]],[[[],[]],[]],[2,[[],[],[]],[3,[],[[]],'worldcrazy'],[]],[]]
# == Output ==
# crazyworld

lst = eval(input())
a = lst[0]
b = lst[a][0]
c = lst[a][b][0]
word = lst[a][b][c]
length = len(word)
word_right = word[:length//2]
word_left = word[length//2:]
print(word_left+word_right)

# SOLUTION:
""" mylist = eval(input())
ind1 = mylist[0]
temp = mylist[ind1]
ind2 = temp[0]
temp = temp[ind2]
ind3 = temp[0]
embeddedword = temp[ind3]
length = len(embeddedword)
print(embeddedword[length//2:length] + embeddedword[:length//2]) """
