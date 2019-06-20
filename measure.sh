FILEPATH=../../assets/sample_data/lineitem.tbl
ITEMS=6000
EXECUTIONS=10


cd build
rm CMakeCache.txt
cmake -DVECTORIZE=ON -DCMAKE_BUILD_TYPE=Release ..
make -j 8 -B
(cd src && ./Measurements $FILEPATH $ITEMS $EXECUTIONS)
cd ..
