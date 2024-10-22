#include"exam_japanese.h"
#include"utility.h"
#include<random>
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
		{"市井", "しせい",		"人が多く集まって暮らす所、町" },
		{"捺印", "なついん",		"(署名と共に)印鑑を押すこと" },
		{"相殺", "そうさい",		"足し引きの結果、差がなくなること"},
		{"凡例", "はんれい",		"本や図表の初めに、使い方や約束事を箇条書きにしたもの"},
		{"約定", "やくじょう",	"約束をして決めること、契約"},
		{"必定", "ひつじょう",	"必ずそうなると決まっていること"},
		{"知己", "ちき",			"自分をよく理解してくれる人、親しい友人" },
		{"境内", "けいだい",		"神社、寺院の敷地内" },
		{"破綻", "はたん",		"物事がうまくいかなくなること" },
		{"拘泥", "こうでい",		"ひとつの考え方や行動にこだわること" },
		{"吟味", "ぎんみ",		"物事を念入りに調べること" },
		{"承る", "うけたまわる",	"敬意を持って受ける、「受ける」、「聞く」の謙譲語" },
		{"寸暇", "すんか",		"ほんの少しの空き時間" },
		{"弄ぶ", "もてあそぶ",	"手であれこれいじる、好き勝手に扱う" },
		{"灰汁", "あく",			"食べ物を煮たときに出る渋みやえぐみの成分、独特の個性" },
		{"潔い", "いさぎよい",	"思い切りがよい、道に反することがない" },
		{"借款", "しゃっかん",	"金銭を借ること、国同士の長期的な金銭の貸し借り" },
		{"培う", "つちかう",		"時間をかけて育てること" },
		{"赴く", "おもむく",		"ある場所、方向へ向かって行く" },
		{"疾病", "しっぺい",		"健康でない状態、病気" },
		{"老舗", "しにせ",		"先祖代々同じ商売をしている信用のある店" },
	};

	constexpr int quizeCount = 5;
	QuestionList questions;
	questions.reserve(quizeCount);
	const vector<int> indices = CreateRandomIndices(size(data));

	random_device rd;

	// 問題の種類を選ぶ
	int type = uniform_int_distribution<>(0, 1)(rd);
	if (type == 0) {
	// 漢字の読みを答える問題

	for (int i = 0; i < quizeCount; i++)
	{
		const auto& e = data[indices[i]];
		questions.push_back(
			{ "「" + string(e.kanji) + "」の読みをひらがなで答えよ", e.reading });
	}
	}
	else {
		// 正しい熟語を答える問題
		for (int i = 0; i < quizeCount; i++)
		{
		// 間違った番号をランダムに選ぶ
		const int correctIndex = indices[i];
		vector<int> answers = CreateWrongIndices(size(data), correctIndex);
				
		// ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 3)(rd);
		answers[correctNo - 1] = correctIndex;
		
		// 問題文を作成
		string s = "「" + string(data[correctIndex].meaning) +
		"」を意味する熟語の番号を選べ";
		for (int j = 0; j < 3; j++) {
			s += "\n  " + to_string(j + 1) + ":" + data[answers[j]].kanji;
		}
		questions.push_back({ s, to_string(correctNo) });
		}
			
	} // if type
	return questions;
}


//慣用句の意味を答える問題を作成する

QuestionList CreateIdiomExam()
{
	static const struct {
		const char* idiom;   // 慣用句
		const char* meaning; // 意味

	} data[] = {
		{ "気のおけない",				"気づかいがいらない" },
		{ "琴線に触れる",				"心から感動する" },
		{ "汚名をそそぐ",				"名誉を回復する" },
		{ "言質を取る",				"証拠となる言葉を聞き出す" },
		{ "糠(ぬか)に釘",			"効き目がない" },
		{ "二階から目薬",				"回りくどくて効果がない" },
		{ "意表をつく",				"予想外なことをして驚かせる" },
		{ "禁じざるを得ない",			"禁止しなくてはならない" },
		{ "虎の尾を踏む",				"進んで危険なことをする" },
		{ "目から鼻へ抜ける",			"頭の回転が早くて行動が素早い" },
		{ "情けは人の為(ため)ならず", "親切な行いは、いずれ自分のためになる" },
		{ "青菜に塩",				"元気を失っている様(さま)" },
		{ "他山の石",				"人の失敗を、自分の行いを正す参考にする" },
		{ "口を糊(のり)する",			"余裕のない貧しい生活をする" },
		{ "身命を賭す",				"命を投げ出す覚悟で努力する" },
	};
	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++)
	{
		// 間違った番号をランダムに選ぶ
		const int correctIndex = indices[i];
		vector<int> answers = CreateWrongIndices(size(data), correctIndex);

		// ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 3)(rd);
		answers[correctNo - 1] = correctIndex;

		// 問題文を作成
		string s = "「" + string(data[correctIndex].idiom) + "」の意味として正しい番号を選べ";

		for (int j = 0; j < 3; j++)
		{
			s += "\n  " + to_string(j + 1) + ":" + data[answers[j]].meaning;
		}
		questions.push_back({ s, to_string(correctNo) });
	}
		return questions;
}
