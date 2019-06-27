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

fig1, ax1 = plt.subplots()
ax1.plot([np.mean(m) for m in veced_df], '--', label="Vectorized", color="#b1063aff")
ax1.plot([np.mean(m) for m in compiled_df], '--', label="Compiled",  color="#f6a800ff")
ax1.plot([np.mean(m) for m in hybrid_df], '--', label="Hybrid", color="#dd640cff")

get_errors = lambda x: [[np.mean(m) - np.percentile(m, 25) for m in x], [np.percentile(m, 75) - np.mean(m) for m in x]]

plt.errorbar(
	y=[np.mean(m) for m in veced_df], 
	x=range(len(veced_df)),
	yerr=get_errors(veced_df),
	fmt='.k',
	capsize=1,
	elinewidth=.7,
	color="#b1063aff"
)

plt.errorbar(
	y=[np.mean(m) for m in compiled_df],
	x=range(len(compiled_df)),
	yerr=get_errors(compiled_df),
	fmt='.k',
	capsize=1,
	elinewidth=.7,
	color="#f6a800ff"
)

plt.errorbar(
	y=[np.mean(m) for m in hybrid_df],
	x=range(len(hybrid_df)),
	yerr=get_errors(hybrid_df),
	fmt='.k',
	capsize=1,
	elinewidth=.7,
	color="#dd640cff"
)

ax1.set_xlabel('1st Operator Selectivity (in %)')
ax1.set_ylabel('time in ns')
ax1.set_xticklabels(volumes)
ax1.set_title("TPC-H Q 6 (Scale Factor: 1; Executions: 20)")
ax1.legend()

plt.show()
