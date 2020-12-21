#include <stdio.h>
#include <math.h>


int main() {

	char op_type;
	long double balance, amount;
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

        case 'Q':
            break;

        default:
            printf("ERROR: Operation is not supported\n");
            break;
        }
    }
    printf("END");

	return 0;
}