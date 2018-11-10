e() {
    vim "${PWD##*/}.cpp"
}

c() {
    g++ $@ -Wall -Wextra -g -o "${PWD##*/}" "${PWD##*/}.cpp"
}

u() {
    cp "${PWD##*/}$1.in" "${PWD##*/}.in"
}

x() {
    "./${PWD##*/}" && less "${PWD##*/}.out"
}

d() {
    gdb "${PWD##*/}"
}

i() {
    vim "${PWD##*/}$1.in"
}

o() {
    vim "${PWD##*/}$1.out"
}

a() {
    vim "${PWD##*/}$1.ans"
}

v() {
    diff -qZ "${PWD##*/}$1.ans" "${PWD##*/}.out" || vimdiff "${PWD##*/}$1.ans" "${PWD##*/}.out"
}
