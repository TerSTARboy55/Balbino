#pragma once
#include "Component.h"
#include <box2d/box2d.h>

namespace Balbino
{
	class Collider2D;
	//https://docs.unity3d.com/ScriptReference/Rigidbody.html
	//https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_dynamics.html#autotoc_md55
	class Rigidbody2D : public Component
	{
	public:
		Rigidbody2D( const GameObject* const origine );


		Rigidbody2D( const Rigidbody2D& ) = delete;
		Rigidbody2D( Rigidbody2D&& ) = delete;
		Rigidbody2D& operator=( const Rigidbody2D& ) = delete;
		Rigidbody2D& operator=( Rigidbody2D&& ) = delete;

		virtual ~Rigidbody2D() = default;

		virtual void Create() override;
		virtual void FixedUpdate()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Draw() const override;

		virtual void Save( std::ostream& file ) override;
		virtual void Load( std::istream& file ) override;

		bool SweepTest( const Balbino::Vector3& direction, Balbino::RaycastHit& hitInfo, float maxDistance = std::numeric_limits<float>::infinity() );
		Balbino::RaycastHit& SweepTestAll( const Balbino::Vector3& direction, int& hitInfoSize, float maxDistance = std::numeric_limits<float>::infinity() );

#ifdef _DEBUG
		virtual void DrawInpector();
#endif // _DEBUG
	private:
		bool m_IsKinematic;
		bool m_FreezRotation;
		bool m_UseGravity;
		float m_AngularDrag;
		float m_Drag;
		float m_Mass;
		float m_MaxAngularVelocity;
		Balbino::Vector3 m_AngularVelocity;
		Balbino::Vector3 m_CenterOfMass;
		Balbino::Vector3 m_Velocity;
		Balbino::RaycastHit m_Hits[128];

		b2BodyDef m_BodyDef;
		b2Body* m_pBody;
	};
}