```
➜  build git:(master) ✗ lscpu
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
Address sizes:       39 bits physical, 48 bits virtual
CPU(s):              4
On-line CPU(s) list: 0-3
Thread(s) per core:  2
Core(s) per socket:  2
Socket(s):           1
NUMA node(s):        1
Vendor ID:           GenuineIntel
CPU family:          6
Model:               142
Model name:          Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz
Stepping:            9
CPU MHz:             1224.772
CPU max MHz:         3500,0000
CPU min MHz:         400,0000
BogoMIPS:            5808.00
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            4096K
NUMA node0 CPU(s):   0-3
Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xgetbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp flush_l1d
```


Max Memory Bandwidth:  [34.1 GB/s](
https://ark.intel.com/content/www/de/de/ark/products/95451/intel-core-i7-7500u-processor-4m-cache-up-to-3-50-ghz.html)
since there are 2 cores and we use a single threaded application the maximal bandwidth is 17.1 GB/s
(All branchless)
(All values are implemented as `uint64_t`)

# Random Vector Scan
```
Selectivity: 27491679 / 250 *10⁶ = 11%

Measurements (ns): 189394376 189061298 187842284 189126518 188030161 187571031 189150227 189203284 187641356 187714797

250 *10⁶ * 8 byte / 188.5 ms = 10.61 GB/s

10.61 GB/s / 34.1 GB/s = 31.11 %
```
=> effective memory bandwidth utilization is 31.11 % --> 62.22% for one core

# TCPH Full Table Scan
```
Selectvity: 4851 / 5000000 =  0.10 %

Measurements (ns): 3717247 3672888 3691449 3697739 5336719 4965723 4768795 8904177 3651819 3623240

Median: 3.707 ms

5000000 * 8 byte /  3.707 ms  = 10.79 GB/s

10.79 GB/s / 34.1 GB/s = 31.64 %
```
=> effective memory bandwidth utilization is 31.64 % --> 63.28% for one core

# Query 6 compiled
Query 6 uses values
l_extendedprice
l_discount
l_quantity
l_shipdate
l_shipdate
```
4 * Decimal + 2 * Date = 6 * 8 byte = 48 byte

5000000 * 48 byte /  61864257 ns = 3.879 GB/s

3.879 GB/s / 34.1 GB/s = 11.38%
```
=> effective memory bandwidth utilization is 11.38% --> 22.76% for one core
