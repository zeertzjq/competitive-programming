setxkbmap -option caps:escape
alias g++='g++ -Wall -Wextra -g'
alias x='./a.out'
alias g='gdb a.out'
c() { g++ "${PWD##*/}.cpp" $@; }
u() { cp "${PWD##*/}$1.in" "${PWD##*/}.in"; }
d() { vimdiff "${PWD##*/}$1.ans" "${PWD##*/}.out"; }
