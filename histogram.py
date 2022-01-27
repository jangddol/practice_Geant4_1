import csv
import numpy as np
import matplotlib.pyplot as plt

f = open('output_nt_ed_t0.csv', 'r')
reader = csv.reader(f)
next(reader)
next(reader)
next(reader)
next(reader)
next(reader)
histlist = []
for line in reader:
    histlist.append(float(line[0]))

plt.figure()
plt.hist(histlist, bins=100)
plt.grid()
plt.savefig('histogram.png')
