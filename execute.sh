#!/bin/bash -e

FILEPATH=assets/sample_data2
LINEITEMS="${LINEITEMS:-$(wc -l $FILEPATH/lineitem.tbl | awk '{print $1}')}"
# PARTS=$(wc -l $FILEPATH/part.tbl | awk '{print $1}')
PARTS=$(($LINEITEMS / 30))
EXECUTIONS="${EXECUTIONS:-20}"
# Selectivity 5 translates to 50% (TCP-H standard)
SELECTIVITY="${SELECTIVITY:-5}"


rm -f build/CMakeCache.txt
cd build
cmake -DVECTORIZE=ON -DCMAKE_BUILD_TYPE=Debug -DSELECTIVITY=$SELECTIVITY ..
make -j 8 -B
(cd src && ./Main ../../$FILEPATH $LINEITEMS $PARTS $EXECUTIONS)
rm -rf vectorized
mkdir vectorized
mv src/*.csv vectorized/
cd ..
