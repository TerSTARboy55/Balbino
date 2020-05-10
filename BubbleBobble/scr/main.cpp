#include "pch.h"
#include <vld.h>
namespace BubbleBobble
{
	class BubbleBobbleGame: public Balbino::Application
	{
	public:
		BubbleBobbleGame() = default;

		virtual void LoadGame() const override;
	};

	void BubbleBobbleGame::LoadGame() const
	{
		Balbino::SceneManager::Get().CreateScene( "First Scene" );

		int* pI = new int[64];
		(void*) pI;
		for( int i = 0; i < 64; i++ )
		{
			pI[i] = rand();
		}
	}
}

Balbino::Application* Balbino::CreateApplication()
{
	return new BubbleBobble::BubbleBobbleGame{};
}