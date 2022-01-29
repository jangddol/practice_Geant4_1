import csv
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

f = open('output_nt_data_t0.csv', 'r')
reader = csv.reader(f)
energyDepositList = []
energyDepositProtonList = []
distanceList = []
for line in reader:
    if '#' in line[0]:
        pass
    else:
        energyDepositList.append(float(line[0]))
        energyDepositProtonList.append(float(line[1]))
        distanceList.append(float(line[2]))

energyDepositList = np.array(energyDepositList)
energyDepositProtonList = np.array(energyDepositProtonList)
distanceList = np.array(distanceList)

histoutput = [0, 0, 0]
histdata = [0, 0]
binedge = [0, 0]

fig = plt.figure(figsize=[14, 10], dpi=300)
axes = fig.subplots(nrows=2, ncols=2)

histoutput = axes[0, 0].hist(energyDepositList, bins=1000, alpha=0.6, label='All Particles')
histdata[0], binedge[0] = histoutput[:2]
axes[0, 0].hist(energyDepositProtonList, binedge[0], alpha=0.4, label='Only Proton')
axes[0, 0].legend()
# axes[0, 0].grid(linewidth=1)
axes[0, 0].set_title("Energy Deposit Histogram")
axes[0, 0].set_xlabel("Energy Deposit (MeV)")
axes[0, 0].set_ylabel("Number of Data")
axes[0, 0].text(0, max(histdata[0]) * 0.55, "mean : {:.3f}".format(np.average(energyDepositList)))
axes[0, 0].text(0, max(histdata[0]) * 0.48, "stdv : {:.3f}".format(np.std(energyDepositList, dtype=np.float64)))

histoutput = axes[0, 1].hist(distanceList, bins=1000)
histdata[1], binedge[1] = histoutput[:2]
axes[0, 1].grid(linewidth=0.3)
axes[0, 1].set_title("Travel Distance Histogram")
axes[0, 1].set_xlabel("Travel Distance (mm)")
axes[0, 1].set_ylabel("Number of Data")
axes[0, 1].text(0, max(histdata[1]) * 0.97, "mean : {:.3f}".format(np.average(distanceList)))
axes[0, 1].text(0, max(histdata[1]) * 0.9, "stdv : {:.3f}".format(np.std(distanceList, dtype=np.float64)))

axes[1, 0].hist(energyDepositList, bins=1000, alpha=0.6, label='All Particles')
axes[1, 0].hist(energyDepositProtonList, binedge[0], alpha=0.4, label='Only Proton')
axes[1, 0].legend()
axes[1, 0].grid(linewidth=0.3)
axes[1, 0].set_yscale("log")
axes[1, 0].set_title("Energy Deposit Histogram (Log Scale)")
axes[1, 0].set_xlabel("Energy Deposit (MeV)")
axes[1, 0].set_ylabel("Number of Data")

axes[1, 1].hist(distanceList, bins=1000)
axes[1, 1].grid(linewidth=0.3)
axes[1, 1].set_yscale("log")
axes[1, 1].set_title("Travel Distance Histogram (Log Scale)")
axes[1, 1].set_xlabel("Travel Distance (mm)")
axes[1, 1].set_ylabel("Number of Data")

plt.subplots(constrained_layout=True)
fig.savefig("Histogram.png")

plt.figure(dpi=300, figsize=[14, 10])
plt.hist2d(energyDepositList, energyDepositProtonList, bins=[1000, 1000], norm=mpl.colors.LogNorm())
plt.colorbar()
plt.title("Total Energy Deposit vs. Proton Energy Deposit")
plt.xlabel("Total Energy Deposit (MeV)")
plt.ylabel("Proton Energy Deposit (MeV)")
plt.xlim(-5, 105)
plt.savefig("Histogram2D.png")
