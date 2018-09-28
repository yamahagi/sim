open Syntax


let opcode e = 
(
    match e with 
    | Label _ -> failwith "label doesn't appear in bin"
    | ADDI _ -> "000000"
    | SUBI _ -> "000001"
    | MULI _ -> "000010"
    | DIVI _ -> "000011"
    | ADD _ ->  "001000"
    | SUB _ ->  "001001"
    | MUL _ ->  "001010"
    | DIV _ ->  "001011"
    | LOAD _ -> "011000"
    | STORE _-> "011001"
    | JUMP _->  "100000"
    | BEQ _ -> "101000"
    | BLE _ -> "101001"
    | AND _ -> "010000"
    | OR _ -> "010001"
    | IN _ -> "110000"
    | OUT _ -> "110001"
    | CMPD _ -> "101010"
    | CMPDI _ -> failwith "yet implemented"
    | LI _ -> failwith "yet implemented"
)
let binary_encode (env:(string * int) list) keta number = 
    let str = String.make keta '0' in
    str
let encode env e = 
match e with
| Label s  -> []
| _ -> 
    let op = opcode e in
    let t = 
    (
    match e with
    | ADDI(t,s,d) | SUBI(t,s,d) | MULI(t,s,d) | DIVI(t,s,d) -> 
        binary_encode env 26 ((t lsl 26) lor ))
    in
    [t]


let make_env (env,counter) expr = 
    match expr with
    | Label s -> 
            ((s,counter)::env,counter)
    | _ -> 
            (env,counter+1)
let f (exp_list) = 
    let (env,counter) = List.fold_left make_env ([],0) exp_list in
    List.concat (List.map (encode env) exp_list)
