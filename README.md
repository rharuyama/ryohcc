# Cコンパイラryohcc

初期のCコンパイラに近いものををC言語で書きました．`ryohcc`は，四則演算や比較演算、代入文(例えば`a = 32; b = 23; c = b + 1; a + b + c;`)をx86-64へコンパイルします．

以下の説明では，環境としてMacを想定しています．その他のUnix系OSの場合は`docker`コマンドの前に`sudo`が必要な場合があります．

## テスト

テストするには，`docker`をインストールした上で，以下のコマンドを実行してください．

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

注．`make test`は実行ファイルの実行を含むので，コンテナ内に入ってからでなければうまく実行できないことに注意してください．

テストが実行され、最後に`Done!`と表示されたら成功です。ここで行われたテストの入力を参考に、自分で入力を考えて試してみるためには、次の手順を踏んでください。

1. ファイル`source`の中にプログラムを入力する（例：`a = 10; b = 7; c = a * b; c + 7;`）。
2. `bash build_execute.sh`を実行する。このシェルスクリプトは、`source`のなかのプログラムを読み込んでコンパイルし、実行します。
3. 実行結果を表示するためにはコマンド`echo $?`を行ってください。先の例では、`77`が出力されるはずです。

## 参考文献
[低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook)
