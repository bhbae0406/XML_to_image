"Always include line numbers"
set number 

"Always autoindent (taken from stack overflow)
:set autoindent
:set cindent

"Reduce tab/indent size to 3 spaces
:set tabstop=8 softtabstop=0 expandtab shiftwidth=3 smarttab

"Easier movement between splits:
nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

   "Swapping windows - found in stack overflow"
function! MarkWindowSwap()
   let g:markedWinNum = winnr()
   endfunction

function! DoWindowSwap()
   "Mark destination
let curNum = winnr()
   let curBuf = bufnr( "%" )
   exe g:markedWinNum . "wincmd w"
   "Switch to source and shuffle dest->source
   let markedBuf = bufnr( "%" )
   "Hide and open so that we aren't prompted and keep history
   exe 'hide buf' curBuf
   "Switch to dest and shuffle source->dest
   exe curNum . "wincmd w"
   "Hide and open so that we aren't prompted and keep history
   exe 'hide buf' markedBuf 
   endfunction

   nmap <silent> <leader>mw :call MarkWindowSwap()<CR>
   nmap <silent> <leader>pw :call DoWindowSwap()<CR>
