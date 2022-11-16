import matplotlib.pyplot as plt
#from pandas import read_csv

# input arrays
arr12_4     =   [12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104]
arr12_5     =   [12,17,22,27,32,37,42,47,52,57,62,67,72,77,82,87,92,97,102,107,112,117,122,127]
arr12_10    =   [12,22,32,42,52,62,72,82,92,102,112,122]
arr12_12    =   [12,24,36,48,60,72,84,96,108,120,132,144,156,168,180,192,204,216,228,240,252]
arand_20ns  =   [88,159,27,182,206,249,192,197,234,240,263,169,18,186,112,107,189,244,80,78,183,93,199,6]

Qarr12_4    =   [3,6,7,11,12,17,18,21,22,25,26,29,30,33,34,37,38,41,42,45,46,49,50,53,54,57,58,61,62,65,66,69,70,73,74,77,78,81,82,85,89,90,93,94,97,98,101]

def average_finder(inputarr):
    outputarr = []
    totalaverage = 0
    for x in inputarr:
        x = x/4
        totalaverage = totalaverage + x
        outputarr.append(totalaverage)
    return outputarr, totalaverage

def main():
    arr12_4_outarr, out12_4_average = average_finder(arr12_4)
    arr12_5_outarr, out12_5_average = average_finder(arr12_5)
    arr12_10_outarr, out12_10_average = average_finder(arr12_10)
    arr12_12_outarr, out12_12_average = average_finder(arr12_12)
    arand_20ns_outarr, outarand_20ns_average = average_finder(arand_20ns)
    #plt.scatter(arr12_4, arr12_4_outarr)
    plt.plot(arr12_4_outarr)
    plt.show()
    plt.scatter(arr12_5, arr12_5_outarr)
    plt.show()
    plt.scatter(arr12_10, arr12_10_outarr)
    plt.show()
    plt.scatter(arr12_12, arr12_12_outarr)
    plt.show()
    plt.scatter(arand_20ns,arand_20ns)
    plt.show()








if __name__ == '__main__':
 main()