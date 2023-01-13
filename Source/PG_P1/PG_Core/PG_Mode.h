#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "PG_Delegate.h"

namespace PG_Core
{
	enum class PG_Modes
	{
		None,
		Init,
		Run,
		Reset,
		Pause,
	};

	struct PG_ModeEventData : public PG_Core::EventData
	{
		PG_Modes before;
		PG_Modes after;
	};

	class PG_Mode : public PG_Core::EventEmitter
	{
	public:
		PG_Mode();
		~PG_Mode();
		void setNext(PG_Modes mode);
		PG_Modes current();
		PG_Modes next();

	private:
		PG_Modes _current = PG_Modes::Init;
		PG_Modes _next = PG_Modes::None;

		void transition();
	};
}
