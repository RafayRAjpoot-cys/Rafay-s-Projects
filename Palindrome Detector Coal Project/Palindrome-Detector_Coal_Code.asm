; ==============================================================================
; PROJECT: PALINDROME DETECTOR
; MEMBERS: Abdul Rafay (243705), Abdullah Rafay (243619)    
; Instroctor: Engr Anum Aftab.
; ==============================================================================  


.MODEL SMALL                                                                      
.STACK 100H

.DATA
    BANNER      DB  0Dh,0Ah,'=== PALINDROME CHECKER ===',0Dh,0Ah,'$'
    PROMPT      DB  0Dh,0Ah,'Input string (or "EXIT"): > $'
    MSG_CLEAN   DB  0Dh,0Ah,'[Analysis]: Processing: $'
    MSG_YES     DB  0Dh,0Ah,'[Result]  : YES! Palindrome.',0Dh,0Ah,'$'
    MSG_NO      DB  0Dh,0Ah,'[Result]  : NO. Not a palindrome.',0Dh,0Ah,'$'
    MSG_POS     DB  0Dh,0Ah,'[Mismatch]: Position: $'
    MSG_CHAR    DB  0Dh,0Ah,'[Mismatch]: Char: $'
    MSG_DIFF    DB  ' != $'
    MSG_EXIT    DB  0Dh,0Ah,'Exiting... Goodbye!',0Dh,0Ah,'$'
    MSG_ERR     DB  0Dh,0Ah,'[Error]   : Empty Input.',0Dh,0Ah,'$'
    BAR         DB  0Dh,0Ah,'--------------------------',0Dh,0Ah,'$'

    INPUT       DB  81, ?, 81 DUP('$') 
    CLEAN_STR   DB  81 DUP('$') 
    EXIT_KEY    DB  'EXIT'
    LEN         DW  0

.CODE

P_STR MACRO MSG
    LEA DX, MSG
    MOV AH, 09H
    INT 21H
ENDM

P_CHAR MACRO CHAR
    MOV DL, CHAR
    MOV AH, 02H
    INT 21H
ENDM

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    MOV ES, AX              

    P_STR BANNER

MAIN_LOOP:
    P_STR PROMPT
    LEA DX, INPUT
    MOV AH, 0AH
    INT 21H
    
    MOV AL, [INPUT+1]
    OR  AL, AL
    JZ  ERR_EMPTY

    CALL TO_UPPER
    CALL CHECK_EXIT
    CALL SANITIZE
    
    CMP LEN, 0
    JE  ERR_EMPTY
             
    P_STR MSG_CLEAN
    P_STR CLEAN_STR
             
    CALL COMPARE
    
    P_STR BAR
    JMP MAIN_LOOP

ERR_EMPTY:
    P_STR MSG_ERR
    P_STR BAR
    JMP MAIN_LOOP

DO_EXIT:
    P_STR MSG_EXIT
    MOV AH, 4CH
    INT 21H
MAIN ENDP

TO_UPPER PROC
    PUSH CX
    PUSH SI
    XOR CH, CH
    MOV CL, [INPUT+1]
    LEA SI, INPUT+2
UP_L:
    MOV AL, [SI]
    CMP AL, 'a'
    JB  NEXT_U
    CMP AL, 'z'
    JA  NEXT_U
    SUB [SI], 32
NEXT_U:
    INC SI
    LOOP UP_L
    POP SI
    POP CX
    RET
TO_UPPER ENDP

CHECK_EXIT PROC
    PUSH CX
    PUSH SI
    PUSH DI
    MOV CL, [INPUT+1]
    CMP CL, 4
    JNE NO_EXIT
    LEA SI, INPUT+2
    LEA DI, EXIT_KEY
    CLD
    MOV CX, 4
    REPE CMPSB
    JE  DO_EXIT             
NO_EXIT:
    POP DI
    POP SI
    POP CX
    RET
CHECK_EXIT ENDP

SANITIZE PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH SI
    PUSH DI
    XOR CH, CH
    MOV CL, [INPUT+1]
    LEA SI, INPUT+2
    LEA DI, CLEAN_STR
    XOR BX, BX
FILT_L:
    MOV AL, [SI]
    CMP AL, '0'
    JB  CHK_A
    CMP AL, '9'
    JBE SAVE
CHK_A:
    CMP AL, 'A'
    JB  SKIP
    CMP AL, 'Z'
    JA  SKIP
SAVE:
    STOSB
    INC BX
SKIP:
    INC SI
    LOOP FILT_L
    MOV BYTE PTR [DI], '$'
    MOV LEN, BX
    POP DI
    POP SI
    POP CX
    POP BX
    POP AX
    RET
SANITIZE ENDP

COMPARE PROC
    PUSH AX
    PUSH BX
    PUSH SI
    PUSH DI

    LEA SI, CLEAN_STR       
    LEA DI, CLEAN_STR
    ADD DI, LEN
    DEC DI

CHECK_LOOP:
    CMP SI, DI
    JAE IS_PAL

    MOV AL, [SI]
    MOV BL, [DI]
    CMP AL, BL
    JNE MISMATCH

    INC SI
    DEC DI
    JMP CHECK_LOOP

IS_PAL:
    P_STR MSG_YES
    JMP DONE_CMP

MISMATCH:
    MOV AX, SI
    LEA BX, CLEAN_STR
    SUB AX, BX
    INC AX
    
    PUSH AX
    P_STR MSG_POS
    POP AX
    CALL P_NUM
    
    P_STR MSG_CHAR
    P_CHAR [SI]
    P_STR MSG_DIFF
    P_CHAR [DI]
    P_STR MSG_NO

DONE_CMP:
    POP DI
    POP SI
    POP BX
    POP AX
    RET
COMPARE ENDP

P_NUM PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    XOR CX, CX
    MOV BX, 10
DIV_L:
    XOR DX, DX
    DIV BX
    PUSH DX
    INC CX
    OR  AX, AX
    JNZ DIV_L
PRN_L:
    POP DX
    ADD DL, '0'
    MOV AH, 02H
    INT 21H
    LOOP PRN_L
    POP DX
    POP CX
    POP BX
    POP AX
    RET
P_NUM ENDP

END MAIN