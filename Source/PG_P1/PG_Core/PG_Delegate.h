#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

namespace PG_Core
{
	class EventEmitter;
	class EventData;

	// template

	template<class TReceiver>
	struct DelegateSchemeType {
		typedef void (TReceiver::*MethodPointer)(void*, EventData*);
	};

	template<class TReceiver>
	using PickDelegatePointerType = typename DelegateSchemeType<TReceiver>::MethodPointer;

	// typedef

	typedef void (Handler)(void*, EventData* e);
	typedef std::function<Handler> Invoker;
	typedef std::vector<std::function<Handler>> Handlers;

	// sender

	class EventData {};

	class EventEmitter {
	public:
		template<class TReceiver>
		void on(std::string key, TReceiver* receiver, PickDelegatePointerType<TReceiver> func) {
			if (this->handlers.find(key) == this->handlers.end()) {
				this->handlers[key] = Handlers();
			}

			Invoker invoker = [=](void* sender, EventData* e) {
				(receiver->*func)(sender, e);
			};
			this->handlers[key].push_back(invoker);
		}

		void emit(std::string key, void* sender, EventData* e) {
			if (this->handlers.find(key) == this->handlers.end()) {
				return;
			}

			for (Invoker invoker : this->handlers[key]) {
				invoker(sender, e);
			}
		}

	private:
		std::map<std::string, Handlers> handlers;
	};

	/*
	 * @example
	 * // receiver
	 * 
	 * class A {
	 * public:
	 * 	void onClick(EventEmitter* sender, EventData* e);
	 * };
	 * 
	 * class B {
	 * public:
	 * 	void onClick(EventEmitter* sender, EventData* e);
	 * };
	 * 
	 * // runner
	 * 
	 * class Runner {
	 * 	void run() {
	 * 		EventEmitter sender;
	 * 	
	 * 		A a;
	 * 		auto funcA = &A::onClick;
	 * 		sender.on("on", &a, funcA);
	 * 	
	 * 		B b;
	 * 		auto funcB = &B::onClick;
	 * 		sender.on("on", &b, funcB);
	 * 
	 * 		EventData e;
	 * 		sender.emit("on", &e);
	 * 	}
	 * };
	 */
}
