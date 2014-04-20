#!/bin/bash

# run the specified configuration, wait 15 seconds and then
# send SIGINT to the process, which handles it well and dumps
# the statistical information
function run 
{
	TEST='./testf'
	test "${10}" = "double" && TEST='./testd'

	"$TEST" -o "$1" -d "$2" -s "$3" -m "$4" -v "$5" -b "$6" -t "$7" -l "$8" -w "$9" &
	PID="$!"
	sleep 5 
	kill -s INT "$PID" 
}

function main
{
	# print the OpenGL info
	./info

	# flat basics in immediate mode
	echo "" > tests/floating/float
	run sierpinsky 1 flat immediate ignore off off off off >> tests/floating/float 
	run sierpinsky 3 flat immediate ignore off off off off >> tests/floating/float
	run sierpinsky 5 flat immediate ignore off off off off >> tests/floating/float
	run sierpinsky 7 flat immediate ignore off off off off >> tests/floating/float
	run sierpinsky 9 flat immediate ignore off off off off >> tests/floating/float

	# flat basics in immediate mode (double)
	echo "" > tests/floating/double 
	run sierpinsky 1 flat immediate ignore off off off off double >> tests/floating/double 
	run sierpinsky 3 flat immediate ignore off off off off double >> tests/floating/double 
	run sierpinsky 5 flat immediate ignore off off off off double >> tests/floating/double 
	run sierpinsky 7 flat immediate ignore off off off off double >> tests/floating/double 
	run sierpinsky 9 flat immediate ignore off off off off double >> tests/floating/double 

	# create graph for above
	(cd ./tests/floating && ./main.sh)

  # flat basics in immediate mode 
	run sierpinsky 6 flat immediate ignore off off off off > tests/vertex_buffer/immediate

	# flat basics in vertex-buffer mode interleaved
	run sierpinsky 6 flat vertex-buffer interleaved off off off off > tests/vertex_buffer/interleaved

	# flat basics in vertex-buffer mode separate
	run sierpinsky 6 flat vertex-buffer separate off off off off > tests/vertex_buffer/separate

	# create graph for above
	(cd ./tests/vertex_buffer && ./main.sh)

	# smooth basics in immediate mode
	run sierpinsky 6 smooth immediate ignore off off off off > tests/shading/smooth

	# blending
	run sierpinsky 6 flat immediate ignore off off off off > tests/shading/flat

	# create graph for above
	(cd ./tests/shading && ./main.sh)

	# menger sponge basic tests
	echo "" > tests/quads/quads
	run menger 1 flat immediate ignore off off off off >> tests/quads/quads
	run menger 2 flat immediate ignore off off off off >> tests/quads/quads
	run menger 3 flat immediate ignore off off off off >> tests/quads/quads
	run menger 4 flat immediate ignore off off off off >> tests/quads/quads

	# create graph for above
	(cd ./tests/quads && ./main.sh)

	# blending
	run menger 3 flat immediate ignore on off off off > tests/various/blending

	# texture tests
	run menger 3 flat immediate ignore off on off off > tests/various/textures

	# light 
	run menger 3 flat immediate ignore off off on off > tests/various/light

	# wireframe
	run menger 3 flat immediate ignore off off off on > tests/various/wireframe

	# all but wireframe 
	run menger 3 flat immediate ignore on on on off > tests/various/all

	# create graph for above
	(cd ./tests/various && ./main.sh)
}

main

