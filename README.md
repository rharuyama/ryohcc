# Cコンパイラryohcc

初期のCコンパイラに近いものををC言語で書きました．`ryohcc`は，四則演算や比較演算、代入文(例えば`a = 32; b = 23; c = b + 1; a + b + c;`)をx86-64へコンパイルします．

以下の説明では，環境としてMacを想定しています．その他のUnix系OSの場合は`docker`コマンドの前に`sudo`が必要な場合があります．

## テスト

テストするには，`docker`をインストールした上で，`Dockerfile`があるディレクトリ`ryohcc`へ移動し，以下のコマンドを実行してください．

```
git clone https://github.com/rharuyama/ryohcc
cd ryohcc
docker build -t ryohcc-image .
docker run -it -d -v $(pwd):/home/ --name ryohcc ryohcc-image
docker exec -it ryohcc bash
```

するとコンテナ`ryohcc`の中に入るので，続けて次のコマンドを入力してください．

```
make test
```

筆者の環境だと，初めての時は2分半程かかりました．

乗算と除算は，加算と減算より優先的に解釈されます．以下は`ryohcc`へ入力する項の例です．式が真の時に1，偽の時0にを出力します．

```
2 <= 1
7 <= 7
-(3+5) + 10<=3 
1 >= 3
6 >= -3*+5 + 20
```

注．`build.sh`と`test.sh`は実行ファイルの実行を含むので，コンテナ内に入ってからでなければうまく実行できないことに注意してください．

## 参考文献
[低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook)
