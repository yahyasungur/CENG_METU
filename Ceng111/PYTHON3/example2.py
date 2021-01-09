# ####### CENGCLASS VPL EXAMPLE #######
# EXAMPLE-2 (Number To Word Converter)

# In this task, you are expected to write a function named number_to_words that converts a given integer 
# (between -99 and 99) into words.  
# For instance, when 23 is provided, the function should return the string "twenty three".


# SOLUTION:
def number_to_words(value):
    tens_extra = ["eleven", "twelve", "thirteen", "fourteen", "fifteeen", "sixteen", "seventeen", "eighteen", "nineteen"]
    ones = ["zero", "one", "two", "three","four", "five", "six", "seven", "eight", "nine"]
    tens = ["ten", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"]
    value = str(value)
    read_string = ""
    if value[0] == "-":
        read_string += "negative "
        value = value[1:]
    if len(value) == 2:
        if value == "10":
            read_string += "ten"
        elif value[0] == "1":
            read_string += tens_extra[int(value[1])-1]
        else:
            read_string += tens[int(value[0])-1]
            if value[1] == "0":
                pass
            else:
                read_string += " "+ ones[int(value[1])]
    elif len(value) == 1:
        read_string += ones[int(value)]
    return read_string


# SAMPLE INPUT/OUTPUTs:
# == Input ==
print(number_to_words(24))
# == Output ==
# twenty four

# == Input ==
print(number_to_words(-46))
# == Output ==
#negative forty six

# == Input ==
print(number_to_words(-11))
# == Output ==
#negative eleven

# == Input ==
print(number_to_words(63))
# == Output ==
#sixty three