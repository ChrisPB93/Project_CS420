#!/bin/bash

rm -rf results.txt
make > /dev/null

size=32

echo "=========== Start of sequential LU decomposition ==========" >> results.txt
echo "" >> results.txt

echo "Running sequentialLU.exe for size $size" >> results.txt
./sequentialLU.exe $size >> results.txt

echo "" >> results.txt
echo "=========== End of sequential LU decomposition ============" >> results.txt
echo "" >> results.txt
echo "=========== Start of parallel LU decomposition ============" >> results.txt
echo "" >> results.txt

for nodes in 1 2 4 8
do
	for cores in 1
	do
	    echo "Running parallelLU.exe for size $size on $nodes nodes and $cores cores" >> results.txt
	    mpirun -np $nodes ./parallelLU.exe $size $cores >> results.txt
	    echo "" >> results.txt
	done
done

echo "=========== End of parallel LU decomposition ==============" >> results.txt
echo ""
