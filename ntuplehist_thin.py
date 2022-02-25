import csv
import numpy as np
import matplotlib as mpl
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
            temp.append(int(line[1]))
            temp.append(int(line[2]))
            temp.append(line[3])
            temp.append(float(line[4]))
            temp.append(float(line[5]))
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
    energyDepositProton = 0
    travelDistance = 0
    for x in X:
        particleNameList.append(x[2])
        energyDeposit += x[3]
        if x[1] == 1:
            energyDepositProton = x[3]
            travelDistance = x[4]
    CalculatedData.append([trackMax, particleNameList, energyDeposit, energyDepositProton, travelDistance])

del EventList

trackMaxMax = max(CalculatedData, key=lambda x: x[0])[0]  # 1부터 센다

dataNumber = len(CalculatedData)

trackIdList = [0 for i in range(trackMaxMax)]
energyDepositList = []
energyDepositProtonList = []
energyDepositIfAlphaContainList = []
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
    if 'alpha' in X[1]:
        energyDepositIfAlphaContainList.append(X[2])

histoutput = [0, 0, 0]
histdata = [0, 0]
binedge = [0, 0]

DPI = 100

histbin = 1000
hist2dbin = 1000


E_p = 2000
gamma = 0.5772156649


def Energy_to_b2(E):
    #  MeV
    #  proton
    m = 938.272029  # MeV/c^2, mass of proton
    c = 1  # speed of light
    b2 = 1 - 1 / (((E / m / c / c) + 1)**2)  # no unit
    return b2


def KSI(b2):
    K = 0.307075  # MeV cm^2 / mol
    Z = 14  # C : 6, Si : 14
    A = 28.0588  # g/mol, C : 12.011, Si : 28.0588
    rho = 2.22  # g/cm^3, C : 2, Si : 2.33
    s = 1  # um
    s = s * 1e-4  # um -> cm
    x = rho * s
    z = 1
    return K * Z * z * z * x / 2 / A / b2


b2 = Energy_to_b2(E_p)
ksi = KSI(b2)


def Landau_phi_approx(x):
    y = 2 * x / np.pi - np.log(np.pi / 2)
    power = -(y + np.exp(-y)) / 2
    return np.exp(power) / np.sqrt(2 * np.pi) * 2 / np.pi


def LAMBDA_1(x):
    return x + np.log(x) - 1 + gamma


def LAMBDA_2(x):
    return LAMBDA_1(x) - 0.5 / (1 + x)


def Bisection_Method(func, a, b, stop='rel', zer=10**(-6), endN=100):
    # stop condition Error handling
    if stop == 'rel' or stop == 'acc' or stop == 'zer':
        pass
    else:
        raise NameError("Parameter 'stop' must be 'rel', 'acc' or 'zer'.")
    # 'rel' is relative error method. |Ans[-1] - Ans[-2]|/|Ans[-1]| < zer
    # 'acc' is absolute error method. |Ans[-1] - Ans[-2]| < zer
    # 'zer' is zero tolerance method. f(Ans) < zer
   
    # input Error handling
    if func(a)*func(b) >= 0:
        raise ValueError("Inputs 'a' and 'b' are NOT suitable.")
    else:
        pass

    if a > b:
        c = np.copy(b)
        b = np.copy(a)
        a = c
    elif a == b:
        raise ValueError("'a' and 'b' must not be same.")
    else:
        pass

    p = [a, (a+b)/2, b]
    i = 0
    while i < endN:
        # bisecting iteration part
        bp = np.copy(p[1])
        if func(p[0])*func(p[1]) < 0:
            p = [p[0], (p[0]+p[1])/2, p[1]]
        elif func(p[1])*func(p[2]) < 0:
            p = [p[1], (p[1]+p[2])/2, p[2]]
        else:
            return p[1]
            break
        # stop condition part
        if stop == 'rel':
            if abs((bp-p[1])/p[1]) < zer:
                return p[1]
                break
            else:
                pass
        elif stop == 'acc':
            if abs(p[1]-bp) < zer:
                return p[1]
                break
            else:
                pass
        else:
            if func(p[1]) < zer:
                return p[1]
                break
        i += 1


