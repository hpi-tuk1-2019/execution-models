import matplotlib.pyplot as plt
import itertools
import numpy as np

volumes = [600000, 6600000, 12600000, 18600000, 24600000, 30600000, 36600000, 42600000, 48600000, 54600000]

def values_from_file(file_path):
	with open(file_path, 'r') as fp:
		return [int(line) for line in fp]

compiled_df = []
veced_df = []
hybrid_df = []

for level in volumes:
	veced_df.append(values_from_file('./data_volume/{}/vectorized/q6_normal.csv'.format(level)))
	compiled_df.append(values_from_file('./data_volume/{}/vectorized/q6_compiled.csv'.format(level)))
	hybrid_df.append(values_from_file('./data_volume/{}/vectorized/q6_hybrid.csv'.format(level)))

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

volumes_with_comma = ["{:,}".format(int(x)) for x in volumes]
print(volumes_with_comma)

ax1.set_xlabel('Number of Rows')
ax1.set_ylabel('ms')
ax1.get_xaxis().set_major_formatter(plt.FuncFormatter(lambda x, loc: "{:,}".format(int(x))))
ax1.get_yaxis().set_major_formatter(plt.FuncFormatter(lambda x, loc: "{:,}".format(int(x))))
ax1.set_xticklabels(volumes_with_comma)
ax1.set_title("TPC-H Q 6 (Executions: 20, means)")
ax1.legend()

plt.show()
