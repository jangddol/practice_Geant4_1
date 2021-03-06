import csv
import numpy as np
import matplotlib.pyplot as plt

f1 = open('output_nt_data_t0.csv', 'r')
f2 = open('output_nt_data_t1.csv', 'r')
f3 = open('output_nt_data_t2.csv', 'r')
f4 = open('output_nt_data_t3.csv', 'r')
f5 = open('output_nt_data_t4.csv', 'r')
f6 = open('output_nt_data_t5.csv', 'r')
f7 = open('output_nt_data_t6.csv', 'r')
f8 = open('output_nt_data_t7.csv', 'r')
h1 = open('output_h1_1.csv', 'r')

F = [f1, f2, f3, f4, f5, f6, f7, f8]

protonEnergy = input("How much the Kinetic Energy of Proton is? : ")

ReaderList = [csv.reader(f) for f in F]
RawData = []
for reader in ReaderList:
    for line in reader:
        if '#' in line[0]:
            pass
        else:
            temp = []
            temp.append(int(line[1]))    # event ID
            temp.append(int(line[2]))    # track ID
            temp.append(line[3])         # particle Name
            temp.append(float(line[4]))  # energy loss
            temp.append(float(line[5]))  # distance
            temp.append(float(line[6]))  # energy loss in Inelastic
            temp.append(float(line[7]))  # energy leak
            RawData.append(temp)

for f in F:
    f.close()

del ReaderList

RawData = sorted(RawData, key=lambda x: (x[0], x[1]))
eventMax = max(RawData, key=lambda x: x[0])[0]
EventList = [[] for i in range(eventMax + 1)]
rawEnergyDepositList = []
for X in RawData:
    EventList[X[0]].append(X)
    rawEnergyDepositList.append(X[3])
del RawData

CalculatedData = []
for X in EventList:
    trackMax = max(X, key=lambda x: x[1])[1]  # 1부터 센다
    particleNameList = []
    energyDeposit = 0
    energyLossInelastic = 0
    energyLossLeak = 0
    energyDepositProton = 0
    travelDistance = 0
    for x in X:
        particleNameList.append(x[2])
        energyDeposit += x[3]
        energyLossInelastic += x[5]
        energyLossLeak += x[6]
        if x[1] == 1:
            energyDepositProton = x[3]
            travelDistance = x[4]
    CalculatedData.append([trackMax, particleNameList, energyDeposit, energyDepositProton, travelDistance, energyLossInelastic, energyLossLeak])

del EventList

trackMaxMax = max(CalculatedData, key=lambda x: x[0])[0]  # 1부터 센다

dataNumber = len(CalculatedData)

trackIdList = [0 for i in range(trackMaxMax)]
energyDepositList = []
energyLossInelasticList = []
energyLossLeakList = []
energyTotalLossList = []
energyDepositProtonList = []
energyDepositIfAlphaContainList = []
energyTotalLossIfAlphaContainList = []
energyDepositIfNotAlphaContainList = []
energyDepositIfC12ContainList = []
energyTotalLossIfC12ContainList = []
energyDepositIfNotC12ContainList = []
trackSortedEnergyDepositList = [[] for i in range(trackMaxMax)]
trackSortedEnergyDepositProtonList = [[] for i in range(trackMaxMax)]
travelDistanceList = []
for X in CalculatedData:
    trackIdList[X[0]-1] = X[0]
    energyDepositList.append(X[2])
    energyDepositProtonList.append(X[3])
    trackSortedEnergyDepositList[X[0]-1].append(X[2])
    trackSortedEnergyDepositProtonList[X[0]-1].append(X[3])
    travelDistanceList.append(X[4])
    energyLossInelasticList.append(X[5])
    energyLossLeakList.append(X[6])
    energyTotalLossList.append(X[2] + X[5] + X[6])
    if 'alpha' in X[1]:
        energyDepositIfAlphaContainList.append(X[2])
        energyTotalLossIfAlphaContainList.append(X[2] + X[5] + X[6])
    else:
        energyDepositIfNotAlphaContainList.append(X[2])
    if 'C12' in X[1]:
        energyDepositIfC12ContainList.append(X[2])
        energyTotalLossIfC12ContainList.append(X[2] + X[5] + X[6])
    else:
        energyDepositIfNotC12ContainList.append(X[2])

histoutput = [0, 0, 0]
histdata = [0, 0]
binedge = [0, 0]

DPI = 100

histbin = 1000
hist2dbin = 1000


fig = plt.figure(figsize=[12, 8], dpi=DPI)
axes = fig.subplots(nrows=2, ncols=2)

histoutput = axes[0, 0].hist(energyDepositList, bins=histbin, alpha=0.6, label='All Particles')
histdata[0], binedge[0] = histoutput[:2]
print("Number of Data : ", sum(histdata[0]))
axes[0, 0].hist(energyDepositProtonList, binedge[0], alpha=0.4, label='Only Proton')
axes[0, 0].set_title("Energy Deposit Histogram")
axes[0, 0].set_xlabel("Energy Deposit (MeV)")
axes[0, 0].set_ylabel("Number of Data")
axes[0, 0].text(0, max(histdata[0]) * 0.55, "mean : {:.3f}".format(np.average(energyDepositList)))
axes[0, 0].text(0, max(histdata[0]) * 0.48, "stdv : {:.3f}".format(np.std(energyDepositList, dtype=np.float64)))

