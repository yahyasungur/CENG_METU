
# EXAMPLE-4

# Write a script which will take input as a list of 3 groups of strings where each group is separated by a pipe '|'. 
# Your solution will print a list which compounds all 3 groups in a special order. 
# The ordering will be done in the following way: 
# elements of group1 in the original order + elements of group3 in the reversed order + elements of group2 in the original order.

# SAMPLE INPUT/OUTPUTs:

# == Input ==
# jack,nicole,sissy,mary|rose,ted|x,marty,y
# == Output ==
# ['jack', 'nicole', 'sissy', 'mary', 'y', 'marty', 'x', 'rose', 'ted']

# == Input ==
# m,nancy,joey,jessy,r|x,y|a,bob,liz,k
# == Output ==
# ['m', 'nancy', 'joey', 'jessy', 'r', 'k', 'liz', 'bob', 'a', 'x', 'y']

lst = input()
splited = lst.split("|")
gr1 = splited[0].split(",")
gr2 = splited[1].split(",")
gr3 = splited[2].split(",")
lst = gr1 + gr3[::-1] + gr2
print(lst)

# SOLUTION:
""" mystring = input()
ind1 = mystring.find('|')
group1 = mystring[:ind1]
ind2 = mystring[ind1+1:].find('|')
group2 = mystring[ind1+1:ind1+1+ind2]
group3 = mystring[ind1+1+ind2+1:]
group1 = group1.split(',')
group2 = group2.split(',')
group3 = group3.split(',')
group3 = group3[::-1]
group1 += group3	# group1.extend(group3)
group1 += group2	# group1.extend(group2)
print(group1) """