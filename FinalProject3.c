#include <stdio.h>
#include <math.h>		

float HomePrice = 0;   //Declaration of global variables, could be used in functions later
float DownPayment = 0;
int LoanYears = 0;
float InterestRate = 0;
float ExtraPayment = 0;

void printReportHeader() {   //Function that prints out the header on the report
	printf("\nPayment No.  Payment Date  Beginning Balance  Scheduled Payment  Extra Payment  Total Payment  Principal  Interest  Ending Balance  Cumulative Interest\n");
}


void printLoanInputs() {     //Function that asks for the inputs of the loan like Price, Down Payment amount, Interest rate, Mortgage years, etc
	printf("Please enter the price of the home you want to purchase: ");
	scanf("%f", &HomePrice);
	printf("Please enter what amount you will put down for the down payment: ");
	scanf("%f", &DownPayment);
	printf("Please enter the length of the loan in years i.e. 15, 20, or 30 years: ");
	scanf("%d", &LoanYears);
	printf("Please enter the interest rate of the loan: ");
	scanf("%f", &InterestRate);
	printf("How much extra do you want to pay towards the principal each month? ");
	scanf("%f", &ExtraPayment);	
	printf("Let's assume that the loan will begin January 1, 2021.\n\n");
}

void printRateCompareHeader() {   //This function prints the field names of each column in each amortization table
	printf("\nLoan No.\tMortgage Amount\t\tInterest Rate\tMonthly Payment\t\tCumulative Interest Paid\n");
}


