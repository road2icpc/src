cp ~/.config/nvim/init.lua ~/.backup_init_$RANDOM.lua
DIR="$(dirname "$0")"
cp "${DIR}"/config/init.lua ~/.config/nvim/init.lua
export PATH="$DIR/scripts:$PATH"
