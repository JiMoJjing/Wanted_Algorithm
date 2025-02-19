#include <iostream>
#include <queue>
#include <string>

// 미로 탐색 예제.
// 위치 구조체.
struct Location
{
	Location(int row = 0, int col = 0)
		: row(row), col(col)
	{

	}

	int operator[](int num)
	{
		if (num == 0)
		{
			return row;
		}
		else if (num == 1)
		{
			return col;
		}
		else
		{
			return 0;
		}
	}

	int row;
	int col;
};

// 맵 선언.
int mazeSize = 0;
char startMark;
char destinationMark;

std::vector<std::vector<char>> map;

// 이동하려는 위치가 이동 가능한 위치인지 확인하는 함수.
bool IsValid(int row, int col)
{
	// Out of Index 검사.
	if (row < 0 || row >= mazeSize || col < 0 || col >= mazeSize)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == destinationMark;
}

// 맵 출력 및시작 위치 검색 함수.
void FindStartLocation(int& row, int& col)
{
	for (int ix = 0; ix < mazeSize; ++ix)
	{
		for (int jx = 0; jx < mazeSize; ++jx)
		{
			// 시작 위치를 찾았으면 전달한 파라미터에 출력.
			if (map[ix][jx] == startMark)
			{
				row = ix;
				col = jx;
			}
			// 맵 출력.
			std::cout << map[ix][jx] << " ";
		}

		// 개행.
		std::cout << "\n";
	}
}

void EscapeMaze()
{
	// 시작 위치.
	int row = 0;
	int col = 0;

	FindStartLocation(row, col);

	// 탐색에 사용 할 큐 선언.
	std::queue<Location> queue;
	
	// 시작 위치 추가.
	queue.emplace(Location(row, col));

	// 탐색.
	while (!queue.empty())
	{
		// 큐에서 가장 앞에 위치한 데이터를 추출.
		Location current = queue.front();
		queue.pop();

		// 탐색한 위치 출력.
		std::cout << "(" << current.row << "," << current.col << ") ";

		// 탈출 조건 (목표 지점에 도달한 경우).
		if (map[current.row][current.col] == destinationMark)
		{
			std::cout << "\n 미로 탐색 성공. \n";
			return;
		}

		// 방문한 위치를 다른 문자로 설정.
		map[current.row][current.col] = '.';
		

		// 탐색할 위치를 큐에 넣기.
		// 상 / 하 / 좌 / 우.
		if (IsValid(current.row - 1, current.col))
		{
			queue.emplace(Location(current.row - 1, current.col));
		}
		if (IsValid(current.row + 1, current.col))
		{
			queue.emplace(Location(current.row + 1, current.col));
		}
		if (IsValid(current.row, current.col - 1))
		{
			queue.emplace(Location(current.row, current.col - 1));
		}
		if (IsValid(current.row, current.col + 1))
		{
			queue.emplace(Location(current.row, current.col + 1));
		}
	}
}

bool ParseMap(const std::string& fileDirectory)
{
	FILE* file = nullptr;
	fopen_s(&file, fileDirectory.c_str(), "r");

	if (file == nullptr)
	{
		std::cout << " 파일 오픈에 실패했습니다. \n";
		return false;
	}
	
	char buffer[2048];
	fgets(buffer, 2048, file);
	// 맵 크기 설정 및 시작/ 목적 지점 문자 설정 ( char는 크기 전달해야함 ).
	sscanf_s(buffer, "size: %d start: %c destination: %c", &mazeSize, &startMark, 1, &destinationMark, 1);

	//줄 데이터 저장을 위한 임시 배열 선언.
	std::vector<std::string> lines;
	lines.reserve(mazeSize);

	// 첫 줄을 제외한 나머지 데이터를 한 번에 읽기.
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

	// 나머지 읽기.
	fread_s(buffer, 2048, size, sizeof(char), file);

	// 라인 파싱.
	char* context = nullptr;
	char* splitString = strtok_s(buffer, "\n", &context);
	if (splitString)
	{
		lines.emplace_back(splitString);
	}

	while (context)
	{
		splitString = strtok_s(nullptr, "\n", &context);
		if (!splitString)
		{
			break;
		}

		lines.emplace_back(splitString);
	}

	// 라인별 파싱 데이터 저장.
	std::vector<char> line;
	line.reserve(mazeSize);

	// 라인 배열을 순회하면서 파싱 처리.
	for (auto& item : lines)
	{
		// 첫 칸 처리.
		context = nullptr;
		splitString = strtok_s(const_cast<char*>(item.c_str()), ",", &context);
		if (splitString)
		{
			line.emplace_back(splitString[0]);
		}

		while (context)
		{
			splitString = strtok_s(nullptr, ",", &context);
			if (!splitString)
			{
				break;
			}
			line.emplace_back(splitString[0]);
		}
		map.emplace_back(line);
		line.clear();
	}
	fclose(file);

	return true;
}

int main()
{
	if (ParseMap("../Assets/BFSMap.txt"))
	{
		EscapeMaze();
	}

	std::cin.get();
}