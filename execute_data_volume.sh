#!/bin/bash -e

mkdir data_volume

for i in `seq 600000 600000 6000000`;
do
	export LINEITEMS=$i
	./execute.sh
	mkdir data_volume/$LINEITEMS/
	mv build/non_vectorized data_volume/$LINEITEMS/
	mv build/vectorized data_volume/$LINEITEMS/
done