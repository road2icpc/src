cp ~/.config/nvim/init.lua ~/.backup_init_$RANDOM.lua
DIR=~/road2icpc/src
mkdir -p ~/.config/nvim
cp "${DIR}"/config/init.lua ~/.config/nvim/init.lua
export PATH="$DIR/scripts:$PATH"
