#include<stdio.h>
#include<stdlib.h>
struct cardsReveledList{
	char number;
	char suit;
	int playersCard;
}drawnCard[53];
int playerTurn = 1;
int revealCount = 0;
int playerCardValue=0;
int dealerCardValue=0;
int *ptr;
void cardGenerator();
void printCard(char,char);
void draw();
char cardNumber[13] = {'A','2','3','4','5','6','7','8','9','X','J','Q','K'};
char cardNumberText[13][6] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};
char cardSuit[4] = {3,4,5,6};
char cardSuitText[4][8] = {"Spades","Diamond","Heart","Club"};
void userInput();
int valueFinder(char);
void dealersTurn();
int main(){
	srand(time(0));
	cardGenerator();
	cardGenerator();
	while(playerCardValue <= 21){
		draw();
		userInput();
		system("cls");
	}
	draw();
	printf("\nYou are busted,You lose!");
}
void draw(){
	printf("________________________________\n");
	printf("|\tPress h to hit\t\t|\n");
	printf("|\tPress s to stand\t|\n");
	printf("|\t\t\t\t|\n");
	int i;
	for(i = 0;i<revealCount;i++){
		if(drawnCard[i].playersCard == 1){
			printCard(drawnCard[i].number,drawnCard[i].suit);
		}
	}
	printf("|\tYour hand value is %d\t|\n",playerCardValue);
	printf("|_______________________________|");
}
void cardGenerator(){
	int temp=0;
	redraw:
	drawnCard[revealCount].number = cardNumber[rand() % 13];
	drawnCard[revealCount].suit = cardSuit[rand() % 4];
	drawnCard[revealCount].playersCard = playerTurn;
	int i;
	if(revealCount >= 1){
		for(i = 0; i< revealCount - 1;i++){
			if((drawnCard[revealCount].number == drawnCard[i].number) && (drawnCard[revealCount].suit == drawnCard[i].suit)){
				goto redraw;
				break;
			}
		}
	}
	temp = valueFinder(drawnCard[revealCount].number);
	if(drawnCard[revealCount].playersCard == 1){
		playerCardValue +=temp;
	}else{
		dealerCardValue +=temp;
	}
	revealCount++;
}
int valueFinder(char num){
	int i;
	for(i = 0;i<13;i++){
		if(cardNumber[i] == num){
			if(i>=9){
				return 10;
			}else{
				return i + 1;
			}
		}
	}
}
void printCard(char num, char st){
	printf("|   _____\t\t\t|\n");
	num=='X'?printf("|   |10%c|\t\t\t|\n",st):printf("|   |%c %c|\t\t\t|\n",num,st);
	printf("|   |   |\t\t\t|\n");
	printf("|   |___|\t\t\t|\n");
}
void userInput(){
	char ch;
	printf("\nenter here: ");
	scanf("%c",&ch);
	if(ch == 'h'){
		cardGenerator();
	}else if(ch == 's'){
		playerTurn = 0;
		dealersTurn();
	}
}
void dealersTurn(){
	int firstTime = 1,i;
	cardGenerator();
	cardGenerator();
	printf("________________________________\n");
	printf("|\t\t\t\t|\n");
	for(i = 0;i<revealCount;i++){
		if(drawnCard[i].playersCard == 0){
			printCard(drawnCard[i].number,drawnCard[i].suit);
		}
	}
	again:
	sleep(1);
	if(dealerCardValue<playerCardValue && dealerCardValue<=21){
		cardGenerator();
		printCard(drawnCard[i].number,drawnCard[i].suit);
		i++;
		goto again;
	}else if(dealerCardValue>21){
		printf("|\tDealer busted. You win!\t|\n");
	}else if(dealerCardValue > playerCardValue){
		printf("|\tYou lose!\t\t|\n");
	}else if(dealerCardValue == playerCardValue && dealerCardValue>17){
		printf("|\tIts a Draw!\t\t|\n");
	}
	printf("|\t\t\t\t|\n");
	printf("|\tDealer\' hand value: %d\t|\n",dealerCardValue);	
	printf("|_______________________________|");
	exit(0);
}
