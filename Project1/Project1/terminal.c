#include"terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Getting Time...");
	time_t rawtime = time(NULL);
	struct tm* ptm = localtime(&rawtime);
	strftime(termData->transactionDate, 11, "%d/%m/%Y", ptm);
	puts(termData->transactionDate);
	return OKEY;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData) {

	trnmonth = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
	trnyear = ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

	if (expyear > trnyear || (expyear == trnyear && expmonth >= trnmonth)) {
		printf("CARD_NOT_EXPIRED\n");
		return OKEY;
	}
	else {
		printf("EXPIRED_CARD\n");
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {
	printf("Please Enter Transaction Amount (<5000)...\n");
	scanf("%f", &termData->transAmount);
	if (termData->transAmount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		return OKEY;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData) {
	termData->maxTransAmount = 5000;
	return OKEY;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		printf("DECLINED_AMOUNT_EXCEEDING_LIMIT\n");
		return EXCEED_MAX_AMOUNT;
	}
	else {
		printf("AMOUNT_ACCEPTED\n");
		return OKEY;
	}
}



//printf("Is Card Expired...\n");
//printf("INVALID_AMOUNT\n");
	//printf("VALID_AMOUNT\n");