import matplotlib.pyplot as plt


originalx_arr = [154,194,79,117,176,128,150,66,95,2,83,159,205,79,213,236,116,185,162,105]
filter_out = [38,86,105,134,140,124,142,129,108,76,59,82,110,129,162,182,160,187,174,141]
computed_out = []

def freq_setter(t_interval):
    modifier = 0
    arr_freq = []
    for x in range(20):
        arr_freq.append(int(modifier))
        modifier += t_interval
    return arr_freq


def average_finder(inputarr):
    outputarr = []
    counter = 0
    x1 = 0
    x2 = 0
    x3 = 0
    x4 = 0
    y = 0
    for x in inputarr:
        x1 = x/4
        counter += 1
        if counter >= 2 :
            x2 = inputarr[counter-2] / 4
            if counter >= 3 :
                x3 = inputarr[counter-3] / 4
                if counter >= 4 :
                    x4 = inputarr[counter-4] / 4
        y = x1 + x2 + x3 + x4
        outputarr.append(y)
        x1, x2, x3, x4 = 0, 0, 0, 0
    return outputarr

def main():
    freq_10_ns = freq_setter(10)
    computed_out = average_finder(originalx_arr)
    print("Timescale\t" , "originalinput\t", "outputfilter\t", "calculatedoutput")
    for r in range(20):
        print("", freq_10_ns[r] , "\t\t" , originalx_arr[r] , "\t\t", filter_out[r], "\t\t", computed_out[r])
    plt.plot(freq_10_ns, originalx_arr, 'b', label='input')
    plt.plot(freq_10_ns, filter_out, 'r--', label = 'filter output')
    plt.plot(freq_10_ns, computed_out, 'g--', label = 'calculated output')
    plt.legend(loc = "lower right")
    plt.title("Input and Output of Filter in Time Domain")
    plt.xlabel("Time scale")
    plt.ylabel("Magnitude")
    plt.show()
    #plt.plot(freq_10_ns, originalx_arr, 'b', freq_10_ns, computed_out, 'r--')
    #plt.show()

if __name__ == '__main__':
 main()