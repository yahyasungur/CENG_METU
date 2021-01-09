
# EXAMPLE-3

# Write a function that takes two arguments whose name is "isSpaceEnough". 
# The first argument is available free space on hardisk which is a string. 
# It can be in terms of MB or GB. 
# The second parameter is also a string which is the size of the folder to be copied which can be in terms of MB, GB.(e.g. 15 MB) 
# Your aim is to find if the file will fit the space or not. Your function should return a tuple of two elements. 
# The first element is "Successful" if the space is enough and "Failure" otherwise. 
# Second element will be remaining space(in terms of MB) if the operation is successful 
# and required space if the operation is failure.  1 GB = 1.024 MB

def isSpaceEnough(space,size):
	if space[-2] == "G":
		space = int(space[:-3])*1024
	else:
		space = int(space[:-3])
	
	if size[-2] == "G":
		size = int(size[:-3])*1024
	else:
		size = int(size[:-3])

	if space >= size:
		space -= size
		return ('Successful', space)
	else:
		size -= space
		return ('Failure', size)


# SAMPLE INPUT/OUTPUTs:
# == Input ==
print( isSpaceEnough("1 GB","500 MB") )
# == Output ==
#('Successful', 524)

# == Input ==
print( isSpaceEnough("2054 MB","3 GB") )
# == Output ==
#('Failure', 1018)

# SOLUTION:
""" def isSpaceEnough(availableSpace,size):
	lstAvailable= availableSpace.split(" ")
	lstSize = size.split(" ")
	if lstAvailable[1]=="MB":
		avaSpaceMB = int(lstAvailable[0])
	if lstAvailable[1]=="GB":
		avaSpaceMB = int(lstAvailable[0])*1024
	if lstSize[1]=="MB":
		foldSizeMB = int(lstSize[0])
	if lstSize[1]=="GB":
		foldSizeMB = int(lstSize[0])*1024
	if avaSpaceMB >= foldSizeMB:
		return ("Successful",avaSpaceMB-foldSizeMB)
	else:
		return ("Failure",foldSizeMB-avaSpaceMB)
	"""