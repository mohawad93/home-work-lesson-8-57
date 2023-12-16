#pragma once
#include <iostream>
using namespace std;
namespace datalip
{
	bool isLeapYear(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	short numberOfDayesInMounth(short year, short mounth)
	{
		if (mounth < 1 || mounth>12)
			return 0;
		short numberOfDays[13] = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (mounth == 2) ? (isLeapYear(year) ? 29 : 28) : numberOfDays[mounth];

	}
	struct stDate
	{
		short Year;
		short Month;
		short Day;
	};
	//stDate GetSystemDate()
	//{
	//	stDate Date;
	//	time_t t = time(0);
	//	tm* now = localtime(&t);
	//	Date.Year = now->tm_year + 1900;
	//	Date.Month = now->tm_mon + 1;
	//	Date.Day = now->tm_mday;
	//	return Date;
	//}
	bool isDate1EqualDate2(stDate date1, stDate date2)
	{
		return ((date1.Day == date2.Day) && (date1.Month == date2.Month) && (date1.Year == date2.Year));
	}
	bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}
	bool IsDate1AftereDate2(stDate Date1, stDate Date2)
	{

		return (!IsDate1BeforeDate2(Date1, Date2) && !isDate1EqualDate2(Date1, Date2));
	}

	bool IsLastDayInMounth(stDate Date1)
	{
		return (Date1.Day == numberOfDayesInMounth(Date1.Year, Date1.Month));
	}
	bool IsLastMounthInYear(short mounth)
	{
		return(mounth == 12);
	}
	short ReadDay()
	{
		short Day;
		cout << "\nPlease enter a Day? ";
		cin >> Day;
		return Day;
	}
	short ReadMonth()
	{
		short Month;
		cout << "Please enter a Month? ";
		cin >> Month;
		return Month;
	}
	short ReadYear()
	{
		short Year;
		cout << "Please enter a Year? ";
		cin >> Year;
		return Year;
	}
	stDate ReadFullDate()
	{
		stDate Date;
		Date.Day = ReadDay();
		Date.Month = ReadMonth();
		Date.Year = ReadYear();
		return Date;
	}
	stDate EncresedDateBy1Day(stDate Date)
	{

		//(IsLastDayInMounth(Date) ? Date.Day = 1 ,((IsLastMounthInYear(Date.Month))?Date.Month=1,Date.Year++:Date.Month++) : Date.Day++);
		if (IsLastDayInMounth(Date))
		{

			if (IsLastMounthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}
		return Date;


	}
	void swapDates(stDate& date1, stDate& date2)
	{
		stDate tempDate;
		tempDate.Day = date1.Day;
		tempDate.Month = date1.Month;
		tempDate.Year = date1.Year;
		date1.Day = date2.Day;
		date1.Month = date2.Month;
		date1.Year = date2.Year;
		date2.Day = tempDate.Day;
		date2.Month = tempDate.Month;
		date2.Year = tempDate.Year;
	}
	int GetDifferenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = EncresedDateBy1Day(Date1);
		}
		return IncludeEndDay ? ++Days : Days;
	}
	void PrintDate(stDate date)
	{
		cout << " " << date.Day << "/" << date.Month << "/" << date.Year;
	}
	short readYear()
	{
		short year;
		cout << "please enter year ? ";
		cin >> year;
		return year;
	}
	short readMounth()
	{
		short mounth;
		cout << "\nplease enter mounth ? ";
		cin >> mounth;
		return mounth;
	}
	short readDay()
	{
		short day;
		cout << "please enter Day ? ";
		cin >> day;
		return day;
	}
	short dayOfWeekOrder(short day, short mounth, short year)
	{
		short a, y, m;
		a = (14 - mounth) / 12;
		y = year - a;
		m = mounth + (12 * a) - 2;
		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short dayOfWeekOrder(stDate date)
	{
		return dayOfWeekOrder(date.Day, date.Month, date.Year);
	}
	string dayShortName(short dayOfTheWeek)
	{
		string arr[] = { "sun","mon","tus","wen","ther","fri" ,"sat" };
		return arr[dayOfTheWeek];
	}
	bool IsEndOfWeek(stDate date)
	{
		return dayOfWeekOrder(date) == 6;
	}
	bool IsWeekEnd(stDate date)
	{
		short dayIndex = dayOfWeekOrder(date);
		return (dayIndex == 5 || dayIndex == 6);
	}
	bool IsBusinessDay(stDate date)
	{
		return !IsWeekEnd(date);
	}
	short DayUntilEndOfTheWeek(stDate date)
	{
		return 6 - dayOfWeekOrder(date);
	}
	short DayUntilEndOfTheMonth(stDate date)
	{
		stDate EndOfMonthDate;
		EndOfMonthDate.Day = numberOfDayesInMounth(date.Year, date.Month);
		EndOfMonthDate.Month = date.Month;
		EndOfMonthDate.Year = date.Year;
		return GetDifferenceInDays(date, EndOfMonthDate, true);

	}
	short DayUntilEndOfTheYear(stDate date)
	{
		stDate EndOfMonthDate;
		EndOfMonthDate.Day = 31;
		EndOfMonthDate.Month = 12;
		EndOfMonthDate.Year = date.Year;
		return GetDifferenceInDays(date, EndOfMonthDate, true);

	}

	stDate CountVecationReturnDate(stDate vecationBegin, short vecationDayes)
	{
		/*short day = 0;
		while (true)
		{

			if (IsBusinessDay(vecationBegin))
				day++;
			vecationBegin = EncresedDateBy1Day(vecationBegin);
			if (day == numberOfDayes)
			{
				return vecationBegin;
				break;
			}


		}*/
		short weekendConter = 0;
		while (IsWeekEnd(vecationBegin))
		{
			vecationBegin = EncresedDateBy1Day(vecationBegin);
		}
		for (int i = 1; i <= vecationDayes + weekendConter; i++)
		{
			if (IsWeekEnd(vecationBegin))
				weekendConter++;
			vecationBegin = EncresedDateBy1Day(vecationBegin);

		}
		while (IsWeekEnd(vecationBegin))
		{
			vecationBegin = EncresedDateBy1Day(vecationBegin);
		}
		return vecationBegin;
	}
	enum encompareDate{date1BeforDate2=-1,date1AfterDate2=1,date1EqualDate2=0};
	encompareDate compairDate(stDate date1, stDate date2)
	{

		if (IsDate1BeforeDate2(date1, date2))
			return encompareDate::date1BeforDate2;
	    if (isDate1EqualDate2(date1, date2))
			return encompareDate::date1EqualDate2;
		else 
			return encompareDate::date1AfterDate2;
	}
	void result()
	{
		stDate date1, date2;
		cout << "Enter date 1:\n";
		date1 = ReadFullDate();
		cout << "Enter date 2:\n";
		date2 = ReadFullDate();
		cout << "compair result = " << compairDate(date1, date2);


	}
}
