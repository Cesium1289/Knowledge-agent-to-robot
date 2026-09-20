# Architecture

TODO: fill in as stages come online.

## Stage 1 — Agent (console)

`WumpusWorld` (physics) ↔ `WumpusWorldAgent` (KB-AGENT loop) ↔ `KnowledgeBase`
(inference engine). All in-process, no networking yet.

## Stage 2/3 — Server + agent as HTTP client

Diagram and endpoint list go here once the server's request/response schema
is designed (e.g. `POST /percept`, response body is the next action).

## Stage 4 — Dashboard

Polling model, `/history` endpoint shape, and how the frontend renders the
agent's move history.

## Stage 5 — Physical robot

Raspberry Pi ↔ L298N motor driver ↔ same HTTP request/response loop as
Stage 3, replacing the simulated `WumpusWorld` with real sensor input.
