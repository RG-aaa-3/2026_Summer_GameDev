#pragma once
#include <string>
#include<vector>
#include "Vector2.h"
#include "Vector2F.h"


class AsoUtility
{
public:
	//•¶š—ñ‚Ì•ªŠ„
	static std::vector<std::string> Split(std::string& line, char delimiter);
	//•ûŒü
	enum class DIRECTION {
		E_DIR_UP,					//ã
		E_DIR_RIGHT,				//‰E
		E_DIR_DOWN,					//‰º
		E_DIR_LEFT,					//¶

		E_DIR_MAX,
	};

	//lÌŒÜ“ü
	static int Round(float val);
	static Vector2 Round(Vector2F val);


private:

};

