# TSP

## Compilar

```bash
gcc -O2 main.c -o main
gcc -O2 main_lowerbound.c -o main_lowerbound
```

## Rodar

```bash
./main tsp1_253.txt
```

ou

```bash
./main_lowerbound tsp1_253.txt
```

Troque `tsp1_253.txt` pelo arquivo que deseja testar.

## Visualizador

> **Aviso:** `visualizer.py` foi criado apenas para visualização. Ele não faz parte da implementação do TSP e não interfere nos algoritmos desenvolvidos em C. Funciona somente com o 'main.c'.

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install matplotlib networkx

python visualizer.py tsp1_253.txt
```

Para sair do ambiente:

```bash
deactivate
```
