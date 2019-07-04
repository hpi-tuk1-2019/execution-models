FILEPATH=../../assets/sample_data
LINEITEMS=6000
EXECUTIONS=20

echo "build with vectorization"
cd build
rm CMakeCache.txt
cmake -DVECTORIZE=ON -DCMAKE_BUILD_TYPE=Release ..
make -j 8 -B
(cd src && ./Main $FILEPATH $LINEITEMS $EXECUTIONS)
mkdir vectorized
mv src/*.csv vectorized/
cd ..
