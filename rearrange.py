
fin = open("./dblp_au_relation3.txt", "r")
fout = open("./dblp_temporal2.txt", "w")
temp = []
min = 2025
max = 0
now = 0
while True:
    line = fin.readline()
    if line == '':
        break
    if line[0] != '\'':
        temp.append(line[:-1])
    else :
        if len(line) < 5:
            temp.clear()
        else:
            year = int(line[1:]) 
            if year < min:
                min = year
            if max < year:
                max = year
            for l in temp:
                fout.write(l + ' ' + line[1:])
            temp.clear()
    now += 1
    
    if now % 10000 == 0:
        print(now)

fout.write(str(min) + '\n')
fout.write(str(max))