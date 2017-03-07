#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
extern char *environ[];

char *readLine(void);
char **parser(char *input);
int execute(char **args);

int main(int argc, char *argv[])
{
  
  char *input;
  char **argv;
  int check = 1;

  do {
    printf("BillsShell> "); //prints prompt
    input = readLine(); //reads user input
    argv = parser(input); //parses user input
    check = execute(args); //executes input, looks for "0" return

    free(input);
    free(args);
  } while (check);
  
  return 0;
}

char *readLine(void)
{
  char *input = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&input, &bufsize, stdin);
  return input;
}

char **parser(char *input)
{
  int argc = 0;
  char *argv[100];
  char *token;

  if (!argv) {
    printf("allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(input, " \t\r\n\a"); //takes users inputs, breakes them down into individual strings
  
  while (token != NULL) {
    argv[argc] = token;
    argc++;

    }//adds string to array, increases spot if need be

    token = strtok(NULL, " \t\r\n\a");
  
  argv[argc] = NULL; //sets last spot to null
  return argv;

}

int execute(char **args)
{
  pid_t pid, wpid;
  int check;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (exec(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("bad fork");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &check, WUNTRACED);
    } while (!WIFEXITED(check) && !WIFSIGNALED(check));
  }

  return 1;
}
