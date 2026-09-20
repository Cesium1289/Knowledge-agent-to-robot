# Wumpus World Systems

A knowledge-based AI agent, wired end-to-end into a custom C++ HTTP server (built
from raw POSIX sockets, no frameworks), a live browser dashboard, and eventually
a physical robot. This project exists to demonstrate systems/networking and
hardware-software integration skills in C++.

## Why this project exists

Most AI course projects stop at "the agent works in a console." This one keeps
going: the agent becomes a real network client, the server is written from
scratch against the raw socket API (no `libcurl`, no web framework), the
frontend polls it live, and the final stage swaps the simulated world for a
physical robot driven by the same decision loop. The goal is to demonstrate
comfort across the layers that matter for systems/embedded/aerospace-adjacent
roles: low-level C++, Linux, networking fundamentals, and hardware integration.

## Staged roadmap

- [ ] **Stage 1 — Knowledge-based agent (console only).** A from-scratch C++
      port of the classic AIMA Wumpus World, with a real propositional
      inference engine (not a stub). Core deduction: if a visited square has
      no breeze/stench, every neighboring square is provably safe.
- [ ] **Stage 2 — Custom HTTP server.** Built directly on `socket()`, `bind()`,
      `listen()`, `accept()`, `recv()`, `send()`. Staged as: (a) accept a
      connection and print the raw request, (b) parse the request line and
      return a hardcoded response, (c) serve real files from disk with 404
      handling, (d) handle multiple connections via `select()`/`poll()`/`epoll()`.
- [ ] **Stage 3 — Agent as HTTP client.** The Stage 1 agent sends its percepts
      and actions to the Stage 2 server as real HTTP requests.
- [ ] **Stage 4 — Live dashboard.** Plain HTML/JS (no Node.js) served by the
      same custom C++ server, polling for and visualizing the agent's move
      history.
- [ ] **Stage 5 — Physical robot (stretch goal).** A Raspberry Pi + motor
      driver (e.g. L298N) replaces the simulated world. The robot `POST`s a
      completed action, the server decides the next action and returns it as
      the response, the robot executes it, and the loop repeats. The dashboard
      keeps polling the same `/history`-style endpoint to show it live.

## Repo layout

```
agent/    Stage 1: the knowledge-based agent and its inference engine
server/   Stage 2 & 3: the raw-sockets HTTP server
web/      Stage 4: plain HTML/JS dashboard, served by server/
robot/    Stage 5: Raspberry Pi client code (stretch goal)
docs/     Architecture notes and the inference rule spec
```

## Building

See each subproject's own `CMakeLists.txt`. A top-level build will be wired up
as stages come online.

## Status

Just getting started — Stage 1 in progress.
