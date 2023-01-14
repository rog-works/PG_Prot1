#include "../PG_Save.h"

class UESavePersister : public PG_Core::IPersister
{
public:
	virtual void save(std::string name, PG_Core::SaveData* data) override;
	virtual void load(std::string name, PG_Core::CopyFunc func) override;
	virtual void remove(std::string name) override;
	virtual bool exists(std::string name) override;

	static UESavePersister* getInstance() {
		static UESavePersister self = UESavePersister();
		return &self;
	}
};
