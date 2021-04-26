#!/bin/bash

assert(){
    input="$1"
    expected="$2"

    # 自作のコンパイラでのコンパイル結果をtarget.sに出力
     ./ryohcc "$input" > target.s
    
    # 出力したアセンブリ言語を実行
    clang -o target target.s
    ./target
    actual="$?"

    if [ "$actual" == "$expected" ]; then
	echo "$input => $actual"
    else
	echo "$input => $expected expected, but got $actual"
	exit 1
    fi   
}

assert 1 1
assert 42 42
#assert "5 * 20" 100
#assert "1+2" "3"

echo Done
