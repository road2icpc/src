setxkbmap -option caps:escape
# fast:
xset r rate 200 120
# normal:
xset r rate 500 35
# debug compile (C++):
dc() {
	bsnm=$(basename "$1" .cpp)
	# EUC uses -std=gnu++20
	command="g++ ${bsnm}.cpp -o $bsnm -Wshadow -Wall -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG -std=gnu++20 -Wfatal-errors"
	echo $command
	$command
}
set -o vi
