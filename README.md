# execution-models
This repository is used to compare query performance of compiled and vectorized queries using the TPCH queries.


# How to install

```
mkdir build
cd build
cmake ..
make -j 8
```

# How to compile with vectorization enabled

```
cd <project_root>
cmake -D CMAKE_CXX_FLAGS="-ftree-vectorize" -B build
```


# How to save profiling values
Create folder data for profiling files

# Run with ICC (Intel Compiler)

Use `activate_intel.sh` script to set the environment variables suited for your system. Then run it. Run cmake with `cmake -B build` from the project root. Now you can make use of the execute script just like always. 
