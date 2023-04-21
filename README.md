# MPI Tutorium

## Installation unter Windows mit WSL (nur ein mal nötig)

1. [VScode installieren](https://code.visualstudio.com/download)
2. [WSL/VM installieren](https://bookstack.kamaux.de/books/it-tools/page/wsl-installieren)
3. [Projekt klonen und MPI installieren](https://bookstack.kamaux.de/books/oth/page/ca-linuxwsl-vorbereiten)

## Installation unter Linux (nur ein mal nötig)

1. [VScode installieren](https://code.visualstudio.com/download)
2. [Projekt klonen und MPI installieren](https://bookstack.kamaux.de/books/oth/page/ca-linuxwsl-vorbereiten)

## Installation auf CIP-Pool (jedes mal nötig)

1. [MPI und VScode installieren, Projekt klonen](https://bookstack.kamaux.de/books/oth/page/ca-cip-pool-vm-vorbereiten)

## Projekte bauen und ausführen

Entweder kann das Skript `serve.sh` ausgeführt werden oder manuell die Befehle ausführen.

script:

```bash
chmod +x serve.sh
./serve.sh mpi_hello_world.c
```

die serve.sh startet standardmäßig 4 Prozesse, kann aber auch als 2. Parameter angegeben werden:

```bash
./serve.sh mpi_hello_world.c 4
```
