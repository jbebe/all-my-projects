:: first argument %1
:: file name: %~n1
:: file extension: %~x1
nasm -f bin -o %~n1.img %~n1%~x1
set/p a=