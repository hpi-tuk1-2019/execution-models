echo "Build without vectorization"
cd build
rm CMakeCache.txt
cmake -DVECTORIZE=OFF ..
make -j 8 -B
(cd src && ./Main)
mkdir non_vectorized
mv src/*.csv non_vectorized/
cd ..

echo "build with vectormrization"
cd build
rm CMakeCache.txt
cmake -DVECTORIZE=ON ..
make -j 8 -B
(cd src && ./Main)
mkdir vectorized
mv src/*.csv vectorized/
cd ..
