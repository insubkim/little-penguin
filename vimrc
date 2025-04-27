" enable syntax, file-type plugins & indenting
syntax on
filetype plugin indent on

" show line numbers, match brackets
set number
set showmatch

" C-style tabs → 4 spaces
set tabstop=4
set shiftwidth=4
set expandtab

" smarter auto-indent for C
set smartindent
" or for even more C-specific indenting:
" set cindent


call plug#begin('~/.vim/plugged')
Plug 'preservim/tagbar'
call plug#end()


map <F12> :TagbarToggle<CR>
" Tagbar 열면 바로 사이드바에 포커스
let g:tagbar_autofocus = 1

" 태그 점프 후 Tagbar를 자동으로 닫고 편집 창으로 복귀
let g:tagbar_autoclose   = 1

