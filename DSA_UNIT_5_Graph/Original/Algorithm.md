# Algorithm

1.Start.

2.Read the number of terminals n and their names.

3.Read the number of routes, and for each route read terminal 1, terminal 2 and travel time. 
  Store it in the matrix (both directions).
  
4.Read the source and destination terminals.

5.Set dist[source] = 0, dist[all others] = INF, visited[all] = false, and parent[all] = -1.

6.Repeat n - 1 times:
  a. Pick the unvisited terminal u with the smallest dist.
  b. Mark u as visited.
  c. For every neighbour v of u that is unvisited and connected: if dist[u] + weight(u,v) < dist[v], 
     then set dist[v] = dist[u] + weight(u,v) and parent[v] = u.
     
7.If dist[destination] is INF, print “No route”. Otherwise follow parent[] back from the destination 
  to the source to get the path.
  
8.Print the path and dist[destination] as the total travel time.

9.Stop.
