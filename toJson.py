fin1 = open('dblp_authors3.txt', "r")
fin2 = open('dblp_temporal2.txt', "r")

aucount = 0
authors = []
visited = []
minyear = 0
maxyear = 0
while True:
    line = fin1.readline()
    if line == '':
        break
    keys = line.split('\t')
    aucount += 1
    authors.append(keys[1][:-1])
    visited.append(-1)

years = []
timeArray = []
newAuthors = []
to = []
newId = 0
edgeArray = []

while True:
    line = fin2.readline()
    keys = line.split(' ')
    if len(keys) == 1:
        if minyear == 0:
            minyear = int(keys[0])
        else:
            maxyear = int(keys[0])
            break
        continue
    from_ = int(keys[0])
    to_ = int(keys[1])
    year = int(keys[2])
    if visited[from_] == -1:
        visited[from_] = newId
        newAuthors.append(authors[from_])
        newId += 1
        to.append({})
    if visited[to_] == -1:
        visited[to_] = newId
        newAuthors.append(authors[to_])
        newId += 1
        to.append({})
    
    if visited[to_] in to[visited[from_]]:
        if year in to[visited[from_]][visited[to_]]:
            continue
        else:
            edgeArray.append(f'{visited[from_]},{visited[to_]},{year}')
            #fromArray.append(visited[from_])
            #toArray.append(visited[to_])
            years.append(year)
            to[visited[from_]][visited[to_]].append(year)
            to[visited[to_]][visited[from_]].append(year)
    else:
        edgeArray.append(f'{visited[from_]},{visited[to_]},{year}')
        #fromArray.append(visited[from_])
        #toArray.append(visited[to_])
        years.append(year)
        to[visited[from_]][visited[to_]] = [year]
        to[visited[to_]][visited[from_]] = [year]

year_count = []
for i in range(minyear, maxyear + 1):
    year_count.append(0)
for year in years:
    year_count[year - minyear] += 1
'''print(fromArray)
print(toArray)
print(years)
print(newAuthors)
for i in range(len(authors)):
    if visited[i] != -1:
        print(authors[i], visited[i], i)'''

#data_set_auth = {'authors' : newAuthors}
import json
#auth_dump = json.dumps(data_set_auth, indent=1)
#with open('authors.json', 'w', encoding='utf-8') as f:
#    json.dump(auth_dump, f, ensure_ascii=False, indent=4)
print(1)
f = open('../tempGraph.json', 'w')
data_set_graph = {'min_year': minyear, 'max_year': maxyear, 'edge_count_by_year': year_count, 'edges': edgeArray}
graph_dump = json.dumps(data_set_graph, indent=4)
f.write(graph_dump)
f.close()
print(2)
f = open('../authors.json', 'w')
data_set_label = {'authors': newAuthors}
author_dump = json.dumps(data_set_label, indent=4)
f.write(author_dump)
f.close()






