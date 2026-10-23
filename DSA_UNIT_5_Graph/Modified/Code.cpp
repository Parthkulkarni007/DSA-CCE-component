#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define N 5
#define INF 9999

string name[N] = {"Central", "Market", "College", "Station", "Airport"};

// travel time in minutes (0 = no direct route)
int graph[N][N] = {
    {0, 4, 2, 0, 0},
    {4, 0, 1, 5, 0},
    {2, 1, 0, 8, 10},
    {0, 5, 8, 0, 3},
    {0, 0, 10, 3, 0}
};

int dist[N], parent[N];
bool visited[N];

int minDistance()
{
    int min = INF, index = -1;
    for (int i = 0; i < N; i++)
    {
        if (visited[i] == false && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int src)
{
    for (int i = 0; i < N; i++)
    {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < N - 1; count++)
    {
        int u = minDistance();
        if (u == -1)
            break;
        visited[u] = true;

        for (int v = 0; v < N; v++)
        {
            if (visited[v] == false && graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

// Modification B: complete path with time of each hop
void printPath(int j)
{
    if (parent[j] == -1)
    {
        cout << name[j];
        return;
    }
    printPath(parent[j]);
    cout << " -(" << graph[parent[j]][j] << ")-> " << name[j];
}

void showAllPaths(int src)
{
    cout << "\nShortest paths from " << name[src] << ":\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < N; i++)
    {
        if (i == src)
            continue;
        cout << "To " << name[i] << " : ";
        if (dist[i] == INF)
        {
            cout << "No route" << endl;
        }
        else
        {
            printPath(i);
            cout << "  | Total = " << dist[i] << " min" << endl;
        }
    }
}

int main()
{
    int src, choice;

    do
    {
        cout << "\n===== Bus Terminals =====" << endl;
        for (int i = 0; i < N; i++)
            cout << i + 1 << ". " << name[i] << endl;

        cout << "\nEnter source terminal number (1-" << N << "): ";
        cin >> src;

        if (src < 1 || src > N)
        {
            cout << "Invalid source terminal." << endl;
        }
        else
        {
            src--;
            dijkstra(src);       // recalculated for every new source (Mod A)
            showAllPaths(src);   // full path to every terminal (Mod B)
        }

        cout << "\nChange source terminal? (1 = Yes, 0 = No): ";
        cin >> choice;

    } while (choice == 1);

    system("pause");
    return 0;
}
