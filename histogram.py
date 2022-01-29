import csv
import numpy as np
import matplotlib.pyplot as plt

f = open('output_nt_data_t0.csv', 'r')
reader = csv.reader(f)
energyDepositList = []
distanceList = []
for line in reader:
    if '#' in line[0]:
        pass
    else:
        energyDepositList.append(float(line[0]))
        distanceList.append(float(line[1]))

plt.figure()
plt.hist(energyDepositList, bins=1000)
plt.grid()
# plt.text(x, y, '')
plt.title("Energy Deposit Histogram")
plt.xlabel("Energy Deposit (MeV)")
plt.yscale("log")
plt.ylabel("Number of Data")
plt.savefig('Energy Deposit Histogram.png')

plt.figure(figsize=[12, 8])
plt.hist(distanceList, bins=1000)
plt.grid()
plt.title("Distance Histogram")
plt.xlabel("Distance (mm)")
plt.ylabel("Number of Data")
plt.yscale("log")
plt.savefig("Distance Histogram.png")
