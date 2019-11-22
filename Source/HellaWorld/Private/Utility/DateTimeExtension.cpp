// Fill out your copyright notice in the Description page of Project Settings.

#include "DateTimeExtension.h"



int32 UDateTimeExtension::DateMask()
{
	return (1 << (int32)EDateTimeRelevancy::Day) | (1 << (int32)EDateTimeRelevancy::Month) | (1 << (int32)EDateTimeRelevancy::Year);
}

int32 UDateTimeExtension::TimeMask()
{
	return (1 << (int32)EDateTimeRelevancy::Minute) | (1 << (int32)EDateTimeRelevancy::Hour);
}

int32 UDateTimeExtension::DateTimeMask()
{
	return TimeMask() | DateMask();
}

bool UDateTimeExtension::CompareDateTime(const FDateTime& A, const FDateTime& B, int32 RelevancyFlags)
{
	int32 Result = 0;

	if (A.GetMinute() == B.GetMinute())			Result |= 1 << (int32)EDateTimeRelevancy::Minute;
	if (A.GetHour() == B.GetHour())				Result |= 1 << (int32)EDateTimeRelevancy::Hour;
	if (A.GetDay() == B.GetDay())				Result |= 1 << (int32)EDateTimeRelevancy::Day;
	if (A.GetDayOfWeek() == B.GetDayOfWeek())	Result |= 1 << (int32)EDateTimeRelevancy::DayOfWeek;
	if (A.GetMonth() == B.GetMonth())			Result |= 1 << (int32)EDateTimeRelevancy::Month;
	if (A.GetYear() == B.GetYear())				Result |= 1 << (int32)EDateTimeRelevancy::Year;

	return (Result & RelevancyFlags) == RelevancyFlags; //Select only relevant bits from Result and check if they all match to mask
}

FDateTime UDateTimeExtension::CreateDayOfWeekDate(EDayOfWeekBP DayOfWeek)
{
	return FDateTime(1, 1, 1+static_cast<uint8>(DayOfWeek));
}

EDayOfWeekBP UDateTimeExtension::GetDayOfWeek(const FDateTime& Date)
{
	return static_cast<EDayOfWeekBP>(Date.GetDayOfWeek());
}