//The below function InterestRateComparison is the function that compares the initial loan with two different interest rates. 
void InterestRateComparison(float HomePrice, int LoanYears, float InterestRate, float RateCompareRateTwo, int RateComparePaymentNumber[], float RateCompareBeginningBalance[], float RateCompareScheduledPayment[], float RateComparePrincipalPayment[], float RateCompareInterestPayment[], float RateCompareEndingBalance[], float RateCompareCumulativeInterest[], int RateComparePaymentNumberTwo[], float RateCompareBeginningBalanceTwo[], float RateCompareScheduledPaymentTwo[], float RateComparePrincipalPaymentTwo[], float RateCompareInterestPaymentTwo[], float RateCompareEndingBalanceTwo[], float RateCompareCumulativeInterestTwo[]) {
	
	RateComparePaymentNumber[0] = 1;
	RateCompareBeginningBalance[0] = (HomePrice);
	RateCompareScheduledPayment[0] = (HomePrice)*((InterestRate/12/100)*pow(1+(InterestRate/12/100), LoanYears*12))/(pow(1+(InterestRate/12/100), LoanYears*12)-1);
	RateComparePrincipalPayment[0] = (RateCompareScheduledPayment[0] - (RateCompareBeginningBalance[0] * (InterestRate/12/100)));
	RateCompareInterestPayment[0] = (RateCompareBeginningBalance[0] * (InterestRate/12/100));
	RateCompareEndingBalance[0] = (RateCompareBeginningBalance[0] - RateComparePrincipalPayment[0]);
	RateCompareCumulativeInterest[0] = (RateCompareBeginningBalance[0] * (InterestRate/12/100));
	
	RateComparePaymentNumberTwo[0] = 1;
	RateCompareBeginningBalanceTwo[0] = (HomePrice);
	RateCompareScheduledPaymentTwo[0] = (HomePrice)*((RateCompareRateTwo/12/100)*pow(1+(RateCompareRateTwo/12/100), LoanYears*12))/(pow(1+(RateCompareRateTwo/12/100), LoanYears*12)-1);
	RateComparePrincipalPaymentTwo[0] = (RateCompareScheduledPaymentTwo[0] - (RateCompareBeginningBalanceTwo[0] * (RateCompareRateTwo/12/100)));
	RateCompareInterestPaymentTwo[0] = (RateCompareBeginningBalanceTwo[0] * (RateCompareRateTwo/12/100));
	RateCompareEndingBalanceTwo[0] = (RateCompareBeginningBalanceTwo[0] - RateComparePrincipalPaymentTwo[0]);
	RateCompareCumulativeInterestTwo[0] = (RateCompareBeginningBalanceTwo[0] * (RateCompareRateTwo/12/100));
	
	for(int i = 1; i < (LoanYears*12); i++) {		//Here is the loop that prints row 1 and down of the amortization table
		 RateComparePaymentNumber[i] = i + 1;					//Increases Payment number by 1
		 RateCompareBeginningBalance[i] = RateCompareEndingBalance[i - 1];	//Makes the beginning balance of the next row equal the ending balance of the previous row
		 RateCompareScheduledPayment[i] = RateCompareScheduledPayment[i - 1];	//The scheduled payment will always be the same
		 RateComparePrincipalPayment[i] = (RateCompareScheduledPayment[i] - (RateCompareBeginningBalance[i] * (InterestRate/12/100)));	//The principal payment changes each month depending on the balance left on the loan
		 RateCompareInterestPayment[i] = (RateCompareBeginningBalance[i] * (InterestRate/12/100));	//The interest payment changes each month depending on the balance left of the loan
		 RateCompareEndingBalance[i] = (RateCompareBeginningBalance[i] - RateComparePrincipalPayment[i]);		//Calculates the ending balance after each payment
		 RateCompareCumulativeInterest[i] = RateCompareCumulativeInterest[i-1] + RateCompareInterestPayment[i];	//This calculates the cumulative interest for each month, for the length of the loan 
		if (RateCompareBeginningBalance[i] < RateComparePrincipalPayment[i]) {	//This if statement makes our table end once we pay off the remaining balance on the loan
			break;
		}
	}	
	
	for(int i = 1; i < LoanYears*12; i++) {		//Here is the loop that prints row 1 and down of the amortization table
		 RateComparePaymentNumberTwo[i] = i + 1;					//Increases Payment number by 1
		 RateCompareBeginningBalanceTwo[i] = RateCompareEndingBalanceTwo[i - 1];	//Makes the beginning balance of the next row equal the ending balance of the previous row
		 RateCompareScheduledPaymentTwo[i] = RateCompareScheduledPaymentTwo[i - 1];	//The scheduled payment will always be the same
		 RateComparePrincipalPaymentTwo[i] = (RateCompareScheduledPaymentTwo[i] - (RateCompareBeginningBalanceTwo[i] * (RateCompareRateTwo/12/100)));	//The principal payment changes each month depending on the balance left on the loan
		 RateCompareInterestPaymentTwo[i] = (RateCompareBeginningBalanceTwo[i] * (RateCompareRateTwo/12/100));	//The interest payment changes each month depending on the balance left of the loan
		 RateCompareEndingBalanceTwo[i] = (RateCompareBeginningBalanceTwo[i] - RateComparePrincipalPaymentTwo[i]);		//Calculates the ending balance after each payment
		 RateCompareCumulativeInterestTwo[i] = RateCompareCumulativeInterestTwo[i-1] + RateCompareInterestPaymentTwo[i];	//This calculates the cumulative interest for each month, for the length of the loan 
		if (RateCompareBeginningBalanceTwo[i] < RateComparePrincipalPaymentTwo[i]) {	//This if statement makes our table end once we pay off the remaining balance on the loan
			break;
		}
	}		
	
}


