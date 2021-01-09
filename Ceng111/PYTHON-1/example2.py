
# EXAMPLE-2

#   Write a Python script which does the following:
# - It takes 2 strings (say K and S) as input from the user: K is a small string representing 
#   a keyword and S is a big string consisting of 3 substrings separated by '/'.
# - Numbering each substring from 0 to 2, your script should find which substring includes the 
#   keyword K and call its number as ind1. Then, indexing each item from 0 to N in the related 
#   substring, your script should find the index of the keyword K in that substring and call the
#   index as ind2.
# - In the end, your script should print a list whose elements are the items of the related 
#   substring with just some difference: In the index <ind2> of the resulted list, there will be 
#   the string '<ind1>-<ind2>' instead of the keyword K.

# SPECIFICATIONS:
# - The inputs K and S will be given in separete lines.
# - Each substring is separated by a space '/' and each item of a substring is separated by a ','.
# - It is guaranteed that exactly 1 substring of the the second input string will include the
#   keyword K, and there will be exactly 1 occurence of the keyword K in the related substring.
# - The second input string will consist of 3 substrings; however, it is not known how many items
#   there will be in those substrings. 
# - You must NOT import any modules.
# - You can NOT use conditional statements, loops, etc.
# - You can NOT define functions.
# - You may use built-in functions.
# - Write your code inside a script named q3.py and save it under the home directory.
# - Submit your script to CengClass system.

# SAMPLE INPUT/OUTPUTs:

# == Input ==
# password
# hey,whats,up/hard,password/hidden,words
# == Output ==
# ['hard', '1-1']

# == Input ==
# econ
# ceng,math/stat,eng,ee,econ,mine/phys,chem
# == Output ==
# ['stat', 'eng', 'ee', '1-3', 'mine']

K = input()
S = input()

splited = S.split('/')
first = splited[0].split(",")
second = splited[1].split(",")
third = splited[2].split(",")
S = first + ["/"] + second + ["/"] + third
index = S.index(K)
ind1 = S[:index].count("/")
innerS = splited[ind1].split(",")
ind2 = innerS.index(K)
print(innerS[:ind2]+[str(ind1)+"-"+str(ind2)]+innerS[ind2+1:])

# SOLUTION:
""" word = input()
mystr = input()
mylist = mystr.split('/')
newlist = mylist[0].split(',') + ['/'] + mylist[1].split(',') + ['/'] + mylist[2].split(',')
wordIndex = newlist.index(word)
ind1 = newlist[:wordIndex].count('/')
relatedList = mylist[ind1].split(',')
ind2 = relatedList.index(word)
print(relatedList[:ind2] + [str(ind1)+'-'+str(ind2)] + relatedList[ind2+1:]) """