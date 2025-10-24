#include "index_generated.h"
#include "raycast-controller.h"

using namespace js;

RaycastController::RaycastController(Model model, VirtualBoxController boxes, VirtualTilesController tiles, ItemConfigController items) {
    {
            this->_model = model;
            this->_boxes = boxes;
            this->_tiles = tiles;
            this->_items = items;
            this->_meshes = model["meshes"]();
    }
}

auto RaycastController::cast(VirtualMeshManager mesh, Representation representation, js::any ray, js::any frustum, std::optional<SnappingClass> snap) {
    {
            const js::any reprId = representation["id"]();
            if (snap === SnappingClass::FACE) {
                        {
                                        return mesh["faceRaycast"](reprId, ray, frustum);
                        }
            }
            if (snap === SnappingClass::LINE) {
                        {
                                        return mesh["lineRaycast"](reprId, ray, frustum);
                        }
            }
            if (snap === SnappingClass::POINT) {
                        {
                                        return mesh["pointRaycast"](reprId, ray, frustum);
                        }
            }
            if (snap === js::undefined) {
                        {
                                        return mesh["raycast"](reprId, ray, frustum);
                        }
            }
            return js::undefined;
    }
}

auto RaycastController::raycast(js::any ray, js::any frustum, js::array<unknown> planes) {
    {
            const CastData data = []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("ray", ray);
                  obj_temp_0.set("frustum", frustum);
                  obj_temp_0.set("planes", planes);
                  return js::any(obj_temp_0);
                }();
            const js::any ids = this->castBox(frustum, planes);
            if (ids.length()) {
                        {
                                        return this->computeRaycastList(ids, data);
                        }
            }
            return js::null;
    }
}

auto RaycastController::snapRaycast(js::any ray, js::any frustum, js::array<Snap> snaps, js::array<unknown> planes) {
    {
            js::array<js::any> results = js::array<js::any>{};
            const CastData data = []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("ray", ray);
                  obj_temp_1.set("frustum", frustum);
                  obj_temp_1.set("planes", planes);
                  return js::any(obj_temp_1);
                }();
            const js::any first = this->raycast(ray, frustum, planes);
            if (!first) {
                        {
                                        return this->snapCastEdges(data, snaps);
                        }
            }
            this->getSnaps(first, data, snaps, results);
            if (!first["normal"]) {
                        {
                                        return results;
                        }
            }
            return this->filterOnFront(results);
    }
}

auto RaycastController::rectangleRaycast(js::any frustum, js::array<unknown> planes, bool fullyInside) {
    {
            const js::any lookup = this->_boxes.lookup;
            const js::any itemIds = lookup["collideFrustum"](planes, frustum, fullyInside);
            const js::any raycastedItemIds = this->filterVisible(itemIds);
            return this->localIdsFromItemIds(raycastedItemIds);
    }
}

auto RaycastController::snapCastEdges(CastData data, js::array<Snap> snaps) {
    {
            js::array<js::any> results = js::array<js::any>{};
            const js::any pointSnap = snaps.includes(SnappingClass::POINT);
            const js::any lineSnap = snaps.includes(SnappingClass::LINE);
            if ((pointSnap || lineSnap)) {
                        {
                                        this->computeEdgesCast(data, snaps, results);
                        }
            }
            this->addDistanceToEdgeResult(results, data->ray);
            return results;
    }
}

auto RaycastController::filterVisible(js::array<js::number> ids) {
    {
            js::array<js::number> result = js::array<js::any>{};
            for (const auto& id : ids) {
                        {
                                        this->_meshes.samples(id, this->_temp.sample);
                                        const js::any itemId = this->_temp.sample.item();
                                        const js::any sampleVisible = this->_items.visible(itemId);
                                        if (sampleVisible) {
                                                            {
                                                                                    result.push(id);
                                                            }
                                        }
                        }
            }
            return result;
    }
}

