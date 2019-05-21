/*
    Cigarette Smokers Problem

    cf. Patil, Suhas: Limitations and Capabilities of Dijkstra's Semaphore Primitives for 
        Coordination among Processes, Technical Report, MIT, 1971
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t tobacco, paper, matches;
sem_t agentsem;

void* smoker_with_matches(void *arg)
{
  while(1) {
    sem_wait(&tobacco);
    int ret = sem_trywait(&paper);
    if(ret == -1) {
        sem_post(&tobacco);
        printf("Smoker with matches gives tobacco back.\n");
        continue;
    }
    printf("Smoker with matches smokes.\n");
    sem_post(&agentsem);
  }
}

void* smoker_with_tobacco(void *arg)
{
  while(1) {
    sem_wait(&paper);
    int ret = sem_trywait(&matches);
    if(ret == -1) {
        sem_post(&paper);
        printf("Smoker with tobacco gives paper back.\n");
        continue;
    }
    printf("Smoker with tobacco smokes.\n");
    sem_post(&agentsem);
  }
}

void* smoker_with_paper(void *arg)
{
  while(1) {
    sem_wait(&tobacco);
    int ret = sem_trywait(&matches);
    if(ret == -1) {
        sem_post(&tobacco);
        printf("Smoker with paper gives tobacco back.\n");
        continue;
    }
    printf("Smoker with paper smokes.\n");
    sem_post(&agentsem);
  }
}

void* agent_a(void *arg)
{
  while(1) {
    sem_wait(&agentsem);
    printf("Agent puts tobacco and paper on the table.\n");
    sem_post(&tobacco);
    sem_post(&paper);
  }
}

void* agent_b(void *arg)
{
  while(1) {
    sem_wait(&agentsem);
    printf("Agent puts paper and matches on the table.\n");
    sem_post(&paper);
    sem_post(&matches);

  }
}

void* agent_c(void *arg)
{
  while(1) {
    sem_wait(&agentsem);
    printf("Agent puts tobacco and matches on the table.\n");
    sem_post(&tobacco);
    sem_post(&matches);
  }
}



	     
int main(void)
{
  pthread_t one, two, three;
  pthread_t agenta, agentb, agentc;
  int ret;

  /* Init semaphores for smoker's ingredients closed */
  ret = sem_init(&tobacco, 0, 0);
  ret |= sem_init(&paper, 0, 0);
  ret |= sem_init(&matches, 0, 0);
  if (ret) {
    printf("Initializing some semaphore failed with code %d.\n", ret);
    exit(EXIT_FAILURE);
  }
  /* Init agent semaphore open */
  ret = sem_init(&agentsem, 0, 1);

  /* Start three smoker threads */
  ret = pthread_create(&one, NULL, &smoker_with_matches, NULL);
  ret |= pthread_create(&two, NULL, &smoker_with_tobacco, NULL);
  ret |= pthread_create(&three, NULL, &smoker_with_paper, NULL);
  if (ret) {
    printf("Creating some smoker thread failed with code %d.\n", ret);
    exit(EXIT_FAILURE);
  }

  /* Start three agent threads which consitute the agent */
  ret = pthread_create(&agenta, NULL, &agent_a, NULL);
  ret |= pthread_create(&agentb, NULL, &agent_b, NULL);
  ret |= pthread_create(&agentc, NULL, &agent_c, NULL);
  if (ret) {
    printf("Creating some agent thread failed with code %d.\n", ret);
    exit(EXIT_FAILURE);
  }

  
  


  
  pause();

  /* destroy the threads */
  
  ret = sem_destroy(&tobacco);
  ret |= sem_destroy(&paper);
  ret |= sem_destroy(&matches);
  if (ret) {
    printf("Destroying some semaphore failed with code %d.\n", ret);
    exit(EXIT_FAILURE);
  }
  
  exit(EXIT_SUCCESS);
}
