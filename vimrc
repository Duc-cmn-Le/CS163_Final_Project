" Gotta be first
set nocompatible
	
filetype off

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'

Plugin 'scrooloose/nerdtree'
Plugin 'jistr/vim-nerdtree-tabs'
Plugin 'lervag/vimtex'

call vundle#end()

filetype plugin indent on

" --- General settings ---
set backspace=indent,eol,start
set ruler
set number
set showcmd
set incsearch
set hlsearch
set bg=dark
set bs=2
set autoindent

" Tab related stuffs
set shiftwidth=4 " tab size = 4
set expandtab
set softtabstop=4
set shiftround 

syntax on

set mouse=a

function! MyTabCompletion()
  if col('.')>1 && strpart( getline('.'), col('.')-2, 3 ) =~ '^\w'
    return "\<C-P>"
  else
    return "\<Tab>"
  endif
endfunction
inoremap <Tab> <C-R>=MyTabCompletion()<CR>
function! MyComment()
  let l = getline('.')
  if l =~ '^\s*\/\/'
    let l = substitute(l, '\/\/', '', '')
  else
    let l = '//' . l
  endif
  call setline(line('.'), l)
endfunction
nnoremap <C-c> :call MyComment()<CR>

" Allow us to use Ctrl-s and Ctrl-q as key blinds
silent !stty -ixon

" Restore default behavior when leaving Vim
autocmd VimLeave * silent !stty ixon
inoremap jj <Esc>

function! CPPSET()
  nnoremap <buffer> <F9> :w<cr>:!g++ % -O2 -o %< -std=c++11 -I ./<cr>:!clear;./%<<cr>
  nnoremap <buffer> <F8> :w<cr>:!g++ % -O2 -o %< -std=c++11 -I ./<cr>
  nnoremap <buffer> <F7> :w<cr>:!g++ *.cpp -O2 -o %< -std=c++11 -I ./<cr>:!clear;./%<<cr>
  nnoremap <buffer> <F6> :w<cr>:!g++ *.cpp -O2 -o %< -std=c++11 -I ./<cr>
  nnoremap <c-s> :w<CR>
  inoremap <c-s> <Esc>:w<CR>l
  vnoremap <c-s> <Esc>:w<CR>
endfunction

function! JAVASET()
  nnoremap <buffer> <F8> :!javac %<cr>
  nnoremap <buffer> <F9> :!javac %<cr>:!clear;java %< %<cr>
  nnoremap <c-s> :w<CR>
  inoremap <c-s> <Esc>:w<CR>l
  vnoremap <c-s> <Esc>:w<CR>
endfunction

function! RUBYSET() 
  nnoremap <buffer> <F9> :w<cr>:!ruby %<cr>
  nnoremap <c-s> :w<CR>
  inoremap <c-s> <Esc>:w<CR>l
  vnoremap <c-s> <Esc>:w<CR>
endfunction

function! PYTHONSET()
  nnoremap <buffer> <F9> :w<cr>:!python %<cr>
  nnoremap <c-s> :w<CR>
  inoremap <c-s> <Esc>:w<CR>l
  vnoremap <c-s> <Esc>:w<CR>
endfunction

function! HTMLSET()
  nnoremap <buffer> <F9> :w<cr>:!open %<cr>
  nnoremap <c-s> :w<CR>
  inoremap <c-s> <Esc>:w<CR>l
  vnoremap <c-s> <Esc>:w<CR>
endfunction 

autocmd FileType cpp    call CPPSET()
autocmd FileType java   call JAVASET()
autocmd FileType ruby   call RUBYSET()
autocmd FileType python call PYTHONSET()
autocmd FileType html   call HTMLSET()

" ----- jistr/vim-nerdtree-tabs -----
"  Open/close NERDTree Tabs with \t
nmap <silent> <leader>t :NERDTreeTabsToggle<CR>
" To have NERDTree always open on startu
let g:nerdtree_tabs_open_on_console_startup = 1
