
cd build
rm CMakeCache.txt
cmake -DVECTORIZE=ON -DCMAKE_BUILD_TYPE=Release ..
make -j 8 -B
(cd src && ./Measurements ../../assets/sample_data/lineitem.tbl 2500000 100)
cd ..
