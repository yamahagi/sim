%{
open Syntax
exception ParseError
%}

%token <int> INT
%token <float> FLOAT
%token COMMA
%token EOF
%token ADDI 
%token ADD
%token SUBI 
%token SUB
%token MULI 
%token MUL
%token DIVI
%token DIV
%token MR
%token LI
%token STORE
%token LOAD
%token CMPDI
%token CMPD
%token BEQ
%token BLE
%token IN
%token OUT
%token JUMP
%token COLON
%token <int> PERCENTINT
%token <string> IDENT
%type <Syntax.t list> exp
%start exp
%%
exp:
    | order exp { $1::$2 }
    | EOF {[]}
label: 
    | IDENT COLON {$1}
reg: 
    | PERCENTINT {$1}
order:
    | label  { Label($1) }
    | ADDI reg COMMA reg COMMA INT { ADDI($2,$4,$6) }
    | MULI reg COMMA reg COMMA INT { MULI($2,$4,$6) }
    | SUBI reg COMMA reg COMMA INT { SUBI($2,$4,$6) }
    | DIVI reg COMMA reg COMMA INT { DIVI($2,$4,$6) }
    | ADD reg COMMA reg COMMA reg { ADD($2,$4,$6) }
    | MUL reg COMMA reg COMMA reg { MUL($2,$4,$6) }
    | SUB reg COMMA reg COMMA reg { SUB($2,$4,$6) }
    | DIV reg COMMA reg COMMA reg { DIV($2,$4,$6) }
    | LI reg COMMA INT { LI($2,$4)}
    | LOAD reg COMMA reg COMMA INT { LOAD($2,$4,$6)}
    | STORE reg COMMA reg COMMA INT { STORE($2,$4,$6)}
    | CMPDI reg COMMA INT { CMPDI($2,$4)}
    | CMPD reg COMMA reg { CMPD($2,$4)}
    | BEQ reg COMMA reg { BEQ($2,$4)}
    | BLE reg COMMA reg { BLE($2,$4)}
    | IN reg { IN($2)}
    | OUT reg { OUT($2)}
    | JUMP IDENT {JUMP($2)}

