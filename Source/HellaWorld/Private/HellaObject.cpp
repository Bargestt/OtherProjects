#include "HellaObject.h"
#include "GameFramework/Actor.h"

UWorld* UHellaObject::GetWorld() const
{
	const UObject* Outer = GetOuter();
	bool IsValidOuter = Outer->IsA<UHellaObject>() || Outer->IsA<UActorComponent>() || Outer->IsA<AActor>();
	if (IsValidOuter)
	{
		return Outer->GetWorld();
	}
	return nullptr;
}

void UHellaObject::SortActorsByDist(FVector Location, const TArray<AActor*>& InArr, TArray<AActor*>& OutArr, bool Inverse /*= false*/)
{
	OutArr = InArr.FilterByPredicate([](AActor* A) { return IsValid(A); });

	
	Algo::Sort(OutArr,
		[Location, Inverse](AActor* A, AActor* B)
		{
			bool ACloser = FVector::DistSquared(Location, A->GetActorLocation()) < FVector::DistSquared(Location, B->GetActorLocation());
			return Inverse ? !ACloser : ACloser;
		}
	);
}