//The below function is the calculation of the original loan being refinanced. It is called down in main. 
void Refinance(int RefinanceLoanYears, float RefinanceInterestRate, float RefinanceHomePrice, float RefinanceExtraPayment, int RefinancePaymentNumber[], float RefinanceBeginningBalance[], float RefinanceScheduledPayment[], float RefinanceExtraPaymentArray[], float RefinancePrincipalPayment[], float RefinanceInterestPayment[], float RefinanceTotalPayment[], float RefinanceEndingBalance[], float RefinanceCumulativeInterest[], int month[], int day[], int year[]) {
	RefinancePaymentNumber[0] = 1;
	RefinanceBeginningBalance[0] = (RefinanceHomePrice);
	RefinanceScheduledPayment[0] = (RefinanceHomePrice)*((RefinanceInterestRate/12/100)*pow(1+(RefinanceInterestRate/12/100), RefinanceLoanYears*12))/(pow(1+(RefinanceInterestRate/12/100), RefinanceLoanYears*12)-1);
	RefinanceExtraPaymentArray[0] = RefinanceExtraPayment;
	RefinancePrincipalPayment[0] = ((RefinanceScheduledPayment[0] - (RefinanceBeginningBalance[0] * (RefinanceInterestRate/12/100))) + RefinanceExtraPayment);
	RefinanceInterestPayment[0] = (RefinanceBeginningBalance[0] * (RefinanceInterestRate/12/100));
	RefinanceTotalPayment[0] = (RefinanceScheduledPayment[0] + RefinanceExtraPayment);	
	RefinanceEndingBalance[0] = (RefinanceBeginningBalance[0] - RefinancePrincipalPayment[0]);
	RefinanceCumulativeInterest[0] = (RefinanceBeginningBalance[0] * (RefinanceInterestRate/12/100));
	
	printf("%d      \t\t%d/%d/%d\t%.2f           %.2f            %.2f         %.2f       %.2f    %.2f      %.2f         %.2f\n", RefinancePaymentNumber[0], month[0], day[0], year[0], RefinanceBeginningBalance[0], RefinanceScheduledPayment[0], RefinanceExtraPaymentArray[0], RefinanceTotalPayment[0], RefinancePrincipalPayment[0], RefinanceInterestPayment[0], RefinanceEndingBalance[0], RefinanceCumulativeInterest[0]);	

	for(int i = 1; i < RefinanceLoanYears*12; i++) {		//Here is the loop that prints row 1 and down of the amortization table
		 RefinancePaymentNumber[i] = i + 1;					//Increases Payment number by 1
		 day[i] = 1; 								//Makes the payment date always on the first of the month
		 RefinanceBeginningBalance[i] = RefinanceEndingBalance[i - 1];	//Makes the beginning balance of the next row equal the ending balance of the previous row
		 RefinanceScheduledPayment[i] = RefinanceScheduledPayment[i - 1];	//The scheduled payment will always be the same
		 RefinanceExtraPaymentArray[i] = RefinanceExtraPaymentArray[i - 1];//The extra payment will always be the same in this program
		 RefinanceTotalPayment[i] = RefinanceScheduledPayment[i] + RefinanceExtraPaymentArray[i];	//The total payment for each month is equal to the scheduled payment plus extra payment
		 RefinancePrincipalPayment[i] = ((RefinanceScheduledPayment[i] - (RefinanceBeginningBalance[i] * (RefinanceInterestRate/12/100))) + RefinanceExtraPaymentArray[i]);	//The principal payment changes each month depending on the balance left on the loan
		 RefinanceInterestPayment[i] = (RefinanceBeginningBalance[i] * (RefinanceInterestRate/12/100));	//The interest payment changes each month depending on the balance left of the loan
		RefinanceEndingBalance[i] = (RefinanceBeginningBalance[i] - RefinancePrincipalPayment[i]);		//Calculates the ending balance after each payment
		RefinanceCumulativeInterest[i] = RefinanceCumulativeInterest[i-1] + RefinanceInterestPayment[i];	//This calculates the cumulative interest for each month, for the length of the loan
		 printf("%d      \t\t%d/%d/%d\t%.2f           %.2f            %.2f         %.2f       %.2f    %.2f      %.2f         %.2f\n", RefinancePaymentNumber[i], month[i], day[i], year[i], RefinanceBeginningBalance[i], RefinanceScheduledPayment[i], RefinanceExtraPaymentArray[i], RefinanceTotalPayment[i], RefinancePrincipalPayment[i], RefinanceInterestPayment[i], RefinanceEndingBalance[i], RefinanceCumulativeInterest[i]);	
		 //This printf function is how we print the table. 
		if (RefinanceBeginningBalance[i] < RefinancePrincipalPayment[i]) {	//This if statement makes our table end once we pay off the remaining balance on the loan
			break;
		}
	}
	
}


