import matrix1

history = []
mat =[]
num = 0

while(1):
	command = raw_input("enter input command\n")
	#print("here")
	for i in range(0,len(command)):
	
		if (command[i] == '='):
			row = 1
			column = 0
			total = 0
			for j in range(i,len(command)):
				if(command[j]==';'):
					row=row+1
				try:				 
				    val = int(command[j])
				    total = total + 1
				except ValueError:
				    continue
			column = total/row
			mat.append(matrix1.matrix(row,column))
			#print row , " " , column	
			#print("size = ", len(mat[num].Matrix))

			#print("matrix = ",mat[num].Matrix)
			v = matrix1.mdatatype()
			v = mat[num].Matrix
			#print("len(v[0]) = ",len(v[0]))
			#print("v[0][0] = ",v[0][0])
			r=0
			c=0
			for j in range(i,len(command)):
				if (command[j]==';' ):
					r=r+1
					c = 0
				if (command[j] == ']'):
					break
				try:
					letter = float(command[j])
					try:
						letter = float(command[j:j+2])
						j= j+1
					except ValueError:
						continue	
					#print("r,c,letter = ",r,c,command[j])
					v[r][c]=letter					
					c=c+1
				except ValueError:
				    continue
			num=num+1
			break

		elif ( command[i] == '+'):
			name1 = command[0:i].strip
			name2 = command[i+1 : len(command)].strip
			a = num-1 
			b = num-2
			
			history.append(mat[a]+mat[b])
			#print "hi"
			for j in range(0,(mat[a]+mat[b]).rows):
				print"\n"
				for k in range (0,(mat[a]+mat[b]).columns):
					print (mat[a]+mat[b]).Matrix[j][k],
			print"\n"

		elif ( command[i] == '-'):
			name1 = command[0:i].strip
			name2 = command[i+1 : len(command)].strip
			a = num-1 
			b = num-2
			history.append(mat[a]-mat[b])
			for j in range(0,(mat[a]-mat[b]).rows):
				print"\n"
				for k in range (0,(mat[a]-mat[b]).columns):
					print (mat[a]-mat[b]).Matrix[j][k],
			print"\n"

		elif ( command[i] == '*'):
			name1 = command[0:i].strip
			name2 = command[i+1 : len(command)].strip
			a = num-1 
			b = num-2
			history.append(mat[a]*mat[b])
			for j in range(0,(mat[a]*mat[b]).rows):
				print"\n"
				for k in range (0,(mat[a]*mat[b]).columns):
					print (mat[a]*mat[b]).Matrix[j][k],
			print"\n"

	if (command[0:7] == "history"):
		for j in range (0,len(history)):
			for l in range(0,history[j].rows):
				print"\n"
				for k in range (0,history[j].columns):
					print history[j].Matrix[l][k],
			print"\n"		

	elif (command[0:7] == "inverse"):
		name1 = command[7:len(command)].strip
		a=num-1
		history.append(mat[a].inverse())
		for j in range ( 0 , mat[a].inverse().rows):
			print"\n"
			for k in range ( 0 , mat[a].inverse().columns):
				print(mat[a].inverse().Matrix[j][k]),
		print"\n"