histoutput = axes[0, 1].hist(travelDistanceList, bins=histbin)
histdata[1], binedge[1] = histoutput[:2]
print("Number of Data : ", sum(histdata[1]))
axes[0, 1].grid(linewidth=0.3)
axes[0, 1].set_title("Travel Distance Histogram")
axes[0, 1].set_xlabel("Travel Distance (mm)")
axes[0, 1].set_ylabel("Number of Data")
axes[0, 1].text(0, max(histdata[1]) * 0.97, "mean : {:.3f}".format(np.average(travelDistanceList)))
axes[0, 1].text(0, max(histdata[1]) * 0.9, "stdv : {:.3f}".format(np.std(travelDistanceList, dtype=np.float64)))

axes[1, 0].hist(energyDepositList, bins=histbin, alpha=0.6, label='All Particles')
axes[1, 0].hist(energyDepositProtonList, binedge[0], alpha=0.4, label='Only Proton')
axes[1, 0].grid(linewidth=0.3)
axes[1, 0].set_yscale("log")
axes[1, 0].set_title("Energy Deposit Histogram (Log Scale)")
axes[1, 0].set_xlabel("Energy Deposit (MeV)")
axes[1, 0].set_ylabel("Number of Data")

axes[1, 1].hist(travelDistanceList, bins=histbin)
axes[1, 1].grid(linewidth=0.3)
axes[1, 1].set_yscale("log")
axes[1, 1].set_title("Travel Distance Histogram (Log Scale)")
axes[1, 1].set_xlabel("Travel Distance (mm)")
axes[1, 1].set_ylabel("Number of Data")

plt.subplots(constrained_layout=True)
fig.savefig("Histogram" + str(protonEnergy) + ".png")

"""
plt.figure(dpi=DPI, figsize=[12, 8])
plt.hist2d(energyDepositList, energyDepositProtonList, bins=[hist2dbin, hist2dbin], norm=mpl.colors.LogNorm())
plt.colorbar()
plt.title("Total Energy Deposit vs. Proton Energy Deposit")
plt.xlabel("Total Energy Deposit (MeV)")
plt.ylabel("Proton Energy Deposit (MeV)")
# plt.xlim(-5, 105)
plt.savefig("Histogram2D" + str(protonEnergy) + ".png")


fig2 = plt.figure(dpi=DPI, figsize=[14, 10])
axes2 = fig2.subplots(nrows=3, ncols=3)
i = 0
while i < min(9, len(trackSortedEnergyDepositList)):
    ax = axes2[int((i - i % 3)/3), int(i % 3)]
    ax.hist(trackSortedEnergyDepositList[i], binedge[0], alpha=0.4, label=str(trackIdList[i])+' tracks case')
    ax.set_title(str(trackIdList[i]) + "tracks case")
    ax.set_xlabel("Total Energy Deposit (MeV)")
    ax.set_ylabel("Number of Data")
    ax.set_yscale("log")
    i += 1
fig2.subplots_adjust(wspace=0.3, hspace=0.3)
fig2.savefig("Histogram_trackMax" + str(protonEnergy) + ".png")
"""


casename = input("casename : ")

fig3 = plt.figure(dpi=DPI, figsize=[12, 8])
fig3.suptitle("Energy Loss Histogram : " + casename)
axes3 = fig3.subplots(nrows=2, ncols=2)

axes3[0, 0].hist(energyDepositList, bins=histbin)
axes3[0, 0].grid(linewidth=0.3)
axes3[0, 0].set_yscale("log")
axes3[0, 0].set_title("Energy Deposit Histogram (Log Scale)")
axes3[0, 0].set_xlabel("Energy Deposit (MeV)")
axes3[0, 0].set_ylabel("Number of Data")

axes3[0, 1].hist(energyLossInelasticList, bins=histbin)
axes3[0, 1].grid(linewidth=0.3)
axes3[0, 1].set_yscale("log")
axes3[0, 1].set_title("Energy Loss with Inelastic Histogram (Log Scale)")
axes3[0, 1].set_xlabel("Energy Loss with Inelastic (MeV)")
axes3[0, 1].set_ylabel("Number of Data")

axes3[1, 0].hist(energyLossLeakList, bins=histbin)
axes3[1, 0].grid(linewidth=0.3)
axes3[1, 0].set_yscale("log")
axes3[1, 0].set_title("Leak Energy Histogram (Log Scale)")
axes3[1, 0].set_xlabel("Leak Energy (MeV)")
axes3[1, 0].set_ylabel("Number of Data")

axes3[1, 1].hist(energyTotalLossList, bins=histbin)
axes3[1, 1].grid(linewidth=0.3)
axes3[1, 1].set_yscale("log")
axes3[1, 1].set_title("Total Energy Loss Histogram (Log Scale)")
axes3[1, 1].set_xlabel("Total Energy Loss (MeV)")
axes3[1, 1].set_ylabel("Number of Data")

fig3.savefig("Energy Loss Histogram_" + casename + ".png")

plt.figure(dpi=DPI, figsize=[12, 8])
histoutput = plt.hist(energyTotalLossList, bins=histbin, label='Total Energy Loss')
plt.hist(energyTotalLossIfAlphaContainList, bins=histbin, label='TEL with alpha')
# plt.hist(energyDepositIfC12ContainList, bins=histbin, label='data with C12')
Thres = 7.9452
"""
i = 0
while i < 100/Thres:
    plt.plot([100 - i * Thres for j in range(2)], [1, 1e6], 'r', alpha=0.5)
    i += 1
"""
plt.legend()
plt.yscale("log")
binedge = histoutput[1]
binminmax = [binedge[0], binedge[-1]]
plt.xlabel("Energy Deposit (MeV)")
plt.ylabel("Number of Data")
plt.title(str(casename) + " , " + "mean:{:.3e}".format(np.average(energyDepositList)) + " , " + "stdv:{:.3e}".format(np.std(energyDepositList)))
plt.savefig("Total Energy Loss_" + str(casename) + ".png")
plt.show()

