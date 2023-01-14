#include "PG_Save.h"

using namespace PG_Core;

GlobalSaveSlot::~GlobalSaveSlot()
{
}

std::string GlobalSaveSlot::name()
{
	return this->_name;
}

GlobalSaveData* GlobalSaveSlot::data()
{
	return &this->_data;
}

void GlobalSaveSlot::save()
{
	this->_persister->save(this->name(), this->data());
}

void GlobalSaveSlot::load()
{
	auto func = [&, this](SaveData* data) {
		this->_data = *((GlobalSaveData*)data);
	};
	this->_persister->load(this->name(), func);
}

void GlobalSaveSlot::update(GlobalSaveData *data)
{
	this->_data = *data;
}

bool GlobalSaveSlot::exists()
{
	return this->_persister->exists(this->name());
}

void GlobalSaveSlot::remove()
{
	this->_persister->remove(this->name());
}

SessionSaveSlot::~SessionSaveSlot()
{
}

std::string SessionSaveSlot::name()
{
	return this->_name;
}

SessionSaveData* SessionSaveSlot::data()
{
	return &this->_data;
}

void SessionSaveSlot::save()
{
	this->_persister->save(this->name(), this->data());
}

void SessionSaveSlot::load()
{
	auto func = [&, this](SaveData* data) {
		this->_data = *((SessionSaveData*)data);
	};
	this->_persister->load(this->name(), func);
}

void SessionSaveSlot::update(SessionSaveData *data)
{
	this->_data = *data;
}

bool SessionSaveSlot::exists()
{
	return this->_persister->exists(this->name());
}

void SessionSaveSlot::remove()
{
	this->_persister->remove(this->name());
}

Save::~Save()
{
}

GlobalSaveSlot* Save::global()
{
	return &this->_global;
}

SessionSaveSlotMap* Save::sessions()
{
	return &this->_sessions;
}

SessionSaveSlot* Save::newSession(std::string name)
{
	auto slot = new SessionSaveSlot(this->_persister, name);
	this->_sessions[name] = slot;
	return slot;
}

void PG_Core::Save::removeSession(std::string name)
{
	if (this->_sessions[name]) {
		auto slot = this->_sessions[name];
		slot->remove();
		this->_sessions.erase(name);
		delete slot;
	}
}
