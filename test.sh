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
    echo "--------------------------------"  
}

assert "42;" 42
assert "6 * 5;" 30
assert "6*5*4*1;" 120 # 1~255の範囲
assert " 1 * 2 * 2 *1 * 1 *3*  1 * 4 * 4;" 192
assert "6*5*4+3*2*1;" 126
assert "35 / 5;" 7
assert " 6 * 5 / 5/3 * 7;" 14
assert "7 + 5;" 12
assert "7 + 5 * 2;" 17
assert "7 - 3;" 4
assert "2 * 5 / 1 + 9;" 19
assert "2 * 5 - 9;" 1
assert "6 * (5 + 4);" 54
assert "(6 + 5) * (4 + 3);" 77
assert "-3*+5*-1;" 15
assert "5 <= 7;" 1
assert "3 + 4 <= 6;" 0
assert "7 >= 5;" 1
assert "38 * 0 >= 1;" 0
assert "1 <= 1;" 1
assert "1 < 1;" 0
assert "17 > 13;" 1
assert "83 == 83;" 1
assert "83 != 83;" 0
assert "1;2;3;" 3
assert "a = 3; a + 4;" 7
assert "a = 3; a = 4 + a; a * 10;" 70
assert "a = 32; b = 23; c = b + 1; a + b + c;" 79
assert "return 42;" 42
assert "a = 32; b = 23; c = b + 1; return a + b + c;" 79
assert "return 3; return 4;" 3
assert "foo = 1; bar = 2 + 3; return foo + baz;" 6
assert "f00 = 1; bar = 2 + 3; return f00 + baz;" 6
assert "if(7 == 7) return 88;" 88
assert "if(7 == 2) 88; else 77;" 77 # returnが付くと途中でリターンしてしまい88になる
assert "if(7==2)return 88; else return 77;" 77

echo Done!
