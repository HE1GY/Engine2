#pragma once

#include <functional>

/**
 * Subscribe member function
 */
#define SUB_MEM(func) [this](auto arg) {return func(arg);}


namespace Engine
{
	template<typename T>
	class Event
	{
	public:
		using Callback = std::function<bool(const T&)>;

		Event() = default;

		~Event() = default;

		void Invoke(const T& payload) const;

		void AddCallback(const Callback& cb);

		void RemoveCallback(const Callback& cb);

	private:
		std::vector<Callback> m_callbacks;
	};

	template<typename T>
	void Event<T>::Invoke(const T& payload) const
	{
		for (const auto& callback: m_callbacks)
		{
			bool handled = callback(payload);
			if (handled)break;
		}
	}

	template<typename T>
	void Event<T>::RemoveCallback(const Event::Callback& cb)
	{
		m_callbacks.erase(std::find(m_callbacks.begin(), m_callbacks.end(), cb));
	}

	template<typename T>
	void Event<T>::AddCallback(const Event::Callback& cb)
	{
		m_callbacks.push_back(cb);
	}

}