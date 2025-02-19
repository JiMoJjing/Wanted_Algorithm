#include <iostream>
#include <stack>
#include <vector>

// 미로 탐색에 사용 할 좌표 구조체.
struct Location2D
{
	Location2D(int row = 0, int col = 0)
		: row(row), col(col)
	{

	}

	// 행.
	int row;

	// 열.
	int col;
};

// 맵 배열.
int mapSize = 0;
std::vector<std::vector<char>> map;

// 이동 가능 여부 판단 함수.
bool IsValidLocation(int row, int col)
{
	if (row >= mapSize || col >= mapSize || row < 0 || col < 0)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == 'x';
}

// 시작 지점 검색 함수.
void FindStartLocation(int& row, int& col)
{ 
	for (int ix = 0; ix < mapSize; ++ix)
	{
		for (int jx = 0; jx < mapSize; ++jx)
		{
			if (map[ix][jx] == 'e')
			{
				row = ix;
				col = jx;
				return;
			}
		}
	}
}

bool ParseMap(const char* path)
{
	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "r");

	// 파일 열기 성공 확인.
	if (file == nullptr)
	{
		std::cout << "파일 읽기 실패.\n";
		return false;
	}

	char buffer[256] = { };
	char* context = nullptr;

	// 첫 줄 읽기.
	if (!fgets(buffer, 256, file))
	{
		fclose(file);
		return false;
	}

	// 맵 사이즈 설정.
	sscanf_s(buffer, "size %d", &mapSize);

	std::vector<char> line;
	line.reserve(mapSize);

	while (fgets(buffer, 256, file))
	{
		char* context = nullptr;
		char* splitString = strtok_s(buffer, ",", &context);

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

// 미로 탈출 함수.
void EscapeMaze()
{
	for (int ix = 0; ix < mapSize; ++ix)
	{
		for (int jx = 0; jx < mapSize; ++jx)
		{
			std::cout << map[ix][jx] << " ";
		}
		std::cout << "\n";
	}

	// 위치 저장할 변수 선언.
	int row = 0, col = 0;

	// 탐색 시작을 위해 시작 위치 찾기.
	FindStartLocation(row, col);

	// DFS를 위한 스택 선언.
	std::stack<Location2D> stack;

	// 처음 시작 위치를 스택에 삽입.
	stack.push(Location2D(row, col));

	// 미로 탐색.
	while (!stack.empty())
	{
		// 현재 위치 반환.
		Location2D current = stack.top();
		stack.pop();

		// 탐색 위치 출력.
		std::cout << "(" << current.row << "," << current.col << ")\n";

		// 탈출 조건 확인.
		if (map[current.row][current.col] == 'x')
		{
			std::cout << " \n 미로 탐색 성공 \n";
			return;
		}

		// 방문한 현재 위치는 재방문 방지를 위해 표시.
		map[current.row][current.col] = '.';

		if (IsValidLocation(current.row - 1, current.col))
		{
			stack.push(Location2D(current.row - 1, current.col));
		}
		if (IsValidLocation(current.row + 1, current.col))
		{
			stack.push(Location2D(current.row + 1, current.col));
		}
		if (IsValidLocation(current.row, current.col + 1))
		{
			stack.push(Location2D(current.row, current.col + 1));
		}
		if (IsValidLocation(current.row, current.col - 1))
		{
			stack.push(Location2D(current.row, current.col - 1));
		}
	}

	std::cout << "\n 미로 탐색 실패 \n";
}

// Depth First Search
int main()
{
	if (ParseMap("../Assets/Map.txt"))
	{
		EscapeMaze();
	}

	std::cin.get();
}