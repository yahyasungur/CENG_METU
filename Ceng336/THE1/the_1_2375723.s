PROCESSOR 18F8722
    
#include <xc.inc>

; configurations
CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

; global variable declarations
GLOBAL _t1, _t2, _t3    ; variables for time delay
GLOBAL port_selection, b_state, c_state, d_state, c_led_flag, ra4_flag, re4_flag

; allocating memory for variables
PSECT udata_acs
    port_selection:
        DS 1    ; allocate 1 byte
    b_state:
        DS 1    ; allocate 1 byte
    c_state:
        DS 1    ; allocate 1 byte
    d_state:
        DS 1    ; allocate 1 byte
    _t1:
        DS 1    ; allocate 1 byte
    _t2:
        DS 1    ; allocate 1 byte
    _t3:
        DS 1    ; allocate 1 byte
    c_led_flag:
        DS 1    ; allocate 1 byte
    ra4_flag:
        DS 1    ; allocate 1 byte
    re4_flag:
        DS 1    ; allocate 1 byte

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto    main
    
    
delay_500ms:
    movlw 0x84      ; copy desired value to W
    movwf _t3       ; copy W into t3
    _loop3:
	movlw 0xAF      ; copy desired value to W
        movwf _t2       ; copy W into t2
	_loop2:
	    movlw 0x06      ; copy desired value to W
            movwf _t1       ; copy W into t1
	    _loop1:
		call re4_task
		call ra4_task
		call update_on_d
		decfsz _t1, 1   ; decrement t1, if 0 skip next 
		goto _loop1     ; else keep counting down
		decfsz _t2, 1   ; decrement t2, if 0 skip next 
		goto _loop2     ; else keep counting down
		decfsz _t3, 1   ; decrement t3, if 0 skip next 
		goto _loop3     ; else keep counting down
		return

    
    ;call re4_task
    ;call ra4_task
    ;call update_on_d
    
; 1 second delay implemented as busy-wait
; while executing this procedure, for 1 second,
; your program will not respond to any input.
busy_delay_1sec:
    movlw 0x84      ; copy desired value to W
    movwf _t3       ; copy W into t3
    _loop33:
        movlw 0xAF      ; copy desired value to W
        movwf _t2       ; copy W into t2
        _loop22:
            movlw 0x8F      ; copy desired value to W
            movwf _t1       ; copy W into t1
            _loop11:
                decfsz _t1, 1   ; decrement t1, if 0 skip next 
                goto _loop11     ; else keep counting down
                decfsz _t2, 1   ; decrement t2, if 0 skip next 
                goto _loop22     ; else keep counting down
                decfsz _t3, 1   ; decrement t3, if 0 skip next 
                goto _loop33     ; else keep counting down
                return
		
init:
    
    clrf port_selection ; initially, port_selection is set to 0
    clrf b_state
    clrf c_state
    clrf d_state
    clrf c_led_flag
    clrf ra4_flag
    clrf re4_flag
    
    ; set RA4 as input source, clear PORTA LEDs
    movlw 00010000B     ; move literal written as a binary value to W 
    movwf TRISA         ; move W to TRISA to indicate input/output direction 
                        ; only RA4 pin is input
    clrf  LATA          ; clear output latch so that all LEDs in PORTA is turned off
    
    ; set RE4 as input source, clear PORTA LEDs
    movlw 00010000B     ; move literal written as a binary value to W 
    movwf TRISE         ; move W to TRISA to indicate input/output direction 
                        ; only RA4 pin is input
    clrf  LATE          ; clear output latch so that all LEDs in PORTE is turned off

    ; initialize PORTB as output source
    movlw 0x00          ; move literal written as a hexadecimal value to W
    movwf TRISB         ; move W to TRISB to indicate input/output direction
    clrf LATB
    movlw 00001111B     ; move all 1's to W
    movwf LATB          ; move W to LATB to light RB 0-1-2-3 leds
    
    ; initialize PORTC as output source
    movlw 0x00          ; move literal written as a hexadecimal value to W
    movwf TRISC         ; move W to TRISB to indicate input/output direction
    clrf LATC
    movlw 00000011B     ; move all 1's to W
    movwf LATC          ; move W to LATB to light RB 0-1 leds
    
    ; initialize PORTD as output source
    movlw 0x00          ; move literal written as a hexadecimal value to W
    movwf TRISD         ; move W to TRISB to indicate input/output direction
    clrf LATD
    movlw 0xFF	        ; move all 1's to W
    movwf LATD          ; move W to LATB to light all leds
    
    movlw 0x01
    movwf c_led_flag
    return

default_conf:
    clrf port_selection ; 0..01 for b, 0..10 for c, 0..100 for d
    clrf d_state
    clrf LATD
    
    movlw 00000001B
    movwf LATB
    
    movlw 00000001B
    movwf b_state
    
    movlw 00000001B
    movwf LATC
    
    movlw 00000001B
    movwf c_state
    
    movlw 0x01
    movwf c_led_flag
    return

re4_task:
    btfsc PORTE, 4          ; if ra4 is currently not pressed, return
    goto wait_re4_release   ; if pressed, wait until released
    btfsc re4_flag, 0
    goto check_port_selection
    return
    
    wait_re4_release:
	bsf re4_flag, 0
        btfsc PORTE, 4          ; if ra4 is not released
        return			; wait until it is released (else skip here)
	goto check_port_selection
	return
	
    check_port_selection:
	clrf re4_flag
	movlw 00000100B	   ; if port_selection is on portD
	cpfseq port_selection
	goto increment_port
	return

    increment_port:
	movlw 0x00
	cpfseq port_selection
	goto inc
	movlw 0x01
	movwf port_selection
	return
    
    inc:
	rlncf port_selection
	return
	
