typedef struct {
  char name[30];
  int mart;
  float klnote;
  int bnote;
}student;

typedef union {
  unsigned long l;
  char bc[sizeof(long)];
}uniLong;
