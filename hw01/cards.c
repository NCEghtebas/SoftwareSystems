/*
 * Program to evaluate face values.
 * HFC ch. 1
 * 1-26-13 
 */

 #include <stdio.h>
 #include <stdlib.h>


/*First fucntion out of five
 *returns val based on user input*/
int get_value(int val ,char card_name[]){
	switch (card_name[0]){
	case 'K':
	case 'Q':
	case 'J':	
		val=10;
		break;
	case 'A':
		val =11;
		break;
	case 'X':
		return 0;
	default:
		val = atoi(card_name);
		if ((val < 1) || (val>10) ){
			puts("I don't understand that value!");
		}
	}
	return val;
}


/*Second fucntion out of five
 *Checks to see if val is within bounds*/
int value_checker(int val, int count){
		/*Check uf the value is 3 to 6*/
	if (val >2 && val<7){
		count++;
	}else if(val ==10){ 
		count--;
	}
	return count;
}

/*Third functin out of five
 *Displays the current count*/
void current_count(int count){
	printf("Current count: %i \n", count);
}

/*Fourth function out of five
 *Evaluates face values of card */
void black_jack(int val, char card_name[], int count){
	while (card_name[0] != 'X'){
		puts("Enter the card_name: ");
		scanf("%2s", card_name);
		val= get_value(val, card_name);
		count= value_checker(val, count);
		current_count(count);
	}
}

/*Fifth function out of five 
 *good ol main function*/
int main(){
	char card_name[3];	
	int count =0;
	int val = 0;
	black_jack(val, card_name, count);
	return 0;
}
