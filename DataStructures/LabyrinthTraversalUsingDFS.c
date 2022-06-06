#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_SIZE 50
#define MAZE_FILE "maze.txt"
#define NUMBER_OF_APPLES 10
#define PATH_CHARACTER '*'
// #define TERMINAL_CLEAR "clear" // for ubuntu
#define TERMINAL_CLEAR "cls" // for windows
#define SLEEP 100000         // 1000000 to pause for a second

typedef struct
{
    int x, y;
} coordinates;

typedef struct
{
    coordinates start;
    coordinates finish;
    int intTable[MAX_SIZE][MAX_SIZE];
    char printTable[MAX_SIZE][MAX_SIZE];
    int rows, cols;
} maze;

maze *initMaze()
{
    maze *m;
    if ((m = (maze *)malloc(sizeof(maze))) == NULL)
    {
        printf("Error: malloc failed\n");
        exit(-1);
    }
    return m;
}

void inputMaze(maze *m)
{
    int i, j;
    FILE *file;
    if ((file = fopen(MAZE_FILE, "r")) == NULL)
    {
        printf("Error: Could not open file %s\n", MAZE_FILE);
        exit(-1);
    }

    i = 0;
    while (!feof(file))
    {
        fscanf(file, "%[^\n]\n", m->printTable[i]);

        j = 0;
        while (m->printTable[i][j] != '\0')
        {
            if (m->printTable[i][j] == 'b')
            {
                // get coordinates of starting point
                m->start.x = i;
                m->start.y = j;
            }
            else if (m->printTable[i][j] == 'c')
            {
                // get coordinates of finishing point
                m->finish.x = i;
                m->finish.y = j;
            }
            // marks walls as 0 and hallways as 1
            (m->intTable)[i][j] = !(m->printTable[i][j] == '+' || m->printTable[i][j] == '|' || m->printTable[i][j] == '-');
            j++;
        }
        i++;
    }
    fclose(file);

    m->rows = i;
    m->cols = j;
}

void putApples(maze *m)
{
    int i, j;
    int tempX, tempY;

    for (i = 0; i < NUMBER_OF_APPLES; i++)
    {
        do
        {
            tempX = rand() % m->rows;
            tempY = rand() % m->cols;
        } while ((m->intTable)[tempX][tempY] == 2 || (m->intTable)[tempX][tempY] == 0);

        (m->intTable)[tempX][tempY] = 2;
        (m->printTable)[tempX][tempY] = 'o';
    }
}

void dfs(maze *m, int currentX, int currentY, int *point);
void print(maze *m, int point);

int main()
{
    maze *m = initMaze();
    int i, j;
    int point = 0;
    char trash;

    srand(time(NULL));

    inputMaze(m);
    putApples(m);

    print(m, 0);
    printf("\nPress ENTER key to start.");
    scanf("%c", &trash);

    dfs(m, m->start.x, m->start.y, &point);

    return 0;
}

void dfs(maze *m, int currentX, int currentY, int *point)
{
    coordinates temp;
    static int isEndOfRoad;

    if (m->intTable[currentX][currentY] == 0 || m->intTable[currentX][currentY] == 10)
        return;

    if (currentX == m->finish.x && currentY == m->finish.y)
    {
        m->printTable[currentX][currentY] = '#';
        print(m, *point);
        printf("\n\n%33s\n", "PATH FOUND SUCCESSFULLY!");
        printf("%17s %5d", "Score:", *point);
        exit(0);
    }
    else if (currentX == m->start.x && currentY == m->start.y)
        m->printTable[currentX][currentY] = '#';
    else
        m->printTable[currentX][currentY] = PATH_CHARACTER;

    if (m->intTable[currentX][currentY] == 2)
        *point += 10;

    m->intTable[currentX][currentY] = 10;
    print(m, *point);
    isEndOfRoad = 1;

    dfs(m, currentX + 1, currentY, point);
    dfs(m, currentX, currentY - 1, point);
    dfs(m, currentX - 1, currentY, point);
    dfs(m, currentX, currentY + 1, point);

    if (isEndOfRoad)
    {
        *point -= 5;
        isEndOfRoad = 0;
    }

    m->printTable[currentX][currentY] = ' ';
    print(m, *point);
}

void print(maze *m, int point)
{
    int i, j;

    usleep(SLEEP);
    system(TERMINAL_CLEAR);
    printf("%20s %6d\n\n", "TOTAL POINTS:", point);

    for (i = 0; i < m->rows; i++)
    {
        for (j = 0; j < m->cols; j++)
            printf(" %c", m->printTable[i][j]);
        printf("\n");
    }
}