#define MAX_LENGTH 30

typedef int solutionType [MAX_LENGTH];

typedef struct {
	solutionType solution;
	float energy;
} memberType;

/*  Параметры алгоритма */
#define INITIAL_TEMPERATURE 30.0
#define FINAL_TEMPERATURE   0.5
#define ALPHA               0.95
#define STEPS_PER_CHANGE    100

void tweakSolution ( memberType *member )
{
	int temp, x, y;
	
	x = getRand(MAX_LENGTH);
	do {
		y = getRand(MAX_LENGTH);
	} while (x == y);
	
	temp = member->solution[x];
	member->solution[x] = member->solution[y];
	member->solution[y] = temp;
}

void initializeSolution ( memberType *member )
{
	int i;
	/* Начальная инициация решения */
	for (i = 0 ; i < MAX_LENGTH ; i++) {
		member->solution[i] = i;
	}
	
	/* Изменение решения случайным образом*/
	for (i = 0; i < MAX_LENGTH ; i++) {
		tweakSoution( member );
	}

}

void computeEnergy ( memberType *member )
{
	int i, j, x, y, tempx, tempy;
	char board[MAX_LENGTH] [MAX_LENGTH];
	int conflicts;
	const int dx[4] = {-1, 1, -1, 1};
	const int dy[4] = {-1, 1, 1, -1};
	
	/* Стандартная функция очистки памяти */
	bzero( (void *)board, MAX_LENGTH * MAX_LENGTH );
	
	for (i = 0 ; i < MAX_LENGTH ; i ++) {
		board[i] [member->solution[i]] = 'Q';
	}
	
	/* Считает количество конфликтов для каждого ферзя */
	conflicts = 0;
	
	for (i = 0 ; i < MAX_LENGTH ; i++ ) {
		x = i; y = member->solution[i];
		/* Замечания: по условию кодировки конфликты по вертикали
		и горизонтали исключены */
		/* Проверяем диагонали */
		for (j = 0 ; j < 4 ; j++) {
			tempx = x ; tempy = y;
			while(1) {
				tempx += dx[j]; tempy += dy[j];
				if ((tempx < 0) || (tempx > MAX_LENGTH) || (tempy < 0) || (tempy > MAX_LENGTH)) break;
				if (board[tempx][tempy] == 'Q') conflicts++;
			}
		}
	}
	
	member->energy = (float)conflicts;
}

void copySolution ( memberType *dest, memberType *src )
{
	int i;
	
	for (i = 0 ; i < MAX_LENGTH ; i++ ) {
		dest->solution[i] = src->solution[i];
	}
	
	dest->energy = src->energy;
}