ra4_task:
    btfsc PORTA, 4          ; if ra4 is currently not pressed, return
    goto wait_ra4_release   ; if pressed, wait until released
    btfsc ra4_flag, 0
    goto check_port_selection
    return
    
    wait_ra4_release:
	bsf ra4_flag, 0
        btfsc PORTA, 4          ; if ra4 is not released
        return   ; wait until it is released (else skip here)
        goto update_states
	return
	
    update_states:
	clrf ra4_flag
	movlw 0x00
	cpfseq port_selection
	goto update1
	return
	
    update1:
	movlw 00000001B
	cpfseq port_selection
	goto update2
	goto update_on_b
	return
	
    update2:
	movlw 00000010B
	cpfseq port_selection
	return
	goto update_on_c
	return

    update_on_b:
	movlw 00001000B
	cpfseq b_state
	goto increment_b
	movlw 00000001B
	movwf b_state
	return
	
    increment_b:
	rlncf b_state
	return
	
    update_on_c:
	movlw 00000010B
	cpfseq c_state
	goto set_defend
	movlw 00000001B
	movwf c_state
	return

    set_defend:
	rlncf c_state
	return
	
update_on_d:
    movlw 00000100B
    cpfslt port_selection
    return
    goto d_up1
    
    d_up1:
	movlw 00000001B
	cpfseq c_state
	goto d_up2
	movf b_state, 0
	mulwf c_state
	movff PRODL, d_state
	return
	
    d_up2:
	movlw 00000001B
	cpfseq b_state
	goto d_up3
	movlw 00000010B
	movwf d_state
	return
	
    d_up3:
	movlw 00000010B
	cpfseq b_state
	goto d_up4
	movlw 00001000B
	movwf d_state
	return

    d_up4:
	movlw 00000100B
	cpfseq b_state
	goto d_up5
	movlw 00100000B
	movwf d_state
	return

    d_up5:
	movlw 10000000B
	movwf d_state
	return
    
    
update_leds:
    movlw 0000000B
    cpfseq port_selection
    goto up1
    return
    
    up1:
	call update_c_leds
	call update_b_leds
	return

    up2:
	movlw 0000001B
	cpfseq port_selection
	goto update_c_leds
	goto update_b_leds
	return
	
    update_c_leds:
	movlw 0000001B
	cpfseq c_state
	goto defend_mod
	movlw 0000001B
	movwf LATC
	return
    
    defend_mod:
	movlw 0000010B
	movwf LATC
	return
	
    update_b_leds:
	movlw 0000001B
	cpfseq b_state
	goto two_leds
	movlw 0000001B
	movwf LATB
	return
	
    two_leds:
	movlw 0000010B
	cpfseq b_state
	goto three_leds
	movlw 0000011B
	movwf LATB
	return
	
    three_leds:
	movlw 0000100B
	cpfseq b_state
	goto four_leds
	movlw 0000111B
	movwf LATB
	return
	
    four_leds:
	movlw 0001111B
	movwf LATB
	return
	
blink:
    movlw 0000000B
    cpfseq port_selection
    goto upp1
    return
    
    upp1:
	movlw 0000100B
	cpfseq port_selection
	goto upp2
	goto countdown
	return

    upp2:
	movlw 0000001B
	cpfseq port_selection
	goto blink_c
	goto blink_b
	return
	
    countdown:
	call update_d_leds
	bcf d_state, 0
	rrncf d_state
	return

    blink_c:
	movlw 0x00          
	cpfseq c_led_flag
	goto turn_off_c
	goto turn_on_c
	return

    turn_on_c:
	movlw 0x01
	movwf c_led_flag
	goto update_leds
	return

    turn_off_c:
	clrf c_led_flag
	clrf LATC
	return
	
    blink_b:
	btfsc LATB, 0
	goto turn_off_b
	goto turn_on_b
	return
	
    turn_on_b:
	goto update_leds
	return
	
    turn_off_b:
	clrf LATB
	return
	
update_d_leds:
    movlw 00000100B
    cpfseq port_selection
    return    
    movlw 0x00
    cpfseq d_state
    goto one
    clrf LATD
    return
    
    one:
	movlw 00000001B
	cpfseq d_state
	goto two
	movlw 00000001B
	movwf LATD
	return
    
    two:
	movlw 00000010B
	cpfseq d_state
	goto three
	movlw 00000011B
	movwf LATD
	return
	
    three:
	movlw 00000100B
	cpfseq d_state
	goto four
	movlw 00000111B
	movwf LATD
	return    
    
    four:
	movlw 00001000B
	cpfseq d_state
	goto five
	movlw 00001111B
	movwf LATD
	return    
    
    five:
	movlw 00010000B
	cpfseq d_state
	goto six
	movlw 00011111B
	movwf LATD
	return    
    
    six:
	movlw 00100000B
	cpfseq d_state
	goto seven
	movlw 00111111B
	movwf LATD
	return    
    
    seven:
	movlw 01000000B
	cpfseq d_state
	goto eight
	movlw 01111111B
	movwf LATD
	return
    
    eight:
	movlw 11111111B
	movwf LATD
	return
	
	
; DO NOT DELETE OR MODIFY
; 500ms pass check for test scripts
ms500_passed:
    nop
    return

; DO NOT DELETE OR MODIFY
; 1sec pass check for test scripts
ms1000_passed:
    nop
    return
    
	
PSECT CODE
main:
    ; some code to initialize and wait 1000ms here, maybe
    call init
    call busy_delay_1sec
    call default_conf
    call ms1000_passed
    ; a loop here, maybe
    loop:
	call delay_500ms
	movlw 0x00
	cpfsgt d_state
	call default_conf
	call blink
        ; inside the loop, once it is confirmed 500ms passed
        call ms500_passed
        goto loop

end resetVec