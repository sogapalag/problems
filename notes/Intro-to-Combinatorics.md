
## Orderings

**Thm.** finite $(X,\preceq)$, then $\exists(X,\leq)$ s.t. $\preceq$ implies $\leq$.(e.g. topological sort)
**Thm.** finite $(X,\preceq)$, then $\exists$ minimal(no $x\prec m$).
**Def.** smallest(minimum), $\forall x\in X, s\preceq x$. obvious smallest implies minimal.
**Def.** embedding: $f:X\rightarrow X'$, if injective, and $f(x)\preceq'f(y)$ iff $x\preceq y$.
**Thm.** $(X,\preceq)$, then $\exists$ embedding to $(2^X, \subseteq)$. (e.g. $f(x)=\{y\in X:y\preceq x\}$)
**Def.** independent/antichain, $A\subseteq X$, independent in $P=(X,\preceq)$, no two distinct $x,y\in A$ that $x\preceq y$. i.e. elements in $A$ are incomparable.
**Def.** "width", $\alpha(P)=\max_A\{|A|\}$. 
**Con.** set of all minimals is antichain.
**Def.** chain $C$, every pair comparable. i.e. $(C,\leq).$
**Def.** "height", $\omega(P)=\max_C\{|C|\}$.
**Thm.** finite, $\alpha(P)\omega(P)\geq |X|$.
**Thm.(Erdős–Szekeres lemma)** real array $a$, $|a|=n^2+1$. then $\exists$ a monotone sequence of length $n+1$. (proof, by previous thm.)
**Def.** Chain Decomposition(CD). disjoint chain sets.
**Dilworth's Thm.**  $\alpha(P)=\min|CD|$.
**dual of Dilworth** $\omega(P)=\min|AD|$.
**Sperne's  Thm.** $|F|\leq {n\choose \lfloor {n/2}\rfloor}$, where $F\subseteq 2^X$ antichain. (related topic: The Christmas tree pattern)

## Combinatorics

**Inclusion-Exclusion Principle** $|\bigcup_{i=1}^n A_i|=\sum_{I\neq \emptyset}(-1)^{|I|-1}|\bigcap_{i\in I}A_i|$

**Hall's matching Thm.** bi-p. $G(X+Y,E)$. $\exists m(X)$ iff $|W|\leq|N(W)|, \forall W\subseteq X$.
**Kőnig's Thm.** bi-p $G$. max matching = min vertex cover.

**Kirchhoff's matrix tree Thm.** undirected $G$, number of spanning trees $\kappa(G)=\frac{1}{n}\lambda_1...\lambda_{n-1}$ the non-zero eigenvalues of Laplacian matrix $L=D-A$, $D$ diag of degrees, $A=\delta_E$.
**Cayley's formula** $\kappa(K_n)=n^{n-2}$.

## Permutation

count derangement: $c_n=(n-1)(c_{n-1}+c_{n-2})$.
Stirling number(1st): partition $n$ into $k$ cycles, $\begin{bmatrix}n \\ k\end{bmatrix}=(n-1)\begin{bmatrix}n-1 \\ k\end{bmatrix} + \begin{bmatrix}n-1 \\ k-1\end{bmatrix}$.
Stirling number(2nd): partition $n$ into $k$ non-empty sets, $\begin{Bmatrix}n \\ k\end{Bmatrix}=k\begin{Bmatrix}n-1 \\ k\end{Bmatrix} + \begin{Bmatrix}n-1 \\ k-1\end{Bmatrix}$.
Bell number: $B_n=\sum_{k=0}^n\begin{Bmatrix}n \\ k\end{Bmatrix}$.

## Integer Partition
**The Pentagonal Number Thm.** $$(1-x)(1-x^2)(1-x^3)...=1-x-x^2+x^5+x^7-x^{12}-x^{15}+...$$ where $e=k(3k-1)/2, k=1,-1,2,-2,3,-3,...$
note GF of integer partition $=\frac{1}{(1-x)(1-x^2)(1-x^3)...}=\sum p_n x^n$. by thm, that $p_n-p_{n-1}-p_{n-2}+p_{n-5}+p_{n-7}-...=0$.
