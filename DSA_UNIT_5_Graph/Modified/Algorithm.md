# Algorithm

1.Start.

2.Store the terminal names and the travel-time matrix.

3.Display the list of terminals.

4.Read the source terminal.

5.Set dist[source] = 0, dist[others] = INF, visited[all] = false, and parent[all] = -1.

6.Repeat n - 1 times:
  a. Pick the unvisited terminal u with the smallest dist.
  b. Mark u as visited.
  c. For each unvisited neighbour v of u: if dist[u] + weight(u,v) < dist[v], then set dist[v] = dist[u] 
  + weight(u,v) and parent[v] = u.
    
7.For each terminal, trace the path using parent[] and display the complete path with the time of each 
  hop, and the total time. (Mod B)
  
8.Ask: “Change source?” If yes, go to step 3 and recalculate. (Mod A) If no, go to step 9.

9.Stop.
