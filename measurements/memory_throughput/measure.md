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
34.1 GB/s / 4 (per kernel) = 8.525 GB/s

# Random Vector
250 *10⁶ * 2 byte = 500 MB
500 MB / 53183490 ns = 2.94 GB/s
2.94 GB/s / 8.525 GB/s = 34.5 %

# TCPH Full Table Scan (touch_all_values)
600000 * 4 byte /  460000ns  = 5.217 GB/s

5.217 GB/s / 8.525 GB/s = 61.2 %

=> effective usage: 61.2 % of available bandwidth is used

# Query 6 compiled
Query 6 uses values
l_extendedprice
l_discount
l_quantity
l_shipdate
l_shipdate

4 x Decimal + 2 x Date = 6 * 4 byte = 24 byte 

600000 * 24 byte /  2s  = 0.72 GB/s

0.72 GB/s / 8.525 GB/s = 8.45 %