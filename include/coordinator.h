#ifndef COORDINATOR_H
#define COORDINATOR_H

#define N_CLIENTS

typedef struct {
    int rank;
    char name[MAX_NAME];
} User;

User users[] =
{
    {1, "Sasha"},
    {2, "Karina"},
    {3, "Amber"},
    {4, "Wendy"}
}

#endif //COORDINATOR_H