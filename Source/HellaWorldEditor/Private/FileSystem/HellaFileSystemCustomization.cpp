#include "HellaFileSystemCustomization.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "HellaFileSystemWidget.h"
#include "HellaFileSystem.h"

#define LOCTEXT_NAMESPACE "HellaFileSystemCustomization"

TSharedRef<IDetailCustomization> FHellaFileSystemCustomization::MakeInstance()
{
	return MakeShareable(new FHellaFileSystemCustomization);
}

void FHellaFileSystemCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr< UObject >> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);
	if (Objects.Num() != 1)
	{
		return;
	}
	TWeakObjectPtr< UHellaFileSystem > CustomizedObject = Cast< UHellaFileSystem >(Objects[0].Get());

	
	// Create a category so this is displayed early in the properties
	IDetailCategoryBuilder& MyCategory = DetailBuilder.EditCategory("FileSystem");

	MyCategory.AddCustomRow(LOCTEXT("FileSystemDisplay", "FileSystem"))
	.WholeRowContent()
	.VAlign(VAlign_Fill)		
	[
		SNew(SHellaFileSystemWidget)
		.OwnerSystemArg(CustomizedObject)
	];

}

#undef LOCTEXT_NAMESPACE