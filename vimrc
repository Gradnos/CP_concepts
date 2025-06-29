set nocompatible    " use vim, not vi api
syntax on           " enable syntax processing
set number          " show line numbers
set relativenumber
set mouse=a
set guioptions-=T
set guioptions-=m
set noerrorbells
set t_vb=
set visualbell t_vb=
set scrolloff=5
set tabstop=4       " number of visual spaces per tab
set softtabstop=4   " number of spaces in tab when editing
set autoindent      " indent at the same level of the previous line
set smartindent     " if you wnat to paste in insert mode, press `f5` (paste toggle)
set autoindent
set showmatch
set smarttab
set shiftwidth=4    " use indents of 4 spaces
set bs=2
set cursorline      " highlight current line
set hlsearch
set expandtab       " tabs are spaces
set incsearch       " search as characters are entered
set showcmd
set ignorecase
set smartcase

let mapleader = " "

nnoremap <leader>w :w<CR>
nnoremap <leader>e :Ex<CR>
nnoremap <leader>x :wq<CR>
nnoremap <leader>n :nohlsearch<CR>
nnoremap <leader>z :copen<CR>
nnoremap <leader>Z :cclose<CR>
nnoremap <leader>, :cp<CR>
nnoremap <leader>. :cn<CR>
nnoremap <leader>p "+p
nnoremap <leader>q :q!<CR>
nnoremap <leader>y "+y
nnoremap <leader>f <C-^>

nnoremap H ^
nnoremap L $
nnoremap <leader>T gtGdgg"+p:w<cr>gt:call BuildAndRun()<cr>
nnoremap <leader>t gtGdgg"+p:w<cr>gt:call Run()<cr>
nnoremap <leader>P :cd %:h<cr>
autocmd filetype cpp setlocal makeprg=mingw32-make\ F=%:p

function! BuildAndRun()
    w
    silent make
    if v:shell_error
        copen
    else
        cclose
        call Run()
    endif
endfunction

function! Run()
    execute '!'.expand('%<').'.exe'
endfunction

nnoremap <leader>R :call BuildAndRun()<CR>
nnoremap <leader>r :call Run()<CR>

inoremap jk <esc>
inoremap kj <esc>
inoremap { {<CR>}<esc>O
set nowrap
set laststatus=2 " always show the status bar colorscheme zaibatsu
set guifont=Consolas:h14
colorscheme retrobox
