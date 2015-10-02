set number
set linebreak
set showbreak=+++
set showmatch
set visualbell

set hlsearch
set smartcase
set ignorecase
set incsearch

set autoindent
"set tabstop=8
"set softtabstop=4
"set shiftwidth=4
set expandtab
set smartindent
set smarttab

set ruler

set undolevels=1000

"Cursor tends to rest in the middle-area of screen
set scrolloff=10

"80th line is red
set formatoptions=qrn1
set colorcolumn=80

"remap for ESC
ino jkl <esc>
ino jlk <esc>
ino kjl <esc>
ino klj <esc>
ino ljk <esc>
ino lkj <esc>
nno jkl <esc>
nno jlk <esc>
nno kjl <esc>
nno klj <esc>
nno ljk <esc>
nno lkj <esc>
vno jkl <esc>
vno jlk <esc>
vno kjl <esc>
vno klj <esc>
vno ljk <esc>
vno lkj <esc>

"syntax settings
syntax on
autocmd FileType c set cindent
"set cindent
