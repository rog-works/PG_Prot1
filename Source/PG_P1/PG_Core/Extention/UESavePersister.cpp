#include "UESavePersister.h"
#include "Kismet/GameplayStatics.h"
#include "../../PG_SaveGame.h" // FIXME

void UESavePersister::save(std::string name, PG_Core::SaveData *data)
{
	PG_Core::SessionSaveData* session = (PG_Core::SessionSaveData*)data;
	UPG_SaveGame* saveGame = NewObject<UPG_SaveGame>();
	saveGame->session = *session;
	UGameplayStatics::SaveGameToSlot(saveGame, name.c_str(), 0);
}

void UESavePersister::load(std::string name, PG_Core::CopyFunc func)
{
	UPG_SaveGame* saveGame = Cast<UPG_SaveGame>(UGameplayStatics::LoadGameFromSlot(name.c_str(), 0));
	func(&saveGame->session);
}

void UESavePersister::remove(std::string name)
{
	UGameplayStatics::DeleteGameInSlot(name.c_str(), 0);
}

bool UESavePersister::exists(std::string name)
{
	return UGameplayStatics::DoesSaveGameExist(name.c_str(), 0);;
}