auto RaycastController::computeSnaps(js::array<Snap> snaps, CastData data, js::number id, js::array<js::any> results) {
    {
            for (const auto& snapClass : snaps) {
                        {
                                        const js::any isValidSnap = this->isValidSnap(snapClass);
                                        if (isValidSnap) {
                                                            {
                                                                                    const js::any castData = []() {
                                                                                          js::object obj_temp_2;
                                                                                          obj_temp_2.set("snap", snapClass);
                                                                                          return js::any(obj_temp_2);
                                                                                        }();
                                                                                    const js::any founds = this->castSample(id, castData);
                                                                                    for (const auto& found : founds) {
                                                                                                                {
                                                                                                                                                results.push(found);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
    }
}

auto RaycastController::computeEdgesCast(CastData data, js::array<Snap> snaps, js::array<js::any> results) {
    {
            const js::any raw = this->getRawEdges(data);
            const js::any start = performance["now"]();
            for (const auto& sample : raw) {
                        {
                                        this->fetchSampleData(sample);
                                        this->computeSnaps(snaps, data, sample, results);
                                        const js::any tooMuchTime = this->isTimeExceeded(start);
                                        if (tooMuchTime) {
                                                            {
                                                                                    break;
                                                            }
                                        }
                        }
            }
    }
}

auto RaycastController::addDistanceToEdgeResult(js::array<js::any> input, js::any ray) {
    {
            for (const auto& result : input) {
                        {
                                        const js::any point = result->point;
                                        result->raySquaredDistance = ray["distanceSqToPoint"](point);
                        }
            }
    }
}

auto RaycastController::getRawEdges(CastData data) {
    {
            const js::any result = this->castBox(data->frustum, data->planes);
            if (result.length() <= this->_edgeThreshold) {
                        {
                                        return result;
                        }
            }
            return this->sortBoxes(data->ray, result, this->_edgeThreshold);
    }
}

js::array<js::number> RaycastController::sortBoxes(js::any ray, js::array<js::number> boxes, std::optional<js::number> limit) {
    {
            js::array<js::number> result = js::array<js::any>{};
            const std::shared_ptr<three::Vector3> tempVector = std::make_shared<three::Vector3>();
            const js::any origin = ray["origin"];
            for (js::number i = js::number(0); (i < boxes.length()); i++) {
                        {
                                        const js::any boxId = boxes[i];
                                        const js::any box = this->_boxes.get(boxId);
                                        ray["intersectBox"](box, tempVector);
                                        const js::any distance = tempVector->distanceToSquared(origin);
                                        result.push(distance);
                        }
            }
            const js::any sortedResult = this->dataSort(boxes, result);
            const js::any limitExceeded = (limit && (sortedResult.length() > limit));
            if (limitExceeded) {
                        {
                                        sortedResult->splice(limit);
                        }
            }
            return sortedResult;
    }
}

auto RaycastController::castBox(js::any input, js::array<unknown> planes) {
    {
            const js::any lookup = this->_boxes.lookup;
            if (js::instanceof_op(input, "three::Ray")) {
                        {
                                        const js::any result = lookup["collideRay"](planes, input);
                                        return this->filterVisible(result);
                        }
            }
            const js::any result = lookup["collideFrustum"](planes, input);
            return this->filterVisible(result);
    }
}

auto RaycastController::dataSort(js::array<js::number> ids, js::array<js::number> data) {
    {
            const js::any keys = js::array.from(ids["keys"]());
            const js::any sortedKeys = keys["sort"]([&](auto a, auto b) -> auto { return (data->a - data->b); });
            js::array<js::number> result = js::array<js::any>{};
            for (const auto& key : sortedKeys) {
                        {
                                        const js::any found = ids[key];
                                        result.push(found);
                        }
            }
            return result;
    }
}

auto RaycastController::localIdsFromItemIds(js::array<js::number> raycastedItemIds) {
    {
            const std::shared_ptr<Set> localIds = std::make_shared<Set>();
            for (const auto& id : raycastedItemIds) {
                        {
                                        this->_meshes.samples(id, this->_temp.sample);
                                        const js::any itemId = this->_temp.sample.item();
                                        const js::any localIdIndex = this->_meshes.meshesItems(itemId);
                                        if (localIdIndex === js::null) {
                                                            continue;
                                        }
                                        const js::any localId = this->_model.localIds(localIdIndex);
                                        if (localId === js::null) {
                                                            continue;
                                        }
                                        localIds->add(localId);
                        }
            }
            return js::array.from(localIds);
    }
}

auto RaycastController::getNearest(js::array<js::any> hits) {
    {
            js::any nearest = hits[js::number(0)];
            for (js::number i = js::number(1); (i < hits.length()); i++) {
                        {
                                        const js::any current = hits[i];
                                        if ((nearest["raySquaredDistance"] && current["raySquaredDistance"])) {
                                                            {
                                                                                    const js::any nearestScore = this->getNearScore(nearest);
                                                                                    const js::any currentScore = this->getNearScore(current);
                                                                                    if ((currentScore < nearestScore)) {
                                                                                                                {
                                                                                                                                                nearest = current;
                                                                                                                }
                                                                                    }
                                                            }
                                        } else {
                                                            if ((current["cameraSquaredDistance"] < nearest["cameraSquaredDistance"])) {
                                                                                    {
                                                                                                                nearest = current;
                                                                                    }
                                                            }
                                        }
                        }
            }
            return nearest;
    }
}

auto RaycastController::getEdges(CastData data, js::array<Snap> snaps, js::array<js::any> results) {
    {
            const js::any founds = this->snapCastEdges(data, snaps);
            if (founds) {
                        {
                                        for (const auto& found : founds) {
                                                            {
                                                                                    results.push(found);
                                                            }
                                        }
                        }
            }
    }
}

auto RaycastController::getNearScore(js::any input) {
    {
            const js::any factor = this->_raycastMultiplier;
            const js::number nearestRay = (input["raySquaredDistance"] * factor);
            const js::number nearScore = (nearestRay + input["cameraSquaredDistance"]);
            return nearScore;
    }
}

auto RaycastController::setupSampleCastData(CastData data) {
    {
            TransformHelper::get(this->_temp.sample, this->_meshes, this->_temp.m1);
            this->_temp.m2.copy(this->_temp.m1).invert();
            this->_temp.ray.copy(data->ray).applyMatrix4(this->_temp.m2);
            CameraUtils::transform(data->frustum, this->_temp.m2, this->_temp.frustum);
    }
}

auto RaycastController::addLocalId(js::any raycast) {
    {
            if (!raycast) {
                        {
                                        return;
                        }
            }
            const js::any localIdIndex = this->_meshes.meshesItems(raycast["itemId"]);
            if (localIdIndex === js::null) {
                        {
                                        return;
                        }
            }
            raycast["localId"] = this->_model.localIds(localIdIndex);
    }
}

auto RaycastController::fetchSampleData(js::number sampleId) {
    {
            this->_meshes.samples(sampleId, this->_temp.sample);
            const js::any reprId = this->_temp.sample.representation();
            this->_meshes.representations(reprId, this->_temp.representation);
    }
}

auto RaycastController::computeRaycastList(js::array<js::number> ids, CastData data) {
    {
            const js::any uniqueIds = js::array.from(std::make_shared<Set>(ids));
            const js::any sorted = this->sortBoxes(data->ray, uniqueIds);
            const js::any byRay = this->castBox(data->ray, data->planes);
            const js::any results = this->findAll(sorted, byRay, data);
            if (results.length()) {
                        {
                                        const js::any result = this->getNearest(results);
                                        this->addLocalId(result);
                                        return result;
                        }
            }
            return js::null;
    }
}

auto RaycastController::formatRaycastResult(js::array<js::any> results, js::number id, CastData data) {
    {
            for (const auto& result : results) {
                        {
                                        result->point.applyMatrix4(this->_temp.m1);
                                        if (result->normal) {
                                                            {
                                                                                    result->normal.transformDirection(this->_temp.m1);
                                                            }
                                        }
                                        if (js::in_op("facePoints"_S, result)) {
                                                            {
                                                                                    const js::any sample = this->_meshes.samples(id, this->_temp.sample);
                                                                                    TransformHelper::get(sample, this->_meshes, this->_temp.m3);
                                                                                    for (js::number i = js::number(0); (i < result->facePoints.length()); i += js::number(3)) {
                                                                                                                {
                                                                                                                                                const js::any x = result->facePoints[i];
                                                                                                                                                const js::any y = result->facePoints[(i + js::number(1))];
                                                                                                                                                const js::any z = result->facePoints[(i + js::number(2))];
                                                                                                                                                this->_temp.v1.set(x, y, z);
                                                                                                                                                this->_temp.v1.applyMatrix4(this->_temp.m3);
                                                                                                                                                result->facePoints[i] = this->_temp.v1.x;
                                                                                                                                                result->facePoints[(i + js::number(1))] = this->_temp.v1.y;
                                                                                                                                                result->facePoints[(i + js::number(2))] = this->_temp.v1.z;
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                                        result->sampleId = id;
                                        result->itemId = this->_temp.sample.item();
                                        const js::any distance = data->ray.origin.distanceToSquared(result->point);
                                        result->cameraSquaredDistance = distance;
                                        if (!result->snappingClass) {
                                                            {
                                                                                    result->snappingClass = data->snap;
                                                            }
                                        }
                                        if (result->snappedEdgeP1) {
                                                            {
                                                                                    result->snappedEdgeP1.applyMatrix4(this->_temp.m1);
                                                            }
                                        }
                                        if (result->snappedEdgeP2) {
                                                            {
                                                                                    result->snappedEdgeP2.applyMatrix4(this->_temp.m1);
                                                            }
                                        }
                        }
            }
    }
}

auto RaycastController::findAll(js::array<js::number> sortedIds, js::array<js::number> byRay, CastData data) {
    {
            js::array<js::any> allResults = js::array<js::any>{};
            const js::any start = performance["now"]();
            for (const auto& sample : sortedIds) {
                        {
                                        this->fetchSampleData(sample);
                                        if (!byRay.includes(sample)) {
                                                            {
                                                                                    continue;
                                                            }
                                        }
                                        const js::any results = this->castSample(sample, data);
                                        for (const auto& raycasted : results) {
                                                            {
                                                                                    allResults.push(raycasted);
                                                            }
                                        }
                                        const js::any tooMuchTime = this->isTimeExceeded(start);
                                        if (tooMuchTime) {
                                                            {
                                                                                    break;
                                                            }
                                        }
                        }
            }
            return allResults;
    }
}

auto RaycastController::isTimeExceeded(js::number start) {
    {
            const js::any finish = performance["now"]();
            const js::number duration = (finish - start);
            return (duration > this->_maxDuration);
    }
}

auto RaycastController::getFilteredSampleCast(CastData data) {
    {
            const js::any rawResult = this->_tiles.raycast(this->_temp.representation, this->_temp.ray, this->_temp.frustum, data->snap);
            if (this->_temp.planes.length() === js::number(0)) {
                        {
                                        return rawResult;
                        }
            }
            js::array<js::any> filteredResult = js::array<js::any>{};
            if (rawResult) {
                        {
                                        for (const auto& result : rawResult) {
                                                            {
                                                                                    const js::any planes = this->_temp.planes;
                                                                                    const js::any point = result->point;
                                                                                    const js::any contained = PlanesUtils::containedInParallelPlanes(planes, point);
                                                                                    if (contained) {
                                                                                                                {
                                                                                                                                                filteredResult.push(result);
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            return filteredResult;
    }
}

auto RaycastController::getSnaps(js::any first, CastData data, js::array<Snap> snaps, js::array<js::any> results) {
    {
            this->fetchSampleData(first["sampleId"]);
            if (first["normal"]) {
                        {
                                        this->setCastSide(first, data->ray);
                                        this->setCastPlane(first);
                        }
            }
            this->getFaces(snaps, data, first, results);
            this->getEdges(data, snaps, results);
            for (const auto& found : results) {
                        {
                                        this->addLocalId(found);
                        }
            }
    }
}

auto RaycastController::filterOnFront(js::array<js::any> results) {
    {
            js::array<js::any> resultsOnFront = js::array<js::any>{};
            for (const auto& result : results) {
                        {
                                        const js::any plane = this->_temp.tempPlane;
                                        const js::any distance = plane["distanceToPoint"](result->point);
                                        const js::any isInFront = distance >= js::number(0);
                                        if (isInFront) {
                                                            {
                                                                                    resultsOnFront.push(result);
                                                            }
                                        }
                        }
            }
            return resultsOnFront;
    }
}

auto RaycastController::setCastSide(js::any input, js::any ray) {
    {
            const js::any p1 = input["point"]["clone"]();
            const js::any vec = p1["sub"](ray["origin"]);
            const bool sameSide = (input["normal"]["dot"](vec) > js::number(0));
            if (sameSide) {
                        {
                                        input["normal"]["negate"]();
                        }
            }
    }
}

auto RaycastController::getFaces(js::array<Snap> snaps, CastData data, js::any first, js::array<js::any> results) {
    {
            for (const auto& snap : snaps) {
                        {
                                        const CastData snapData = []() {
                                              js::object obj_temp_3;
                                              obj_temp_3.set("snap", snap);
                                              return js::any(obj_temp_3);
                                            }();
                                        const js::any founds = this->castSample(first["sampleId"], snapData);
                                        for (const auto& found : founds) {
                                                            {
                                                                                    results.push(found);
                                                            }
                                        }
                        }
            }
    }
}

auto RaycastController::setCastPlane(js::any input) {
    {
            const js::any plane = this->_temp.tempPlane;
            const js::any point = input["point"]["clone"]();
            const js::any normal = input["normal"]["clone"]();
            normal["multiplyScalar"](this->_precission);
            point["sub"](normal);
            plane["setFromNormalAndCoplanarPoint"](input["normal"], point);
    }
}

auto RaycastController::castSample(js::number id, CastData data) {
    {
            this->setupSampleCastData(data);
            this->setupPlanesForSampleCast(data);
            const js::any results = this->getFilteredSampleCast(data);
            if (results) {
                        {
                                        this->formatRaycastResult(results, id, data);
                        }
            }
            return results;
    }
}

auto RaycastController::isValidSnap(SnappingClass snapClass) {
    {
            const js::any isLine = snapClass === SnappingClass::LINE;
            const js::any isPoint = snapClass === SnappingClass::POINT;
            return (isLine || isPoint);
    }
}

auto RaycastController::transform(js::array<unknown> planes, js::any transform) {
    {
            js::array<unknown> result = js::array<js::any>{};
            if (planes) {
                        {
                                        for (const auto& plane : planes) {
                                                            {
                                                                                    const js::any clone = std::make_shared<three::Plane>().copy(plane);
                                                                                    clone["applyMatrix4"](transform);
                                                                                    result.push(clone);
                                                            }
                                        }
                        }
            }
            return result;
    }
}

auto RaycastController::setupPlanesForSampleCast(CastData data) {
    {
            this->_temp.planes.length() = js::number(0);
            if ((data->planes && (data->planes.length() > js::number(0)))) {
                        {
                                        const js::any tranformedPlanes = this->transform(data->planes, this->_temp.m2);
                                        for (const auto& plane : tranformedPlanes) {
                                                            {
                                                                                    this->_temp.planes.push(plane);
                                                            }
                                        }
                        }
            }
    }
}