def Inverse_func(func, x):
    def equa(y):
        return func(y) - x
    b = 1 + x * x
    return Bisection_Method(equa, 1e-9, b, stop='rel', zer=1e-9, endN=100)


def Landau_phi_approx_LAMBDA_1(x):
    y = Inverse_func(LAMBDA_1, x)
    return np.exp(-1 / y) / y / (1 + y)


def Landau_phi_approx_LAMBDA_2(x):
    y = Inverse_func(LAMBDA_2, x)
    temp1 = np.exp(-1 / y) / y / (1 + y)
    temp2 = np.sqrt(y / (y + 1))
    temp3 = np.exp(1 / 2 / (y + 1))
    temp4 = 1 + y * y / 2 / (1 + 3.5 * y + 3 * y * y + y * y * y)
    return temp1 * temp2 * temp3 * temp4


def Density_Eff(b2):
    lorentz = 1 / np.sqrt(1 - b2)
    X = np.log10(np.sqrt(b2) * lorentz)
    X_1 = 2.87  # C : 2.486, Si : 2.87
    m = 3.25  # C : 3.00, Si : 3.25
    a = 0.1492  # C : 0.2024, Si : 0.1492
    C = -4.44  # C : -2.99, Si : -4.44
    return 4.6052*X + C + a * (X_1 - X)**m


def Landau_lambda(E):
    # MeV
    II = (173 * 1e-6)**2  # MeV**2, C : 81, Si : 173
    m_e = 0.51099895000  # MeV/c2
    c = 1
    m_ecc = m_e * c * c
    inside_log = 2 * m_ecc * b2 * ksi / II / (1 - b2)
    Most_Probable = ksi * (np.log(inside_log) - b2 + 0.2 - Density_Eff(b2))
    return (E - Most_Probable) / ksi


def kappa(b2):
    m_ecc = 0.51099895000
    lorentz = 1 / np.sqrt(1 - b2)
    eta = b2 * lorentz
    m = 938.272029  # MeV/c^2, mass of proton
    s = m_ecc / m
    temp1 = 2 * m_ecc * eta * eta
    temp2 = 1 + 2 * s * np.sqrt(1 + eta * eta) + s * s
    W_max = temp1 / temp2
    return ksi / W_max


print("KSI   : ", KSI(b2))
print("kappa : ", kappa(b2))


def Landau_dist_e_LAMBDA_2(E):
    return Landau_phi_approx_LAMBDA_2(Landau_lambda(E)) / ksi


def Landau_dist_e_LAMBDA_1(E):
    return Landau_phi_approx_LAMBDA_1(Landau_lambda(E)) / ksi


casename = input("casename : ")

plt.figure(dpi=DPI, figsize=[12, 8])
# histoutput = plt.hist(energyDepositList, bins=50000, label='data')
histoutput = plt.hist(energyDepositList, bins=np.linspace(0, 5e-4, 1000), label='data')
binedge = histoutput[1]
binminmax = [binedge[0], binedge[-1]]
plotrange = np.linspace(binminmax[0], -Landau_lambda(0)*ksi + 10*ksi, 1000)
plt.plot(plotrange, [Landau_dist_e_LAMBDA_2(e)*dataNumber*(binedge[1] - binedge[0]) for e in plotrange], label='Landau Lindhard 2nd Approx')
# plt.plot(plotrange, [Landau_dist_e_LAMBDA_1(e)*dataNumber*(binedge[1] - binedge[0]) for e in plotrange], label='Landau Lindhard 1st Approx')
plt.legend()
plt.xlabel("Energy Deposit (MeV)")
plt.ylabel("Number of Data")
# plt.xlim(-Landau_lambda(0)*ksi - 5*ksi, -Landau_lambda(0)*ksi + 10*ksi)
plt.xlim(0, -Landau_lambda(0)*ksi + 10*ksi)
plt.ylim(0, 5000)
plt.title(str(casename) + " , " + "mean:{:.3e}".format(np.average(energyDepositList)) + " , " + "stdv:{:.3e}".format(np.std(energyDepositList)))
plt.savefig("Only Hist - Total Energy Deposit_" + str(casename) + ".png")
plt.show()
