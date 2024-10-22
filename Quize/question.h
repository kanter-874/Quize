#pragma once
#include<string>
#include<vector>

//–â‘è•¶‚Æ“š‚¦‚ğ‚Ü‚Æ‚ß‚é\‘¢‘Ì
struct Question
{
	std::string q;	 //–â‘è•¶
	std::string a;	 //“š‚¦
};

//–â‘è‚Ì”z—ñ‚ğ•\‚·Œ^
using QuestionList = std::vector<Question>;
