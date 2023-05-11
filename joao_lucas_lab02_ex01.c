/*
Implemente um kernel em C que possua um escalonador de processos e suporte a definição de prioridades para os processos. O kernel deve ser capaz de criar e executar processos, alterar a prioridade de um processo em execução e finalizar processos. Além disso, implemente uma função para imprimir o estado atual do sistema, incluindo a lista de processos em execução e as prioridades de cada processo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define MAX_PROCESSES 10

typedef struct {
  int id;
  int priority;
  int time_left;
  int running;
} Process;

Process processes[MAX_PROCESSES];
int num_processes = 0;
int current_process = -1;

void create_process(int priority) {
  if (num_processes == MAX_PROCESSES) {
    printf("Maximum number of processes reached\n");
    return;
  }
  Process p = {num_processes, priority, 10, 0};
  processes[num_processes++] = p;
}

void set_priority(int id, int priority) {
  for (int i = 0; i < num_processes; i++) {
    if (processes[i].id == id) {
      processes[i].priority = priority;
      return;
    }
  }
  printf("Process not found\n");
}

void terminate_process(int id) {
  for (int i = 0; i < num_processes; i++) {
    if (processes[i].id == id) {
      processes[i].running = 0;
      return;
    }
  }
  printf("Process not found\n");
}

void schedule_next_process();