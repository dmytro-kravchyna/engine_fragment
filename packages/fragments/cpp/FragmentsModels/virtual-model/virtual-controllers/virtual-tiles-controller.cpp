#include "index_generated.h"
#include "virtual-tiles-controller.h"

using namespace js;

// Enum TileDimension implementation
const js::number TileDimension::SMALL = js::number(0);
const js::number TileDimension::MEDIUM = js::number(1);
const js::number TileDimension::LARGE = js::number(2);

js::string TileDimension::getName(js::number key) {
    if (key.value() == js::number(0).value()) return "SMALL"_S;
    if (key.value() == js::number(1).value()) return "MEDIUM"_S;
    if (key.value() == js::number(2).value()) return "LARGE"_S;
    return "undefined"_S;
}


VirtualTilesController::VirtualTilesController(VirtualTileData data) {
    {
            this->_modelId = data->modelId;
            this->_boxes = data->boxes;
            this->_items = data->items;
            this->_materials = data->materials;
            this->_meshConnection = std::make_shared<MeshConnection>(data->modelId, data->connection);
            this->meshes = data->model.meshes();
            this->_sampleAmount = this->meshes.samplesLength();
            this->_samples = std::make_shared<ItemConfigController>(this->_sampleAmount);
            this->_samplesDimensions = std::make_shared<Int32Array>(this->_sampleAmount);
            this->_sampleLodClass = std::make_shared<Uint8Array>(this->_sampleAmount);
            this->_sampleLodState = std::make_shared<Uint8Array>(this->_sampleAmount);
            this->_sampleLodSize = std::make_shared<Float32Array>(this->_sampleAmount);
            this->_tileDimension = this->computeTileSize();
            this->_tileBySample = std::make_shared<js::array>(this->_sampleAmount);
            this->_lodBySample = std::make_shared<js::array>(this->_sampleAmount);
            this->init();
    }
}

auto VirtualTilesController::restart() {
    {
            this->resetUpdateProcess();
            this->_meshConnection.clean();
    }
}

auto VirtualTilesController::fetchSample(js::number id, CurrentLod lod) {
    {
            this->fetchSampleAndRepresentation(id);
            const js::any mesh = this->fetchCurrentMesh();
            const js::any sample = this->sampleTemplate(id);
            sample["geometries"] = this->sampleGeoms(sample, lod, mesh);
            return sample;
    }
}

auto VirtualTilesController::dispose() {
    {
            this->_meshConnection.dispose();
            for (const auto& js::undefined : this->_virtualMeshes) {
                        {
                                        mesh["dispose"]();
                        }
            }
    }
}

auto VirtualTilesController::generate() {
    {
            for (const auto& js::undefined : this->_virtualMeshes) {
                        {
                                        mesh["setupTemplates"]();
                        }
            }
            for (js::number i = js::number(0); (i < this->_sampleAmount); i++) {
                        {
                                        this->generateSampleInTiles(i);
                        }
            }
            this->setupTileVisibilityAndHighlight();
    }
}

auto VirtualTilesController::setupView(js::any view) {
    {
            this->_virtualView = view;
            VirtualMemoryController::setCapacity(view["meshThreshold"]);
            this->restart();
            this->updateOrientationIfNeeded();
            this->updatePositionIfNeeded();
            this->setupViewPlanes();
    }
}

auto VirtualTilesController::updateVirtualMeshes(js::array<js::number> itemIds) {
    {
            if ((!itemIds || !this->_virtualView)) {
                        {
                                        return;
                        }
            }
            for (const auto& itemId : itemIds) {
                        {
                                        this->updateItem(itemId);
                        }
            }
            this->restart();
    }
}

auto VirtualTilesController::getSampleTransform(js::number id) {
    {
            this->fetchSampleAndRepresentation(id);
            const js::any sample = this->sampleTemplate(id);
            return sample["transform"];
    }
}

auto VirtualTilesController::update(js::number time) {
    {
            this->updateTiles(time);
            this->notifyUpdateFinished();
            for (const auto& tileId : this->_tilesChanged) {
                        {
                                        const js::any tile = this->_tiles.get(tileId);
                                        this->_meshConnection.process([]() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("tileRequestClass", TileRequestClass::UPDATE);
                                              obj_temp_0.set("modelId", this->_modelId);
                                              obj_temp_0.set("tileId", tileId);
                                              obj_temp_0.set("objectClass", tile["objectClass"]);
                                              obj_temp_0.set("material", tile["materialId"]);
                                              obj_temp_0.set("tileData", this->getTileData(tile));
                                              obj_temp_0.set("currentLod", tile["lod"]);
                                              return js::any(obj_temp_0);
                                            }());
                        }
            }
            this->_tilesChanged.clear();
    }
}

auto VirtualTilesController::raycast(Representation representation, js::any ray, js::any frustum, std::optional<SnappingClass> snap) {
    {
            this->_temp.raycastPoints = js::array<js::any>{};
            const js::any rClass = representation["representationClass"]();
            const js::any mesh = this->_virtualMeshes.get(rClass);
            this->manageRaycast(mesh, representation, ray, frustum, snap);
            return this->_temp.raycastPoints;
    }
}

auto VirtualTilesController::init() {
    {
            const std::shared_ptr<VirtualShellManager> shells = std::make_shared<VirtualShellManager>(this->_modelId, this->meshes);
            const js::any shellsRepresentation = shells["getRepresentation"]();
            this->_virtualMeshes.set(shellsRepresentation, shells);
            const std::shared_ptr<VirtualCircleExtrusionManager> ces = std::make_shared<VirtualCircleExtrusionManager>(this->_modelId, this->meshes);
            const js::any cesRepresentation = ces["getRepresentation"]();
            this->_virtualMeshes.set(cesRepresentation, ces);
            this->processSamplesDimension();
            this->fetchSampleLodSize();
    }
}

auto VirtualTilesController::initSampleLod(js::number id) {
    {
            this->fetchSampleAndRepresentation(id);
            const js::any mesh = this->fetchCurrentMesh();
            this->_sampleLodClass[id] = mesh["getLodClass"]();
            this->_sampleLodState[id] = CurrentLod::INVISIBLE;
    }
}

