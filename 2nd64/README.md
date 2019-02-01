https://github.com/occho/cpuex/tree/master/simulator

これを参考にしてます

makeで実行ファイルsim作成

simの引数は
第一引数:命令ファイル
第二引数:出力先
第三引数:入力元
となってます。

出力先を指定せずに入力元を指定すると(./sim 命令ファイル 入力元のように)入力元を出力先と勘違いしてしまうゴミ仕様なので気をつけてください。
基本的には
make fib
make mandelbrot,
make minrt
を使うことによってそれぞれのプログラムを実行できるのでこちらを使ってください。

make silentで何も表示しないで実行結果のみ出力するsim,
make silentmemでメモリを表示しないsim,
make silentregでレジスタを表示しないsimが作れます。
make silentmemregでメモリとレジスタを表示しない（pcと命令のみ表示する)simが作れます。

outはデフォルトはd.txtというものに出力されます。二つ目の引数で出力先を指定できます。新規作成です。
レジスタ表示は命令実行後ではなく命令実行時のレジスタの状態を表示します。


