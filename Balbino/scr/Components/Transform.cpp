#include "BalbinoPCH.h"
#include "Transform.h"
#include "../GameObject/GameObject.h"
#include "../BinaryReaderWrider.h"
#include "../SceneManager.h"

#define _USE_MATH_DEFINES
#include <cmath> 

Balbino::Transform::Transform( const GameObject* const origine )

	:Component{ origine }
	, m_Position{ 0.f, 0.f, 0.f }
	, m_Rotation{ 0.f, 0.f, 0.f }
	, m_Scale{ 1.f, 1.f, 1.f }
	, m_pParent{}
	, m_pChilderen{}
{
}

Balbino::Transform::~Transform()
{
	m_pChilderen.clear();
}

void Balbino::Transform::Create()
{
	this->Component::Create();
}

void Balbino::Transform::Update()
{
	glm::mat4x4 translate{ {1.f, 0.f, 0.f, m_Position.x}, {0.f, 1.f, 0.f, -m_Position.y}, {0.f, 0.f, 1.f, m_Position.z}, {0.f, 0.f, 0.f, 1.f} };
	glm::mat4x4 scale{ {m_Scale.x, 0.f, 0.f, 0.f}, {0.f, m_Scale.y, 0.f, 0.f}, {0.f, 0.f, m_Scale.z, 0.f}, {0.f, 0.f, 0.f, 1.f} };
	glm::mat4x4 rotateX{ {cos( m_Rotation.x ), 0.f, sin( m_Rotation.x ), 0.f},{0.f, 1.f, 0.f, 0.f}, {-sin( m_Rotation.x ), 0, cos( m_Rotation.x ), 0.f},{0.f, 0.f, 0.f, 1.f} };
	glm::mat4x4 rotateY{ {1.f, 0.f, 0.f, 0.f},{0.f, cos( m_Rotation.y ), -sin( m_Rotation.y ), 0.f}, {0.f, sin( m_Rotation.y ), cos( m_Rotation.y ), 0.f},{0.f, 0.f, 0.f, 1.f} };
	glm::mat4x4 rotateZ{ {cos( m_Rotation.z ), -sin( m_Rotation.z ), 0.f, 0.f}, {sin( m_Rotation.z ), cos( m_Rotation.z ), 0.f, 0.f},{0.f, 0.f, 1.f, 0.f},{0.f, 0.f, 0.f, 1.f} };
	glm::mat4x4 rotate{ rotateX * rotateY * rotateZ };
	TransfomationMatrix = scale * rotate * translate;

	auto parent = m_pParent;
	if( parent )
	{
		TransfomationMatrix *= parent->TransfomationMatrix;
		//TransfomationMatrix = m_Parent->TransfomationMatrix * TransfomationMatrix;
	}
}

void Balbino::Transform::LateUpdate()
{

}

