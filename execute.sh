FILEPATH=assets/sample_data
LINEITEMS=$(wc -l $FILEPATH/lineitem.tbl | awk '{print $1}')
PARTS=$(wc -l $FILEPATH/part.tbl | awk '{print $1}')
EXECUTIONS=20

echo "build with vectorization"
cd build
rm CMakeCache.txt
cmake -DVECTORIZE=ON -DCMAKE_BUILD_TYPE=Release ..
make -j 8 -B
(cd src && ./Main ../../$FILEPATH $LINEITEMS $PARTS $EXECUTIONS)
mkdir vectorized
mv src/*.csv vectorized/
cd ..
