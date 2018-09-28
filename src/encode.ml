open Syntax

let opcode e =
  match e with
  | Label _ -> failwith "label doesn't appear in bin"
  | ADDI _ -> "000000"
  | SUBI _ -> "000001"
  | MULI _ -> "000010"
  | DIVI _ -> "000011"
  | ADD _ -> "001000"
  | SUB _ -> "001001"
  | MUL _ -> "001010"
  | DIV _ -> "001011"
  | LOAD _ -> "011000"
  | STORE _ -> "011001"
  | JUMP _ -> "100000"
  | BEQ _ -> "101000"
  | BLE _ -> "101001"
  | AND _ -> "010000"
  | OR _ -> "010001"
  | IN _ -> "110000"
  | OUT _ -> "110001"
  | CMPD _ -> "101010"
  | CMPDI _ -> failwith "yet implemented"
  | LI _ -> "011010"

let binary_encode keta number =
  let str = Bytes.make keta '0' in
  let _ =
    for i = 0 to keta - 1 do
      if (number lsr i) land 1 = 1 then Bytes.set str (keta - 1 - i) '1'
      else Bytes.set str (keta - 1 - i) '0'
    done
  in
  Bytes.to_string str

let encode env e =
  match e with
  | Label s -> []
  | _ ->
      let op = opcode e in
      let t =
        binary_encode 26
          ( match e with
          | ADDI (t, s, d) | SUBI (t, s, d) | MULI (t, s, d) | DIVI (t, s, d)
            ->
              (t lsl 21) lor (s lsl 16) lor d
          | ADD (t, a, b) | SUB (t, a, b) | MUL (t, a, b) | DIV (t, a, b) | AND(t,a,b) | OR(t,a,b) ->
              (t lsl 21) lor (a lsl 16) lor (b lsl 11)
          | JUMP label  
          | BEQ (label) | BLE (label) -> List.assoc label env
          | LOAD (t, a, d) | STORE (t, a, d) -> (t lsl 21) lor (a lsl 16) lor d
          | LI (t, d) -> (t lsl 21) lor d
          | CMPD (a, b) -> (a lsl 21) lor (b lsl 16)
          | IN a -> a lsl 21
          | OUT a -> a lsl 21 
          | Label _ -> failwith "label is unreachble"
          | _ -> failwith "yet implemented"
          )
      in
      [op ^ t]

let make_env (env, counter) expr =
  match expr with
  (* alignを考えて４かける *)
  | Label s -> ((s, 4 * counter) :: env, counter)
  | _ -> (env, counter + 1)

let f exp_list =
  let env, counter = List.fold_left make_env ([], 0) exp_list in
  List.concat (List.map (encode env) exp_list)
