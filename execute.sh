cd build
cmake .. -DVECTORIZE=OFF
make -j 8
(cd src && ./Main)
mkdir non_vectorized
mv src/*.csv non_vectorized/

#start second run with vectorization
cmake .. -DVECTORIZE=ON
make -j 8
(cd src && ./Main)
mkdir vectorized
mv src/*.csv vectorized/
cd ..
