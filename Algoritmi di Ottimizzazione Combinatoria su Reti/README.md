# 🚚🛸 PDS-TSP — Parallel Drone Scheduling Traveling Salesman Problem

**Progetto AOCR** · Metodo esatto (MILP + Gurobi) vs. euristica *Truck First, Drone Second*

**Autori:** A. D'Angiolella · A. Iardino · C. Capone

![Camion e drone per le consegne](images/21-delivery.png)

---

## 📑 Indice

1. [Cos'è il PDS-TSP](#1--cosè-il-pds-tsp)
2. [Formulazione del problema (MILP)](#2--formulazione-del-problema-milp)
3. [Risoluzione esatta con Gurobi](#3--risoluzione-esatta-con-gurobi)
4. [Algoritmo euristico: Truck First, Drone Second](#4--algoritmo-euristico-truck-first-drone-second)
5. [Implementazione dell'euristica](#5--implementazione-delleuristica)
6. [Risultati dell'euristica](#6--risultati-delleuristica)
7. [Confronto esatto vs. approssimato](#7--confronto-esatto-vs-approssimato)

---

## 1. 🧭 Cos'è il PDS-TSP

Il **PDS-TSP** è un'evoluzione avanzata del classico *Problema del Commesso Viaggiatore* (TSP), progettata per la **logistica dell'ultimo miglio**.

![Concetto PDS-TSP](images/01-pds-tsp-concetto.png)

### Flotta ibrida e dinamiche di routing

| Veicolo | Comportamento |
|---|---|
| 🚚 **Camion** | Percorso continuo e sequenziale tra i clienti (routing tradizionale). |
| 🛸 **Droni** (multipli) | Operano **in parallelo**: volo diretto verso il cliente e ritorno immediato al deposito. |

### 🎯 Obiettivo

Minimizzare il **makespan**, cioè il tempo totale necessario affinché tutti i clienti siano serviti e l'ultimo veicolo rientri alla base.

### 💡 Valore aggiunto

Massimizzare il parallelismo delle operazioni per abbattere i tempi di consegna, assegnando strategicamente **i nodi isolati ai droni** e **i percorsi densi al camion**.

---

## 2. 📐 Formulazione del problema (MILP)

![TSP](images/02-tsp-intro.png)

### Insiemi e parametri

| Simbolo | Significato |
|---|---|
| `C` | Insieme di tutti i clienti |
| `C' ⊆ C` | Clienti le cui consegne rispettano i limiti operativi del drone |
| `C'' ⊆ C'` | Clienti idonei che rientrano entro il raggio d'azione del drone dal deposito |
| `N₀ = {0, 1, …, c}` | Nodi da cui un veicolo può partire, incluso il deposito di partenza (nodo 0) |
| `N₊ = {1, 2, …, c+1}` | Nodi che un veicolo può visitare, incluso il deposito di arrivo (nodo c+1) |
| `V` | Insieme dei droni identici a disposizione |
| `τᵢⱼ` | Tempo di percorrenza stradale del camion dal nodo *i* al nodo *j* |
| `τ'₀,ᵢ + τ'ᵢ,c+1` | Tempo di volo (andata e ritorno) del drone dal deposito al cliente *i* |

### Variabili decisionali

| Variabile | Descrizione |
|---|---|
| `x̂ᵢⱼ ∈ {0,1}` | 1 se il camion viaggia dal nodo *i ∈ N₀* al nodo *j ∈ N₊* (con *i ≠ j*), 0 altrimenti |
| `ŷᵢ,ᵥ ∈ {0,1}` | 1 se il cliente *i ∈ C''* è servito dal drone *v ∈ V*, 0 altrimenti |
| `ûᵢ` | Variabile continua ausiliaria per l'eliminazione dei subtour del camion, con `1 ≤ ûᵢ ≤ c+2` |
| `z` | Tempo di completamento massimo (**makespan**) per il rientro di tutti i veicoli al deposito |

### Funzione obiettivo e vincoli

![Formulazione MILP](images/03-formulazione-milp.png)

| Eq. | Significato |
|---|---|
| **(33)** | Funzione obiettivo: minimizzare `z`. |
| **(34)** | `z` deve essere ≥ al tempo totale accumulato dal camion lungo il suo tragitto. |
| **(35)** | `z` deve essere ≥ alla somma dei tempi di volo di tutti i viaggi (andata e ritorno dal deposito) effettuati da ciascun drone `v ∈ V`. |
| **(36)** | Ogni cliente `j` è servito **una sola volta**: o dal camion, o da uno dei droni. |
| **(37)** | Il camion parte dal nodo origine (nodo 0) esattamente una volta. |
| **(38)** | Il camion rientra alla destinazione (nodo c+1) al termine delle consegne. |
| **(39)** | Continuità del percorso: se il veicolo entra in un nodo cliente, deve uscirne verso la destinazione successiva. |
| **(40)** | Impedisce la formazione di cicli disconnessi dal deposito (**vincolo MTZ**). |
| **(41)** | L'indice di sequenza di visita di ogni nodo è compreso tra 1 e `c+2`. |
| **(42)–(43)** | Dominio binario delle variabili `x̂` e `ŷ`. |

---

## 3. 🧮 Risoluzione esatta con Gurobi

Il modello MILP è stato implementato e risolto con **Gurobi**, prima su un'istanza da **20 nodi** e poi su una da **60 nodi**.

### Caso con 20 nodi

**Setup e parametri generali**

![Setup e parametri](images/04-setup-parametri.png)

**Generazione casuale dei nodi**

![Generazione nodi](images/05-generazione-nodi.png)

**Calcolo di distanze e matrici dei tempi**

![Matrici distanze e tempi](images/06-matrici-distanze-tempi.png)

**Costruzione del modello Gurobi**

![Modello Gurobi](images/07-modello-gurobi.png)

**Output**

![Output Gurobi](images/08-output-gurobi.png)

**Risultati dell'istanza a 20 nodi**

![Risultati 20 nodi](images/09-risultati-20-nodi.png)

**Visualizzazione grafica delle rotte**

![Rotte 20 nodi](images/10-rotte-20-nodi.png)

| Metrica | Valore |
|---|---|
| Makespan ottimo | **128.66 min** |
| Tempo di calcolo Gurobi | 1.6250 s |
| Tempo camion | 128.66 min |
| Tempo Drone 1 | 117.51 min |
| Tempo Drone 2 | 53.25 min |

### Caso con 60 nodi

![Rotte 60 nodi - metodo esatto](images/11-rotte-60-nodi-esatto.png)

```text
============================================================
OTTIMO TROVATO! Makespan (Tempo rientro ultimo veicolo): 190.61 min
============================================================
Tempo di calcolo Gurobi: 475.4030 secondi

--- PERCORSO DEL CAMION ---
Camion: Nodo 0 -> Nodo 53 (Tempo: 7.08 min)
Camion: Nodo 53 -> Nodo 28 (Tempo: 2.90 min)
...
Camion: Nodo 48 -> Nodo 61 (Tempo: 9.22 min)
>> Tempo totale Camion: 190.61 min

--- ASSEGNAZIONI DEI DRONI ---
Drone 1 serve: Cliente 2 (27.96 min), Cliente 6 (21.75 min), Cliente 11 (29.46 min),
               Cliente 15 (26.43 min), Cliente 19 (14.12 min), Cliente 40 (13.56 min),
               Cliente 41 (20.39 min), Cliente 44 (29.45 min), Cliente 58 (5.85 min)
>> Tempo totale Drone 1: 188.96 min

Drone 2 serve: Cliente 8 (19.55 min), Cliente 14 (16.80 min), Cliente 17 (14.71 min),
               Cliente 22 (29.91 min), Cliente 35 (14.24 min), Cliente 38 (18.17 min),
               Cliente 50 (28.96 min), Cliente 52 (29.14 min), Cliente 60 (7.90 min)
>> Tempo totale Drone 2: 179.37 min
```

| Metrica | Valore |
|---|---|
| Makespan ottimo | **190.61 min** |
| Tempo di calcolo Gurobi | **475.40 s** (~8 min) |

---

## 4. 🧠 Algoritmo euristico: *Truck First, Drone Second*

L'esatto diventa rapidamente costoso al crescere dei nodi, quindi è stata sviluppata un'euristica costruttiva + miglioramento iterativo.

### Funzioni di servizio

- **`Solve_TSP`** — calcola il percorso del camion e il relativo tempo di viaggio con l'algoritmo costruttivo **Nearest Neighbor**.
- **`Solve_PMS`** — alloca i clienti alla flotta di droni e ne calcola il tempo di volo, risolvendo un problema di *Parallel Machine Scheduling* con la regola **LPT** (*Longest Processing Time*).

### Idea dell'algoritmo

L'algoritmo parte assegnando **tutti i clienti al camion** (*Truck First*) e calcola il makespan iniziale. Poi itera:

1. 🔄 **Simula** lo spostamento di ciascun cliente idoneo dal camion alla flotta di droni (*Drone Second*).
2. 📊 **Valuta** l'impatto di ogni spostamento sul makespan globale.
3. 🎯 **Seleziona** in modo greedy il cliente che garantisce la massima riduzione del makespan.
4. ✅ Se lo spostamento è vantaggioso, **aggiorna** le liste di assegnazione e ricalcola il makespan.

Il ciclo si ripete finché non è più possibile ottenere miglioramenti, restituendo la configurazione finale.

---

## 5. 💻 Implementazione dell'euristica

**Setup dell'euristica**

![Setup euristica](images/12-euristica-setup.png)

**Generazione dei nodi**

![Generazione nodi euristica](images/13-euristica-generazione-nodi.png)

**Funzioni matematiche e di servizio**

![Funzioni di servizio](images/14-euristica-funzioni-servizio.png)

**Moduli dell'euristica** (TSP e PMS)

![Modulo TSP](images/15-euristica-modulo-tsp.png)

![Modulo PMS](images/16-euristica-modulo-pms.png)

**Algoritmo Truck First, Drone Second**

![Algoritmo TF,DS](images/17-euristica-algoritmo-tfds.png)

**Risultati finali e output**

![Output euristica](images/18-euristica-output.png)

---

## 6. 📈 Risultati dell'euristica

### Istanza con 60 nodi

```text
--- INIZIO EURISTICA: TRUCK FIRST, DRONE SECOND ---

Stato Iniziale (100% al Camion) -> Camion: 279.36 min | Droni: 0.00 min | Makespan: 279.36 min

Iterazione  1: Spostato Cliente  8 ai Droni. Nuovo Makespan = 269.65 min
Iterazione  2: Spostato Cliente  2 ai Droni. Nuovo Makespan = 260.06 min
Iterazione  3: Spostato Cliente 22 ai Droni. Nuovo Makespan = 255.82 min
Iterazione  4: Spostato Cliente 14 ai Droni. Nuovo Makespan = 250.52 min
Iterazione  5: Spostato Cliente 38 ai Droni. Nuovo Makespan = 246.28 min
Iterazione  6: Spostato Cliente 44 ai Droni. Nuovo Makespan = 242.81 min
Iterazione  7: Spostato Cliente 49 ai Droni. Nuovo Makespan = 240.95 min
Iterazione  8: Spostato Cliente 53 ai Droni. Nuovo Makespan = 239.73 min
Iterazione  9: Spostato Cliente 15 ai Droni. Nuovo Makespan = 238.72 min
Iterazione 10: Spostato Cliente 35 ai Droni. Nuovo Makespan = 237.70 min
Iterazione 11: Spostato Cliente 40 ai Droni. Nuovo Makespan = 237.07 min
Iterazione 12: Spostato Cliente 19 ai Droni. Nuovo Makespan = 231.76 min
Iterazione 13: Spostato Cliente 41 ai Droni. Nuovo Makespan = 224.63 min
Iterazione 14: Spostato Cliente 11 ai Droni. Nuovo Makespan = 223.71 min
Iterazione 15: Spostato Cliente 27 ai Droni. Nuovo Makespan = 223.17 min
Iterazione 16: Spostato Cliente  6 ai Droni. Nuovo Makespan = 223.16 min
```

```text
============================================================
SOLUZIONE EURISTICA TROVATA in 0.2138 secondi!
============================================================
Makespan Globale Finale: 223.16 min

--- PERCORSO DEL CAMION FINALIZZATO ---
Il camion visita 44 clienti.
>> Tempo totale Camion: 223.16 min

--- ASSEGNAZIONI DEI DRONI FINALIZZATE ---
Drone 1 serve 8 clienti.  >> Tempo totale Drone 1: 172.76 min
Drone 2 serve 8 clienti.  >> Tempo totale Drone 2: 172.63 min
```

> ⚡ A differenza dell'algoritmo esatto, il tempo di calcolo dell'euristica è molto più basso: **~8 minuti vs 0.2138 secondi**.

**Visualizzazione grafica delle rotte (euristica, 60 nodi)**

![Rotte 60 nodi - euristica](images/19-rotte-60-nodi-euristica.png)

---

## 7. ⚖️ Confronto esatto vs. approssimato

Per quantificare il compromesso tra qualità della soluzione e sforzo computazionale è stato calcolato il **GAP**:

$$
\text{GAP}(\%) = \frac{|M_{ottimo} - M_{euristico}|}{|M_{ottimo}|} \times 100
$$

Sostituendo i valori (60 nodi):

$$
\text{GAP}(\%) = \frac{|190.61 - 223.16|}{|190.61|} \times 100 \approx 17.08\%
$$

| | Esatto (Gurobi) | Euristica TF,DS |
|---|---|---|
| Makespan | **190.61 min** | 223.16 min |
| Tempo di calcolo | 475.40 s | **0.21 s** |

A fronte di un GAP del **17.08%**, il tempo computazionale subisce un abbattimento del **99.95%** (da quasi 8 minuti a 0.21 secondi).

### Scalabilità: istanza con 120 nodi (solo euristica)

```text
--- INIZIO EURISTICA: TRUCK FIRST, DRONE SECOND ---

Stato Iniziale (100% al Camion) -> Camion: 402.00 min | Droni: 0.00 min | Makespan: 402.00 min

Iterazione  1: Spostato Cliente 95 ai Droni. Nuovo Makespan = 387.21 min
Iterazione  2: Spostato Cliente 83 ai Droni. Nuovo Makespan = 379.17 min
…
Iterazione 30: Spostato Cliente 49 ai Droni. Nuovo Makespan = 323.27 min
Iterazione 31: Spostato Cliente 80 ai Droni. Nuovo Makespan = 323.20 min
```

```text
============================================================
SOLUZIONE EURISTICA TROVATA in 2.2274 secondi!
============================================================
Makespan Globale Finale: 323.20 min

Il camion visita 89 clienti.   >> Tempo totale Camion: 323.20 min
Drone 1 serve 16 clienti.      >> Tempo totale Drone 1: 318.58 min
Drone 2 serve 15 clienti.      >> Tempo totale Drone 2: 316.29 min
```

![Rotte 120 nodi - euristica](images/20-rotte-120-nodi-euristica.png)

Con **120 nodi** l'euristica trova una soluzione in circa **2 secondi**.

---

<p align="center"><b>Grazie per l'attenzione! 🙏</b></p>
