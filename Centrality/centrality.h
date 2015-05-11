#ifndef centrality_H
#define centrality_H

//����degree centrality
void degree(Matrix mat);

//����eigenvector centrality
void eigenvector(Matrix mat);

//����Katz centrality
void Katz(Matrix mat);

//����PageRank centrality
void PageRank(Matrix mat);

//����betweenness centrality
void betweenness(Matrix mat);

//����closeness centrality
void closeness(Matrix mat);
#endif