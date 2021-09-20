.model small
.stack 100h
.code
start:
  mov ax, @data
  mov ds, ax

  ;Let{
  XOR BX, BX
  PUSH BX
  ;get numeric
  MOV AX, 4
  PUSH AX
  ;
  POP AX
  POP BX
  MOV c[BX], AX
  ;}
  XOR DI, DI
  XOR SI, SI
@M1:
  MOV AL, @L0[SI]
  CMP AL, '$'
  JZ @M2
  MOV buffer_write[DI], AL
  INC SI
  INC DI
  JMP @M1
@M2:
  XOR SI, SI
@M3:
  MOV AL, @L1[SI]
  CMP AL, '$'
  JZ @M4
  MOV buffer_write[DI], AL
  INC SI
  INC DI
  JMP @M3
@M4:
  XOR SI, SI
@M5:
  MOV AL, @L2[SI]
  CMP AL, '$'
  JZ @M6
  MOV buffer_write[DI], AL
  INC SI
  INC DI
  JMP @M5
@M6:
  ;get ident{
  XOR BX, BX
  MOV AX, c[BX]
  PUSH AX
  ;}
  CALL write_chislo
  MOV buffer_write[di],'$'
  MOV DX, offset buffer_write
  MOV AH, 9
  INT 21h
  MOV DX, offset crlf
  MOV AH, 9
  INT 21h
  ;Let{
  XOR BX, BX
  PUSH BX
  ;get ident{
  XOR BX, BX
  MOV AX, c[BX]
  PUSH AX
  ;}
  ;get numeric
  MOV AX, 1
  PUSH AX
  ;sub
  POP BX
  POP AX
  SUB AX, BX
  PUSH AX
  ;
  POP AX
  POP BX
  MOV c[BX], AX
  ;}
  XOR DI, DI
  XOR SI, SI
@M7:
  MOV AL, @L0[SI]
  CMP AL, '$'
  JZ @M8
  MOV buffer_write[DI], AL
  INC SI
  INC DI
  JMP @M7
@M8:
  XOR SI, SI
@M9:
  MOV AL, @L1[SI]
  CMP AL, '$'
  JZ @M10
  MOV buffer_write[DI], AL
  INC SI
  INC DI
  JMP @M9
@M10:
  XOR SI, SI
@M11:
  MOV AL, @L2[SI]
  CMP AL, '$'
  JZ @M12
  MOV buffer_write[DI], AL
  INC SI
  INC DI
  JMP @M11
@M12:
  ;get ident{
  XOR BX, BX
  MOV AX, c[BX]
  PUSH AX
  ;}
  CALL write_chislo
  MOV buffer_write[di],'$'
  MOV DX, offset buffer_write
  MOV AH, 9
  INT 21h
  MOV DX, offset crlf
  MOV AH, 9
  INT 21h

Exit:
  mov ah, 4Ch
  int 21h
read_chislo proc 
  xor ax, ax
  mov cl, blength
  xor ch, ch
  xor bx, bx
  mov si, cx
  mov cl, 10
Read1:
  cmp di, si
  ;if error
  ja End1
  mov bl, byte ptr bcontents[di]
  inc di
  sub bl, '0'
  jb Read1
  cmp bl, 9
  ja Read1
Read2:
  mul cx
  add ax, bx
  mov bl, byte ptr bcontents[di]
  sub bl, '0'
  jb End1
  cmp bl, 9
  ja End1
  inc di
  jmp Read2
End1:
  ret
read_chislo endp
write_chislo proc 
  mov cx, 10000
  xor bp, bp
Loop1 :
  xor dx, dx
  div cx
  ; проверка на первые нули
  cmp ax, 0
  jnz WriteInBuf
  cmp bp, 0
  jnz WriteInBuf
  jmp Div10
WriteInBuf :
  mov bp, 1; взводим флаг
  add ax, '0'
  mov byte ptr buffer_write[di], al
  inc di
Div10 :
  cmp cx, 1
  jz ifZero
  mov ax, cx
  mov cx, dx
  xor dx, dx
  mov bx, 10
  div bx
  mov bx, ax
  mov ax, cx
  mov cx, bx
  jmp Loop1
ifZero :
  cmp di, 0
  jnz End2
  mov byte ptr buffer_write[di], '0'
  inc di;
End2:
  ret
write_chislo endp
.data
  b   DB     (?)
  a   DW   4   DUP  (?)
  c   DW     (?)
  r   DB     (?)
  @L0   DB "c$"
  @L1   DB " $"
  @L2   DB "= $"
  crlf db 0Dh, 0Ah, '$'
  buffer_write db 20 dup (?),'$'
  buffer db 20
  blength db ?
  bcontents db 20 dup (?)
end start
