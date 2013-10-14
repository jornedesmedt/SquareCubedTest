#pragma once

#include <functional>
#include <forward_list>
#include <list>

namespace Utils {
	class EventScope;
	class IEvent {
	public:
		virtual ~IEvent() {}
	public: // Attaching and Detaching events
		virtual void DetachForScope(const EventScope &scope) = 0;
	};
	
	/// <summary>
	/// Used to define the scope within an event exists.
	/// Events are unhooked automatically on destruction.
	/// </summary>
	class EventScope final {
		std::forward_list<std::reference_wrapper<IEvent>> m_HookedEvents;

	public:
		void HookEvent(IEvent &event) { m_HookedEvents.push_front(std::ref(event)); }
		~EventScope() {
			// Detach all Events from Scope
			for (IEvent &event : m_HookedEvents)
				event.DetachForScope(*this);
		}
	};

	/// <summary>
	/// Used for event hooking. Add to class as public member.
	/// </summary>
	template <class T> class Event final : public IEvent{
		typedef std::function<void(const T&)> Callback;

		// Internal Storage Entry
		struct CallbackEntry {
			Callback CallbackFunc;
			const EventScope &Scope;
			CallbackEntry(Callback callback, const EventScope &scope) :
				CallbackFunc(callback),
				Scope(scope)
			{}
		};

		std::list<CallbackEntry> m_Callbacks;

	public: // Attaching and Detaching Events
		void Attach(Callback callback, EventScope &scope) {
			// Register Function and Scope
			m_Callbacks.push_back(CallbackEntry(callback, scope));
			scope.HookEvent(*this);
		}

		// Admittely a somewhat ugly hack but it makes classes using this look nicer
		#define AttachFromThis(CALLBACK, SCOPE) Attach(std::bind(&CALLBACK, this, std::placeholders::_1), SCOPE)

		void DetachForScope(const EventScope &scope) {
			auto i = m_Callbacks.begin();
			while (i != m_Callbacks.end()) {
				// Compare pointers
				if (&((*i).Scope) == &scope) {
					// Remove Scope from List
					i = m_Callbacks.erase(i);
				}
				else
					i++;
			}
		}

	public: // Event Invoking
		void Invoke(const T &param) {
			// Call all Functions in the Callbacks List
			for (CallbackEntry &entry : m_Callbacks)
				entry.CallbackFunc(param);
		}
	};

	class EmptyEventArgs final {};
	const EmptyEventArgs NO_ARGS;
}