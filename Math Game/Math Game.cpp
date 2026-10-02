#include<iostream>
#include<cstdlib>
#include<climits>
using namespace std;

enum enLevel { Easy = 1, Mid, Hard, MixedLevel };
enum enOperation { Add = 1, Substract, Multiply, Divide, MixedOperations };


struct stQuestion
{
	enLevel QuesLevel;
	enOperation QuesOperation;
	short UpperLine = 0;
	short LowerLine = 0;
	int ComputerAnswer = 0;
	int UserAnswer = 0;
	short QuesNumber = 0;
	bool IsCorrect = true;
};
struct stQuizz
{
	stQuestion QuestionList[100];
	enLevel QuizzLevel;
	enOperation QuizzOperation;
	short QuestionsNumber = 0;
	short CorrectAnswers = 0;
	short WrongAnswers = 0;
	bool IsPassed = true;
};

int RandomNumberInRange(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

float ReadUserAnswer()
{
	float Answer;
	cin >> Answer;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Enter Valid Number please : ";
		cin >> Answer;
	}

	return Answer;
}
short ReadNumberOfQuestions()
{
	short num = 0;
	cout << "How Many Question you wanna answer: ";
	cin >> num;
	return num;
}

enLevel ReadQuizzLevel()
{
	short number = 0;
	do
	{
		cout << "\nChoose Level of Quizz : [1]Easy ,[2]Middle ,[3]Hard ,[4]Mixed : ";
		cin >> number;
	} while (number < 1 || number>4);

	return enLevel(number);
}

enOperation ReadQuizzOperation()
{
	short number = 0;
	do
	{
		cout << "\nChoose Quizz operation : [1]Add ,[2]substract ,[3]multiply ,[4]Divide ,[5]Mixed : ";
		cin >> number;
	} while (number < 1 || number>5);
	return enOperation(number);
}

float MiniCalculator(stQuestion& Question)
{

	switch (Question.QuesOperation)
	{
	case enOperation::Add:
		return Question.UpperLine + Question.LowerLine;
		break;
	case enOperation::Substract:
		return Question.UpperLine - Question.LowerLine;
		break;
	case enOperation::Multiply:
		return Question.UpperLine * Question.LowerLine;
		break;
	case enOperation::Divide:
		return Question.UpperLine / Question.LowerLine;
		break;
	}
	return 0;
}


char ReturnOperSymbol(enOperation op)
{
	switch (op)
	{
	case enOperation::Add:
		return '+';
		break;
	case enOperation::Substract:
		return '-';
		break;
	case  enOperation::Multiply:
		return '*';
		break;
	case enOperation::Divide:
		return'/';
		break;
	}
}
string OperationName(enOperation op)
{
	switch (op)
	{
	case enOperation::Add:
		return "Addition\n";
		break;
	case enOperation::Substract:
		return"Subtraction\n";
		break;
	case enOperation::Multiply:
		return"Multiplication\n";
		break;
	case enOperation::Divide:
		return "Division\n";
		break;
	case enOperation::MixedOperations:
		return "Mixed\n";
		break;
	}
}


string LevelName(enLevel level)
{
	switch (level)
	{
	case enLevel::Easy:
		return"Easy\n";
		break;
	case enLevel::Mid:
		return "Middle Level\n";
		break;
	case enLevel::Hard:
		return "Hard\n";
		break;
	case enLevel::MixedLevel:
		return "Mixed Levels\n";
		break;
	}
}



void DisplayQuestion(stQuestion Question)
{
	cout << "\nQuestion ( " << Question.QuesNumber + 1 << " )" << endl;
	cout << "------------------------------------------------------\n";
	cout << Question.UpperLine << endl;
	cout << Question.LowerLine;
	cout << "\t" << ReturnOperSymbol(Question.QuesOperation);
	cout << "\n----------------\n";
}
void SetScreenForCorrectAnswer(bool win)
{
	if (win)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << '\a';
	}
}
void CorrectQuestionAnswer(stQuizz& Quizz, stQuestion Question)
{
	if (Question.UserAnswer != Question.ComputerAnswer)
	{
		cout << "\nSorry ,Right answer is : " << Question.ComputerAnswer << endl;
		Question.IsCorrect = false;
		SetScreenForCorrectAnswer(Question.IsCorrect);
		Quizz.WrongAnswers++;
	}
	else
	{
		cout << "\nGreat Job\n";
		Question.IsCorrect = true;
		SetScreenForCorrectAnswer(Question.IsCorrect);
		Quizz.CorrectAnswers++;
	}
}

