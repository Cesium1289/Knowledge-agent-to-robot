#pragma once

// KnowledgeBase
// The actual reasoning engine: tracks visited squares, derives safety of
// neighboring squares from breeze/stench percepts, and decides the next
// action. This is the core, from-scratch inference logic of the project —
// see docs/inference-rules.md for the design spec before implementing.
//
// TODO: design and implement. No prior implementation exists to port from —
// this is genuinely new logic.

namespace wumpus {

class KnowledgeBase {
public:
    // TODO: tell(), ask(), and the internal square-status representation
};

}  // namespace wumpus
