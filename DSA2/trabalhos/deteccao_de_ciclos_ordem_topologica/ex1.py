class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, u, v):
        if u not in self.graph:
            self.graph[u] = []

        if v not in self.graph:
            self.graph[v] = []

        self.graph[u].append(v)

    def dfs(self, node, color):
        color[node] = 1  # gray

        for neighbor in self.graph[node]:

            if color[neighbor] == 1:
                return True

            if color[neighbor] == 0:
                if self.dfs(neighbor, color):
                    return True

        color[node] = 2  # black
        return False

    def has_cycle(self):
        color = {}

        for node in self.graph:
            color[node] = 0

        for node in self.graph:
            if color[node] == 0:
                if self.dfs(node, color):
                    return True

        return False


g = Graph()

g.add_edge("A", "B")
g.add_edge("B", "C")
g.add_edge("C", "A")

if g.has_cycle():
    print("[ERROR: CIRCULAR DEPENDENCY DETECTED]")
else:
    print("[INSTALLATION APPROVED]")
