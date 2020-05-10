#include "BalbinoPCH.h"
#include "Time.h"
#include <algorithm>

float Balbino::BTime::DeltaTime()
{
	return Get().UnscaledDeltaTime() * Get().TimeScale();
}

float Balbino::BTime::FixedDeltaTime()
{
	return Get().UnscaledFixedDeltaTime() * Get().TimeScale();
}

float Balbino::BTime::FixedTime()
{
	return Get().m_FixedTime;
}

float Balbino::BTime::MaximumDeltaTime()
{
	return Get().m_MaximumDeltaTime;
}

float Balbino::BTime::Time()
{
	return Get().m_Time;
}

float Balbino::BTime::TimeScale()
{
	return Get().m_TimeScale;
}

float Balbino::BTime::TimeSinceLevelLoad()
{
	return Get().m_TimeSinceLevelLoad;
}

float Balbino::BTime::UnscaledFixedDeltaTime()
{
	return Get().m_FixedDeltaTime;
}

float Balbino::BTime::UnscaledFixedTime()
{
	return Get().m_UnscaledFixedTime;
}

float Balbino::BTime::UnscaledDeltaTime()
{
	return ( std::min )( Get().m_DeltaTime, Get().MaximumDeltaTime() );
}

float Balbino::BTime::UnscaledTime()
{
	return Get().m_UnscaledTime;
}

void Balbino::BTime::SetDT( float dt )
{
	m_DeltaTime = dt;
	m_Time += dt * m_TimeScale;
	m_UnscaledTime += dt;
	m_TimeSinceLevelLoad += dt;
}

void Balbino::BTime::SetTS( float ts )
{
	m_TimeScale = ts;
}

void Balbino::BTime::UpdateFT()
{
	m_FixedTime += m_FixedDeltaTime * m_TimeScale;
	m_UnscaledFixedTime += m_FixedDeltaTime;
}

void Balbino::BTime::LoadLevel()
{
	m_TimeSinceLevelLoad = 0;
}
