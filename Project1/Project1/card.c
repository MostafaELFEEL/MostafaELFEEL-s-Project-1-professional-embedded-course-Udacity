#include"card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Please Enter Your Name (20 to 24 characters)...\n");
	gets(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) > 19 && strlen(cardData->cardHolderName) < 25) {
		puts("CORRECT_FORMAT\n");
		return OK;
	}
	else { 
		puts("WRONG_NAME_FORMAT\n"); 
		return WRONG_NAME;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Please Enter Your Exp Date (MN/YR Format)...\n");
	gets(cardData->cardExpirationDate);
	expmonth = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
	expyear = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');
	if (expmonth >= 1 && expmonth <= 12 && cardData->cardExpirationDate[2] == '/' ) {
		puts("CORRECT_FORMAT\n");
		return OK;
	}
	else {
		puts("WRONG_DATE_FORMAT\n");
		return WRONG_EXP_DATE; 
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Please Enter Your Primary Account Number (16 to 19 characters)...\n");
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) > 15 && strlen(cardData->primaryAccountNumber) < 20) {
		puts("CORRECT_FORMAT\n");
		return OK;
	}
	else {
		puts("WRONG_PAN_FORMAT\n");
		return WRONG_PAN;
	}
}












//struct ST_cardData_t data[5] = { {"Mostafa Ashraf Ebrahim",""} };



/*extern struct client {
	char name[20];//name
	char expdate[5];//expiration date
	char PAN[10];//PAN account no.
	double bal;
};*/


/*void data() {

	gets(data[0].name);

	printf("\n%s\n", data[0].name);
	int x;
	x= data[0].name[0]
}*/
//data();

//EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
//{
//return EN_cardError_t();
//}
