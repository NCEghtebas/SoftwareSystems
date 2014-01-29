/*
 * Program to evaluate face values.
 * HFC ch. 1
 * 1-26-13 
 */

 #include <stdio.h>
 #include <stdlib.h>

/*First fucntion out of three
 *Checks to see if val is within bounds*/
int ValueChecker(int val, int count){
		/*Check uf the value is 3 to 6*/
	if (val >2 && val<7){
		count++;
	}else if(val ==10){ 
		count--;
	}
	return val;
}

/*Second functin out of three
 *Displays the current count*/
void CurrentCount(int count){
	printf("Current count: %i \n", count);
}

/*Third function  out of three because spent too 
 *long dealing with passing in char arrays to 
 *come up with more refactored functions
 *good ol main function*/
int main(){
	char card_name[3];	
	int count =0;
	int val = 0;
	while (card_name[0] != 'X'){
		puts("Enter the card_name: ");
		scanf("%2s", card_name);
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
			continue;
		default:
			val = atoi(card_name);
			if ((val < 1) || (val>10) ){
				puts("I don't understand that value!");
				continue;
			}
		}
	
	count= ValueChecker(val, count);
	CurrentCount(count);
	}
	return 0;
	
}
