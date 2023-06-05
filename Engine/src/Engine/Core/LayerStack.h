#pragma once

#include <vector>
#include "Ptrs.h"
#include "Layer.h"

namespace Engine
{
	/**
	 * Contains app layers (now useless)
	 */
	class LayerStack
	{
	public:
		LayerStack() = default;

		~LayerStack() = default;

		void Push(Ref<Layer>& layer);

		void PushOverlay(Ref<Layer>& layer);

		void Remove(Ref<Layer>& layer);

		inline std::vector<Ref<Layer>>::const_iterator begin() const
		{
			return m_layers.cbegin();
		}

		inline std::vector<Ref<Layer>>::const_iterator end() const
		{
			return m_layers.end();
		}

	private :
		std::vector<Ref<Layer>> m_layers;
		size_t m_position{ 0 };
	};
}