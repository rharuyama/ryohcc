#!/bin/bash

assert(){
    echo "--------------------------------"
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

assert 42 42
assert "6 * 5" 30
assert "6*5*4*1" 120 # 1~255の範囲
assert " 1 * 2 * 2 *1 * 1 *3*  1 * 4 * 4" 192
assert "6*5*4+3*2*1" 126
assert "35 / 5" 7
assert " 6 * 5 / 5/3 * 7" 14
assert "7 + 5" 12
assert "7 + 5 * 2" 17
assert "7 - 3" 4
assert "2 * 5 / 1 + 9" 19
assert "2 * 5 - 9" 1
assert "6 * (5 + 4)" 54
assert "(6 + 5) * (4 + 3)" 77
assert "-3*+5*-1" 15
assert "5 <= 7" 1 
echo Done!
