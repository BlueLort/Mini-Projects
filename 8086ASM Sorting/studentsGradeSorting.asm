include 'emu8086.inc'
               org 100h
               jmp start
;------------------------------------------------------------- 
;-------------------------------------------------------------
stringTemp     db 100,?, 100 dup(' ')  
const_ten      dw 0Ah
tempMem        dw 1
readNumIntoDX  proc near 
               push ax
               push bx
               push cx
               lea ax,stringTemp
               mov dx,ax
               mov ah, 0ah 
               int 21h
               mov ah, 2
	           mov dl, 10 ;print newline
	           int 21h 
	           mov dl, 13 ;return to start of line
	           int 21h
               mov cl,stringTemp[1];n bytes were read  
               mov dx,0 ;dx has the out
reDo:  
               mov ax,0 ;reset ax , bx
               mov bx,0
               mov bl,stringTemp[1];
               sub bl,cl
               add bl,2             
               mov al,stringTemp[bx]   
               sub al,48;0 is 48 in ascii
               mov bh,cl
               sub bh,1
               cmp bh,0 
               mov tempMem,dx
               jle doneGetNum  
                
reMul:         mul const_ten
               sub bh,1
               cmp bh,0
               jg  reMul 
doneGetNum:   
               mov dx,tempMem
               add dx,ax  
               loop reDo 
               pop cx
               pop bx
               pop ax
               ret
readNumIntoDX  endp 
;-------------------------------------------------------------
;-------------------------------------------------------------

studentsNum    dw 25,?,25 dup(0000h)  
studentsGrade  dw 25,?,25 dup(0000h) 
const_N        dw 25 ;number of students -> should be 25
const_two      db 2
start:        
               mov  cx,const_N    ;25 is number of students
readStudents:   
               lea  ax,msg1 
               mov  si,ax 
               call PRINT_STRING
               call readNumIntoDX 
               mov  bx,const_N
               sub  bx,cx
               mov  ax,bx
               mul  const_two
               mov  bx,ax
               mov  studentsNum[bx],dx
               lea  ax,msg2 
               mov  si,ax 
               call PRINT_STRING     
               call readNumIntoDX
               mov  bx,const_N
               sub  bx,cx 
               mov  ax,bx
               mul  const_two
               mov  bx,ax
               mov  studentsGrade[bx],dx    
               PUTC  0dh
               PUTC  0ah 
               loop readStudents     
               jmp  bubbleSort  
;-------------------------------------------------------------
;-------------------------------------------------------------               
iteOuter       dw 1
iteInner       dw 1
maxOuter       dw 1
maxInner       dw 1 
bubbleSort:    
               mov iteOuter,0
               mov ax,const_N
               sub ax,1
               mov maxOuter,ax
outerLoop:                       
               mov iteInner,0
               mov ax,const_N
               sub ax,iteOuter
               sub ax,1
               mov maxInner,ax
innerLoop:     
               mov ax,iteInner
               mul const_two 
               mov si,ax             
               mov bx,studentsGrade[si]
               add si,2
               mov dx,studentsGrade[si] 
               cmp bx,dx
               jg  finishInner 
               ;swap grades                  
               mov studentsGrade[si],bx  
               sub si,2  
               mov studentsGrade[si],dx 
               
               ;swap numbers              
               mov bx,studentsNum[si]
               add si,2
               mov dx,studentsNum[si]
               mov studentsNum[si],bx  
               sub si,2  
               mov studentsNum[si],dx 
finishInner:               
               mov ax,iteInner
               add ax,1
               mov iteInner,ax 
               cmp ax,maxInner
               jge  finishOuter

               jmp innerLoop
finishOuter:               
               mov ax,iteOuter
               add ax,1
               mov iteOuter,ax
               cmp ax,maxOuter 
               jge  doneSorting

               jmp outerLoop
doneSorting:   
               PRINT 'Student Grade - '
               PRINTN 'Student Number'
               mov cx,const_N 
printTables:  
               mov bx,const_N
               sub bx,cx
               mov ax,bx
               mov dl,2
               mul dl
               mov bx,ax
               mov ax,studentsGrade[bx]
               call PRINT_NUM_UNS
               PRINT ' - '
               mov ax,studentsNum[bx] 
               call PRINT_NUM_UNS
               PUTC  0dh
               PUTC  0ah 
               loop printTables   
               
               ret                    
msg1           db 'Enter Student Number:',0
msg2           db 'Enter Student Grade:',0  
DEFINE_PRINT_STRING                 
DEFINE_PRINT_NUM_UNS 
              END