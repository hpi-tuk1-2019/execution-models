#!/bin/bash -e

mkdir data_volume

for i in `seq 600000 6000000 59986050`;
do
	export LINEITEMS=$i
	./execute.sh
	mkdir data_volume/$LINEITEMS/
	mv build/vectorized data_volume/$LINEITEMS/
done