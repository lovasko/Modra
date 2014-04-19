#!/bin/bash

# run the specified configuration, wait 15 seconds and then
# send SIGINT to the process, which handles it well and dumps
# the statistical information
function run 
{
	./test -o "$1" -d "$2" -s "$3" -m "$4" -b "$5" -t "$6" -l "$7" -w "$8" &
	PID="$!"
	sleep 20 
	kill -s INT "$PID" 
}

function main
{
	# print the OpenGL info
	./info

	# flat basics
	run sierpinsky 1 flat immediate off off off off
	run sierpinsky 3 flat immediate off off off off
	run sierpinsky 5 flat immediate off off off off
	run sierpinsky 7 flat immediate off off off off
	run sierpinsky 9 flat immediate off off off off

	# smooth basics
	run sierpinsky 1 smooth immediate off off off off
	run sierpinsky 3 smooth immediate off off off off
	run sierpinsky 5 smooth immediate off off off off
	run sierpinsky 7 smooth immediate off off off off
	run sierpinsky 9 smooth immediate off off off off

	# blending
	run sierpinsky 5 flat immediate on off off off

	# wireframe 
	run sierpinsky 5 flat immediate off off off on

	# light 
	run sierpinsky 5 flat immediate off off on off

	# light & blending
	run sierpinsky 3 flat immediate on off on off

	# light & blending
	run sierpinsky 5 flat immediate on off on off

	# light & blending
	run sierpinsky 7 flat immediate on off on off
}

main

