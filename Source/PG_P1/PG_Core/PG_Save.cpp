#include "PG_Save.h"

using namespace PG_Core;

template <class T>
PG_Core::SaveSlot<T>::~SaveSlot()
{
}

template <class T>
std::string SaveSlot<T>::name()
{
	return this->_name;
}

template<class T>
T* SaveSlot<T>::data()
{
	return &this->_data;
}

template<class T>
void SaveSlot<T>::save()
{
	this->_persister->save(this->name(), this->data());
}

template<class T>
void SaveSlot<T>::load()
{
	this->_persister->save(this->name(), this->data());
}

template<class T>
void SaveSlot<T>::update(T* data)
{
	this->data = *this->_persister->load(this->name());
}

template<class T>
void SaveSlot<T>::remove()
{
	this->_persister->remove(this->name());
}

template<class T>
bool SaveSlot<T>::exists()
{
	return 	this->_persister->exists(this->name());
}

Save::~Save()
{
}

GlobalSaveSlot *Save::global()
{
	// return &this->_global;
	return nullptr;
}

SessionSaveSlotMap *Save::sessions()
{
	// return &this->_sessions;
	return nullptr;
}

SessionSaveSlot *Save::newSession(std::string name)
{
	// this->_sessions[name] = SaveSlot<SessionSaveData>(this->_persister, name);
	// return &this->_sessions[name];
	return nullptr;
}

void PG_Core::Save::removeSession(std::string name)
{
	// this->_sessions.erase(name);
}
