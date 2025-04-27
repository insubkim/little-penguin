# little-penguin

1. ctags
vim - ctrl + ] 로 해당 심볼로 이동, 
    - ctrl + T 뒤로가기
db 파일 생성
cd [소스 파일]
ctags -R .

https://harryp.tistory.com/130


2. cscope
db 생성
find ./ -name '*.[cCsShH]' > file_list$ cscope -i file_list
cscope -i file_list

검색
:cs find 검색유형 keyword

0 (s) - 키워드를 검색

1 (g) - 선언 (정의) 되어 있는 부분으로 이동
2 (d) - 이 함수가 호출 하는 함수 목록 출력
3 (c) - 이 함수를 호출하는 함수 출력
4 (t) - 문자열 검색
5 (e) - 확장 정규식을 사용하여 검색
7 (f) - 파일 검색 (파일 이름 검색)
8 (i) - 이 파일을 include 하는 파일을 검색
출처: https://harryp.tistory.com/131 [Park's Life:티스토리]

Tagbar
플러그인 설치
git clone https://github.com/preservim/tagbar.git \
  ~/.vim/pack/vendor/start/tagbar

tagbar는 ctags 설치시 같이 따라옴.
.vimrc 수정
call plug#begin('~/.vim/plugged')
Plug 'preservim/tagbar'
call plug#end()

:PlugInstall
https://my.yirum.net/universal-ctags-%EC%99%80-tagbar-%EC%84%A4%EC%B9%98/

 map <F12> :TagbarToggle<CR>
let g:tagbar_autofocus = 1

let g:tagbar_autoclose   = 1

