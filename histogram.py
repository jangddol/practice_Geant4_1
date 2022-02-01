import csv
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import sys

np.set_printoptions(threshold=sys.maxsize)

# 형태는 (4+1)-dimension array
# 처음에 int와 float으로의 전환을 마친 후
# 파티클 이름에 대한 값을 모두 모아서 몇종류가 있는지 파악,
# 나머지 인덱스도 최대 값이 얼마인지 파악,
# 이를 이용해 array를 생성한후,
# 각 자리에 [energyDeposit, travelDistance]를 넣는다.

# run은 무시하고, event 인덱스를 모두 그냥 이어버리는게 좋을 것 같다.

# 스레드가 여러개인 것을 잘 고려해야한다.

# 최종 목표는 반응이 일어난 목록대로 분류하는 것
    # 현재 목표는 파티클이 튀어나온 종류에 따라서 분류하는 것
        # 각 파티클이 몇 트랙을 차지하고 있는지 분류할 것

f1 = open('output_nt_data_t0.csv', 'r')
f2 = open('output_nt_data_t1.csv', 'r')

F = [f1, f2]

ReaderList = [csv.reader(f) for f in F]
RawData = []
for reader in ReaderList:
    for line in reader:
        if '#' in line[0]:
            pass
        else:
            temp = []
            temp.append(int(line[1]))
            temp.append(int(line[2]))
            temp.append(line[3])
            temp.append(float(line[4]))
            temp.append(float(line[5]))
            RawData.append(temp)

RawData = sorted(RawData, key=lambda x: (x[0], x[1]))
eventMax = max(RawData, key=lambda x: x[0])[0]
EventList = [[] for i in range(eventMax + 1)]
for X in RawData:
    EventList[X[0]].append(X)

CalculatedData = []
for X in EventList:
    trackMax = max(X, key=lambda x: x[1])[1]  # 1부터 센다
    particleNameList = []
    energyDeposit = 0
    energyDepositProton = 0
    travelDistance = 0
    for x in X:
        particleNameList.append(x[2])
        energyDeposit += x[3]
        if x[1] == 1:
            energyDepositProton = x[3]
            travelDistance = x[4]
    CalculatedData.append([trackMax, particleNameList, energyDeposit, energyDepositProton, travelDistance])

CalculatedData = np.array(CalculatedData, dtype=object)

# print(CalculatedData)

trackMaxMax = max(CalculatedData, key=lambda x: x[0])[0]  # 1부터 센다

energyDepositList = []
energyDepositProtonList = []
trackSortedEnergyDepositList = [[] for i in range(trackMaxMax)]
trackSortedEnergyDepositProtonList = [[] for i in range(trackMaxMax)]
travelDistanceList = []
for X in CalculatedData:
    energyDepositList.append(X[2])
    energyDepositProtonList.append(X[3])
    trackSortedEnergyDepositList[X[0]-1].append(X[2])
    trackSortedEnergyDepositProtonList[X[0]-1].append(X[3])
    travelDistanceList.append(X[4])

# print(energyDepositList)

energyDepositList = np.array(energyDepositList)
energyDepositProtonList = np.array(energyDepositProtonList)
travelDistanceList = np.array(travelDistanceList)

histoutput = [0, 0, 0]
histdata = [0, 0]
binedge = [0, 0]

DPI = 100

fig = plt.figure(figsize=[14, 10], dpi=DPI)
axes = fig.subplots(nrows=2, ncols=2)

histbin = 100
hist2dbin = 100

histoutput = axes[0, 0].hist(energyDepositList, bins=histbin, alpha=0.6, label='All Particles')
histdata[0], binedge[0] = histoutput[:2]
axes[0, 0].hist(energyDepositProtonList, binedge[0], alpha=0.4, label='Only Proton')
axes[0, 0].legend()
# axes[0, 0].grid(linewidth=1)
axes[0, 0].set_title("Energy Deposit Histogram")
axes[0, 0].set_xlabel("Energy Deposit (MeV)")
axes[0, 0].set_ylabel("Number of Data")
axes[0, 0].text(0, max(histdata[0]) * 0.55, "mean : {:.3f}".format(np.average(energyDepositList)))
axes[0, 0].text(0, max(histdata[0]) * 0.48, "stdv : {:.3f}".format(np.std(energyDepositList, dtype=np.float64)))

histoutput = axes[0, 1].hist(travelDistanceList, bins=histbin)
histdata[1], binedge[1] = histoutput[:2]
axes[0, 1].grid(linewidth=0.3)
axes[0, 1].set_title("Travel Distance Histogram")
axes[0, 1].set_xlabel("Travel Distance (mm)")
axes[0, 1].set_ylabel("Number of Data")
axes[0, 1].text(0, max(histdata[1]) * 0.97, "mean : {:.3f}".format(np.average(travelDistanceList)))
axes[0, 1].text(0, max(histdata[1]) * 0.9, "stdv : {:.3f}".format(np.std(travelDistanceList, dtype=np.float64)))

axes[1, 0].hist(energyDepositList, bins=histbin, alpha=0.6, label='All Particles')
axes[1, 0].hist(energyDepositProtonList, binedge[0], alpha=0.4, label='Only Proton')
axes[1, 0].legend()
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
fig.savefig("Histogram.png")

plt.figure(dpi=DPI, figsize=[14, 10])
plt.hist2d(energyDepositList, energyDepositProtonList, bins=[hist2dbin, hist2dbin], norm=mpl.colors.LogNorm())
plt.colorbar()
plt.title("Total Energy Deposit vs. Proton Energy Deposit")
plt.xlabel("Total Energy Deposit (MeV)")
plt.ylabel("Proton Energy Deposit (MeV)")
# plt.xlim(-5, 105)
plt.savefig("Histogram2D.png")