#!/bin/bash -e

mkdir selectivity

for i in `seq 0 2 10`;
do
	export SELECTIVITY=$i
	./execute.sh
	mkdir selectivity/$SELECTIVITY/
	mv build/vectorized selectivity/$SELECTIVITY/
done