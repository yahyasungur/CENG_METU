
# EXAMPLE-4

# Write a function named "edit", which edits the string given as argument and
# returns the newly created string. This function either deletes or inserts
# characters from/to the string according to the mode argument.
# Edit function takes 5 arguments:
# - first argument is the string you need to change.
# - second argument (mode) is a one character string, specifies the action.
#   if the mode is "w",
# 	 the third argument, must be written to the first argument at the specified
#    position with fifth argument. If the end of string is reached before
#    writing the whole string, write the part of string that fits the string
#    (i.e. the length of the string must not change). the fourth argument is
#    not used in this mode.
#   if mode is "d",
#	 n characters beginning from the specified position (fifth argument)
#    must be deleted (put "_" for each character of word). If end of line is
#	 reached before deleting n characters, delete until the end of string.
#    third argument is not used in this mode.
# - third argument is the string to be written.
# - fourth argument is the integer that specifies how many characters will
#	be deleted.
# - fifth argument is an integer, which holds the indexes for the operation
#   that will be carried out (i.e. specifies where to delete or insert
#   characters).
#
# SPECIFICATIONS:
# - If nothing is written at the specified position, it means it is "_".
# - Your script should return the resulting STRING after the operations.
# - fourth argument is always positive
# - You must not import any modules.
# - You cannot use loops, etc.
# - You may use conditional statements
# - You may define functions.
# - You may use built-in functions.
# - You must not print anything.
# - Write your code inside a script and save it as ~/q4.py (under the home directory).
# - Submit your script to CengClass system.
#
# HINT: Strings are immutable

def edit(string,operation,insert,num,index):
  lst = list(string)
  lst_insert = list(insert)
  length = len(lst)
  length_insert = len(lst_insert)
  if operation == "w":
    lst = lst[:index] + lst_insert + lst[index+length_insert:]
    return "".join(lst[:length])
  if operation == "d":
    lst = "".join(lst[:index])+ num*"_" + "".join(lst[index+num:])
    return lst[:length]

# SAMPLE INPUT/OUTPUTs:
# == Input ==
print(edit("s________f", "w", "ceng111", -1, 1))
# == Output ==
# sceng111_f

# == Input ==
print(edit("s________f", "w", "ceng111", -1, 6))
# == Output ==
# s_____ceng

# == Input ==
print(edit("_ceng111", "d", "", 4, 1))
# == Output ==
# _____111

# == Input ==
print(edit("_ceng111", "d", "", 5, 5))
# == Output ==
# _ceng___

# SOLUTION:
""" def edit(str1, mode, str2, n, cursor):
    lineLength = len(str1)

    if (mode == "w"):
      length = len(str2)
    if (mode == "d"):
      length = n

    if (cursor + length > lineLength):
      length = lineLength-cursor

    if (mode == "w"):
      return str1[:cursor] + str2[:length] + str1[(length + cursor):]
    if (mode == "d"):
      return str1[:cursor] + length * "_" + str1[(length + cursor):] """







