class Curriculum:
    def __init__(self):
        self.graph = {}

    def add_prerequisite(self, prereq, course):
        if prereq not in self.graph:
            self.graph[prereq] = []

        if course not in self.graph:
            self.graph[course] = []

        self.graph[prereq].append(course)

    def dfs(self, node, visited, order):
        visited.add(node)

        for neighbor in self.graph[node]:
            if neighbor not in visited:
                self.dfs(neighbor, visited, order)

        order.append(node)

    def topological_sort(self):
        visited = set()
        order = []

        for node in self.graph:
            if node not in visited:
                self.dfs(node, visited, order)

        order.reverse()
        return order

    def critical_course(self):
        critical = None
        max_degree = -1

        for course in self.graph:
            degree = len(self.graph[course])

            if degree > max_degree:
                max_degree = degree
                critical = course

        return critical, max_degree


c = Curriculum()

c.add_prerequisite("Programming", "AED I")
c.add_prerequisite("AED I", "AED II")
c.add_prerequisite("AED I", "OOP")
c.add_prerequisite("AED I", "Algorithms")
c.add_prerequisite("AED II", "Graphs")

print("Topological Order:")

for course in c.topological_sort():
    print(course)

critical, degree = c.critical_course()

print()
print(
    f'[ALERT] "{critical}" is the most critical course '
    f"with {degree} direct dependencies."
)
