#include "../PG_Save.h"

class UESavePersister : public PG_Core::IPersister
{
public:
	virtual void save(std::string name, PG_Core::SaveData* data) override;
	virtual PG_Core::SaveData load(std::string name) override;
	virtual void remove(std::string name) override;
	virtual bool exists(std::string name) override;
};
