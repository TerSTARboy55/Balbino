#pragma once
#include "Singleton.h"
#include "Struct.h"
#include "Core.h"
#pragma warning(push)
#pragma warning(disable:4251)

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace Balbino
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class BALBINO_API Renderer final: public Singleton<Renderer>
	{
	public:
		void Init( SDL_Window* window );
		void Draw() const;
		void Destroy();

		void RenderTexture( const Texture2D& texture, float x, float y ) const;
		void RenderTexture( const Texture2D& texture, float x, float y, float width, float height ) const;
		void RenderTexture( SDL_Texture* texture, float x, float y ) const;
		void RenderTexture( SDL_Texture* texture, float x, float y, float width, float height ) const;
		//void RenderTexture( const Texture2D& texture, const Color& overlay, float x, float y, float width, float height )const;
		//void RenderTexture( const Texture2D& texture, const Color& overlay, float x, float y )const;
		//void RenderTexture( const Color& color, const Texture2D& alphaMap, float x, float y )const;
		//void RenderTexture( const Color& color, const Texture2D& alphaMap, float x, float y, float width, float height )const;

		SDL_Renderer* GetSDLRenderer() const
		{
			return m_Renderer;
		}
	private:
		SDL_Renderer* m_Renderer{};
	};
}
#pragma warning(pop)