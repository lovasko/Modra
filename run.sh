function run 
{
	./test -o $1 -d $2 -s $3 -m $4 -b $5 -t $6 -l $7 -w $8	
	PID=$!
	sleep 15 
	kill -s INT "$PID" 
}

function main
{
	./info
	run sierpinsky 1 flat immediate off off off off
	run sierpinsky 3 flat immediate off off off off
	run sierpinsky 5 flat immediate off off off off
	run sierpinsky 7 flat immediate off off off off
}

main
