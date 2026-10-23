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

int minDistance(int dist[], bool visited[])
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

void printPath(int parent[], int j)
{
    if (parent[j] == -1)
    {
        cout << name[j];
        return;
    }
    printPath(parent, parent[j]);
    cout << " -> " << name[j];
}

void dijkstra(int src, int dest)
{
    int dist[N], parent[N];
    bool visited[N];

    for (int i = 0; i < N; i++)
    {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < N - 1; count++)
    {
        int u = minDistance(dist, visited);
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

    if (dist[dest] == INF)
    {
        cout << "\nNo route available." << endl;
        return;
    }

    cout << "\nShortest Path: ";
    printPath(parent, dest);
    cout << "\nTotal Travel Time: " << dist[dest] << " minutes" << endl;
}

int main()
{
    int src, dest;

    cout << "===== Bus Terminals =====" << endl;
    for (int i = 0; i < N; i++)
        cout << i + 1 << ". " << name[i] << endl;

    cout << "\nEnter source terminal number (1-" << N << "): ";
    cin >> src;
    cout << "Enter destination terminal number (1-" << N << "): ";
    cin >> dest;

    if (src < 1 || src > N || dest < 1 || dest > N)
    {
        cout << "\nInvalid terminal number." << endl;
    }
    else
    {
        dijkstra(src - 1, dest - 1);
    }

    system("pause");
    return 0;
}
