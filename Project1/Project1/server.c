#include"server.h"
/*******************************************************************************/
void ReloadDataBase(ST_accountsDB_t serverData[DataBaseSize]) {
	uint8_t RelaoadedData[35];
	uint32_t PANloop;
	uint32_t DBcounter = 0;
	uint32_t DecimalCounter=0;
	float Decimal;
	FILE* ReadDB;
	ReadDB = fopen("DataBase.txt", "r");
	for (DBcounter ; DBcounter < DataBaseSize; DBcounter++) {
		serverData[DBcounter].balance = 0;
	}
	for (eofloop = 0; fgets(RelaoadedData,34, ReadDB); eofloop++) {
		PANloop = 0;
		while(RelaoadedData[PANloop]!='-') {
			serverData[eofloop].primaryAccountNumber[PANloop] = RelaoadedData[PANloop];
			PANloop++;	
		}
		PANloop++;
		for (PANloop; RelaoadedData[PANloop] != '.'; PANloop++) {
			serverData[eofloop].balance = (serverData[eofloop].balance * 10) +(RelaoadedData[PANloop]-'0');
		}
		PANloop++;
		for (PANloop; RelaoadedData[PANloop] != '-'; PANloop++) {
			DecimalCounter++;
			Decimal = (RelaoadedData[PANloop] - '0');
			serverData[eofloop].balance = (serverData[eofloop].balance)+ (Decimal/pow(10, DecimalCounter));
		}
	}
	fclose(ReadDB);
}
/*******************************************************************************/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t serverData[DataBaseSize]) {
	printf("Returning to Server to Validate Your Account...\n");
	for (uint32_t loop = 0; loop < 255; loop++) {
		flag = 0;
		PAN_validation = strcmp(cardData->primaryAccountNumber, serverData[loop].primaryAccountNumber);
		if (PAN_validation == 0) {
			flag = 1;
			array_number = loop;
			break;
		}
	}
	printf("Your Account Is Being Validated and Verified\n");
	if (flag == 1) {
		flag = 0;
		printf("ACCEPTED(NOT_STOLEN_CARD)\n");
		return OKK;
	}else {
		printf("DECLINED(STOLEN_CARD)\n");
		return DECLINED_STOLEN_CARD;
	}
}
/*******************************************************************************/

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t serverData[DataBaseSize]) {
	if (termData->transAmount > serverData[array_number].balance) {
		printf("LOW_BALANCE_TRANSACTION_FAILED\n");
		return LOW_BALANCE;
	}
	else {
		serverData[array_number].balance = (serverData[array_number].balance) - (termData->transAmount);
		printf("TRANSACTION_ACCEPTED\n");
		return OKK;
	}
}
/*******************************************************************************/
void saveTransaction(ST_accountsDB_t serverData[255]) {
	FILE* WriteDB;
	WriteDB = fopen("DataBase.txt", "w");
	uint32_t loop = 0;
	fprintf(WriteDB, "%s-%f-", serverData[loop].primaryAccountNumber, serverData[loop].balance);
	for (loop = 1; loop < eofloop; loop++) {
		fprintf(WriteDB, "\n%s-%f-", serverData[loop].primaryAccountNumber, serverData[loop].balance);
	}
	fclose(WriteDB);
	printf("TRANSACTION_SAVED\n");
}

/*******************************************************************************/
void ReloadTransactionDataBase(ST_transaction_t transData[DataBaseSize]) {
	uint8_t RelaoadedData[50];
	uint32_t PANloop;
	uint32_t DBcounter;
	uint32_t DecimalCounter = 0;
	float Decimal;
	uint16_t counter;
	FILE* ReadTDB;
	ReadTDB = fopen("TansDB.txt", "r");
	for (DBcounter=0; DBcounter < DataBaseSize; DBcounter++) {
		transData[DBcounter].terminalData.transAmount = 0;
	}

	for (DBcounter=0; DBcounter < DataBaseSize; DBcounter++) {
		transData[DBcounter].transactionSequenceNumber = 0;
	}

	for (eofTloop = 0; fgets(RelaoadedData, 49, ReadTDB); eofTloop++) {
		PANloop = 0;
		while (RelaoadedData[PANloop] != '-') {
			transData[eofTloop].cardHolderData.primaryAccountNumber[PANloop] = RelaoadedData[PANloop];
			PANloop++;
		}

		PANloop++;
		counter = 0;
		for (PANloop; RelaoadedData[PANloop] != '-'; PANloop++) {
			transData[eofTloop].terminalData.transactionDate[counter] = RelaoadedData[PANloop];
			counter++;
		}
		PANloop++;
		
		for (PANloop; RelaoadedData[PANloop] != '.'; PANloop++) {
			transData[eofTloop].terminalData.transAmount = (transData[eofTloop].terminalData.transAmount * 10) + (RelaoadedData[PANloop] - '0');
		}
		PANloop++;
		for (PANloop; RelaoadedData[PANloop] != '-'; PANloop++) {
			DecimalCounter++;
			Decimal = (RelaoadedData[PANloop] - '0');
			transData[eofTloop].terminalData.transAmount = (transData[eofTloop].terminalData.transAmount) + (Decimal / pow(10, DecimalCounter));
		}
		PANloop++;
		while (RelaoadedData[PANloop] != '-') {
			transData[eofTloop].transactionSequenceNumber = (transData[eofTloop].transactionSequenceNumber * 10) + (RelaoadedData[PANloop] - '0');
			PANloop++;
		}
	}
	fclose(ReadTDB);
}



/*******************************************************************************/

void uploadTransactions(ST_transaction_t transData[DataBaseSize], ST_cardData_t* cardData, ST_terminalData_t* termData) {
	FILE* WriteTDB;
	WriteTDB = fopen("TansDB.txt", "w");
	uint32_t loop = 0;
	uint16_t counter = 1;
	for (loop = 0; loop < eofTloop; loop++) {
		fprintf(WriteTDB, "%s-%s-%f-%d-\n", transData[loop].cardHolderData.primaryAccountNumber, transData[loop].terminalData.transactionDate, transData[loop].terminalData.transAmount,counter);
		counter++;
	}
	fprintf(WriteTDB, "%s-%s-%f-%d-", cardData->primaryAccountNumber, termData->transactionDate, termData->transAmount, counter);
	fclose(WriteTDB);
	//printf("TRANSACTION_SAVED\n");
}
