echo "Build without vectorization"
cmake -B build -DVECTORIZE=OFF
cd build
make -j 8 -B
(cd src && ./Main)
mkdir build/non_vectorized
mv build/src/*.csv build/non_vectorized/
cd ..

echo "build with vectroization"
cmake -B build -DVECTORIZE=ON
cd build
make -j 8 -B
(cd src && ./Main)
mkdir vectorized
mv src/*.csv vectorized/
cd ..
