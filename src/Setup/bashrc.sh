alias v=nvim
mcd() {
	mkdir "$1" && cd "$1"
}
# fast:
setxkbmap -option caps:escape
xset r rate 200 120
# normal:
xset r rate 500 35
# debug compile (C++):
dc() {
	base_name=$(basename "$1" .cpp)
	command="g++ -Wshadow -Wall $1 -o $base_name -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG -std=c++2a -Wfatal-errors"
	$command
}
