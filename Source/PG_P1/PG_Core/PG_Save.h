#pragma once

#include <functional>
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
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
	};

	struct Transform
	{
		Vector3D position;
		Vector3D rotation;
	};

	// general

	struct GeneralSaveData
	{
		std::string version = "";
		bool enabled = false;
		unsigned int timestamp = 0;
	};

	// option

	struct DisplaySaveData
	{
		bool fullscreen = false;
	};

	struct SoundSaveData
	{
		unsigned int master = 100;
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

	typedef std::function<void (SaveData*)> CopyFunc;

	class IPersister
	{
	public:
		virtual void save(std::string name, SaveData* data) = 0;
		virtual void load(std::string name, CopyFunc func) = 0;
		virtual void remove(std::string name) = 0;
		virtual bool exists(std::string name) = 0;
	};

	class GlobalSaveSlot
	{
	public:
		GlobalSaveSlot(IPersister* persister, std::string name) : _persister(persister), _name(name) {}
		~GlobalSaveSlot();
		std::string name();
		GlobalSaveData* data();
		void save();
		void load();
		void update(GlobalSaveData* data);
		void remove();
		bool exists();

	private:
		IPersister* _persister;
		std::string _name;
		GlobalSaveData _data;
	};

	class SessionSaveSlot
	{
	public:
		SessionSaveSlot(IPersister* persister, std::string name) : _persister(persister), _name(name) {}
		~SessionSaveSlot();
		std::string name();
		SessionSaveData* data();
		void save();
		void load();
		void update(SessionSaveData* data);
		void remove();
		bool exists();

	private:
		IPersister* _persister;
		std::string _name;
		SessionSaveData _data;
	};

	typedef std::map<std::string, SessionSaveSlot*> SessionSaveSlotMap;

	class Save
	{
	public:
		Save(IPersister* persister) : _persister(persister), _global(GlobalSaveSlot(persister, "global")) {}
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
