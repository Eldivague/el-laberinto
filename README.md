
# 🐀 Laberinto con DFS

## 🧩 ¿Qué creé?

Un sistema en **C++** que genera laberintos dinámicos y los resuelve automáticamente. El usuario elige el tamaño y la computadora aplica lógica recursiva para encontrar la salida.

## 🛠️ Generación del Laberinto

1. **Matriz Sólida:** Comienzo con un bloque lleno de muros (`#`).
2. **Túnel Seguro:** Garantizo una ruta de escape desde `(0,0)` hasta el final mediante un camino aleatorio forzado.
3. **Azar:** Rompo un 40% de los muros restantes para crear bifurcaciones y rutas alternativas.

## 🧠 Algoritmo de Resolución

Utilicé **DFS (Búsqueda en Profundidad)** con **Backtracking**:

* El agente explora cada dirección marcando con `*`.
* Si se bloquea, la recursividad "vuelve atrás" y **borra** el rastro.
* Solo se mantienen los asteriscos que conectan el inicio con la meta.

## ⏱️ Hallazgos y Mejoras

* **Hallazgo:** La lógica es increíblemente rápida (menos de 1ms), pero el tiempo de impresión en consola (`cout`) es el verdadero cuello de botella.
* **Lección:** El paso por referencia (`&`) es vital; sin él, el algoritmo trabaja sobre copias y no sobre el mapa real.
* **Próxima vez:** Implementaría **BFS** para encontrar siempre la ruta más corta, ya que el DFS encuentra la primera que ve, no necesariamente la mejor.
