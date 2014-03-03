

def CreateHashTable ( tableSize ):
	ret = []
	for i in range(0, tableSize):
		ret.append ( [] )
	return ret

def HTlookUp(hashTable, HashFun, ID):
	index = HashFun ( obj )
	for i in hashTable[index]:
		if i.ID == ID:
			return i

def HTInsert(hashTable, HashFun, obj):
	hashTable[HashFun(obj)].append(obj)




