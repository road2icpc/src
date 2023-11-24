-- the entire init.lua from before, pick and choose:

local options = {
  cmdheight = 1,
  ignorecase = true,
  mouse = "a",
  expandtab = true,
  shiftwidth = 4,
  tabstop = 4,
  cursorline = true,
  number = true,
  relativenumber = true,
  numberwidth = 1,
  signcolumn = "yes",
  wrap = false,
  scrolloff = 6,
  sidescrolloff = 6,
  foldmethod="indent",
  foldlevel=99,
  colorcolumn='80',
}

local keymap = vim.api.nvim_set_keymap
local ops = { noremap = true, silent = true }

keymap("v", "<A-Down>", ":m '>+1<CR>gv=gv", ops)
keymap("v", "<A-Up>", ":m '<-2<CR>gv=gv", ops)
keymap("v", "p", "\"_dP", ops)

for k, v in pairs(options) do
  vim.opt[k] = v
end

local function hashCurrentBuffer()
    local buffer_content = table.concat(vim.api.nvim_buf_get_lines(0, 0, -1, false), "\n")
    local command = "echo '"..buffer_content.."' | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6"
    local hash = vim.fn.system(command)
    hash = hash:gsub("%s+", "")
    print("Buffer Hash: " .. hash)
end
vim.api.nvim_create_user_command('Hash', hashCurrentBuffer, {})
