#include"exam_japanese.h"
using namespace std;

//漢字の読み取り問題を作成する
QuestionList CreateKanjiExam()
{
	static const struct
	{
		const char* kanji;		//漢字
		const char* reading;	//読み方
		const char* meaning;	//意味
	}data[] = {
		{"市井", "しせい", "人が多く集まって暮らす所、町" },
		{"捺印", "なついん", "(署名と共に)印鑑を押すこと" },
		{"相殺", "そうさい", "足し引きの結果、差がなくなること"},
		{"凡例", "はんれい", "本や図表の初めに、使い方や約束事を箇条書きにしたもの"},
		{"約定", "やくじょう", "約束をして決めること、契約"},
	};

	constexpr int quizeCount = 5;
	QuestionList questions;
	questions.reserve(quizeCount);
	for (int i = 0; i < quizeCount; i++)
	{
		const auto& e = data[i];
		questions.push_back(
			{ "「" + string(e.kanji) + "」の読みをひらがなで答えよ", e.reading });
	}

	return questions;
}