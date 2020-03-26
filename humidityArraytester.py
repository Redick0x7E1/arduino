# program to test averaging table code

import sys

# logs for 0=month 1=week 2=day 3=hour
log = [[60, 60, 60, 60, 60], [65, 65, 65, 65, 65, 65], [68,68,68,68,90], [60, 65, 65, 68, 67, 70, 72, 77]]

arraySize = sys.getsizeof(log)
print(arraySize)


def logdata(newdata, logindex): # new data is hourly data
    # update current log with new data.
    currentindex = log[logindex]
    currentindex.append(newdata)
    # do calculation
    newlogval = (sum(log[logindex]) / len(log[logindex]))
    #print(newlogval)
    return newlogval

def updatelogs(currVal):
    logdata(logdata(logdata(logdata(currVal, 3), 2), 1), 0)
    return print("Logs Updated!")

def avgData(log2index):
    #print((sum(log[log2index]) / len(log[log2index])))
    return ((sum(log[log2index]) / len(log[log2index])))


updatelogs(65)

def cleanDaily():
    if len(log[3]) > 24:
        log[3].clear()

print(arraySize)
print("monthT: ")
print(avgData(0))
print("weekT: ")
print(avgData(1))
print("dayT: ")
print(avgData(2))
print("hourT: ")
print(avgData(3))
