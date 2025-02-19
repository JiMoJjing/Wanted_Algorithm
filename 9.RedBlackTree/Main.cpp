#include <iostream>
#include "RedBlackTree.h"
#include <Windows.h>
#include <vector>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


// 명령 구분을 위한 열거형.
enum class Command
{
	None,
	Insert,
	Delete,
	Find,
	Print,
	Quit
};

// 화면 지우는 함수.
void ClearScreen()
{
	system("cls");
}

// 입력 처리 함수.
void ProcessCommandInput(int& commandInput)
{
	// 입력 처리.
	char inputBuffer[100] = { };

	while (true)
	{
		std::cout << "명령 숫자를 입력하세요.\n";
		std::cout << "(1) 노드 추가, (2) 노드 삭제, (3) 노드 검색, (4) 노드 출력, (5) 종료 \n";
		std::cin >> inputBuffer;

		// atoi : ascii to integer.
		if (commandInput = atoi(inputBuffer))
		{
			if (commandInput <= (int)Command::None || commandInput > (int)Command::Quit)
			{
				ClearScreen();
				std::cout << "오류: 잘못된 숫자를 입력했습니다.\n";
				continue;
			}

			break;
		}

		// 예외 처리.
		ClearScreen();
		std::cout << "오류: 명령은 숫자만 입력해야 합니다.\n";

	}
}

// 파라미터 입력 처리 함수.
void ProcessParamInput(int& param)
{
	// 입력 처리 버퍼.
	char inputBuffer[100] = { };

	// 입력 처리 루프.

	while (true)
	{
		std::cout << " 파라미터를 입력하세요 ( 1 - 200 ).\n";
		std::cin >> inputBuffer;

		// 검증.
		if (param = atoi(inputBuffer))
		{
			if (param < 1 || param > 200)
			{
				ClearScreen();
				std::cout << "오류: 파라미터는 1 - 200 사이의 숫자만 입력해야 합니다.\n";
				continue;
			}

			break;
		}

		// 예외 처리.
		ClearScreen();
		std::cout << "오류: 파라미터는 숫자만 입력해야 합니다.\n";
	}
}

// 명령 처리 함수.
void ProcessCommand(int commandInput, RedBlackTree& tree)
{
	// 입력 값을 열거형으로 변환.
	Command command = (Command)commandInput;

	// 출력.
	if (command == Command::Print)
	{
		ClearScreen();
		tree.Print(0, 0);

		return;
	}

	// 프로그램 종료.
	if (command == Command::Quit)
	{
		return;
	}

	// 1, 2, 3 명령 처리 ( 파라미터 입력이 추가로 필요함 ).
	int param = 0;
	ProcessParamInput(param);

	// 1, 2, 3 명령 처리.
	switch (command)
	{
		// 노드 추가.
		case Command::Insert:
		{
			ClearScreen();
			tree.Insert(param);
		} 
		break;

		case Command::Delete:
		{
			ClearScreen();
			tree.Remove(param);
		} 
		break;

		case Command::Find:
		{
			ClearScreen();

			// 검색.
			Node* result = nullptr;
			if (!tree.Find(param, &result))
			{
				// 검색 실패.
				std::cout << "노드를 찾지 못했습니다. (검색 값: " << param << ") \n";
				return;
			}
			
			// 노드 색상에 따른 콘솔 텍스트 색상 설정.
			if (result->GetColor() == Color::Red)
			{
				SetTextColor(TextColor::Red);
			}
			else
			{
				SetTextColor(TextColor::White);
			}

			// 검색 결과 출력.
			std::cout
				<< "검색된 노드: " << result->Data()
				<< "(Color: " << result->ColorString()
				<< ")\n";

			// 콘솔 텍스트 복구.
			SetTextColor(TextColor::White);
		} 
		break;
	}
}

void Initialization(const char* directory, RedBlackTree& tree)
{
	FILE* file = nullptr;
	fopen_s(&file, directory, "rb");

	if (file == nullptr)
	{
		std::cout << " 파일 읽기 실패. \n";
		return;
	}

	// 파일의 현재 위치 저장.
	auto currentPosition = ftell(file);
	
	// 마지막 위치로 이동.
	fseek(file, 0, SEEK_END);
	
	// 마지막 위치 저장.
	auto endPosition = ftell(file);

	// 크기 계산.
	int size = (int)(endPosition - currentPosition);

	// rewind.
	fseek(file, currentPosition, SEEK_SET);

	char buffer[512] = { };
	fread_s(buffer, 512, size, sizeof(char), file);

	char* readStr = nullptr;
	char* context = nullptr;
	readStr = strtok_s(buffer, ",", &context);
	tree.Insert(atoi(readStr));

	while (context)
	{
		readStr = strtok_s(nullptr, ",", &context);
		if (readStr == nullptr)
		{
			break;
		}
		tree.Insert(atoi(readStr));
	}

	fclose(file);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 레드 블랙 트리 생성.
	RedBlackTree tree;
	
	Initialization("../Assets/InitData.txt", tree);

	while (true)
	{
		// 명령 입력 처리.
		int commandInput = 0;
		ProcessCommandInput(commandInput);

		// 명령 처리.
		ProcessCommand(commandInput, tree);

		if ((Command)commandInput == Command::Quit)
		{
			break;
		}
	}
}