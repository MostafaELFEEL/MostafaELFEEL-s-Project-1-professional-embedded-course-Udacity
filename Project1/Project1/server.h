#ifndef server_h
#define server_h

#include"card.h"
#include"terminal.h"
#include <math.h>
#define DataBaseSize 255
uint32_t PAN_validation;
uint32_t array_number;
uint32_t eofloop;
uint32_t eofTloop;
_Bool flag;

 typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, INTERNAL_SERVER_ERROR
}EN_transState_t;

 typedef enum EN_serverError_t
 {
	 OKK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, DECLINED_STOLEN_CARD
 }EN_serverError_t;

 typedef struct ST_accountsDB_t
 {
	 float balance;
	 uint8_t primaryAccountNumber[20];
 }ST_accountsDB_t;

 ST_accountsDB_t serverData[DataBaseSize];


 typedef struct ST_transaction_t
 {
	 ST_cardData_t cardHolderData;
	 ST_terminalData_t terminalData;
	 EN_transState_t transState;
	 uint32_t transactionSequenceNumber;
 }ST_transaction_t;

 ST_transaction_t transData[DataBaseSize];
 

   
void ReloadDataBase(ST_accountsDB_t serverData[DataBaseSize]);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t serverData[DataBaseSize]);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t serverData[DataBaseSize]);
void saveTransaction(ST_accountsDB_t serverData[DataBaseSize]);
void ReloadTransactionDataBase(ST_transaction_t transData[DataBaseSize]);
void uploadTransactions(ST_transaction_t transData[DataBaseSize], ST_cardData_t* cardData, ST_terminalData_t* termData);
#endif







//
//EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
