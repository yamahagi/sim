

type t = 
    | Label of string
    | ADDI of int * int * int
    | MULI of int * int * int
    | DIVI of int * int * int
    | SUBI of int * int * int
    | ADD of int * int * int
    | MUL of int * int * int
    | DIV of int * int * int
    | SUB of int * int * int
    | AND of int * int * int
    | OR of int * int * int
    | LI of int * int
    | STORE of int * int * int
    | LOAD of int * int * int
    | CMPDI of int * int
    | CMPD of int * int
    | BEQ of int * int
    | BLE of int * int
    | JUMP of string
    | IN of int 
    | OUT of int
    [@@deriving show]
