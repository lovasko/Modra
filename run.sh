#!/bin/bash

# run the specified configuration, wait 15 seconds and then
# send SIGINT to the process, which handles it well and dumps
# the statistical information
function run 
{
	./test -o "$1" -d "$2" -s "$3" -m "$4" -v "$5" -b "$6" -t "$7" -l "$8" -w "$9" &
	PID="$!"
	sleep 20 
	kill -s INT "$PID" 
}

function main
{
	# print the OpenGL info
	./info

	# flat basics in immediate mode
	run sierpinsky 1 flat immediate ignore off off off off
	run sierpinsky 3 flat immediate ignore off off off off
	run sierpinsky 5 flat immediate ignore off off off off
	run sierpinsky 7 flat immediate ignore off off off off
	run sierpinsky 9 flat immediate ignore off off off off

	# flat basics in vertex-buffer mode 
	run sierpinsky 1 flat vertex-buffer interleaved off off off off
	run sierpinsky 3 flat vertex-buffer interleaved off off off off
	run sierpinsky 5 flat vertex-buffer interleaved off off off off
	run sierpinsky 7 flat vertex-buffer interleaved off off off off
	run sierpinsky 9 flat vertex-buffer interleaved off off off off

	# smooth basics in immediate mode
	run sierpinsky 1 smooth immediate ignore off off off off
	run sierpinsky 3 smooth immediate ignore off off off off
	run sierpinsky 5 smooth immediate ignore off off off off
	run sierpinsky 7 smooth immediate ignore off off off off
	run sierpinsky 9 smooth immediate ignore off off off off

	# blending
	run sierpinsky 5 flat immediate ignore on off off off

	# wireframe 
	run sierpinsky 5 flat immediate ignore off off off on

	# light 
	run sierpinsky 5 flat immediate ignore off off on off

	# light & blending
	run sierpinsky 3 flat immediate ignore on off on off

	# light & blending
	run sierpinsky 5 flat immediate ignore on off on off

	# light & blending
	run sierpinsky 7 flat immediate ignore on off on off
}

main

