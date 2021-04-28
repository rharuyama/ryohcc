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

assert 42 42
assert "6 * 5" 30
assert "6*5*4*1" 120 # 1~255の範囲
assert " 1 * 2 * 2 *1 * 1 *3*  1 * 4 * 4" 192
assert "35 / 5" 7
assert " 6 * 5 / 5/3 * 7" 14
assert "7 + 5" 12
assert "7 + 5 * 2" 17

echo Done!
