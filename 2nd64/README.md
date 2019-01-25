https://github.com/occho/cpuex/tree/master/simulator

これを参考にしてます

makeで実行ファイルsim作成
make silentで何も表示しないで実行結果のみ出力するsim,
make silentmemでメモリを表示しないsim,
make silentregでレジスタを表示しないsimが作れます。

outはデフォルトはd.txtというものに出力されます。二つ目の引数で出力先を指定できます。上書きです。
レジスタ表示は命令実行後ではなく命令実行時のレジスタの状態を表示します。


