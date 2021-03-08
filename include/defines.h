#pragma once
#define DEGTORAD     (PI/180.0)
#define RADTODEG     (180.0/PI)

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

const float PTM_RATIO = 80.0f; 
const double PI = 3.14159265;

#define PTM(x) ( x/PTM_RATIO )