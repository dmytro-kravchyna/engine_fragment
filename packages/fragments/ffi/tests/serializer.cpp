#include <iostream>
#include "Schema/index_generated.h"
#include <flatbuffers/flatbuffers.h>

int main() {
  flatbuffers::FlatBufferBuilder builder;

  // Create two FloatVector entries and pack them into a WireSet using the
  // generated CreateWireSetDirect helper.
  std::vector<FloatVector> pts;
  pts.emplace_back(1.0f, 2.0f, 3.0f);
  pts.emplace_back(4.0f, 5.0f, 6.0f);

  auto ws_off = CreateWireSetDirect(builder, &pts);
  builder.Finish(ws_off);

  auto buf = builder.GetBufferPointer();
  auto ws = flatbuffers::GetRoot<const WireSet>(buf);
  if (!ws) {
    std::cerr << "Deserialization failed\n";
    return 1;
  }
  auto ps = ws->ps();
  if (!ps) {
    std::cerr << "ps vector null\n";
    return 1;
  }
  if (ps->size() != 2) {
    std::cerr << "unexpected ps size=" << ps->size() << "\n";
    return 2;
  }

  // Basic content checks
  auto p0 = ps->Get(0);
  if (p0->x() != 1.0f || p0->y() != 2.0f || p0->z() != 3.0f) {
    std::cerr << "first point mismatch\n";
    return 3;
  }

  return 0;
}
