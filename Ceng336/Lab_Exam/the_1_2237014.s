PROCESSOR 18F8722
    
#include <xc.inc>

; configurations
CONFIG OSC = HSPLL, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF, MCLRE = ON, LPT1OSC = OFF, LVP = OFF, XINST = OFF, DEBUG = OFF

; global variable declarations
GLOBAL var1
GLOBAL var2
GLOBAL var3
GLOBAL ra4_count
GLOBAL re4_count
GLOBAL port
GLOBAL level
GLOBAL action
GLOBAL countdown
    
; allocating memory for variables
PSECT udata_acs
    var1:
	DS     1    ; allocates 1 byte
    var2:
	DS     1 
    var3:
	DS     1
    level:
	DS     1
    port:
	DS     1
    action:
	DS     1
    countdown:
	DS     1
    ra4_count:
	DS     1
    re4_count:
	DS     1

PSECT resetVec,class=CODE,reloc=2
resetVec:
    goto    main

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
    
delay_500msB:
	movlw 0x2F
	movwf var1
	l11:
	    movlw 0x59
	    movwf var2
	    l22:
		movlw 0x51
		movwf var3
		l33:
		    re4_count_check:
			movlw 0x01
			cpfslt re4_count
			goto check_re4_release
		    check_re4_press: 
			btfss PORTE, 4
			goto sub_checkB
			movff port, re4_count
		    check_re4_release:
			btfsc PORTE, 4
			goto sub_checkB
			clrf re4_count
			goto portC_blink
		    sub_checkB:
			movlw 0x01
			cpfslt ra4_count
			goto check_ra4_release
		    check_ra4_press:
			btfss PORTA, 4
			goto wait
			movff port, ra4_count	    	    
		    check_ra4_release:			
			btfsc PORTA, 4
			goto wait
			clrf ra4_count
		    level_updateB:
			movf level, 0
			addwf level
			incf level
			movlw 0x10
			cpfslt level	    
			movff port, level
			movff level, LATB			
		    wait:			    
			decfsz var3, F
			goto l33
			decfsz var2, F
			goto l22
			decfsz var1, F
			goto l11
	return
	
delay_500msB2:
	movlw 0x2F
	movwf var1
	l1B2:
	    movlw 0x59
	    movwf var2
	    l2B2:
		movlw 0x51
		movwf var3
		l3B2:
		    re4_count_checkB2:
			movlw 0x01
			cpfslt re4_count
			goto check_re4_releaseB2
		    check_re4_pressB2: 
			btfss PORTE, 4
			goto sub_checkB2
			movff port, re4_count
		    check_re4_releaseB2:
			btfsc PORTE, 4
			goto sub_checkB2
			clrf re4_count
			goto portC_blink
		    sub_checkB2:
			movlw 0x01
			cpfslt ra4_count
			goto check_ra4_releaseB2
		    check_ra4_pressB2:
			btfss PORTA, 4
			goto waitB2
			movff port, ra4_count		
		    check_ra4_releaseB2:			
			btfsc PORTA, 4
			goto waitB2
			clrf ra4_count
			movf level, 0
			addwf level
			incf level
			movlw 0x10
			cpfslt level	    
			movff port, level
		    waitB2:			    
			decfsz var3, F
			goto l3B2
			decfsz var2, F
			goto l2B2
			decfsz var1, F
			goto l1B2
	return
	
delay_500msC:
	movlw 0x2F
	movwf var1
	l1C:
	    movlw 0x59
	    movwf var2
	    l2C:
		movlw 0x51
		movwf var3
		l3C:
		    re4_count_checkC:
			movlw 0x01
			cpfslt re4_count
			goto check_re4_releaseC
		    check_re4_pressC: 
			btfss PORTE, 4
			goto sub_checkC
			movff port, re4_count
		    check_re4_releaseC:
			btfsc PORTE, 4
			goto sub_checkC
			clrf re4_count
			goto portD_case
		    sub_checkC:
			movlw 0x01
			cpfslt ra4_count
			goto check_ra4_releaseC
		    check_ra4_pressC:
			btfss PORTA, 4
			goto waitC
			movff port, ra4_count
		    check_ra4_releaseC:					
			btfsc PORTA, 4
			goto waitC
			clrf ra4_count
			incf action
			movlw 0x03
			cpfslt action	    
			movff port, action
			movff action, LATC
			
		    waitC:			    
			decfsz var3, F
			goto l3C
			decfsz var2, F
			goto l2C
			decfsz var1, F
			goto l1C
	return

delay_500msC2:
	movlw 0x2F
	movwf var1
	l1C2:
	    movlw 0x59
	    movwf var2
	    l2C2:
		movlw 0x51
		movwf var3
		l3C2:
		    re4_count_checkC2:
			movlw 0x01
			cpfslt re4_count
			goto check_re4_releaseC2
		    check_re4_pressC2: 
			btfss PORTE, 4
			goto sub_checkC2
			movff port, re4_count
		    check_re4_releaseC2:
			btfsc PORTE, 4
			goto sub_checkC2
			clrf re4_count
			goto portD_case
		    sub_checkC2:
			movlw 0x01
			cpfslt ra4_count
			goto check_ra4_releaseC2
		    check_ra4_pressC2:
			btfss PORTA, 4
			goto waitC2
			movff port, ra4_count
		    check_ra4_releaseC2:					
			btfsc PORTA, 4
			goto waitC2
			clrf ra4_count
			incf action
			movlw 0x03
			cpfslt action	    
			movff port, action
			
		    waitC2:			    
			decfsz var3, F
			goto l3C2
			decfsz var2, F
			goto l2C2
			decfsz var1, F
			goto l1C2
	return
	
