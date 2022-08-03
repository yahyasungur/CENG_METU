PROCESSOR 18F8722
    
#include <xc.inc>

CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF
    

PSECT resetVec,class=CODE,reloc=2
resetVec: 
    goto    main



PSECT utils, reloc=2

    
; CODE segment to hold task implementations
PSECT tasks,reloc=2

init:
    CLRF PORTD
    CLRF LATD
    CLRF PORTC
    CLRF LATC
    CLRF PORTE
    CLRF LATE
    CLRF PORTA
    CLRF LATA
    
    MOVLW 11111111B
    MOVWF ADCON1
    
    MOVLW 11111111B
    MOVWF TRISC
    MOVLW 11111111B
    MOVWF TRISD
    MOVLW 00000100B
    MOVWF TRISA
    MOVLW 00000000B
    MOVWF TRISE
    
    return

check_ra5_pressed:
    BTFSS PORTA, 5
    return
    ;ra5 is pressed
    call ra5_pressed
    
    MOVLW 00000000B
    CPFSEQ PORTE
    GOTO addition
    return
    
    addition:
	MOVF PORTD
	ADDWF PORTC, 0
	MOVWF PORTE

	BTFSS STATUS, 0
	return
	; with cary
	BSF PORTA, 0
	
	return
    
    return

check_ra5_released:
    BTFSC PORTA, 5
    return ;not released
    CLRF PORTE
    BCF PORTA, 0
    CALL loop
    return

init_complete:
    return
    
loop:
    return
    
ra5_pressed:
    return
    
job_done:
    return


; CODE segment to hold the main routine
; You need to use init_complete, ra5_pressed and  job_done labels
PSECT main,reloc=2
main:
    CALL init
    CALL init_complete
    CALL loop
    
    main_loop:
	call check_ra5_pressed
	BTFSC PORTA, 5
	call job_done
	call check_ra5_released
	goto main_loop

END resetVec

