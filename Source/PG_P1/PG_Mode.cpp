#include "PG_Mode.h"

PG_Mode::PG_Mode()
{
	UE_LOG(LogTemp, Warning, TEXT("PG_Mode: create"));
}

PG_Mode::~PG_Mode()
{
	UE_LOG(LogTemp, Warning, TEXT("PG_Mode: delete"));
}

void PG_Mode::setNext(PG_Modes mode)
{
	this->_next = mode;
	this->transition();
}

PG_Modes PG_Mode::current()
{
	return this->_current;
}

PG_Modes PG_Mode::next()
{
	return this->_next;
}

void PG_Mode::transition()
{
	if (this->next() == this->current()) {
		return;
	}

	PG_ModeEventData e;
	e.before = this->current();
	e.after = this->next();

	this->_current = this->next();
	this->_next = PG_Modes::None;

	this->emit("on change mode", this, &e);
}
