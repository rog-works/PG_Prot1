#pragma once

namespace PG_Core
{
	template<class TSaveData>
	class ISaver
	{
	public:
		virtual TSaveData save() = 0;
		virtual void load(TSaveData saveData) = 0;
	};

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

	struct PlayerSaveData
	{
		Transform transform;
	};
}
