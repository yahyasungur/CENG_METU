#include <stdio.h>
#include <math.h>

/* Currency exchange table */
double tl_to_usd = 0.131;
double tl_to_eur = 0.11;
double usd_to_tl = 7.6;
double usd_to_eur = 0.85;
double eur_to_tl = 9.02;
double eur_to_usd = 1.18;

int main() {
    
    char op_type,op1,op2;
	long double balance = 0,u_balance = 0,e_balance = 0, amount,temp,experience,debt,score;
    int i;

    scanf("%Lf %c",&balance,&op_type);

        for ( i = 0; op_type != 'Q' ; i++){
        if(i != 0){
            scanf(" %c",&op_type);
        }
        switch (op_type){
  
        case 'W':
            scanf(" %Lf",&amount);
            if(amount <= 0){
                printf("ERROR: Invalid amount\n");
            }
            else if(amount > balance){
                printf("ERROR: Insufficient funds\n");
            }
            else{
                balance -=amount;
                printf("OK\n");
            }
            break;
        
        case 'D':
            scanf(" %Lf",&amount);
            if(amount <= 0){
                printf("ERROR: Invalid amount\n");
            }
            else{
                balance +=amount;
                printf("OK\n");
            }
            break;
        
        case 'I':
            printf("Current balance: %.2Lf\n",balance);
            break;

        case 'X':
            scanf(" %c %Lf %c",&op1,&amount,&op2);
            
                
            
            
                if (op1 == 'T' && op2 == 'U'){
                    if(amount <= 0){
                        printf("ERROR: Invalid amount\n");
                    }
                    else if((amount*usd_to_tl) > balance){
                        printf("ERROR: Insufficient funds\n");
                    }
                    else{
                        printf("Before exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                        balance -=(usd_to_tl*amount);
                        u_balance += amount; 
                        printf("After exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                    }
                    
                }
                else if (op1 == 'T' && op2 == 'E'){
                    if(amount <= 0){
                        printf("ERROR: Invalid amount\n");
                    }
                    else if((amount*eur_to_tl) > balance){
                        printf("ERROR: Insufficient funds\n");
                    }
                    else{
                        printf("Before exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                        balance -=(eur_to_tl*amount);
                        e_balance += amount; 
                        printf("After exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                    }
                    
                }
                else if (op1 == 'U' && op2 == 'T'){
                    if(amount <= 0){
                        printf("ERROR: Invalid amount\n");
                    }
                    else if((amount*tl_to_usd) > u_balance){
                        printf("ERROR: Insufficient funds\n");
                    }
                    else{
                        printf("Before exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                        u_balance -=(tl_to_usd*amount);
                        balance += amount; 
                        printf("After exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                    }
                    
                }
                else if (op1 == 'U' && op2 == 'E'){
                    if(amount <= 0){
                        printf("ERROR: Invalid amount\n");
                    }
                    else if((amount*eur_to_usd) > u_balance){
                        printf("ERROR: Insufficient funds\n");
                    }
                    else{
                        printf("Before exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                        u_balance -=(eur_to_usd*amount);
                        e_balance += amount; 
                        printf("After exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                    }
                }
                else if (op1 == 'E' && op2 == 'T'){
                    if(amount <= 0){
                        printf("ERROR: Invalid amount\n");
                    }
                    else if((amount*tl_to_eur) > e_balance){
                        printf("ERROR: Insufficient funds\n");
                    }
                    else{
                        printf("Before exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                        e_balance -=(tl_to_eur*amount);
                        balance += amount; 
                        printf("After exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                    }
                    
                }
                else if (op1 == 'E' && op2 == 'U'){
                    if(amount <= 0){
                        printf("ERROR: Invalid amount\n");
                    }
                    else if((amount*usd_to_eur) > e_balance){
                        printf("ERROR: Insufficient funds\n");
                    }
                    else{
                        printf("Before exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                        e_balance -=(usd_to_eur*amount);
                        u_balance += amount; 
                        printf("After exchange: %.2Lf TL | %.2Lf USD | %.2Lf EUR\n",balance,u_balance,e_balance);
                    }                  
                }
                else
                {
                    printf("ERROR: Operation is not supported\n");
                }
                
            
            


            break;

        case 'C':

            scanf(" %Lf %Lf",&experience,&debt);
            temp = balance + u_balance*usd_to_tl + e_balance*eur_to_tl;
            score = ((temp*0.001)*experience)/(debt*0.02);
            if(experience < 0 || debt < 0){
                printf("ERROR: Invalid amount");
            }
            else
            {
                if (score <2)
                {
                    printf("Very Poor: %.2Lf\n",score);
                }
                else if (2 <= score && score < 25)
                {
                    printf("Poor: %.2Lf\n",score);               
                }
                else if (25 <= score && score  < 50)
                {
                    printf("Fair: %.2Lf\n",score);               
                }
                else if (50 <= score && score < 100)
                {
                    printf("Good: %.2Lf\n",score);               
                }
                else if (score >= 100)
                {
                    printf("Excellent: %.2Lf\n",score);                
                }

                break;
            }

        case 'Q':
            break;

        default:
            printf("ERROR: Operation is not supported\n");
            break;
        }
    }
    printf("END\n");

	return 0;
}
