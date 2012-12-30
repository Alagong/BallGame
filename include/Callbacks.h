#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/dynamics/b2Fixture.h>
// This callback finds the closest hit. Polygon 0 is filtered.
class RayCastFirstBodyCallback : public b2RayCastCallback
{
public:
	RayCastFirstBodyCallback()
	{
		m_hit = false;
	}

	float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
	{
		m_bodyHit = fixture->GetBody();

		m_hit = true;
		m_point = point;
		m_normal = normal;
		return 0;
	}
	
	bool m_hit;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	b2Body* m_bodyHit;
};