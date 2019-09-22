#!/bin/bash
var=3
for test in {1..6}
do
	elems=$((test*var))
	#callMiniTest="$(python miniTest.py $elems $1)"
	echo 'TEST' $test
	#echo 'TEST' $1
	#echo $callMiniTest
	#echo $callMiniTest | ./main all
	
	python miniTest.py $elems $1 | ./main all
	#python miniTest.py $elems $1 | tee /dev/tty | ./main all
done
