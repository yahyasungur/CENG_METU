
# EXAMPLE-1

#A student must attend a seminar in a week and s/he should stay at least 60 minutes in a seminar to be accepted. 
#The time that students enter and leave are recorded. Your aim is to write a function whose name is "isAccepted" 
#which takes one parameter as a list in the form of [<hour>:<minute>,<hour>:<minute>] 
#Note that the enter and leave times are not ordered in the list. 
#You should PRINT "Accepted" if the time that is spent is greater than 60 minutes, 
#otherwise you should PRINT "Rejected". Your function should also RETURN number of minutes spent on that seminar

# SAMPLE INPUT/OUTPUTs:
# == Input ==
#print( isAccepted(["3:56","4:45"]) )
# == Output ==
# Rejected
# 49

# == Input == 
#print( isAccepted(["14:25","12:55"]) )
# == Output ==
# Accepted
# 90

def isAccepted(times):
    first = times[0].split(":")
    second = times[1].split(":")
    
    if int(first[0]) > int(second[0]):
		temp = first
        first = second
        second = temp
    elif int(first[0]) == int(second[0]) and int(first[1]) > int(second[1]):
        temp = first
        first = second
        second = temp
    hour = int(second[0]) - int(first[0])
    
    if int(first[1]) > int(second[1]):
        minute = int(first[1]) - int(second[1])
        time = hour*60 - minute
    else:
        minute = int(second[1]) - int(first[1])
        time = hour*60 + minute
    
    if time > 60 :
        print("Accepted")
    else:
        print("Rejected")
        
    return time


# SOLUTION:
""" def isAccepted(time):
	time1= time[0].split(":")
	time2= time[1].split(":")
	timeDifference = 0
	if int(time1[0])==int(time2[0]):
		if int(time1[1])<=int(time2[1]):
			timeDifference = int(time2[1]) - int(time1[1])
	else:
		time1Mnt = int(time1[0])*60 + int(time1[1])
		time2Mnt = int(time2[0])*60 + int(time2[1])
		if int(time1[0])<int(time2[0]):
			timeDifference = time2Mnt - time1Mnt
		else:
			timeDifference = time1Mnt - time2Mnt
	if timeDifference >= 60:
		print("Accepted")
	else:
		print("Rejected")
	return timeDifference """


