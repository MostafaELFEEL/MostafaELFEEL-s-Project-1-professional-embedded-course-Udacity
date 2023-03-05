#include"application.h"


void appStart(void) {
	while (getCardHolderName(&cardData) == WRONG_NAME) {}
	while (getCardExpiryDate(&cardData) == WRONG_EXP_DATE) {}
	while (getCardPAN(&cardData) == WRONG_PAN) {}
	getTransactionDate(&termData);
	setMaxAmount(&termData);
	if (isCardExpired(&cardData, &termData)== OKEY) {
		while (getTransactionAmount(&termData) == INVALID_AMOUNT) {}
		if (isBelowMaxAmount(&termData) == OKEY) {
			ReloadDataBase(serverData);
			if (isValidAccount(&cardData, serverData) == OKK) {
				if (isAmountAvailable(&termData, serverData) == OKK) {
					saveTransaction(serverData);
					ReloadTransactionDataBase(transData);
					uploadTransactions(transData, &cardData, &termData);
					
				}
			}
		}
	}
}

int main() {

		appStart();
	
	return 0;
}