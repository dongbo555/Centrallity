#ifndef centrality_H
#define centrality_H

//计算degree centrality
void degree(Matrix mat);

//计算eigenvector centrality
void eigenvector(Matrix mat);

//计算Katz centrality
void Katz(Matrix mat);

//计算PageRank centrality
void PageRank(Matrix mat);

//计算betweenness centrality
void betweenness(Matrix mat);

//计算closeness centrality
void closeness(Matrix mat);
#endif