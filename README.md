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
