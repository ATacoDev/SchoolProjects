def dfs(graph, start, goal):
    frontier = [(start, [])]  # Stack
    visited = set()  # Visited nodes

    while frontier: # - Until frontier is empty
        node, path = frontier.pop()

        if node == goal:  # Check if goal is reached
            return path + [node] # Return solution path if found; used later for calculating cost

        visited.add(node)  # Mark node as explored

        for neighbor, cost in reversed(graph.get(node, {}).items()): # Reversed for readability; before would display forntier as [C, B, A]
            if neighbor not in visited:
                frontier.append((neighbor, path + [node]))

        print("Node expanded:", node)
        print("Frontier:", [n for n, _ in reversed(frontier)])

    return None  # Goal not reachable


# Figure 1
figure1 = dict(
    S = dict(A = 3, B = 1, C = 8),
    A = dict(D = 3, E = 7, G = 15),
    B = dict(G = 20),
    C = dict(G = 5))

graph = figure1
startFigure1 = 'S'
goalFigure1 = 'G'
solution = dfs(graph, startFigure1, goalFigure1)

if solution:
    print("Solution Path (DFS):", solution)
    totalCost = sum(graph[node][solution[i+1]] for i, node in enumerate(solution[:-1])) # Sum cost for solution path; disregard costs after G
    print("Total Cost (DFS):", totalCost)
else:
    print("Goal not reachable.")


# Code cell 3: Define the graph data of Romania Roadmap and call the search funciton you implemented in Cell 1
# DFS - Stack
# BFS - Queue

roadmap = dict(
    Arad=dict(Zerind=75, Sibiu=140, Timisoara=118),
    Bucharest=dict(Urziceni=85, Pitesti=101, Giurgiu=90, Fagaras=211),
    Craiova=dict(Drobeta=120, Rimnicu=146, Pitesti=138),
    Drobeta=dict(Craiova=120, Mehadia=75),
    Eforie=dict(Hirsova=86),
    Fagaras=dict(Bucharest=211, Sibiu=99),
    Giurgiu=dict(Bucharest=90),
    Hirsova=dict(Eforie=86, Urziceni=98),
    Iasi=dict(Vaslui=92, Neamt=87),
    Lugoj=dict(Timisoara=111, Mehadia=70),
    Mehadia=dict(Lugoj=70, Drobeta=75),
    Neamt=dict(Iasi=87),
    Oradea=dict(Zerind=71, Sibiu=151),
    Pitesti=dict(Bucharest=101, Rimnicu=97, Craiova=138),
    Rimnicu=dict(Craiova=146, Sibiu=80, Pitesti=97),
    Sibiu=dict(Arad=140, Fagaras=99, Oradea=151, Rimnicu=80),
    Timisoara=dict(Arad=118,Lugoj=111),
    Vaslui=dict(Iasi=92, Urziceni=98),
    Urziceni=dict(Vaslui=142, Bucharest=85, Hirsova=98),
    Zerind=dict(Arad=75, Oradea=71))

startRoadmap = 'Arad'
goalRoadmap = 'Bucharest'
graph = roadmap
solution = dfs(graph, startRoadmap, goalRoadmap)

if solution:
    print("Solution Path (DFS):", solution)
    totalCost = sum(graph[node][solution[i+1]] for i, node in enumerate(solution[:-1])) # Sum cost for solution path; disregard costs after G
    print("Total Path Cost (DFS):", totalCost)
else:
    print("Goal state is not reachable from the start state.")

# Code cell 4: additional setup for A* search and call the A* search function

# A*

heuristics = {
    'Arad': 15,
    'Bucharest': 0,
    'Craiova': 160,
    'Drobeta': 242,
    'Eforie': 161,
    'Fagaras': 176,
    'Giurgiu': 77,
    'Hirsova': 151,
    'Iasi': 226,
    'Lugoj': 244,
    'Mehadia': 241,
    'Neamt': 234,
    'Oradea': 380,
    'Pitesti': 100,
    'Rimnicu': 193,
    'Sibiu': 253,
    'Timisoara': 329,
    'Urzinceni': 80,
    'Vaslui': 199,
    'Zerind': 374
}

def astar(graph, start, goal, heuristic):
    frontier = [(0, start)]
    came_from = {}  # Parent pointers
    totalCost = {start: 0}  # Cost from start to each node
    visited = []  # Visited Nodes

    while frontier:
        frontier.sort()  # Sort by cost
        current_cost, current_node = frontier.pop(0)
        visited.append(current_node)  # Mark as visited
        print("Expanded node:", current_node)
        print()

        if current_node == goal:
            path = []
            while current_node in came_from:
                path.insert(0, current_node)
                current_node = came_from[current_node]
            totalCost = totalCost[goal]
            return path, totalCost

        for next_node, edgeCost in graph[current_node].items():
            aStarCost = totalCost[current_node] + edgeCost
            if next_node not in totalCost or aStarCost < totalCost[next_node]: # If not a visited node, or less than previously recorded cost, update astar value
                totalCost[next_node] = aStarCost
                priority = aStarCost + heuristic[next_node]
                frontier.append((priority, next_node))
                came_from[next_node] = current_node

        print("Frontier:", frontier)

    print("Goal not found")
    return None, visited, None

startA = 'Arad'
goalA = 'Bucharest'

path = astar(roadmap, startA, goalA, heuristics)
print(f"Path solution: {path}")
