echo "Build without vectorization"
cd build
rm CMakeCache.txt
cmake -DVECTORIZE=OFF -DCMAKE_BUILD_TYPE=Release ..
make -j 8 -B
(cd src && ./Main)
mkdir non_vectorized
mv src/*.csv non_vectorized/
cd ..

echo "build with vectormrization"
cd build
rm CMakeCache.txt
cmake -DVECTORIZE=ON -DCMAKE_BUILD_TYPE=Release ..
make -j 8 -B
(cd src && ./Main)
mkdir vectorized
mv src/*.csv vectorized/
cd ..
