#include <isa.h>
#include "expr.h"
#include "watchpoint.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <memory/vaddr.h>
void cpu_exec(uint64_t);
int is_batch_mode();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  if(arg == NULL) {
    cpu_exec(1);
  }
  else {
    for(char *ch = arg; *ch; ch ++) assert(isdigit(*ch));
    cpu_exec(atoi(arg));
  }
  return 0;
}

static int cmd_info(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  if(arg == NULL) {
    cmd_help("info");
  }
  else if(arg[0] == 'r') {
    isa_reg_display();
  }
  else if(arg[0] == 'w') {
    panic("TODO");
  }
  else {
    cmd_help("info");
  }
  return 0;
}

static int cmd_x(char * args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  if(arg == NULL) {
    cmd_help("x");
  }
  else {
    int n = atoi(arg);
    arg = strtok(NULL, " ");
    paddr_t addr = atoi(arg);
    printf("%x: ", addr);
    for(int i = 0; i < n; i ++) {
      printf("\033[43;34m%x\033[0m ", vaddr_read(addr + i, 1));
    }
    printf("\n");
  }
  return 0;  
}

static int cmd_p(char * args) {
  /* extract the first argument */
  //char *arg = strtok(NULL, " ");
  return -1;  
}

static int cmd_w(char * args) {
  /* extract the first argument */
  //char *arg = strtok(NULL, " ");
  return -1;  
}

static int cmd_d(char * args) {
  /* extract the first argument */
  //char *arg = strtok(NULL, " ");
  return -1;  
}

static struct {
  char *name;
  char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "si [N], execute N instructions, N is 1 by default", cmd_si },
  { "info", "info r/w, show all registers or watchpoints", cmd_info },
  { "x", "x N EXP, print N bytes begin at [EXP]", cmd_x },
  { "p", "p EXP, print the value of EXP", cmd_p },
  { "w", "w EXP, create watchpoint for EXP", cmd_w },
  { "d", "d N, delete Nth watchpoint", cmd_d },

  /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void ui_mainloop() {
  if (is_batch_mode()) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " "); // ????????????????????????????????????????????????
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) { // ???????????????????????????????????????????????????
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; } // ??????????????????????????????????????????????????????????????????????????????ui?????????
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}
