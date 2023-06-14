/*
#pragma once

#include <cstdint>

namespace Engine
{
	struct Renderer2DData;

	class Renderer2D
	{
	public :
		static const uint32_t k_max_quads = 10000;
		static const uint32_t k_max_vertices = k_max_quads * 4;
		static const uint32_t k_max_indices = k_max_quads * 6;
		static const uint32_t k_max_texture_slot = 32;

		static void Init();

		static void ShutDown();

		static void BeginScene(const glm::mat4& projection, const glm::mat4& view);

		static void EndScene();

		static void FlushQuad();

		static void FlushCircle();

		static void FlushLine();

		static void DrawQuad(const glm::mat4& transformation,
		  const Ref <Texture>& texture, const glm::vec4& color, int32_t entity_id);

		static void DrawQuad(const glm::mat4& transformation, const Ref <SubTexture2D>& sub_texture,
		  const glm::vec4& color, int32_t entity_id);

		static void DrawCircle(const glm::mat4& transformation, const glm::vec4& color, float thickness, float fade,
		  int32_t entity_id);

		static void
		DrawLine(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, float thickness, int32_t entity_id);

		static void
		DrawRect(const glm::mat4& transformation, const glm::vec4& color, float thickness, int32_t entity_id);

		static void SetLineWidth(float width);

		*/
/*static Statistics GetStats();

		static void ResetStats();*//*


	private:
		static Renderer2DData* s_data;
	};
}
*/