auto VirtualTilesController::fetchSampleAndRepresentation(js::number id) {
    {
            this->meshes.samples(id, this->_temp.sample);
            this->meshes.representations(this->_temp.sample.representation(), this->_temp.representation);
    }
}

auto VirtualTilesController::fetchCurrentMesh() {
    {
            const js::any rClass = this->_temp.representation.representationClass();
            return this->_virtualMeshes.get(rClass);
    }
}

auto VirtualTilesController::fetchCurrentMaterial() {
    {
            const js::any materialId = this->_temp.sample.material();
            return this->_materials[materialId];
    }
}

auto VirtualTilesController::fetchSampleLodSize() {
    {
            for (js::number i = js::number(0); (i < this->_sampleAmount); i++) {
                        {
                                        this->initSampleLod(i);
                                        TransformHelper::getBox(this->_temp.representation, this->_temp.box);
                                        this->_sampleLodSize[i] = BoxUtils::getWidth(this->_temp.box);
                        }
            }
    }
}

auto VirtualTilesController::setupTileVisibilityAndHighlight() {
    {
            for (const auto& js::undefined : this->_tiles) {
                        {
                                        tile["visibilities"] = std::make_shared<MultiBufferData>(tile["size"], false);
                                        tile["highlights"] = std::make_shared<MultiBufferData>(tile["size"], js::number(0));
                        }
            }
    }
}

auto VirtualTilesController::addLodToTile(VirtualMeshManager mesh, js::number id, js::number material) {
    {
            if (mesh["getLodClass"]() === LodClass::AABB) {
                        {
                                        this->addBoxLodToTile(id, material);
                                        return;
                        }
            }
            if (mesh["getLodClass"]() === LodClass::CUSTOM) {
                        {
                                        this->addCustomLodToTile(mesh, id, material);
                        }
            }
    }
}

auto VirtualTilesController::addBoxLodToTile(js::number id, js::number material) {
    {
            this->_lodBySample[id] = this->lodTileAppendSample(id, material);
    }
}

auto VirtualTilesController::notifyUpdateFinished() {
    {
            const js::any noficationNotSentYet = !this->tilesUpdated;
            const js::any samplesUpdated = this->_changedSamples >= this->_sampleAmount;
            const js::any updateFinished = (samplesUpdated && noficationNotSentYet);
            if (!updateFinished) {
                        {
                                        return;
                        }
            }
            this->_meshConnection.process([]() {
                  js::object obj_temp_1;
                  obj_temp_1.set("tileRequestClass", TileRequestClass::FINISH);
                  obj_temp_1.set("modelId", this->_modelId);
                  return js::any(obj_temp_1);
                }());
            this->tilesUpdated = true;
    }
}

auto VirtualTilesController::updatePositionIfNeeded() {
    {
            const js::any positionThreshold = this->_params.updateViewPosition;
            const js::any pos = this->_virtualView.cameraPosition;
            const js::any positionChange = pos["distanceToSquared"](this->_lastView.location);
            const bool positionNeedsUpdate = (positionChange > positionThreshold);
            if (positionNeedsUpdate) {
                        {
                                        this->_currentSample = js::number(0);
                                        this->_lastView.location.copy(pos);
                        }
            }
    }
}

auto VirtualTilesController::updateCurrentSample() {
    {
            this->_currentSample++;
            if (this->_currentSample >= this->_sampleAmount) {
                        {
                                        this->_currentSample = js::number(0);
                        }
            }
            this->_changedSamples++;
    }
}

auto VirtualTilesController::processSamplesDimension() {
    {
            for (js::number i = js::number(0); (i < this->_sampleAmount); i++) {
                        {
                                        this->_samplesDimensions[i] = i;
                        }
            }
            this->_samplesDimensions.sort([&](auto a, auto b) -> auto {
            const js::any bDimension = this->_boxes.dimensionOf(b);
            const js::any aDimension = this->_boxes.dimensionOf(a);
            return (bDimension - aDimension);
            });
    }
}

