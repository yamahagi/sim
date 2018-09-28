let lexbuf outchan l =
  let p = Parser.exp Lexer.token l |> Encode.f in
  List.map (fun x -> print_string x ; print_newline ()) p

let _ = lexbuf stdout (Lexing.from_channel stdin)
