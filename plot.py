import matplotlib.pyplot as plt
import itertools
import numpy as np

slectivity_levels = [10, 8, 6, 4, 2, 0]

def values_from_file(file_path):
	with open(file_path, 'r') as fp:
		return [int(line) for line in fp]

compiled_df = []
veced_df = []
hybrid_df = []

for level in slectivity_levels:
	veced_df.append(values_from_file('./selectivity/{}/vectorized/q6_normal.csv'.format(level)))
	compiled_df.append(values_from_file('./selectivity/{}/vectorized/q6_compiled.csv'.format(level)))
	hybrid_df.append(values_from_file('./selectivity/{}/vectorized/q6_hybrid.csv'.format(level)))

# convert to ms
compiled_df = [[y/1000000 for y in x] for x in compiled_df]
veced_df = [[y/1000000 for y in x] for x in veced_df]
hybrid_df = [[y/1000000 for y in x] for x in hybrid_df]


fig1, ax1 = plt.subplots()
ax1.plot([np.mean(m) for m in veced_df], '--', label="Vectorized", color="#b1063aff", marker='o')
ax1.plot([np.mean(m) for m in compiled_df], '--', label="Compiled",  color="#f6a800ff", marker='v')
ax1.plot([np.mean(m) for m in hybrid_df], '--', label="Hybrid", color="#dd640cff", marker='s')

get_errors = lambda x: [[np.mean(m) - np.percentile(m, 25) for m in x], [np.percentile(m, 75) - np.mean(m) for m in x]]

plt.errorbar(
	y=[np.mean(m) for m in veced_df], 
	x=range(len(veced_df)),
	yerr=get_errors(veced_df),
	fmt='.k',
	capsize=1,
	elinewidth=.7,
	mec="#b1063aff",
	mfc="#b1063aff",
	marker='o',
	markersize=8
)

plt.errorbar(
	y=[np.mean(m) for m in compiled_df],
	x=range(len(compiled_df)),
	yerr=get_errors(compiled_df),
	fmt='.k',
	capsize=1,
	elinewidth=.7,
	mec="#f6a800ff",
	mfc="#f6a800ff",
	marker='v',
	markersize=8
)

plt.errorbar(
	y=[np.mean(m) for m in hybrid_df],
	x=range(len(hybrid_df)),
	yerr=get_errors(hybrid_df),
	fmt='.k',
	capsize=1,
	elinewidth=.7,
	mec="#dd640cff",
	mfc="#dd640cff",
	marker='s',
	markersize=8
)

ax1.set_xlabel('1st Operator Selectivity (in %)')
ax1.set_ylabel('ms')
ax1.axvline(2.5, color='#00000051')
ax1.text(2.6, 12.0, "Standard TCPH Selectivity", rotation=90)
ax1.get_xaxis().set_major_formatter(plt.FuncFormatter(lambda x, loc: "{:,}".format(int(x))))
ax1.get_yaxis().set_major_formatter(plt.FuncFormatter(lambda x, loc: "{:,}".format(int(x))))
ax1.set_xticklabels([0, 0, 20, 40, 60, 80, 100])
ax1.set_title("TPC-H Q 6 (Scale Factor: 1; Executions: 20, means)")
ax1.legend()

plt.savefig('selectivity')
plt.show()
