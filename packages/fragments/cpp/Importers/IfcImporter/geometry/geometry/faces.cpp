#include "index_generated.h"
#include "faces.h"

using namespace js;

auto Faces::add(js::array<Edge> triangle, Plane plane) {
    {
            const js::any matches = this->match(triangle, plane);
            if (matches.length() === js::number(0)) {
                        {
                                        const js::any newFaceID = this->nextFaceID++;
                                        const std::shared_ptr<Face> face = std::make_shared<Face>(newFaceID, plane);
                                        face["add"](triangle);
                                        this->list.set(face["id"], face);
                                        return;
                        }
            }
            if (matches.length() === js::number(1)) {
                        {
                                        const js::any face = this->list.get(matches[js::number(0)]);
                                        face["add"](triangle);
                                        return;
                        }
            }
            if ((matches.length() > js::number(1))) {
                        {
                                        const js::any baseFace = this->list.get(matches[js::number(0)]);
                                        baseFace->add(triangle);
                                        for (js::number i = js::number(1); (i < matches.length()); i++) {
                                                            {
                                                                                    const js::any faceToMergeID = matches[i];
                                                                                    const js::any faceToMerge = this->list.get(faceToMergeID);
                                                                                    baseFace->merge(faceToMerge);
                                                                                    this->list.delete(faceToMergeID);
                                                            }
                                        }
                        }
            }
    }
}

auto Faces::match(js::array<Edge> triangle, Plane plane) {
    {
            js::array<js::number> matchedFaceIDs = js::array<js::any>{};
            for (const auto& face : this->list.values()) {
                        {
                                        if (face.match(triangle, plane)) {
                                                            {
                                                                                    matchedFaceIDs.push(face["id"]);
                                                            }
                                        }
                        }
            }
            return matchedFaceIDs;
    }
}
