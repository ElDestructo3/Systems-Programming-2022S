#!/usr/bin/gawk -f
function isLeapYear(year) {                                       
    #returns 1 if year is a leap year, 0 otherwise
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

function numDays(date1, date2) {
    #returns the number of days between date1 and date2

    split(date1, d1, "-") #split the date into its components
    split(date2, d2, "-")

    monthDays["01"] = 31  #set the number of days in each month in a non-leap year
    monthDays["02"] = 28
    monthDays["03"] = 31
    monthDays["04"] = 30
    monthDays["05"] = 31
    monthDays["06"] = 30
    monthDays["07"] = 31
    monthDays["08"] = 31
    monthDays["09"] = 30
    monthDays["10"] = 31
    monthDays["11"] = 30
    monthDays["12"] = 31

    if (d1[2]==d2[2]) {   #if the months are the same, return the difference of dates
        return d2[1]-d1[1]
    }
    ans=0;
    for (i=d1[2]+1; i<d2[2]-1; i++) { #add the number of days in the months between the dates
        ans += monthDays[i]
    }
    ans+=monthDays[d1[2]]-d1[1]+d2[1] #add the number of days in the months containing the dates
    if (isLeapYear(d1[3]) && d2[2]>=3&&d1[2]<3) { #if Feb 29 is included in the counting, add another day
        ans++
    }
    return ans
}

BEGIN {
    FS = ":"
    updateFlag=0                       #checks whether balances are up-to-date or not
    interest=0                         #calculating the interest
    numTransactions=0                  #number of transactions
    months["01"] = "January"           #create indexDateMap between index and months
    months["02"] = "February"
    months["03"] = "March"
    months["04"] = "April"
    months["05"] = "May"
    months["06"] = "June"
    months["07"] = "July"
    months["08"] = "August"
    months["09"] = "September"
    months["10"] = "October"
    months["11"] = "November"
    months["12"] = "December"
}
{
    #transactions array stores the transactions, positive for debit and negative for credit
    #infoTransactions array stores the information of the transactions (purpose of credit or debit)
    #balance array stores the balance after each transaction
    #indexDateMap maps the date of the transaction to its index in the transactions array
    #lastBalance stores the last updated value of balance
    #finalBalance variable gets updated with each transaction storing the balance
    numTransactions++                         
    if ($2 != "") {                           #if transaction is a debit
        transactions[numTransactions] = $2
    }
    else if ($3!="") {                        #if transaction is a credit
        transactions[numTransactions] = -$3
    }
    else {                                    #if transaction is opening balance
        transactions[numTransactions] = $4
    }
    infoTransactions[numTransactions] = $5    #store the information of the transaction
    if ($4 == "" ) {                          #if balance has not been updated
        if (updateFlag==0) {                  #if this is the first occurence, update the flag, and store index from which balance is to be updated
            updateFlag=1
            updateNum = numTransactions
        }
        finalBalance+= transactions[numTransactions]  #add the transaction to the final balance
        balance[numTransactions] = finalBalance       
        
    }
    else {
        balance[numTransactions] = $4         #if balance has been updated, store the balance, and also update the most recent updated balance
        lastBalance = $4
        finalBalance = $4
    }
    indexDateMap[numTransactions]=$1 
    
    
}

END {
    if (updateFlag==0) {
        printf("+++ No new transactions found\n")
        
        lastDate=""                                       #lastDate variable stores the last date having balance same as the current balance before a transaction
        for (num=1; num<=numTransactions; num++) {
            
            if (infoTransactions[num]=="INTEREST") {      #if the transaction is an interest transaction, reset interest to 0
                interest=0
                date= indexDateMap[num]
                split(date,A, "-")
                year=A[3]+1
                lastDate= "01-01-" year                   #set the last date to 1st Jan of the next year
                
                
                continue
            }
            if (lastDate=="") {                           #for first transaction, set the lastDate to the date of the transaction
                lastDate=indexDateMap[num]
                
                continue
            }
            split(indexDateMap[num],A, "-")
            year= A[3]
            
            if (isLeapYear(year)) {                       #set interest rate according to the number of days
                interestRate = 5/(100*366)
            }
            else {
                interestRate = 5/(365*100)
            }

            numberDays = numDays(lastDate, indexDateMap[num])  #find number of days for which balance has remained constant
            interest += numberDays*interestRate * balance[num-1] #calculate the interest
            
            lastDate=indexDateMap[num]                         #set the lastDate to the date of the transaction
        }
        printf("+++ Interest of this year up to the last transaction = %d\n", interest) #print the interest
    }
    else {
        print "+++ New transactions found"
        printf("Last Balance found = %d\n", lastBalance)      #print the last updated balance
        for (u = updateNum; u<=numTransactions; u++) {        #update the balance for all the transactions after the last updated balance
            split(indexDateMap[u],A, "-")                     #print transaction according to the required format
            printf("%-9s %s, %s      ", months[A[2]], A[1], A[3], transactions[u], infoTransactions[u])
            if (transactions[u]<0) {                          #checking for debit or credit
                printf("Debit  of %-9s", -transactions[u])
            }
            else {
                printf("Credit of %-9s", transactions[u])
            }
            printf(" for %-25s       Balance=%s\n", infoTransactions[u], balance[u])
        }

        lastDate=""                                           
        for (num=1; num<=numTransactions; num++) {            #updating the account.txt file
            
            if (infoTransactions[num]=="INTEREST") {          #similar to above, but printing it in the account.txt file
                
                date= indexDateMap[num]
                split(date,A, "-")
                year=A[3]+1
                lastDate= "01-01-" year
                printf("%s:%s::%s:%s\n", indexDateMap[num], transactions[num], balance[num], infoTransactions[num]) > "account.txt"
                
                interest=0
                continue
            }
            if (lastDate=="") {                               #similar to above, but printing it in the account.txt file   
                lastDate=indexDateMap[num]
                printf("%s:::%s:%s\n", indexDateMap[num], balance[num], infoTransactions[num]) > "account.txt"
                continue
            }
            split(indexDateMap[num],A, "-")
            year= A[3]
            split(lastDate,B, "-")
            if (A[3]!=B[3]) {                                 #if the year is changed, print the interest in the account.txt file
                yearEndDate= "31-12-" B[3]
                numberDays = numDays(lastDate, yearEndDate)
                interest += ((1+interestRate)**numberDays-1) * balance[num-1] #add interest between last transaction and end of year
                for (l=num-1;l<=numTransactions;l++) {        #update balances with the added interest 
                    balance[l]+=int(interest)
                }
                
                printf("%s:%d::%s:%s\n", yearEndDate, interest,balance[num-1],"INTEREST") > "account.txt"
                interest=0.00
                lastDate= "01-01-" A[3]
                
                
            }
            if (isLeapYear(year)) {                           #set interest rate according to the number of days
                interestRate = 5/(100*366)
            }
            else {
                interestRate = 5/(100*365)
            }
            
            if (transactions[num]>0) {                       #printing in required format
                printf("%s:%s::%s:%s\n", indexDateMap[num], transactions[num], balance[num], infoTransactions[num]) > "account.txt"
            }
            else {
                printf("%s::%s:%s:%s\n", indexDateMap[num], -transactions[num], balance[num], infoTransactions[num]) > "account.txt"
            }
            
            numberDays = numDays(lastDate, indexDateMap[num]) #similar to above
            interest += numberDays*interestRate * balance[num-1]
            lastDate=indexDateMap[num]
        }
        printf("+++ Interest of this year up to the last transaction = %d\n", interest) #print the interest
    }
}