import numpy as np
import csv
import matplotlib.pyplot as plt

f1 = open("output_h1_0.csv")

reader = csv.reader(f1)
RawData = []
for line in reader:
    RawData.append(line)
RawData = RawData[7:]
RawData = [int(element[0]) for element in RawData]

plt.figure()
plt.plot(RawData)
plt.yscale("log")
plt.show()
