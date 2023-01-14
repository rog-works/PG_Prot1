#pragma once

#include <string>
#include <map>

namespace PG_Core
{
	template<class TSaveData>
	class ISaver
	{
	public:
		virtual TSaveData save() = 0;
		virtual void load(TSaveData saveData) = 0;
	};

	// scalar

	struct Vector3D
	{
		float x;
		float y;
		float z;
	};

	struct Transform
	{
		Vector3D position;
		Vector3D rotation;
	};

	// general

	struct GeneralSaveData
	{
		std::string version;
		bool enabled;
		unsigned int timestamp;
	};

	// option

	struct DisplaySaveData
	{
		bool fullscreen;
	};

	struct SoundSaveData
	{
		unsigned int master;
	};

	struct OptionSaveData
	{
		DisplaySaveData display;
		SoundSaveData sound;
	};

	// game

	struct PlayerSaveData
	{
		Transform transform;
	};

	struct GameSaveData
	{
		PlayerSaveData player;
	};

	// savedata

	struct SaveData
	{
		GeneralSaveData general;
	};

	struct GlobalSaveData : public SaveData
	{
		OptionSaveData option;
	};

	struct SessionSaveData : public SaveData
	{
		GameSaveData game;
	};

	class IPersister
	{
	public:
		virtual void save(std::string name, SaveData* data) = 0;
		virtual SaveData load(std::string name) = 0;
		virtual void remove(std::string name) = 0;
		virtual bool exists(std::string name) = 0;
	};

	template<class T>
	class SaveSlot
	{
	public:
		SaveSlot(IPersister* persister, std::string name) : _persister(persister), _name(name) {}
		~SaveSlot();
		std::string name();
		T* data();
		void save();
		void load();
		void update(T* data);
		void remove();
		bool exists();

	private:
		IPersister* _persister;
		std::string _name;
		T _data;
	};

	typedef SaveSlot<GlobalSaveData> GlobalSaveSlot;
	typedef SaveSlot<SessionSaveData> SessionSaveSlot;
	typedef std::map<std::string, SessionSaveSlot> SessionSaveSlotMap;

	class Save
	{
	public:
		Save(IPersister* persister) : _persister(persister), _global(SaveSlot<GlobalSaveData>(persister, "global")) {}
		~Save();

		GlobalSaveSlot* global();
		SessionSaveSlotMap* sessions();

		SessionSaveSlot* newSession(std::string name);
		void removeSession(std::string name);

	private:
		IPersister* _persister;
		GlobalSaveSlot _global;
		SessionSaveSlotMap _sessions;
	};
}
