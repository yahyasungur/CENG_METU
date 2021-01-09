
# EXAMPLE-3

# Write a script which will take the input as a list in the first line and 3 strings in the next 3 lines.
# Elements of the list are either a string or an empty list. 
# You will put those 3 strings into the empty lists in the main list and print the output list. 

# SAMPLE INPUT/OUTPUTs:

# == Input ==
# ['elma',[],'armut','uzum',[],'kayisi',[]]
# portakal
# kiraz
# muz
# == Output ==
# ['elma', ['portakal'], 'armut', 'uzum', ['kiraz'], 'kayisi', ['muz']]

# == Input ==
# [[],'ceng','math','chem','hist',[],'phys',[],'elect','mine']
# stat
# econ
# eng
# == Output ==
# [['stat'], 'ceng', 'math', 'chem', 'hist', ['econ'], 'phys', ['eng'], 'elect', 'mine']

lst = eval(input())
str1 = input()
str2 = input()
str3 = input()
index = lst.index([])
lst[index] = [str1]
index = lst.index([])
lst[index] = [str2]
index = lst.index([])
lst[index] = [str3]
print(lst)


# SOLUTION:
""" mylist = eval(input())
str1 = input()
str1 = [str1]
ind1 = mylist.index([])
mylist.remove([])
mylist.insert(ind1, str1)
str2 = input()
str2 = [str2]
ind2 = mylist.index([])
mylist.remove([])
mylist.insert(ind2, str2)
str3 = input()
str3 = [str3]
ind3 = mylist.index([])
mylist.remove([])
mylist.insert(ind3, str3)
print(mylist) """