void AskAndCorrect(stQuizz& Quizz)
{
	for (int i = 0; i < Quizz.QuestionsNumber; i++)
	{
		Quizz.QuestionList[i].QuesNumber = i;
		DisplayQuestion(Quizz.QuestionList[i]);
		Quizz.QuestionList[i].UserAnswer = ReadUserAnswer();
		CorrectQuestionAnswer(Quizz, Quizz.QuestionList[i]);
	}
}


stQuestion GenerateQuestion(enOperation op, enLevel level)
{
	stQuestion Question;

	if (op == enOperation::MixedOperations)
	{
		op = enOperation(RandomNumberInRange(1, 4));
	}

	if (level == enLevel::MixedLevel)
	{
		level = enLevel(RandomNumberInRange(1, 3));
	}

	Question.QuesOperation = op;
	Question.QuesLevel = level;

	switch (level)
	{

	case enLevel::Easy:

		Question.UpperLine = RandomNumberInRange(30, 50);
		Question.LowerLine = RandomNumberInRange(1, 30);
		Question.ComputerAnswer = MiniCalculator(Question);
		return Question;
		break;

	case enLevel::Mid:

		Question.UpperLine = RandomNumberInRange(100, 300);
		Question.LowerLine = RandomNumberInRange(50, 100);
		Question.ComputerAnswer = MiniCalculator(Question);
		return Question;
		break;

	case enLevel::Hard:

		Question.UpperLine = RandomNumberInRange(300, 700);
		Question.LowerLine = RandomNumberInRange(100, 300);
		Question.ComputerAnswer = MiniCalculator(Question);
		return Question;
		break;

	}
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (int i = 0; i < Quizz.QuestionsNumber; i++)
	{
		Quizz.QuestionList[i] = GenerateQuestion(Quizz.QuizzOperation, Quizz.QuizzLevel);

	}

}

bool IsPassedQuizz(stQuizz Quizz)
{
	return Quizz.CorrectAnswers > Quizz.WrongAnswers;
}

void PrintFinalResult(stQuizz Quizz)
{
	cout << "\n\t\t\t==============================================\n";
	cout << "\t\t\t\t\t +++GameOver+++";
	cout << "\n\t\t\t==============================================\n";
	cout << "\t\t\t\tQuizz Result: " << (Quizz.IsPassed ? "Passed\n" : "Failed\n");
	cout << "\n\t\t\t\tQuizz Level : " << LevelName(Quizz.QuizzLevel);
	cout << "\n\t\t\t\tQuizz Operation: " << OperationName(Quizz.QuizzOperation);
	cout << "\n\t\t\t\tNumber of Questions: " << Quizz.QuestionsNumber;
	cout << "\n\n\t\t\t\tNumber of correct answers: " << Quizz.CorrectAnswers;
	cout << "\n\n\t\t\t\tNumber of wrong answers: " << Quizz.WrongAnswers;
	cout << "\n\n\t\t\t==============================================";
}
void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.QuestionsNumber = ReadNumberOfQuestions();
	Quizz.QuizzLevel = ReadQuizzLevel();
	Quizz.QuizzOperation = ReadQuizzOperation();
	GenerateQuizzQuestions(Quizz);
	AskAndCorrect(Quizz);
	Quizz.IsPassed = IsPassedQuizz(Quizz);
	PrintFinalResult(Quizz);
}


void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		system("cls");
		system("color 0F");
		PlayMathGame();
		cout << "\n\n\t\t\tDo you wanna play again? ";
		cin >> PlayAgain;

	} while (tolower(PlayAgain) == 'y');

}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}