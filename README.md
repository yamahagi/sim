# assembly
assembly

# build
* たぶんocamlbuildがあれば大丈夫?
* ppx_derivingとかも必要かも
make 

# usage
./main.native < test.s
で標準出力に機械語(2進数表記)が出る
* 文法はtest.sに書いてあるのがほとんど
* 4Byte alignのはず(?)なの

# sim