int main () {			
		
	printLoanInputs();		//Execution of function that asks for loan inputs
	printReportHeader();		//Execution of function that prints the header of the report
	
	int day[360]; //The day array is used to show the day of the payment. This value is always 1, since the payment is always due on the first of the month. 
	day[0] = 1; 				//initializes first value of the day array as 1
	
	//The month array is used to show the month on the payment date. It is simply the numbers 1 - 12 repeated over and over again to represent months in a year. 
	int month[360] = {1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,
					1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,
					1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,
					1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7,8,9,10,11,12};
	
	
	//The year array is used to show the year in the payment date. The loan always begins in 2021. Each year is listed 12 times to represent 12 months. 
	int year[360] = {2021,2021,2021,2021,2021,2021,2021,2021,2021,2021,2021,2021,2022,2022,2022,2022,2022,2022,2022,2022,2022,2022,2022,2022, 2023,2023,2023,2023,2023,2023,2023,2023,2023,2023,2023,2023,2024,2024,2024,2024,2024,2024,2024,2024,2024,2024,2024,2024,
					2025,2025,2025,2025,2025,2025,2025,2025,2025,2025,2025,2025,2026,2026,2026,2026,2026,2026,2026,2026,2026,2026,2026,2026,2027,2027,2027,2027,2027,2027,2027,2027,2027,2027,2027,2027,2028,2028,2028,2028,2028,2028,2028,2028,2028,2028,2028,2028,
					2029,2029,2029,2029,2029,2029,2029,2029,2029,2029,2029,2029,2030,2030,2030,2030,2030,2030,2030,2030,2030,2030,2030,2030,2031,2031,2031,2031,2031,2031,2031,2031,2031,2031,2031,2031,2032,2032,2032,2032,2032,2032,2032,2032,2032,2032,2032,2032,
					2033,2033,2033,2033,2033,2033,2033,2033,2033,2033,2033,2033,2034,2034,2034,2034,2034,2034,2034,2034,2034,2034,2034,2034,2035,2035,2035,2035,2035,2035,2035,2035,2035,2035,2035,2035,2036,2036,2036,2036,2036,2036,2036,2036,2036,2036,2036,2036,
					2037,2037,2037,2037,2037,2037,2037,2037,2037,2037,2037,2037,2038,2038,2038,2038,2038,2038,2038,2038,2038,2038,2038,2038,2039,2039,2039,2039,2039,2039,2039,2039,2039,2039,2039,2039,2040,2040,2040,2040,2040,2040,2040,2040,2040,2040,2040,2040,
					2041,2041,2041,2041,2041,2041,2041,2041,2041,2041,2041,2041,2042,2042,2042,2042,2042,2042,2042,2042,2042,2042,2042,2042,2043,2043,2043,2043,2043,2043,2043,2043,2043,2043,2043,2043,2044,2044,2044,2044,2044,2044,2044,2044,2044,2044,2044,2044,
					2045,2045,2045,2045,2045,2045,2045,2045,2045,2045,2045,2045,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2046,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2047,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,
					2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2049,2050,2050,2050,2050,2050,2050,2050,2050,2050,2050,2050,2050};
	
	int PaymentNumber[LoanYears * 12];	//This is the array that gives the payment number. Loan Years * 12 gives the months which is needed in amortization table
	PaymentNumber[0] = 1;			//Initializes the first value of the array as 0
	
	float BeginningBalance[LoanYears * 12];		
	BeginningBalance[0] = (HomePrice - DownPayment);	//This calculates the Beginning Balance of the mortgage

	float ScheduledPayment[LoanYears * 12];		//This calculates the monthly payment that will need to be paid each month
	ScheduledPayment[0] = (HomePrice-DownPayment)*((InterestRate/12/100)*pow(1+(InterestRate/12/100), LoanYears*12))/(pow(1+(InterestRate/12/100), LoanYears*12)-1);
	
	float ExtraPaymentArray[LoanYears * 12];	
	ExtraPaymentArray[0] = ExtraPayment;	//This assigns the Extra Payment global variable as the first item in the extra payment array
	
	float PrincipalPayment[LoanYears * 12];	//This calculates the initial principal payment for the first payment on the loan
	PrincipalPayment[0] = ((ScheduledPayment[0] - (BeginningBalance[0] * (InterestRate/12/100))) + ExtraPayment);
	
	float InterestPayment[LoanYears * 12];	//This calculates the initial interest payment for the first payment on the loan
	InterestPayment[0] = (BeginningBalance[0] * (InterestRate/12/100));
	
	float TotalPayment[LoanYears * 12];		//This calculates the total payment that will be made each month, which is the regular payment
	TotalPayment[0] = (ScheduledPayment[0] + ExtraPayment);		//plus the extra payment we entered in the inputs when asked
	
	float EndingBalance[LoanYears * 12];		//This calculates the ending balance each month, after making our payment
	EndingBalance[0] = (BeginningBalance[0] - PrincipalPayment[0]);
	
	float CumulativeInterest[LoanYears * 12];	//This calculates the first value in the cumulative interest array, which is also just the first interest payment
	CumulativeInterest[0] = (BeginningBalance[0] * (InterestRate/12/100));
	
	//This prints the initial row 0 of the amortization table. The loop below will print the subsequent rows
	printf("%d      \t\t%d/%d/%d\t%.2f           %.2f         %.2f         %.2f       %.2f    %.2f      %.2f         %.2f\n", PaymentNumber[0], month[0], day[0], year[0], BeginningBalance[0], ScheduledPayment[0], ExtraPaymentArray[0], TotalPayment[0], PrincipalPayment[0], InterestPayment[0], EndingBalance[0], CumulativeInterest[0]);	
	 
	 
	 for(int i = 1; i < LoanYears*12; i++) {		//Here is the loop that prints row 1 and down of the amortization table
		 PaymentNumber[i] = i + 1;					//Increases Payment number by 1
		 day[i] = 1; 								//Makes the payment date always on the first of the month
		 BeginningBalance[i] = EndingBalance[i - 1];	//Makes the beginning balance of the next row equal the ending balance of the previous row
		 ScheduledPayment[i] = ScheduledPayment[i - 1];	//The scheduled payment will always be the same
		 ExtraPaymentArray[i] = ExtraPaymentArray[i - 1];//The extra payment will always be the same in this program
		 TotalPayment[i] = ScheduledPayment[i] + ExtraPaymentArray[i];	//The total payment for each month is equal to the scheduled payment plus extra payment
		 PrincipalPayment[i] = ((ScheduledPayment[i] - (BeginningBalance[i] * (InterestRate/12/100))) + ExtraPaymentArray[i]);	//The principal payment changes each month depending on the balance left on the loan
		 InterestPayment[i] = (BeginningBalance[i] * (InterestRate/12/100));	//The interest payment changes each month depending on the balance left of the loan
		EndingBalance[i] = (BeginningBalance[i] - PrincipalPayment[i]);		//Calculates the ending balance after each payment
		CumulativeInterest[i] = CumulativeInterest[i-1] + InterestPayment[i];	//This calculates the cumulative interest for each month, for the length of the loan
		 printf("%d      \t\t%d/%d/%d\t%.2f           %.2f         %.2f         %.2f       %.2f    %.2f      %.2f         %.2f\n", PaymentNumber[i], month[i], day[i], year[i], BeginningBalance[i], ScheduledPayment[i], ExtraPaymentArray[i], TotalPayment[i], PrincipalPayment[i], InterestPayment[i], EndingBalance[i], CumulativeInterest[i]);	
		 //This printf function is how we print the table. 
		if (BeginningBalance[i] < PrincipalPayment[i]) {	//This if statement makes our table end once we pay off the remaining balance on the loan
			break;
		}
	}		

	float RateCompareRateTwo = 0;	
	
	printf("********************************************************************************************************************************************************************\n");
	
	//Below are the printf statements that initiate the user to begin using the interest rate comparison function
	printf("\nLet's see what the above loan would look like with different interest rates.\n");
	printf("This is a good exercise to see how different interest rates affect the attributes of a loan.\n\n");
	printf("Remember, the price of the first home was $%.2f.\n", HomePrice);
	printf("The length of the first loan was %d years.\n", LoanYears);
	printf("The interest rate of the first loan was %.2f percent.\n", InterestRate);	
	printf("Please enter a second interest rate to compare against the first one: ");
	scanf("%f", &RateCompareRateTwo);
	
	
	//below is the declaration of the arrays that will be used to compare loans with two different interest rates
	int RateComparePaymentNumber[LoanYears * 12]; 	
	float RateCompareBeginningBalance[LoanYears * 12];		
	float RateCompareScheduledPayment[LoanYears * 12];		
	float RateComparePrincipalPayment[LoanYears * 12];	
	float RateCompareInterestPayment[LoanYears * 12];
	float RateCompareEndingBalance[LoanYears * 12];		
	float RateCompareCumulativeInterest[LoanYears * 12];	
	int RateComparePaymentNumberTwo[LoanYears * 12]; 	
	float RateCompareBeginningBalanceTwo[LoanYears * 12];	
	float RateCompareScheduledPaymentTwo[LoanYears * 12];	
	float RateComparePrincipalPaymentTwo[LoanYears * 12];
	float RateCompareInterestPaymentTwo[LoanYears * 12];	
	float RateCompareEndingBalanceTwo[LoanYears * 12];		
	float RateCompareCumulativeInterestTwo[LoanYears * 12];	

	//Below is the calling of the function that compares two interest rates
	InterestRateComparison(HomePrice, LoanYears, InterestRate, RateCompareRateTwo, RateComparePaymentNumber, RateCompareBeginningBalance, RateCompareScheduledPayment, RateComparePrincipalPayment, RateCompareInterestPayment, RateCompareEndingBalance, RateCompareCumulativeInterest, RateComparePaymentNumberTwo, RateCompareBeginningBalanceTwo, RateCompareScheduledPaymentTwo, RateComparePrincipalPaymentTwo, RateCompareInterestPaymentTwo, RateCompareEndingBalanceTwo, RateCompareCumulativeInterestTwo);
	
	
	//Below is the calling of the function that prints the header for the Rate Comparison function
	printRateCompareHeader();
	
	
	//Below is the printing of the table that shows the comparison between the two interest rates
	printf("%d\t\t  %.2f\t\t  %.2f\t\t  %.2f\t\t\t  %.2f\n", 1, HomePrice, InterestRate, RateCompareScheduledPayment[1], RateCompareCumulativeInterest[LoanYears*12 - 1]);
	printf("%d\t\t  %.2f\t\t  %.2f\t\t  %.2f\t\t\t  %.2f", 2, HomePrice, RateCompareRateTwo, RateCompareScheduledPaymentTwo[1], RateCompareCumulativeInterestTwo[LoanYears*12 - 1]);
	printf("\n\nAs you can see, a higher interest rate results in a higher monthly payment, as well as significantly more interest paid throughout the life of the loan.\n\n");
		
	
	
	printf("********************************************************************************************************************************************************************\n");
	
	//Below are the variable initializations that are used in the Refinancing function
	int RefinanceLoanYears;
	float RefinanceInterestRate;
	float RefinanceHomePrice = BeginningBalance[36];
	float RefinanceExtraPayment;			
		
		
	//Below are the printf statements that let the user know what is going on within the Refinance function
	printf("\nNow let's look at what the original loan would look like after refinancing.\n");
	printf("A refinance takes the remaining balance on a loan, and re-amortizes it with a different interest rate.\n");
	printf("Most people refinance when interest rates drop so that their monthly payment is lower.\n\n");
	printf("Let's refinance this loan when the remaining balance on the loan is $%.2f, which is payment number %d in our first example.\n", BeginningBalance[36], PaymentNumber[36]); 
	printf("The current interest rate on this loan is %.2f percent.\n", InterestRate);
	printf("Please enter a new interest rate that will be used for the refinance: ");
	scanf("%f", &RefinanceInterestRate);
	printf("Please enter the length of the refinanced loan in years i.e. 15, 20, or 30 years: " );
	scanf("%d", &RefinanceLoanYears);
	printf("How much extra do you want to put towards the principal each month for the refinanced loan? ");
	scanf("%f", &RefinanceExtraPayment);	
	
	int RefinancePaymentNumber[RefinanceLoanYears * 12];	//This is the array that gives the payment number. Loan Years * 12 gives the months which is needed in amortization table
	float RefinanceBeginningBalance[RefinanceLoanYears * 12];		
	float RefinanceScheduledPayment[RefinanceLoanYears * 12];		//This calculates the monthly payment that will need to be paid each month
	float RefinanceExtraPaymentArray[RefinanceLoanYears * 12];	
	float RefinancePrincipalPayment[RefinanceLoanYears * 12];	//This calculates the initial principal payment for the first payment on the loan
	float RefinanceInterestPayment[RefinanceLoanYears * 12];	//This calculates the initial interest payment for the first payment on the loan
	float RefinanceTotalPayment[RefinanceLoanYears * 12];		//This calculates the total payment that will be made each month, which is the regular payment
	float RefinanceEndingBalance[RefinanceLoanYears * 12];		//This calculates the ending balance each month, after making our payment
	float RefinanceCumulativeInterest[RefinanceLoanYears * 12];	//This calculates the first value in the cumulative interest array, which is also just the first interest payment

	//Here is where the report header is printed again, to give header for the refinanced amortization table
	printReportHeader();
	
	//Below is my function call for the refinance function, including all variables used in the function above
	Refinance(RefinanceLoanYears, RefinanceInterestRate, RefinanceHomePrice, RefinanceExtraPayment, RefinancePaymentNumber, RefinanceBeginningBalance, RefinanceScheduledPayment, RefinanceExtraPaymentArray, RefinancePrincipalPayment, RefinanceInterestPayment, RefinanceTotalPayment, RefinanceEndingBalance,RefinanceCumulativeInterest,month,day,year);

	return 0;
	
}