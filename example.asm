;Beispielprogramm
Begin:
  in R0       ; Zahl von IN-Port einlesen
  out R0

; Men
  cmp R0, 1   ; R0 == Programm 1 : Carry-Flag Test
  jz Prog1

  cmp R0, 2   ; R0 == Programm 2 : Zero-Flag Test
  jz Prog2

  cmp R0, 4   ; R0 == Programm 3 : ADC Befehl (Add with Carry)
  jz Prog3

  jmp Ende
; Ende Men

; Eingabe von zwei Zahlen ber den IN-Port mit anschliessender
; Subtraktion der beiden Zahlen -> Carry-Flag Test
Prog1:
  out 128
  in R0        ; von IN-Port die beiden Zahlen in R0 und R1
  out R0
  in R1        ; einlesen
  out R1
  sub R0, R1   ; R0 = R0 - R1
  jc Carry_Set
  out R0
  out 128
  jmp Begin

Carry_Set:
  out R0
  out 64
  jmp Begin
; End Prog1

; Eingabe von zwei Zahlen ber den IN-Port mit, wie bei Prog1,
; anschliessender Subtraktion der beiden Zahlen -> Carry-Flag Test
Prog2:
  out 64
  in R0        ; von IN-Port die beiden Zahlen in R0 und R1
  out R0
  in R1        ; einlesen
  out R1
  sub R0, R1   ; R0 = R0 - R1
  jz Zero_Set
  out R0
  out 128
  jmp Begin

Zero_Set:
  out R0
  out 64
  jmp Begin
; End Prog2

; Testen des Carry-Flags im Bezug auf den ADC oder SBC Befehl
Prog3:
  out 32
  mov R1, 1
  mov R0, 245
  add R0, 30
  adc R1, 1
  out R0
  out R1
  jmp Begin
; End Prog3
  
Ende:
  out 170
  jmp Begin