void Balbino::Transform::Draw() const
{
}
void Balbino::Transform::Save( std::ostream& file )
{
	std::string parrent{};
	if( m_pParent )
		parrent = m_pParent->GetGameObject()->GetName();
	else
		parrent = "\a";

	BinaryReadWrite::Write( file, int( ComponentList::Transform ) );
	BinaryReadWrite::Write( file, m_Position );
	BinaryReadWrite::Write( file, m_Rotation );
	BinaryReadWrite::Write( file, m_Scale );
		BinaryReadWrite::Write( file, parrent );
}
void Balbino::Transform::Load( std::istream& file )
{
	BinaryReadWrite::Read( file, m_Position );
	BinaryReadWrite::Read( file, m_Rotation );
	BinaryReadWrite::Read( file, m_Scale );
	std::string parentName{};
	BinaryReadWrite::Read( file, parentName );
	GameObject* parent = SceneManager::GetGameObjectByName( parentName );
	if( parent )
	{
		SetParrent( parent->GetComponent<Transform>() );
	}
}
void Balbino::Transform::SetParrent( Transform* parent )
{
	if( m_pParent == parent )
	{
		return;
	}
	if( m_pParent )
	{
		m_pParent->m_pChilderen.erase( std::remove( m_pParent->m_pChilderen.begin(), m_pParent->m_pChilderen.end(), this ) );
	}
	if( parent )
	{
		parent->m_pChilderen.push_back( this );
	}
	m_pParent = parent;
}
int Balbino::Transform::GetNumberOfChilderen()
{
	return int( m_pChilderen.size() );
}
const std::vector<Balbino::Transform*>& Balbino::Transform::GetChildren() const
{
	return m_pChilderen;
}
void Balbino::Transform::RemoveChild( int index )
{
	m_pChilderen.erase( m_pChilderen.begin() + index );
}
void Balbino::Transform::DestroyChilderen()
{
	for( Transform* childTransform : m_pChilderen )
	{
		childTransform->GetGameObject()->Destroy();
	}
	m_pChilderen.clear();
}
#ifdef _DEBUG
#include "../imgui-1.75/imgui.h"
void Balbino::Transform::DrawInpector()
{
	float xRot{ m_Rotation.x / float( M_PI ) * 180.f };
	float yRot{ m_Rotation.y / float( M_PI ) * 180.f };
	float zRot{ m_Rotation.z / float( M_PI ) * 180.f };

	ImGui::BeginChild( "Transform Component", ImVec2{ -1, 128 }, true );
	ImGui::Text( "Transformation" );
	ImGui::Separator();

	ImGui::PushItemWidth( 80 );
	ImGui::Text( "Position: " ); ImGui::SameLine();
	ImGui::Text( "X:" ); ImGui::SameLine(); ImGui::DragFloat( "##PosX", &m_Position.x, 0.1f ); ImGui::SameLine();
	ImGui::Text( "Y:" ); ImGui::SameLine(); ImGui::DragFloat( "##PosY", &m_Position.y, 0.1f ); ImGui::SameLine();
	ImGui::Text( "Z:" ); ImGui::SameLine(); ImGui::DragFloat( "##PosZ", &m_Position.z, 0.1f );
	ImGui::PopItemWidth();

	ImGui::PushItemWidth( 80 );
	ImGui::Text( "Rotation: " ); ImGui::SameLine();
	ImGui::Text( "X:" ); ImGui::SameLine(); ImGui::DragFloat( "##RotX", &xRot, 0.1f ); ImGui::SameLine();
	ImGui::Text( "Y:" ); ImGui::SameLine(); ImGui::DragFloat( "##RotY", &yRot, 0.1f ); ImGui::SameLine();
	ImGui::Text( "Z:" ); ImGui::SameLine(); ImGui::DragFloat( "##RotZ", &zRot, 0.1f );
	ImGui::PopItemWidth();

	ImGui::PushItemWidth( 80 );
	ImGui::Text( "Scale:    " ); ImGui::SameLine();
	ImGui::Text( "X:" ); ImGui::SameLine(); ImGui::DragFloat( "##ScaleX", &m_Scale.x, 0.1f ); ImGui::SameLine();
	ImGui::Text( "Y:" ); ImGui::SameLine(); ImGui::DragFloat( "##ScaleY", &m_Scale.y, 0.1f ); ImGui::SameLine();
	ImGui::Text( "Z:" ); ImGui::SameLine(); ImGui::DragFloat( "##SclaeZ", &m_Scale.z, 0.1f );
	ImGui::PopItemWidth();
	ImGui::EndChild();

	m_Rotation.x = xRot / 180.f * float( M_PI );
	m_Rotation.y = yRot / 180.f * float( M_PI );
	m_Rotation.z = zRot / 180.f * float( M_PI );
}
#endif
void Balbino::Transform::SetPosition( const float x, const float y, const float z )
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void Balbino::Transform::SetRotation( float x, float y, float z )
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

void Balbino::Transform::SetScale( float x, float y, float z )
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}
