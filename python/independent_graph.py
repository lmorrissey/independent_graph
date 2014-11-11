__author__ = 'Laura'
import csv
import itertools
import sys

graphs  = dict ()
graphno =0

# for line in sys.stdin:
#     print line
with open("vertices.csv", 'rb') as csvfile:
    edgereader = csv.reader(csvfile, delimiter=' ',quotechar = '|' )
    for row in edgereader:
        row = row[0].split(',')
        if not graphs: # first iteration
            graphno+= 1
            graphs[frozenset(set(row))] = graphno
            continue
        if (set(row).issubset(itertools.chain(*graphs.keys()))): # key already exists in graph
            continue
        if (set(row).isdisjoint(itertools.chain(*graphs.keys()))): # no vertices in common, new graph
            graphno+= 1
            graphs[frozenset(row)]=graphno
            continue
        else: #at least one element in common...
            for s, v in graphs.iteritems():
                # print set(row).intersection(s)
                if set(row).intersection(s):
                    newkeyset = set(s)
                    newkeyset.update(set(row)) #sets do not allow for duplicates
                    graphs[frozenset(newkeyset)] = v
                    del graphs[s]
                    break

for k, v in graphs.iteritems():
    print "Unique graph number: " + str(v)
    print "with values " + str(k)
