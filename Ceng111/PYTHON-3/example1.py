# ####### CENGCLASS VPL EXAMPLE #######
# EXAMPLE-1 (Actify)

# Write a function named "actify" which takes a passive sentence in the form:
#
#     Object + 'is'/'are' + <Passive Verb> + 'by' + <Object Pronoun>.
#
# Examples:
#
#  ['the', 'beatles', 'are', 'liked', 'by', 'her']
#  ['the', 'case', 'is', 'investigated', 'by', 'them']
#  ['the', 'cases', 'are', 'investigated', 'by', 'us']
#
# This argument is a list of N strings.
# The last string is a pronoun that specifies the subject that does the
# action: it may be singular or plural. It can be one of the following: him,
# , her, us, them.
# The string before that is always 'by'.
# The string before that is the passive verb,
# the string before that is 'is'/'are',
# the remaining N-4 strings at the beginning together form the object.
# All letters are in small-case. The sentence is guaranteed to be simple
# present passive with a regular verb, and always in the form <verb>+'d'.
#
# The function actify will convert the passive sentence into active form:
#
#    Subject + Verb + Object.
#
# The singularity/plurality must be taken care of. If the original subject is
# plural, the passive verb must be made singular (by removing the 'd', the verb
# is guaranteed to end with 'e'). If the original subject was singular,
# 's' must be added to the verb.
#
# Example outputs:
#  ['she', 'likes', 'the', 'beatles']
#  ['they', 'investigate', 'the', 'case']
#  ['we', 'investigate', 'the', 'cases']
#
# SPECIFICATIONS:
# - Your script should return the resulting LIST after the operation.
# - You must not import any modules.
# - You cannot use loops, etc.
# - You may use conditional statements
# - You may define functions.
# - You may use built-in functions.
# - You must not print anything.
# - Write your code inside a script and save it as ~/q4.py (under the home directory).
# - Submit your script to CengClass system.
#

# SOLUTION:
def actify(sentence):
    verb = sentence[-3][:-1]
    obj = sentence[:-4]
    pronoun = sentence[-1]

    if (pronoun == "him"):
        subject = "he"
        verb = verb + "s"
    if (pronoun == "her"):
        subject = "she"
        verb = verb + "s"
    if (pronoun == "us"):
        subject = "we"
    if (pronoun == "them"):
        subject = "they"

    return [subject] + [verb] + obj


# SAMPLE INPUT/OUTPUTs:
# == Input ==
print( actify(['the', 'beatles', 'are', 'liked', 'by', 'her']) )
# == Output ==
# ['she', 'likes', 'the', 'beatles']

# == Input ==
print( actify(['the', 'case', 'is', 'investigated', 'by', 'them']) )
# == Output ==
# ['they', 'investigate', 'the', 'case']

# == Input ==
print( actify(['the', 'cases', 'are', 'investigated', 'by', 'us']) )
# == Output ==
# ['we', 'investigate', 'the', 'cases']