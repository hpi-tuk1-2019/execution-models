#!/bin/bash -e

FILEPATH=../../assets/sample_data2/lineitem.tbl
LINEITEMS="${LINEITEMS:-5998600}"
EXECUTIONS="${EXECUTIONS:-20}"

# Selectivity 7 translates to 70%
SELECTIVITY="${SELECTIVITY:-7}"

# echo "Build without vectorization"
# rm -f build/CMakeCache.txt
# cmake -DVECTORIZE=OFF -DCMAKE_BUILD_TYPE=Release -DSELECTIVITY=$SELECTIVITY -B build
# cd build
# make -j 8 -B
# (cd src && ./Main $FILEPATH $LINEITEMS $EXECUTIONS)
# rm -rf non_vectorized
# mkdir non_vectorized
# mv src/*.csv non_vectorized/
# cd ..

echo "build with vectormrization"
rm -f build/CMakeCache.txt
cmake -DVECTORIZE=ON -DCMAKE_BUILD_TYPE=Release -DSELECTIVITY=$SELECTIVITY -B build
cd build
make -j 8 -B
(cd src && ./Main $FILEPATH $LINEITEMS $EXECUTIONS)
rm -rf vectorized
mkdir vectorized
mv src/*.csv vectorized/
cd ..