auto VirtualTilesController::setupViewPlanes() {
    {
            this->_virtualPlanes = js::array<js::any>{};
            for (const auto& plane : this->_virtualView.cameraFrustum.planes) {
                        {
                                        this->_virtualPlanes.push(plane);
                        }
            }
            if (this->_virtualView.clippingPlanes) {
                        {
                                        for (const auto& plane : this->_virtualView.clippingPlanes) {
                                                            {
                                                                                    this->_virtualPlanes.push(plane);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualTilesController::updateOrientationIfNeeded() {
    {
            const js::any orientation = this->getCurrentViewOrientation();
            const js::any orientationThreshold = this->_params.updateviewOrientation;
            const js::any orientationChange = orientation["angleTo"](this->_lastView.rotation);
            const bool orientationNeedsUpdate = (orientationChange > orientationThreshold);
            if (orientationNeedsUpdate) {
                        {
                                        this->_currentSample = js::number(0);
                                        this->_lastView.rotation.copy(orientation);
                        }
            }
    }
}

auto VirtualTilesController::getCurrentViewOrientation() {
    {
            return this->_virtualView.cameraFrustum.planes[js::number(4)].normal;
    }
}

auto VirtualTilesController::resetUpdateProcess() {
    {
            this->_changedSamples = js::number(0);
            this->tilesUpdated = false;
    }
}

auto VirtualTilesController::manageRaycast(VirtualMeshManager mesh, Representation repr, js::any ray, js::any frustum, std::optional<SnappingClass> snap) {
    {
            const js::any found = RaycastController::cast(mesh, repr, ray, frustum, snap);
            if (found) {
                        {
                                        for (const auto& point : found) {
                                                            {
                                                                                    point["representationClass"] = mesh["getObjectClass"]();
                                                                                    this->_temp.raycastPoints.push(point);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualTilesController::setTileShellBuffer(TileData tile) {
    {
            if ((tile["usedMemory"] === js::undefined || tile["objectClass"] !== ObjectClass::SHELL)) {
                        {
                                        return;
                        }
            }
            tile["ids"] = std::make_shared<Float32Array>((tile["positionCount"] / js::number(3)));
            tile["usedMemory"] += tile["ids"]["byteLength"];
    }
}

auto VirtualTilesController::getTileWhenSamplePut(js::number tileId, TileData tileData, js::number material) {
    {
            js::any tile = this->_tiles.get(tileId);
            if (tile === js::undefined) {
                        {
                                        const js::any lod = (tileData->lod || CurrentLod::GEOMETRY);
                                        tile = this->newTile(tileData->objectClass, material, lod);
                                        this->_tiles.set(tileId, tile);
                        }
            }
            return tile;
    }
}

auto VirtualTilesController::getPerspTrueDim(js::number fov, js::number distance) {
    {
            const js::number radFactor = (js::Math::PI / js::number(180));
            const js::any tan = js::Math::tan(((fov * js::number(0.5)) * radFactor));
            return (distance * tan);
    }
}

auto VirtualTilesController::getTileHighlight(TileData tile, js::array<js::number> locations) {
    {
            js::any highlightData = js::undefined;
            js::any highlightIds = js::undefined;
            const js::any highlights = tile["highlights"];
            if (!highlights) {
                        {
                                        return []() {
                                              js::object obj_temp_2;
                                              obj_temp_2.set("highlightData", js::undefined);
                                              obj_temp_2.set("highlightIds", js::undefined);
                                              return js::any(obj_temp_2);
                                            }();
                        }
            }
            const js::any highlightSize = highlights["size"]([&](auto id) -> auto { return id !== js::number(0); });
            if ((highlightSize > js::number(0))) {
                        {
                                        highlightIds = std::make_shared<Uint16Array>(highlightSize);
                                        const js::any f = [&](js::number id) -> auto { return id !== js::number(0); };
                                        const js::any c = [&](js::number id, js::number data) -> auto { return highlightIds->id = data; };
                                        highlightData = MultiBufferData::get(highlights, locations, f, c);
                        }
            }
            return []() {
                  js::object obj_temp_3;
                  obj_temp_3.set("highlightData", highlightData);
                  obj_temp_3.set("highlightIds", highlightIds);
                  return js::any(obj_temp_3);
                }();
    }
}

auto VirtualTilesController::setupTileSampleAttributes(TileData tile, js::number location, js::any geometry, js::any sample) {
    {
            const js::number resultPosition = (tile["vertexLocation"][location] * js::number(3));
            for (js::number i = js::number(0); (i < geometry["positionBuffer"].length()); i += js::number(3)) {
                        {
                                        this->_temp.vector.fromArray(geometry["positionBuffer"], i);
                                        this->_temp.vector.applyMatrix4(this->_temp.matrix);
                                        this->_temp.vector.toArray(tile["positionBuffer"], (resultPosition + i));
                        }
            }
            if (tile["normalBuffer"]) {
                        {
                                        const js::number resultPosition = (tile["vertexLocation"][location] * js::number(3));
                                        for (js::number i = js::number(0); (i < geometry["normalBuffer"].length()); i += js::number(3)) {
                                                            {
                                                                                    this->_temp.vector.fromArray(geometry["normalBuffer"], i);
                                                                                    this->_temp.vector.transformDirection(this->_temp.matrix);
                                                                                    this->_temp.vector.multiplyScalar(normalizationValue);
                                                                                    this->_temp.vector.toArray(tile["normalBuffer"], (resultPosition + i));
                                                            }
                                        }
                        }
            }
            if (tile["indexBuffer"]) {
                        {
                                        const js::any indicesPosition = tile["indexLocation"][location];
                                        const js::any position = tile["vertexLocation"][location];
                                        for (js::number i = js::number(0); (i < geometry["indexCount"]); i++) {
                                                            {
                                                                                    const js::number result = (geometry["indexBuffer"][i] + position);
                                                                                    tile["indexBuffer"][(i + indicesPosition)] = result;
                                                            }
                                        }
                        }
            }
            if ((tile["faceIdBuffer"] && geometry["faceIdBuffer"])) {
                        {
                                        const js::number sampleOffset = (sample["sample"] * js::number(100));
                                        const js::any start = tile["vertexLocation"][location];
                                        const js::number end = (start + (geometry["positionCount"] / js::number(3)));
                                        for (js::any i = start; (i < end); i++) {
                                                            {
                                                                                    tile["faceIdBuffer"][i] = (geometry["faceIdBuffer"][(i - start)] + sampleOffset);
                                                            }
                                        }
                        }
            }
            if (geometry["objectClass"] === ObjectClass::SHELL) {
                        {
                                        const js::any start = tile["vertexLocation"][location];
                                        const js::number end = (start + (geometry["positionCount"] / js::number(3)));
                                        tile["ids"]["fill"](this->itemId(sample["sample"]), start, end);
                        }
            }
    }
}

auto VirtualTilesController::getTileVisibility(TileData tile, js::array<js::number> locations) {
    {
            if (!tile["visibilities"]) {
                        {
                                        throw js::any(js::Error("Fragments: Malformed tile!"_S));
                        }
            }
            if (tile["visibilities"]["fullOf"](false)) {
                        {
                                        return js::undefined;
                        }
            }
            const js::any filter = [&](bool data) -> auto { return data; };
            return MultiBufferData::get(tile["visibilities"], locations, filter);
    }
}

auto VirtualTilesController::memoryOverflow() {
    {
            const js::any current = VirtualTilesController::_graphicMemoryConsumed;
            const js::any available = this->_virtualView.graphicThreshold;
            return (current > available);
    }
}

auto VirtualTilesController::updateMesh(js::number sample) {
    {
            js::any current = this->fetchLodLevel(sample);
            const js::any past = this->_sampleLodState[sample];
            current = this->hideHighlightedLods(current, sample);
            if (current === past) {
                        {
                                        this->updateSampleIfSeen(current, sample);
                                        return;
                        }
            }
            this->updateVisible(past, current, sample);
    }
}

auto VirtualTilesController::tileLoadSample(TileData tile, js::any sample, js::number geomIndex) {
    {
            const js::any location = tile["sampleLocation"]["get"](sample["sample"]);
            const js::any geometry = this->getSampleGeometries(sample, geomIndex);
            this->setupTileLocation(tile, geometry, sample);
            this->fetchSampleTransform(tile, sample);
            this->setupTileSampleAttributes(tile, location, geometry, sample);
    }
}

auto VirtualTilesController::updateSampleIfSeen(CurrentLod current, js::number sample) {
    {
            if (current !== CurrentLod::INVISIBLE) {
                        {
                                        this->updateSample(sample, current);
                        }
            }
    }
}

auto VirtualTilesController::hideHighlightedLods(CurrentLod current, js::number sample) {
    {
            if ((current === CurrentLod::WIRES && this->_samples.getHighlight(sample))) {
                        {
                                        current = CurrentLod::INVISIBLE;
                        }
            }
            return current;
    }
}

auto VirtualTilesController::updateVisible(CurrentLod past, CurrentLod current, js::number sample) {
    {
            if (past !== CurrentLod::INVISIBLE) {
                        {
                                        this->makeSampleInvisible(sample, past);
                        }
            }
            const js::any isSeen = current !== CurrentLod::INVISIBLE;
            if (isSeen) {
                        {
                                        this->updateSample(sample, current);
                        }
            }
            this->_samples.setVisible(sample, isSeen);
            this->_sampleLodState[sample] = current;
    }
}

auto VirtualTilesController::makeInvisibleFromTile(js::number tileId, js::number sample) {
    {
            const js::any tile = this->_tiles.get(tileId);
            this->updateTileData(tile, sample, false, js::number(0));
            this->deleteTileIfNeeded(tile, tileId);
    }
}

auto VirtualTilesController::updateSample(js::number id, CurrentLod lod) {
    {
            const js::any itemId = this->itemId(id);
            const js::any visible = this->_items.visible(itemId);
            const js::any highlight = this->_items.getHighlight(itemId);
            const js::any changed = this->hasChanged(id, lod, visible, highlight);
            if (changed) {
                        {
                                        this->setSample(id, visible, highlight, lod);
                        }
            }
    }
}

auto VirtualTilesController::hasHighlightChanged(js::number id, js::number highlight) {
    {
            const js::any currentHighlight = this->_samples.getHighlight(id);
            return highlight !== currentHighlight;
    }
}

auto VirtualTilesController::hasVisibleChanged(js::number id, bool visible) {
    {
            const js::any currentVisible = this->_samples.visible(id);
            return visible !== currentVisible;
    }
}

auto VirtualTilesController::newTile(ObjectClass objectClass, js::number material, CurrentLod lod) {
    {
            const js::any tile = []() {
                  js::object obj_temp_4;
                  return js::any(obj_temp_4);
                }();
            tile["notVirtual"] = false;
            tile["materialId"] = material;
            tile["indexLocation"] = js::array<js::any>{};
            tile["box"] = std::make_shared<three::Box3>();
            tile["objectClass"] = objectClass;
            tile["lod"] = lod;
            tile["normalCount"] = js::number(0);
            tile["indexCount"] = js::number(0);
            tile["vertexLocation"] = js::array<js::any>{};
            tile["size"] = js::number(0);
            tile["geometriesLocation"] = js::array<js::any>{};
            tile["positionCount"] = js::number(0);
            tile["sampleLocation"] = std::make_shared<Map>();
            tile["faceIdBuffer"] = std::make_shared<Uint32Array>(js::number(0));
            return tile;
    }
}

auto VirtualTilesController::createLod(js::any box) {
    {
            const js::any line = TransformHelper::boxSize(box);
            const js::any position = this->_temp.tileData.positionBuffer;
            if (!position) {
                        {
                                        throw js::any(js::Error("Fragments: Malformed tiles!"_S));
                        }
            }
            position[js::number(0)] = line["start"]["x"];
            position[js::number(1)] = line["start"]["y"];
            position[js::number(2)] = line["start"]["z"];
            position[js::number(3)] = line["end"]["x"];
            position[js::number(4)] = line["end"]["y"];
            position[js::number(5)] = line["end"]["z"];
            return this->_temp.tileData;
    }
}

auto VirtualTilesController::sampleTemplate(js::number id) {
    {
            const js::any sample = this->_temp.sample;
            const js::any representation = this->_temp.representation;
            TransformHelper::get(sample, this->meshes, this->_temp.transform);
            TransformHelper::getBox(representation, this->_temp.boundingBox);
            this->_temp.sampleGeometry.sample = id;
            const js::any materialId = sample["material"]();
            this->_temp.sampleGeometry.material = this->_materials[materialId];
            this->_temp.sampleGeometry.transform = this->_temp.transform;
            this->_temp.sampleGeometry.aabb = this->_temp.boundingBox;
            js::delete_property(this->_temp.sampleGeometry, "geometries");
            return this->_temp.sampleGeometry;
    }
}

auto VirtualTilesController::makeSampleInvisible(js::number id, CurrentLod lod) {
    {
            const js::any tileIds = this->getTileIds(id, lod);
            if (!tileIds) {
                        {
                                        return;
                        }
            }
            const js::any callback = [&](js::number tileId) -> auto { return this->makeInvisibleFromTile(tileId, id); };
            MiscHelper::forEach(tileIds, callback);
    }
}

auto VirtualTilesController::setSample(js::number id, bool vis, js::number high, CurrentLod lod) {
    {
            this->_samples.setVisible(id, vis);
            this->_samples.setHighlight(id, high);
            const js::any tileIds = this->getTileIds(id, lod);
            if (tileIds === js::undefined) {
                        return;
            }
            MiscHelper::forEach(tileIds, [&](auto tileId) -> auto {
            this->updateTile(tileId, id, high, high === js::number(0));
            });
    }
}

auto VirtualTilesController::getTileIds(js::number sample, js::number lod) {
    {
            if (lod === CurrentLod::GEOMETRY) {
                        {
                                        return this->_tileBySample[sample];
                        }
            }
            return this->_lodBySample[sample];
    }
}

auto VirtualTilesController::addBasicTileData(TileData a, js::number sample, js::number id) {
    {
            a["sampleLocation"]["set"](sample, a["size"]);
            a["size"]++;
            a["geometriesLocation"].push(id);
            a["indexLocation"].push((a["indexCount"] || js::number(0)));
            a["vertexLocation"].push(((a["positionCount"] || js::number(0)) / js::number(3)));
    }
}

auto VirtualTilesController::buildNewVirtualTile(TileData tile, js::number tileId) {
    {
            this->constructTile(tile);
            this->loadTile(tileId, tile);
            tile["notVirtual"] = true;
            js::delete_property(tile, "indexBuffer");
            js::delete_property(tile, "positionBuffer");
            js::delete_property(tile, "normalBuffer");
            js::delete_property(tile, "faceIdBuffer");
            js::delete_property(tile, "ids");
    }
}

auto VirtualTilesController::deleteTileIfNeeded(TileData tile, js::number tileId) {
    {
            const js::any shouldDelete = this->getShouldDeleteTile(tile);
            if (shouldDelete) {
                        {
                                        this->deleteGeometry(tileId);
                                        tile["notVirtual"] = false;
                                        VirtualTilesController::_graphicMemoryConsumed -= tile["usedMemory"];
                                        return;
                        }
            }
            this->_tilesChanged.add(tileId);
    }
}

auto VirtualTilesController::getShouldDeleteTile(TileData tile) {
    {
            if ((!tile["visibilities"] || !tile["highlights"])) {
                        {
                                        throw js::any(js::Error("Fragments: Malformed tile!"_S));
                        }
            }
            const js::any invisible = tile["visibilities"]["fullOf"](false);
            const js::any noHighlight = tile["highlights"]["fullOf"](js::number(0));
            const js::any memoryOverflow = this->memoryOverflow();
            return ((invisible && noHighlight) && memoryOverflow);
    }
}

auto VirtualTilesController::checkTileMemoryOverflow(js::number tileId, TileData tileData) {
    {
            const js::any tile = this->_tiles.get(tileId);
            const js::any bufferSize = (js::null ? js::null : js::null);
            const js::number totalSize = (bufferSize + tileData->positionCount);
            const bool memoryOverflow = (totalSize > limitOf2Bytes);
            return memoryOverflow;
    }
}

auto VirtualTilesController::updateTileData(TileData tile, js::number sample, bool visible, js::number highlight) {
    {
            if ((!tile["visibilities"] || !tile["highlights"])) {
                        {
                                        throw js::any(js::Error("Fragments: Malformed tile!"_S));
                        }
            }
            const js::any id = tile["sampleLocation"]["get"](sample);
            tile["visibilities"]["update"](id, visible);
            tile["highlights"]["update"](id, highlight);
    }
}

auto VirtualTilesController::getKeepUpdating(js::number sampleId, js::number time) {
    {
            const js::any maxTime = this->_params.updateTime;
            const js::any minSamples = this->_params.updateSamples;
            const bool samplesLeft = (sampleId < this->_sampleAmount);
            const js::number passedTime = (performance["now"]() - time);
            const bool isFirstSamples = (sampleId < minSamples);
            const js::any timeLeft = ((passedTime < maxTime) || isFirstSamples);
            const js::any shouldKeepUpdating = (samplesLeft && timeLeft);
            return shouldKeepUpdating;
    }
}

auto VirtualTilesController::computeTileSize() {
    {
            const js::any dimension = this->_boxes.fullBox.getSize(this->_temp.vector);
            const js::any maxDimension = js::Math::max(dimension["x"], dimension["y"], dimension["z"]);
            const js::number fraction = (maxDimension / this->_params.tileDimensionFactor);
            const js::any maxIntFraction = js::Math::ceil(fraction);
            return js::Math::max(this->_params.minTileDimension, maxIntFraction);
    }
}

auto VirtualTilesController::newTileId(js::number sample, js::number material, TileData tileData) {
    {
            this->logBufferOverflowIfNeeded(tileData);
            const js::any lod = (tileData->lod || CurrentLod::GEOMETRY);
            const js::any code = this->generateTileCode(sample, material, tileData, lod);
            const js::any tileSize = (this->_sizeByTile.get(code) || js::number(1));
            js::number tileId = ((code + tileSize) - js::number(1));
            const js::any memoryOverflow = this->checkTileMemoryOverflow(tileId, tileData);
            if (memoryOverflow) {
                        {
                                        tileId += this->_params.tileIdIncrement;
                                        this->_sizeByTile.set(code, (tileSize + js::number(1)));
                        }
            }
            return tileId;
    }
}

auto VirtualTilesController::logBufferOverflowIfNeeded(TileData tileData) {
    {
            const js::number geometrySize = (tileData->positionCount / js::number(3));
            if ((geometrySize > limitOf2Bytes)) {
                        {
                                        js::console.log("Fragments: Buffer overflow"_S);
                        }
            }
    }
}

auto VirtualTilesController::fetchLodLevel(js::number sample) {
    {
            const js::any item = this->_boxes.get(sample);
            const js::any notClipped = CameraUtils::collides(item, this->_virtualPlanes);
            if (!notClipped) {
                        {
                                        return CurrentLod::INVISIBLE;
                        }
            }
            this->meshes.samples(sample, this->_temp.sample);
            const js::any itemId = this->_temp.sample.item();
            const js::any isSeen = this->_items.visible(itemId);
            if (!isSeen) {
                        {
                                        return CurrentLod::INVISIBLE;
                        }
            }
            const js::any quality = this->_virtualView.graphicQuality;
            const js::any dimension = this->_boxes.dimensionOf(sample);
            const js::any offset = item->distanceToPoint(this->_virtualView.cameraPosition);
            const js::any screenDimension = this->screenSize(dimension, offset);
            const bool isSmall = (dimension < this->_params.smallObjectSize);
            const js::any isLarge = !isSmall;
            const js::number smallScreen = (this->_params.smallScreenSize * quality);
            const js::number mediumScreen = (this->_params.mediumScreenSize * quality);
            const js::number largeScreen = (this->_params.largeScreenSize * quality);
            const bool isSmallInScreen = (screenDimension < smallScreen);
            const bool isMediumInScreen = (screenDimension < mediumScreen);
            const bool isLargeInScreen = (screenDimension < largeScreen);
            const js::any smallAndFar = (isSmall && isMediumInScreen);
            const js::any largeAndVeryFar = (isLarge && isSmallInScreen);
            const js::any smallAndClose = (isSmall && isLargeInScreen);
            const js::any largeAndFar = (isLarge && isMediumInScreen);
            if ((smallAndFar || largeAndVeryFar)) {
                        {
                                        return CurrentLod::INVISIBLE;
                        }
            }
            if ((smallAndClose || largeAndFar)) {
                        {
                                        return CurrentLod::WIRES;
                        }
            }
            const js::any lodSize = this->_sampleLodSize[sample];
            const js::any screenSize = this->screenSize(lodSize, offset);
            const js::any wireLimit = js::Math::max(mediumScreen, this->_params.mediumScreenSize);
            const bool isWireLike = (screenSize < wireLimit);
            if (isWireLike) {
                        {
                                        return CurrentLod::WIRES;
                        }
            }
            return CurrentLod::GEOMETRY;
    }
}

auto VirtualTilesController::generateTileCode(js::number sample, js::number material, TileData tile, CurrentLod lod) {
    {
            this->_tileIdGenerator.reset();
            this->processTileDataId(tile, material, lod);
            const js::any box = this->processTileSpatialId(sample, lod);
            this->processTileDimensionId(box);
            return this->_tileIdGenerator.value;
    }
}

auto VirtualTilesController::processTileDataId(TileData tile, js::number material, CurrentLod lod) {
    {
            this->_tileIdGenerator.compute((js::null ? js::null : js::null));
            this->_tileIdGenerator.compute(material);
            this->_tileIdGenerator.compute(lod);
    }
}

auto VirtualTilesController::deleteGeometry(js::number tileId) {
    {
            this->_meshConnection.process([]() {
                  js::object obj_temp_5;
                  obj_temp_5.set("tileRequestClass", TileRequestClass::DELETE);
                  obj_temp_5.set("modelId", this->_modelId);
                  obj_temp_5.set("tileId", tileId);
                  return js::any(obj_temp_5);
                }());
    }
}

auto VirtualTilesController::processTileSpatialId(js::number sample, CurrentLod lod) {
    {
            const js::any x = this->_temp.tileCenter.x;
            const js::any y = this->_temp.tileCenter.y;
            const js::any z = this->_temp.tileCenter.z;
            const js::any box = this->_boxes.get(sample);
            box["getCenter"](this->_temp.tileCenter);
            const js::any tileDimension = this->getTileDimension(lod);
            const js::number tx = (x - (x % tileDimension));
            const js::number ty = (y - (y % tileDimension));
            const js::number tz = (z - (z % tileDimension));
            this->_tileIdGenerator.compute(tx);
            this->_tileIdGenerator.compute(ty);
            this->_tileIdGenerator.compute(tz);
            return box;
    }
}

auto VirtualTilesController::addCustomLodToTile(VirtualMeshManager mesh, js::number id, js::number material) {
    {
            const js::any lods = this->meshData(mesh, false, CurrentLod::WIRES);
            this->_sampleLodSize[id] = (lods["lodThickness"] || js::number(0));
            this->_lodBySample[id] = this->putSampleInTiles(id, material, lods);
    }
}

auto VirtualTilesController::getTileLocations(TileData tile) {
    {
            if (tile["indexCount"]) {
                        {
                                        return tile["indexLocation"];
                        }
            }
            return tile["vertexLocation"];
    }
}

auto VirtualTilesController::getTileDimension(CurrentLod lod) {
    {
            js::any tileDimension = this->_tileDimension;
            if (lod === CurrentLod::GEOMETRY) {
                        {
                                        tileDimension *= this->_params.tileSizeMultiplier;
                        }
            }
            return tileDimension;
    }
}

auto VirtualTilesController::processTileDimensionId(js::any box) {
    {
            const js::any sizeCategory = this->getTileDimensionClass(box);
            this->_tileIdGenerator.compute(sizeCategory);
    }
}

auto VirtualTilesController::tileAppend(TileData a, TileData b, js::number sample, js::number id) {
    {
            this->addBasicTileData(a, sample, id);
            this->tileAppendAttribute(a, b, "indexCount"_S, false);
            this->tileAppendAttribute(a, b, "positionCount"_S, false);
            this->tileAppendAttribute(a, b, "normalCount"_S, false);
            this->tileAppendAttribute(a, b, "materialId"_S, true);
    }
}

auto VirtualTilesController::putSampleInTiles(js::number sample, js::number material, js::any tiles) {
    {
            js::any tileIds = js::undefined;
            const js::any onSamplePut = [&](TileData tileData, js::number id) -> auto {
            const js::any tileId = this->newTileId(sample, material, tileData);
            tileIds = this->getTileIdsWhenSamplePut(tileIds, tileId);
            const js::any tile = this->getTileWhenSamplePut(tileId, tileData, material);
            this->tileAppend(tile, tileData, sample, id);
            };
            MiscHelper::forEach(tiles, onSamplePut);
            return tileIds;
    }
}

auto VirtualTilesController::hasLodChanged(js::number id, CurrentLod lod) {
    {
            const js::any currentLod = this->_sampleLodState[id];
            return lod !== currentLod;
    }
}

auto VirtualTilesController::getTileIdsWhenSamplePut(js::any tileIds, js::number tileId) {
    {
            if (tileIds === js::undefined) {
                        {
                                        tileIds = tileId;
                        }
            } else {
                        if (js::typeof_op(tileIds) === "number"_S) {
                                        {
                                                            if (tileIds !== tileId) {
                                                                                    tileIds = js::array<js::any>{tileIds, tileId};
                                                            }
                                        }
                        } else {
                                        if (!tileIds.includes(tileId)) {
                                                            {
                                                                                    tileIds.push(tileId);
                                                            }
                                        }
                        }
            }
            return tileIds;
    }
}

auto VirtualTilesController::updateTile(js::number tileId, js::number sample, js::number highlight, bool visible) {
    {
            const js::any tile = this->_tiles.get(tileId);
            this->updateTileData(tile, sample, visible, highlight);
            if (tile["notVirtual"]) {
                        {
                                        this->_tilesChanged.add(tileId);
                                        return;
                        }
            }
            this->buildNewVirtualTile(tile, tileId);
    }
}

auto VirtualTilesController::getLodTileWhenPutSample(js::number tileId, js::number material) {
    {
            js::any tile = this->_tiles.get(tileId);
            if (!tile) {
                        {
                                        const js::any objectClass = this->_temp.tile.objectClass;
                                        tile = this->newTile(objectClass, material, CurrentLod::WIRES);
                                        this->_tiles.set(tileId, tile);
                        }
            }
            return tile;
    }
}

auto VirtualTilesController::lodTileAppendSample(js::number sample, js::number material) {
    {
            const js::any wires = CurrentLod::WIRES;
            const js::any tempTile = this->_temp.tile;
            const js::any tileId = this->generateTileCode(sample, material, tempTile, wires);
            const js::any tile = this->getLodTileWhenPutSample(tileId, material);
            this->tileAppend(tile, tempTile, sample, js::number(0));
            return tileId;
    }
}

auto VirtualTilesController::addSampleToTile(VirtualMeshManager mesh, js::number id, js::number material) {
    {
            const js::any meshes = this->meshData(mesh, false, CurrentLod::GEOMETRY);
            this->_tileBySample[id] = this->putSampleInTiles(id, material, meshes);
    }
}

auto VirtualTilesController::setTileBuffer(TileData tile, js::any key, bool unsigned) {
    {
            if (tile["usedMemory"] === js::undefined) {
                        {
                                        return;
                        }
            }
            const js::any count = tile[(js::toString(key) + "Count"_S)];
            if ((count > js::number(0))) {
                        {
                                        const js::any buffer = (js::null ? js::null : js::null);
                                        tile[(js::toString(key) + "Buffer"_S)] = buffer;
                                        tile["usedMemory"] += buffer["byteLength"];
                        }
            }
    }
}

auto VirtualTilesController::updateTiles(js::number time) {
    {
            const bool needsUpdate = (this->_changedSamples < this->_sampleAmount);
            const js::any viewAvailable = this->_virtualView !== js::undefined;
            if ((!viewAvailable || !needsUpdate)) {
                        {
                                        return;
                        }
            }
            bool keepUpdating = true;
            js::number updatingSampleId = js::number(0);
            while (js::null) {
                        {
                        }
            }
    }
}

auto VirtualTilesController::sampleGeoms(js::any sample, CurrentLod lod, VirtualMeshManager mesh) {
    {
            if ((mesh["getLodClass"]() === LodClass::AABB && lod === CurrentLod::WIRES)) {
                        {
                                        return this->createLod(sample["aabb"]);
                        }
            }
            return this->meshData(mesh, true, lod);
    }
}

auto VirtualTilesController::generateSampleInTiles(js::number id) {
    {
            this->fetchSampleAndRepresentation(id);
            const js::any material = this->fetchCurrentMaterial();
            const js::any mesh = this->fetchCurrentMesh();
            this->addSampleToTile(mesh, id, material);
            this->addLodToTile(mesh, id, material);
    }
}

auto VirtualTilesController::buildSampleInTile(TileData tile, js::number position, js::any sample, bool isStart, js::number id) {
    {
            const js::any found = tile["geometriesLocation"][position];
            this->tileLoadSample(tile, sample, found);
            if (isStart) {
                        {
                                        const js::any box = this->_boxes.get(id);
                                        this->_temp.vector.copy(tile["location"]);
                                        this->_temp.vector.negate();
                                        box["translate"](this->_temp.vector);
                                        tile["box"]["union"](box);
                        }
            }
    }
}

auto VirtualTilesController::getSampleGeometries(js::any sample, js::number geomIndex) {
    {
            if (js::array.isArray(sample["geometries"])) {
                        {
                                        return sample["geometries"][geomIndex];
                        }
            }
            return sample["geometries"];
    }
}

auto VirtualTilesController::constructTile(TileData tile) {
    {
            if (tile["positionBuffer"] === js::undefined) {
                        {
                                        tile["positionBuffer"] = std::make_shared<Float32Array>(tile["positionCount"]);
                                        tile["usedMemory"] = tile["positionBuffer"]["byteLength"];
                                        this->setTileBuffer(tile, "index"_S, true);
                                        this->setTileBuffer(tile, "normal"_S, false);
                                        this->setTileShellBuffer(tile);
                                        tile["faceIdBuffer"] = std::make_shared<Uint32Array>((tile["positionCount"] / js::number(3)));
                                        tile["usedMemory"] += tile["faceIdBuffer"]["byteLength"];
                        }
            }
            const js::any isStart = !tile["location"];
            for (const auto& js::undefined : tile["sampleLocation"]) {
                        {
                                        const js::any sample = this->fetchSample(id, tile["lod"]);
                                        if ((sample && sample["geometries"])) {
                                                            {
                                                                                    this->buildSampleInTile(tile, position, sample, isStart, id);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualTilesController::fetchSampleTransform(TileData tile, js::any sample) {
    {
            this->_temp.vector.copy(tile["location"]);
            this->_temp.vector.negate();
            this->_temp.matrix.identity();
            this->_temp.matrix.setPosition(this->_temp.vector);
            this->_temp.matrix.multiply(sample["transform"]);
    }
}

auto VirtualTilesController::hasChanged(js::number id, CurrentLod lod, bool vis, js::number high) {
    {
            const js::any lodNeedsChanged = this->hasLodChanged(id, lod);
            const js::any visibleChangd = this->hasVisibleChanged(id, vis);
            const js::any highlightChanged = this->hasHighlightChanged(id, high);
            return ((lodNeedsChanged || visibleChangd) || highlightChanged);
    }
}

auto VirtualTilesController::setupTileLocation(TileData tile, js::any geometry, js::any sample) {
    {
            if (tile["location"]) {
                        {
                                        return;
                        }
            }
            const std::shared_ptr<three::Vector3> result = std::make_shared<three::Vector3>();
            result->fromArray(geometry["positionBuffer"]);
            result->applyMatrix4(sample["transform"]);
            tile["location"] = result;
    }
}

auto VirtualTilesController::getTileData(TileData tile) {
    {
            const js::any locations = this->getTileLocations(tile);
            const js::any visibilityData = this->getTileVisibility(tile, locations);
            const js::any highlight = this->getTileHighlight(tile, locations);
            auto _temp4718 = highlight;
            const auto highlightData = _temp4718["highlightData"];
            const auto highlightIds = _temp4718["highlightIds"];
            return []() {
                  js::object obj_temp_6;
                  obj_temp_6.set("visibilityData", visibilityData);
                  obj_temp_6.set("highlightData", highlightData);
                  obj_temp_6.set("highlightIds", highlightIds);
                  return js::any(obj_temp_6);
                }();
    }
}

auto VirtualTilesController::updateMemoryOnTileLoad(TileData tile) {
    {
            VirtualTilesController::_graphicMemoryConsumed += tile["usedMemory"];
    }
}

auto VirtualTilesController::fetchTileMatrixOnLoad(TileData tile) {
    {
            if (tile["location"]) {
                        {
                                        this->_temp.matrix.identity();
                                        this->_temp.matrix.setPosition(tile["location"]);
                        }
            }
    }
}

auto VirtualTilesController::updateItem(js::number itemId) {
    {
            const js::any sampleIds = this->_boxes.sampleOf(itemId);
            if (sampleIds) {
                        {
                                        for (const auto& sampleId : sampleIds) {
                                                            {
                                                                                    this->updateMesh(sampleId);
                                                            }
                                        }
                        }
            }
    }
}

auto VirtualTilesController::screenSize(js::number dimension, js::number distance) {
    {
            const js::any viewDimension = this->getViewDimension(distance);
            const js::number screenDimension = (dimension / viewDimension);
            return (screenDimension * this->_virtualView.viewSize);
    }
}

auto VirtualTilesController::getTileDimensionClass(js::any box) {
    {
            const js::any size = box["min"]["distanceToSquared"](box["max"]);
            const js::any small = this->_params.smallTileSize;
            const js::any medium = this->_params.mediumTileSize;
            if ((size > medium)) {
                        {
                                        return TileDimension::LARGE;
                        }
            }
            if ((size > small)) {
                        {
                                        return TileDimension::MEDIUM;
                        }
            }
            return TileDimension::SMALL;
    }
}

auto VirtualTilesController::getViewDimension(js::number distance) {
    {
            if (this->_virtualView.orthogonalDimension) {
                        {
                                        return this->_virtualView.orthogonalDimension;
                        }
            }
            const js::any currentFov = this->_virtualView.fov;
            const js::any fovChanged = currentFov !== this->_temp.pastFieldOfview;
            if (fovChanged) {
                        {
                                        this->_temp.viewDimension = this->getPerspTrueDim(currentFov, js::number(1));
                                        this->_temp.pastFieldOfview = currentFov;
                        }
            }
            return (distance * this->_temp.viewDimension);
    }
}

auto VirtualTilesController::loadTile(js::number tileId, TileData tile) {
    {
            const js::any tileData = this->getTileData(tile);
            this->fetchTileMatrixOnLoad(tile);
            const js::any faceIds = this->getFaceIds(tile);
            this->_meshConnection.process([]() {
                  js::object obj_temp_7;
                  obj_temp_7.set("tileRequestClass", TileRequestClass::CREATE);
                  obj_temp_7.set("modelId", this->_modelId);
                  obj_temp_7.set("objectClass", tile["objectClass"]);
                  obj_temp_7.set("tileId", tileId);
                  obj_temp_7.set("itemId", js::undefined);
                  obj_temp_7.set("tileData", tileData);
                  obj_temp_7.set("indices", tile["indexBuffer"]);
                  obj_temp_7.set("positions", tile["positionBuffer"]);
                  obj_temp_7.set("normals", tile["normalBuffer"]);
                  obj_temp_7.set("faceIds", faceIds);
                  obj_temp_7.set("itemIds", tile["ids"]);
                  obj_temp_7.set("material", tile["materialId"]);
                  obj_temp_7.set("matrix", this->_temp.matrix.clone());
                  obj_temp_7.set("aabb", tile["box"]["clone"]());
                  obj_temp_7.set("currentLod", tile["lod"]);
                  return js::any(obj_temp_7);
                }());
            this->updateMemoryOnTileLoad(tile);
    }
}

auto VirtualTilesController::getFaceIds(TileData tile) {
    {
            const std::shared_ptr<three::Color> tempColor = std::make_shared<three::Color>();
            const js::any faceIdBuffer = tile["faceIdBuffer"];
            const std::shared_ptr<Float32Array> faceIds = std::make_shared<Float32Array>((faceIdBuffer.length() * js::number(3)));
            for (js::number i = js::number(0); (i < faceIdBuffer.length()); i++) {
                        {
                                        const js::any id = faceIdBuffer->i;
                                        tempColor->set((js::number(0) + id));
                                        faceIds->(i * js::number(3)) = tempColor->r;
                                        faceIds->((i * js::number(3)) + js::number(1)) = tempColor->g;
                                        faceIds->((i * js::number(3)) + js::number(2)) = tempColor->b;
                        }
            }
            return faceIds;
    }
}

auto VirtualTilesController::meshData(VirtualMeshManager mesh, bool allowVoid, js::number lod) {
    {
            const js::any id = this->_temp.representation.id();
            const js::any customLod = mesh["getLodClass"]() === LodClass::CUSTOM;
            const js::any wiresLod = lod === CurrentLod::WIRES;
            if ((customLod && wiresLod)) {
                        {
                                        const js::any meshWithLod = mesh;
                                        const js::any result = meshWithLod->fetchLod(id, allowVoid);
                                        return result;
                        }
            }
            const js::any result = mesh["fetchMeshes"](id, allowVoid);
            return result;
    }
}

auto VirtualTilesController::tileAppendAttribute(TileData a, TileData b, js::string name, bool equal) {
    {
            if (b[name] === js::undefined) {
                        {
                                        return;
                        }
            }
            if (equal) {
                        {
                                        a[name] = b[name];
                                        return;
                        }
            }
            a[name] += b[name];
    }
}

auto VirtualTilesController::itemId(js::number sample) {
    {
            this->meshes.samples(sample, this->_temp.sample);
            return this->_temp.sample.item();
    }
}
