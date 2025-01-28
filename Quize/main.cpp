#include "question.h"
#include "exam_japanese.h"
#include "exam_english.h"
#include "exam_science.h"
#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;



//最大公約数を求める
int gcd(int a, int b)
{
	//余りが0になったときの除数を返す
	while (b)
	{
		int r = a % b;
		a = b; //除数を次の被除数にする
		b = r; //あまりを次の除数にする
	}
	return a;
}

int main()
{
	vector<Question> questions(3);

	random_device rd;
	mt19937 rand(rd());

	int score = 0;
	int miss = 0;

	//掛け算
	int x = uniform_int_distribution<>(1, 30)(rand);
	int y = uniform_int_distribution<>(1, 20)(rand);
	questions[0].q = to_string(x) + "x" + to_string(y) + "の答えは？\n";
	questions[0].a = to_string(x * y);

	//割り算
	x = uniform_int_distribution<>(1, 30)(rand);
	y = uniform_int_distribution<>(1, 20)(rand);
	questions[1].q = to_string(x * y) + "÷" + to_string(y) + "の答えは？\n";
	questions[1].a = to_string(x);

	//複雑な式
	x = uniform_int_distribution<>(1, 100)(rand);
	y = uniform_int_distribution<>(1, 10)(rand);
	int z = uniform_int_distribution<>(1, 10)(rand);
	int w = uniform_int_distribution<>(1, 10)(rand);
	questions[2].q = to_string(x) + "-(" + to_string(y * w) + " + " + to_string(z * w) + ")÷" + to_string(w) + "の答えは？\n";
	questions[2].a = to_string(x - (y + z));

	// 三角形の面積
	int base = uniform_int_distribution<>(1, 10)(rand); // 底辺
	int height = uniform_int_distribution<>(1, 5)(rand) * 2; // 高さ
	double triangle_area = static_cast<double>(base * height) / 2.0; // 面積
	questions.push_back({ "面積を求めよ。底辺 " + to_string(base) + " cm、高さ " + to_string(height) + " cm の三角形。\n", to_string(triangle_area) });

	// 円錐の体積
	int radius = uniform_int_distribution<>(1, 10)(rand); // 半径
	int cone_height = uniform_int_distribution<>(1, 5)(rand) * 3; // 高さ
	double cone_volume = static_cast<double>(radius * radius * cone_height) / 3.0; // 体積
	questions.push_back({ "底面の半径 " + to_string(radius) + " cm、高さ " + to_string(cone_height) + " cm の円錐がある。\nこの円錐の体積を Xπ cm³ とする。X の値を求めよ。\n", to_string(cone_volume) });

	// 球の体積
	int sphere_radius = uniform_int_distribution<>(1, 5)(rand) * 3; // 半径
	double sphere_volume = static_cast<double>(sphere_radius * sphere_radius * sphere_radius * 4) / 3.0; // 体積
	questions.push_back({ "半径 " + to_string(sphere_radius) + " cm の球がある。\nこの球の体積を Xπ cm³ とする。X の値を求めよ。\n", to_string(sphere_volume) });

	//サイコロの確率
	x = uniform_int_distribution<>(1, 5)(rand);
	y = uniform_int_distribution<>(1, 6 - x)(rand);
	z = gcd(y + 1, 6);
	questions.push_back({
		"サイコロを１こ振って、" + to_string(x) + "から" + to_string(x + y) + "が出る確率を求めよ。",
		to_string((y + 1) / z) + "/" + to_string(6 / z) });

	//順列
	x = uniform_int_distribution<>(3, 7)(rand);
	y = uniform_int_distribution<>(1, x)(rand);
	z = 1;
	for (int i = 0; i < y; i++)
	{
		z *= x - i;
	}
	questions.push_back({
		to_string(x) + "人のうち" + to_string(y) + "人を選んで並べる方法は何通りあるか？",
		to_string(z) });

	//組み合わせ
	x = uniform_int_distribution<>(3, 6)(rand);
	y = uniform_int_distribution<>(1, x)(rand);
	z = 1;
	for (int i = 0; i < y; i++)
	{
		z *= x - i;
	}

	for (int i = 0; i < y; i++)
	{
		z /= x - i;
	}
	questions.push_back({
		to_string(x) + "人のうち" + to_string(y) + "人を選ぶ組み合わせは何通りあるか？",
		to_string(z) });

	cout << "[リクルート試験対策クイズ]\n";

	cout << "教科を選んでください\n1=数学\n2=国語\n3=英語\n4=理科\n";
	int subject;
	cin >> subject;
	if (subject == 2)
	{
		questions = CreateKanjiExam();
		const QuestionList idiomExam = CreateIdiomExam();
		questions.insert(questions.end(), idiomExam.begin(), idiomExam.end());
		QuestionList homophoneExam = CreateHomophoneExam();
		questions.insert(questions.end(), homophoneExam.begin(), homophoneExam.end());
		QuestionList antonymExam = CreateAntonymExam();
		questions.insert(questions.end(), antonymExam.begin(), antonymExam.end());
		QuestionList synonymExam = CreateSynonymExam();
		questions.insert(questions.end(), synonymExam.begin(), synonymExam.end());
		QuestionList phraseExam = CreateEnglishPhraseExam();
		questions.insert(questions.end(), phraseExam.begin(), phraseExam.end());
	}

	else if (subject == 3)
	{
		questions = CreateEnglishWordExam();
	}

	else if (subject == 4)
	{
		questions = CreatePhysicsExam();
	}

	for (const auto& e : questions)
	{
		cout << e.q << "\n";
		string answer;
		cin >> answer;
		if (answer == e.a)
		{
			cout << "正解!\n";
			score++;
		}
		else
		{
			cout << "間違い！正解は" << e.a << "\n";
			miss++;
		}
	}//for questions

	if ((score + miss) / 3 <= 10)
	{
		cout << score + miss << "問中" << score << "点だよ まだまだだね" << endl;
	}

	else if ((score + miss) / 3 > 10 && ((score + miss) / 3 < 20 || (score + miss) / 3 < 7))
	{
		cout << score + miss << "問中" << score << "点だよ 結構やるやん" << endl;
	}

	else
	{
		cout << score + miss << "問中" << score << "点だよ 完璧やな" << endl;
	}
}