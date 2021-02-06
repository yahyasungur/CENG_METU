
# EXAMPLE-3

# Write a function whose name is "textEdit" for a small text editor. 
# Your textEditor should have two important functionalities:

# 	1) There should be a space between consecutive sentences and each sentence should start with a capital letter. 
#	   So, if the text are not in this form, your function should fix this.
# 	2) Your function should also count the number of words in the text. However "the" is not included in these words.

# You will add  these two functionalities by "textEdit" function. Your function has two parameters. 
# First one is the name of the operation which can be "FIX"(putting spaces between sentences and capitalizing) and 
# "CW"(count words.) Second parameter is a string. There are 4 sentences in the second parameter. 
# Your funcion should return fixed text if the operation is FIX. 
# Otherwise, your function should return number of words(except the word "the") in the sentences.  
# Note: Assume that each sentence finishes with a dot and there will be no dot used other than this purpose. 
# Also, there will not be spaces between sentences in the text entered as parameter. Hint :count() upper()

def textEdit(operation,text):
	the_num = text.count("the") + text.count("The")
	lst = text.split(".")
	if operation == "FIX":
		cap1 = lst[0][0].upper()
		cap2 = lst[1][0].upper()
		cap3 = lst[2][0].upper()
		cap4 = lst[3][0].upper()
		return cap1+lst[0][1:]+". "+cap2+lst[1][1:]+". "+cap3+lst[2][1:]+". "+cap4+lst[3][1:]
	elif operation == "CW":
		return lst[0].count(" ") + lst[1].count(" ") + lst[2].count(" ") + lst[3].count(" ") + 4 - the_num

# SAMPLE INPUT/OUTPUTs:
# == Input ==
print(textEdit("FIX","Hello world.Have a good quiz.today is sunny.ceng111 is not hard"))
# == Output ==
# 'Hello world. Have a good quiz. Today is sunny. Ceng111 is not hard'

# == Input ==
print(textEdit("CW","the school is crowded.the balloon fell down.Life is good.I am an engineer"))
# == Output ==
# 13

# SOLUTION:
""" def textEdit(op,text):
	if op=="FIX":
		lstSentences = text.split(".")
		sentence1 = lstSentences[0][0].upper()+lstSentences[0][1:]
		sentence2 = lstSentences[1][0].upper()+lstSentences[1][1:]
		sentence3 = lstSentences[2][0].upper()+lstSentences[2][1:]
		sentence4 = lstSentences[3][0].upper()+lstSentences[3][1:]
		fixedText= sentence1+". "+sentence2+". "+sentence3+". "+sentence4
		return fixedText
	if op=="CW":
		lstSentences = text.split(".")
		lstSentence1 = lstSentences[0].split(" ")
		lstSentence2 = lstSentences[1].split(" ")
		lstSentence3 = lstSentences[2].split(" ")
		lstSentence4 = lstSentences[3].split(" ")
		totalWords = len(lstSentence1)+len(lstSentence2)+len(lstSentence3)+len(lstSentence4)
		numberOfthes = lstSentence1.count("the")+lstSentence2.count("the")+lstSentence3.count("the")+lstSentence4.count("the")
		return totalWords-numberOfthes """