#include "index_generated.h"
#include "face.h"

using namespace js;

Face::Face(js::number id, Plane plane) {
    {
            this->id = id;
            this->plane = plane;
    }
}

auto Face::add(Iterable triangle) {
    {
            if (this->edges.size === js::number(0)) {
                        {
                                        for (const auto& edge : triangle) {
                                                            {
                                                                                    this->openEdges.add(edge["hash"]);
                                                                                    this->edges.set(edge["hash"], edge);
                                                            }
                                        }
                                        return;
                        }
            }
            for (const auto& edge : triangle) {
                        {
                                        if (this->openEdges.has(edge["hash"])) {
                                                            {
                                                                                    this->openEdges.delete(edge["hash"]);
                                                            }
                                        } else {
                                                            {
                                                                                    this->openEdges.add(edge["hash"]);
                                                            }
                                        }
                                        this->edges.set(edge["hash"], edge);
                        }
            }
    }
}

auto Face::match(Iterable triangle, Plane plane) {
    {
            if (plane["id"] !== this->plane.id) {
                        {
                                        return false;
                        }
            }
            for (const auto& edge : triangle) {
                        {
                                        if (this->openEdges.has(edge["hash"])) {
                                                            {
                                                                                    return true;
                                                            }
                                        }
                        }
            }
            return false;
    }
}

auto Face::getOpenEdges() {
    {
            js::array<Edge> openEdges = js::array<js::any>{};
            for (const auto& edgeID : this->openEdges) {
                        {
                                        openEdges.push(this->edges.get(edgeID));
                        }
            }
            return openEdges;
    }
}

auto Face::merge(Face face) {
    {
            for (const auto& js::undefined : face["edges"]) {
                        {
                                        this->edges.set(edgeID, edge);
                        }
            }
            for (const auto& edgeID : face["openEdges"]) {
                        {
                                        if (this->openEdges.has(edgeID)) {
                                                            {
                                                                                    this->openEdges.delete(edgeID);
                                                            }
                                        } else {
                                                            {
                                                                                    this->openEdges.add(edgeID);
                                                            }
                                        }
                        }
            }
    }
}
