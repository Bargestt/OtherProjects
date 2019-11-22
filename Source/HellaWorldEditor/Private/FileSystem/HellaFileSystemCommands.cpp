#include "HellaFileSystemCommands.h"


#define LOCTEXT_NAMESPACE "HellaFileSystemCommands"

void FHellaFileSystemCommands::RegisterCommands()
{
	UI_COMMAND(NewFile, "New File", "Create new file in folder", EUserInterfaceActionType::Button, FInputChord(EKeys::N));
	Commands.Add(NewFile);	

	UI_COMMAND(NewFolder, "New Folder", "Create new folder in folder", EUserInterfaceActionType::Button, FInputChord(EKeys::N, EModifierKey::Control));
	Commands.Add(NewFolder);
	
	UI_COMMAND(Delete, "Delete File", "Delete selected file", EUserInterfaceActionType::Button, FInputChord(EKeys::Delete));
	Commands.Add(Delete);

	UI_COMMAND(Copy, "Copy File", "Copy selected file", EUserInterfaceActionType::Button, FInputChord(EKeys::C, EModifierKey::Control));
	Commands.Add(Copy);

	UI_COMMAND(Paste, "Paste File", "Paste file", EUserInterfaceActionType::Button, FInputChord(EKeys::V, EModifierKey::Control));
	Commands.Add(Paste);

	UI_COMMAND(BuildFromFolder, "Build from folder", "Build from folder", EUserInterfaceActionType::Button, FInputChord());
	Commands.Add(BuildFromFolder);

	UI_COMMAND(AddPath, "Add path", "Add Path", EUserInterfaceActionType::Button, FInputChord());
	Commands.Add(AddPath);

	UI_COMMAND(Info, "ShowInfo", "Show Info", EUserInterfaceActionType::Button, FInputChord());
	Commands.Add(Info);
}

#undef LOCTEXT_NAMESPACE