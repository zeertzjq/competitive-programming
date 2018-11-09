c() {
    g++ $@ -Wall -Wextra -g -o "${PWD##*/}" "${PWD##*/}.cpp"
}

u() {
    cp "${PWD##*/}$1.in" "${PWD##*/}.in"
}

x() {
    "./${PWD##*/}" && less "${PWD##*/}.out"
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

d() {
    diff -q "${PWD##*/}$1.ans" "${PWD##*/}.out" || vimdiff "${PWD##*/}$1.ans" "${PWD##*/}.out"
}
