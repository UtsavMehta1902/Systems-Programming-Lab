#!/usr/bin/gawk -f

function LeapYear(year){ # Returns 1 if leap year, 0 if not
    if(year % 400 == 0)
        return 1;
    
    if(year % 100 == 0)
        return 0;
    
    if(year % 4 == 0)
        return 1;
    
    return 0;
}

function DayDiff(date1, date2){ # Returns the number of days between two dates, NOTICE: It always gets same year in both dates.
    if(substr(date1, 4, 2) == substr(date2, 4, 2)){ # Same month
        if(LeapYear(int(substr(date1, 7, 4))))
            return (int(substr(date1, 1, 2)) - int(substr(date2, 1, 2)))/(NON_LEAP_YEAR_DAYS+1);
        else
            return (int(substr(date1, 1, 2)) - int(substr(date2, 1, 2)))/NON_LEAP_YEAR_DAYS;
    }
    ans = 0
    for(k = int(substr(date2, 4, 2)) + 1; k < int(substr(date1, 4, 2)); k++){ # Counting days in months between date-months
        if(k == 2 ){
            ans += 28;
            if(LeapYear(int(substr(date1, 7, 4))))
                ans++;
        }
        else if(k == 4 || k == 6 || k == 9 || k == 11)
            ans += 30;
        else
            ans += 31;
    }
    ans += day_array[int(substr(date2, 4, 2))] - int(substr(date2, 1, 2)); # Counting days after date2, in date2's month
    ans += int(substr(date1, 1, 2));                                  # Counting days before date1, in date1's month

    if(int(substr(date2, 4, 2)) == 2 && LeapYear(int(substr(date2, 7, 4)))) # If leap year, and date2's month is february
        ans++;
    
    if(LeapYear(int(substr(date1, 7, 4)))) # If leap year, total number of days differ than NON_LEAP_YEAR_DAYS
        return ans/(NON_LEAP_YEAR_DAYS+1);

    return ans/NON_LEAP_YEAR_DAYS;
}

function RoundOff(num){ # Rounds off a number to nearest integer
    if(num - int(num) >= 0.5)
        return int(num) + 1
        
    return int(num)
}

BEGIN {
    FS = ":" 
    months = "January, February, March, April, May, June, July, August, September, October, November, December"
    day = "31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31"
    split(months, month_array, ", ")
    split(day, day_array, ", ")
    interest = 0 # Total interest credited
    file_line = 1 # Iterator for file, used for indexing
    updates = 0 # 1 if new transaction encountered, 0 if not
    prev_date = "" # Previous date in transaction list
    INTEREST_RATE = 0.05 # Constant interest rate
    NON_LEAP_YEAR_DAYS = 365 # Number of days in a non-leap year
}

{
    if(substr($1,1,5) == "31-12") # If an entry on 31-12-yyyy is encountered, reset the interest
        interest = 0
    else if(prev_date && substr($1,1,5) != "01-01") # Update interest, if prev_date and current date are in same year
        interest += INTEREST_RATE * DayDiff($1,prev_date) * balance

    prev_year = substr(prev_date,7,4)
    if(prev_date && substr($1,7,4) != prev_year && substr(prev_date,1,5)!="31-12"){  # When a year changes and no entry on 31-12-yyyy is encountered
        interest += (INTEREST_RATE * DayDiff("31-12-"prev_year,prev_date) * balance) # Interest from last transaction upto 31-12-yyyy
        balance += RoundOff(interest)
        account_file[file_line++] = "31-12-"prev_year ":" int(interest+0.5) " :" ":" balance ":INTEREST"

        printf("%-25s %-40s %-20s\n", "December 31, " prev_year, "Credit of " int(interest+0.5) " for INTEREST", "Balance = "  balance)

        interest = INTEREST_RATE * DayDiff($1,"01-01-"(int(prev_year)+1)) * balance # Interest from 01-01-yyyy to current date
        balance += RoundOff(interest)
    }
    
    if(!$4){ # If balance for any transaction in null
        if(!updates)
            print "+++ New transactions found"

        updates = 1 # Set updates to 1

        balance += int($2) - int($3) # Credit - Debit
        date_MMDDYYY = month_array[int(substr($1,4,2))] " " substr($1,1,2) ", " substr($1,7,4) # Output format of date
 
        if($3)
            transaction_statement = "Debit of " $3 " for " $5
        else
            transaction_statement = "Credit of " $2 " for " $5

        printf("%-25s %-40s %-20s\n", date_MMDDYYY, transaction_statement, "Balance = "  balance) # Print transaction statement on console
        account_file[file_line++] = $1 ":" $2 ":" $3 ":" balance ":" $5
    }
    else{
        account_file[file_line++] = $0 
        balance = int($4)
    }

    prev_date = $1
}

END{
    if(!updates)
        print "+++ No new transactions found"
    else{
        for (j=1;j<file_line;j++){ # account_file[] stores all updated transactions to be written to account.txt
            print account_file[j] > "account.txt"
        }
    }
    print "+++ Interest of this year up to the last transaction = " RoundOff(interest)
}