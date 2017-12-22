#!/usr/bin/env bash
OWN_DIR="$( cd "$( dirname "$0" )" && pwd )"
PROBLEM_DIR="$OWN_DIR/.."

g++ -O2 --std=c++11 $PROBLEM_DIR/submissions/accepted/fredrik.cpp

function gen {
	local name=$1
	shift
	echo "Producing $name"
	DATA_FILE="$PROBLEM_DIR/data/secret/$name"
	"$OWN_DIR/generate.py" $* > "$DATA_FILE.in"
	python "$PROBLEM_DIR/input_format_validators/validate.py" < "$DATA_FILE.in"
	if [ $? -ne 42 ]
	then
		echo "Could not validate $name" >&2
		exit
	fi
	./a.out < "$DATA_FILE.in" > "$DATA_FILE.ans"
}

gen medium 50 50 6
gen mediumslow 50 50 180
gen largeslow 125 125 180
gen largequick 125 125 4
gen onlywest 250 0 150
gen onlyeast 0 250 120
gen mostwest 240 10 130
gen mosteast 10 240 110
gen onlywestquick 250 0 9
gen onlyeastquick 0 250 6
gen mostwestquick 240 10 7
gen mosteastquick 10 240 5