delay_500msD:
	movlw 0x9F
	movwf var1
	l1D:
	    movlw 0x59
	    movwf var2
	    l2D:
		movlw 0x71
		movwf var3
		l3D:		    	
		    waitD:			    
			decfsz var3, F
			goto l3D
			decfsz var2, F
			goto l2D
			decfsz var1, F
			goto l1D
	return
	
PSECT CODE
	
main:
    ; some code to initialize and wait 1000ms here, maybe
    ms1000:
	LED_configs:
	    movlw 0b00010000
	    movwf TRISA
	    movlw 0b00010000
	    movwf TRISE
	    movlw 0x00
	    movwf TRISB
	    movwf TRISC
	    movwf TRISD
	turn_on_LEDs:
	    movlw 0b00001111
	    movwf LATB
	    movlw 0b00000011
	    movwf LATC
	    movlw 0b11111111
	    movwf LATD
	delay: 
	    movlw 0xBE
	    movwf var1
	    l1:
		movlw 0xB2
		movwf var2
		l2:
		    movlw 0x61
		    movwf var3
		    l3:
			decfsz var3, F
			goto l3
			decfsz var2, F
			goto l2
			decfsz var1, F
			goto l1
	    
	turn_off_LEDs:
	    movlw 0x01
	    movwf LATB
	    movlw 0x01
	    movwf LATC
	    clrf LATD
	
	
    call ms1000_passed
    ; a loop here, maybe
    
			
    loop:
	movlw 0x01
	movwf LATB
        movlw 0x01
	movwf LATC
        clrf LATD
	movlw 0x01
	movwf level
	movlw 0x01
	movwf action
	movlw 0x01
	movwf port
	clrf var1
	clrf var2
	clrf var3
	clrf countdown
	clrf ra4_count
	clrf re4_count
	
	default:
	movlw 0x2F
	movwf var1
	l1W:
	    movlw 0x59
	    movwf var2
	    l2W:
		movlw 0x66
		movwf var3
		l3W:
		    re4_count_default:
			movlw 0x01
			cpfslt re4_count
			goto re4_release
		    re4_press:
			btfss PORTE, 4
			goto waitW
			movff port, re4_count
		    re4_release:
			btfsc PORTE, 4
			goto waitW
			clrf re4_count
			goto portB_blink
		    waitW:			    
			decfsz var3, F
			goto l3W
			decfsz var2, F
			goto l2W
			decfsz var1, F
			goto l1W
			
	call ms500_passed		
	goto default
	
	portB_blink:
	    movlw 0x10
	    cpfslt level	    
	    movff port, level
	    movff level, LATB
	    call delay_500msB
	    call ms500_passed	    	    
	    movlw 0x00
	    movwf LATB
	    clrf var1
	    clrf var2
	    clrf var3
	    call delay_500msB2
	    call ms500_passed	    
	    goto portB_blink
	  
	clrf var1
	clrf var2
	clrf var3
	clrf ra4_count
	clrf re4_count
			    		    		   		    
	portC_blink:
	    movff level, LATB
	    movff action, LATC
	    call delay_500msC
	    call ms500_passed
	    movlw 0x00
	    movwf LATC
	    clrf var1
	    clrf var2
	    clrf var3
	    call delay_500msC2
	    call ms500_passed	    
	    goto portC_blink
	    
	clrf var1
	clrf var2
	clrf var3
    
	portD_case:
	    movff action, LATC
	    movlw 0x02
	    cpfslt action
	    goto defend
	    goto attack
	    
	attack:
	    movlw 0x07
	    cpfsgt level
	    goto c1
	    _4leds:
		movff level, LATD
		call delay_500msD
		call ms500_passed
		movlw 0x08
		subwf level, 1
	    c1:
		movlw 0x03
		cpfsgt level
		goto c2
	    
	 
	    _3leds:
		movff level, LATD
		call delay_500msD
		call ms500_passed
		movlw 0x04
		subwf level, 1
		
	    c2:
		movlw 0x01
		cpfsgt level
		goto _1led

	    _2leds:
		movff level, LATD
		call delay_500msD
		call ms500_passed
		movlw 0x02
		subwf level, 1

	    _1led:
		movff level, LATD
		call delay_500msD
		call ms500_passed
	    movlw 0x00
	    movwf LATD
	    call delay_500msD
	    call ms500_passed
	    goto loop
	defend:
	    movlw 0x07
	    cpfsgt level
	    goto c11
	    _8ledsD:
		movlw 0b11111111
		movwf LATD
		call delay_500msD
		call ms500_passed
		movlw 0x08
		subwf level, 1
	    _7ledsD:
		movlw 0b01111111
		movwf LATD
		call delay_500msD
		call ms500_passed
		
	    c11:
		movlw 0x03
		cpfsgt level
		goto c22
	    
	    _6ledsD:
		movlw 0b00111111
		movwf LATD
		call delay_500msD
		call ms500_passed
		movlw 0x04
		subwf level, 1
	    _5ledsD:
		movlw 0b00011111
		movwf LATD
		call delay_500msD
		call ms500_passed	
		
	    c22:
		movlw 0x01
		cpfsgt level
		goto _2ledsD
		
	    
	    _4ledsD:
		movlw 0b00001111
		movwf LATD
		call delay_500msD
		call ms500_passed
		movlw 0x02
		subwf level, 1
	    _3ledsD:
		movlw 0b00000111
		movwf LATD
		call delay_500msD
		call ms500_passed

	    _2ledsD:
		movlw 0b00000011
		movwf LATD
		call delay_500msD
		call ms500_passed
	    _1ledD:
		movlw 0b00000001
		movwf LATD
		call delay_500msD
		call ms500_passed
	    movlw 0x00
	    movwf LATD
	    call delay_500msD
	    call ms500_passed
	    goto loop
	    	    

end resetVec


