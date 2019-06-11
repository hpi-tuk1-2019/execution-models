import csv

import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt

# ----------------------- QUERY SIX ------------------------- #

with open('../build/src/benchmark_normal_6.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_normal = []
    for e in readCSV:
        array_normal.append(int(e[0]))
avg_normal = sum(array_normal) / len(array_normal)


with open('../build/src/benchmark_compiled_6.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_compiled = []
    for e in readCSV:
        array_compiled.append(int(e[0]))
avg_compiled = sum(array_compiled) / len(array_compiled)      

with open('../build/src/benchmark_hybrid_6.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_hybrid = []
    for e in readCSV:
        array_hybrid.append(int(e[0]))
avg_hybrid = sum(array_hybrid) / len(array_hybrid)

with open('../build/src/benchmark_vectorized_6.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_vec = []
    for e in readCSV:
        array_vec.append(int(e[0]))
avg_vec = sum(array_vec) / len(array_vec)


objects = ('normal', 'compiled', 'hybrid', 'vectorized')
y_pos = np.arange(len(objects))
performance = [avg_normal, avg_compiled, avg_hybrid, avg_vec]

plt.bar(y_pos, performance, align='center', alpha=0.5)
plt.xticks(y_pos, objects)
plt.ylabel('Runtime in ms')
plt.title("Performance Query 6")
plt.savefig('performance_query_6.png')
plt.clf()

plt.boxplot([array_normal, array_compiled, array_hybrid, array_vec])
plt.xticks([1,2,3,4], ['normal', 'compiled', 'hybrid', 'vectorized'])
plt.ylabel('Runtime in ms')
plt.title("Performance Query 6")
plt.savefig('performance_query_6_boxplot.png')
plt.clf()

# ------------------ QUERY ONE ----------------------------- #

with open('../build/src/benchmark_normal_1.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_normal = []
    for e in readCSV:
        array_normal.append(int(e[0]))
avg_normal = sum(array_normal) / len(array_normal)

with open('../build/src/benchmark_compiled_1.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_compiled = []
    for e in readCSV:
        array_compiled.append(int(e[0]))
avg_compiled = sum(array_compiled) / len(array_compiled)

with open('../build/src/benchmark_hybrid_1.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_hybrid = []
    for e in readCSV:
        array_hybrid.append(int(e[0]))
avg_hybrid = sum(array_hybrid) / len(array_hybrid)

with open('../build/src/benchmark_vectorized_1.csv') as csvFile:
    readCSV = csv.reader(csvFile, delimiter=',')
    array_vec = []
    for e in readCSV:
        array_vec.append(int(e[0]))
avg_vec = sum(array_vec) / len(array_vec)

objects = ('normal', 'compiled', 'hybrid', 'vectorized')
y_pos = np.arange(len(objects))
performance = [avg_normal, avg_compiled, avg_hybrid, avg_vec]

plt.bar(y_pos, performance, align='center', alpha=0.5)
plt.xticks(y_pos, objects)
plt.ylabel('Runtime in ms')
plt.title("Performance Query 1")
plt.savefig("performance_query_1")
plt.clf()

plt.boxplot([array_normal, array_compiled, array_hybrid, array_vec])
plt.xticks([1,2,3,4], ['normal', 'compiled', 'hybrid', 'vectorized'])
plt.ylabel('Runtime in ms')
plt.title("Performance Query 1")
plt.savefig("performance_query_1_boxplot")
plt.clf()
