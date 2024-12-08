error() { echo -e "\033[1;31mError:\033[0m $@" 1>&2; }

dialect='-std=c++20 -fno-rtti -fstrict-enums'
optimizations='-O3 -fipa-pta -flto -fdevirtualize-at-ltrans'

errors='
	-Wfatal-errors
	-Werror
	-Wpedantic
	-pedantic-errors
	-Wall
	-Wextra
	-Wno-parentheses
	-Wstrict-null-sentinel
	-Wdouble-promotion
	-Wfloat-equal
	-Wcast-qual
	-Wzero-as-null-pointer-constant
	-Wlogical-op
	-Wimplicit-fallthrough=5
	-Wnull-dereference
	-Wduplicated-branches
	-Wctor-dtor-privacy
	-Wnon-virtual-dtor
	-Wsuggest-final-types
	-Wsuggest-final-methods
	-Wsuggest-override
	-Wformat-overflow
	-Wformat-security
	-Wformat-signedness
	-Wuseless-cast
	-Wextra-semi
	-Wredundant-decls'

params="$dialect $optimizations $errors"

if [[ $# -ne 1 ]]; then
	error "Wrong number of arguments!"
	return 1
fi

target="$1"

if [[ "$target" -lt 10 ]]; then
	target="0$target"
fi

cd $target-*
g++ main.cpp -o main $dialect $optimizations $errors
./main
