# Knowledge Base Inference Rules

Write the exact deduction rules here *before* implementing `KnowledgeBase`.
Nailing edge cases down in prose first avoids discovering them as bugs later.

## Confirmed-safe deduction

If a square has been visited and its percept included **no breeze and no
stench**, then every orthogonal neighbor of that square is safe — no pit,
no wumpus — with certainty.

## Possible-danger deduction (the trap to get right)

If a visited square's percept **did** include a breeze, that does **not**
mean every unvisited neighbor has a pit. It means *at least one* neighbor
has a pit — a disjunctive fact, not a confirmed one. Same logic for stench
and the wumpus. Naive implementations conflate "possible danger" with
"confirmed danger" and become either too reckless (walking into pits) or
too timid (refusing to move at all).

## Confirmed-danger deduction (by elimination)

A square can be promoted from "possibly dangerous" to "confirmed dangerous"
when it's the *only* remaining unvisited neighbor across two or more
breeze/stench observations that must be explained by something.

## Square status representation

- `UNKNOWN`
- `SAFE`
- `POSSIBLY_DANGEROUS`
- `CONFIRMED_PIT` / `CONFIRMED_WUMPUS`

## Exploration policy when no forced-safe move exists

TODO: decide and document — e.g. refuse to move into anything unproven, or
pick the lowest-risk unvisited square by inferred probability.
