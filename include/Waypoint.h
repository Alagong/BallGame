#pragma once
class Waypoint
{
public:
	Waypoint(int id,float x, float y, int nextWaypointID = 0, float newSpeed = 0, bool usingAltWaypoint = false,
		int altWaypointID = 0) : 
	  m_id(id), m_posX(x), m_posY(y), m_nextWaypointID(nextWaypointID), 
		  m_newSpeed(newSpeed), m_usingAltWaypoint(usingAltWaypoint),
		  m_altWaypointID(altWaypointID)
	{};

	const int GetID() {return m_id;}
	const float GetX() {return m_posX;}
	const float GetY() {return m_posY;}
	const int GetNextWaypointID() { if(m_usingAltWaypoint) return m_altWaypointID; return m_nextWaypointID; }
	const float GetNewSpeed() {return m_newSpeed;}
	void ToggleAltWaypoint() {m_usingAltWaypoint = !m_usingAltWaypoint;}
	
private:
	int m_id;
	float m_posX;
	float m_posY;
	int m_nextWaypointID;
	int m_altWaypointID;
	float m_newSpeed;
	bool m_usingAltWaypoint;

};