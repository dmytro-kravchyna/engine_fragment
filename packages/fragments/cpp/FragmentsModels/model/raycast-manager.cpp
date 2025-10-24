#include "index_generated.h"
#include "raycast-manager.h"

using namespace js;

auto RaycastManager::raycast(FragmentsModel model, RaycastData data) {
    {
            auto _temp6069 = this->getRayAndFrustum(data);
            const auto frustum = _temp6069["frustum"];
            const auto ray = _temp6069["ray"];
            const js::any request = this->getRequest(model, frustum, ray);
            if (!request) {
                        return js::null;
            }
            const js::any response = co_await model["threads"]["fetch"](request);
            if ((response["results"] && response["results"].length())) {
                        {
                                        auto _temp8220 = response["results"];
                                        const auto firstHit = _temp8220[0];
                                        return this->getResult([]() {
                                              js::object obj_temp_0;
                                              obj_temp_0.set("hit", firstHit);
                                              obj_temp_0.set("frustum", frustum);
                                              obj_temp_0.set("ray", ray);
                                              obj_temp_0.set("model", model);
                                              return js::any(obj_temp_0);
                                            }());
                        }
            }
            return js::null;
    }
}

auto RaycastManager::rectangleRaycast(FragmentsModel model, MeshManager meshes, RectangleRaycastData data) {
    {
            const js::any frustum = this->getFrustum(data);
            const js::any request = this->getRequest(model, frustum);
            if (!request) {
                        return js::null;
            }
            request["fullyIncluded"] = data->fullyIncluded;
            const js::any response = co_await model["threads"]["fetch"](request);
            if ((response["localIds"] && response["localIds"].length())) {
                        {
                                        return this->newRectangleCastResponse(response, meshes);
                        }
            }
            return js::null;
    }
}

auto RaycastManager::raycastWithSnapping(FragmentsModel model, SnappingRaycastData data) {
    {
            auto _temp6668 = this->getRayAndFrustum(data);
            const auto frustum = _temp6668["frustum"];
            const auto ray = _temp6668["ray"];
            const js::any request = this->getRequest(model, frustum, ray);
            if (!request) {
                        return js::null;
            }
            request["snappingClass"] = data->snappingClasses;
            const js::any response = co_await model["threads"]["fetch"](request);
            if (response["results"]) {
                        {
                                        return this->newRaycastSnapResult(response, frustum, ray, model);
                        }
            }
            return js::null;
    }
}

auto RaycastManager::screenRectToFrustum(js::any screenTopLeft, js::any screenBottomRight, HTMLElement container, js::any camera) {
    {
            this->screenToCast(screenTopLeft, container, this->_tlp);
            this->screenToCast(screenBottomRight, container, this->_brp);
            this->setVectors(camera);
            this->setPlanes(camera);
            return this->newFrustum();
    }
}

auto RaycastManager::screenToCasterPoint(Point point, js::any viewer, js::any camera) {
    {
            const js::any casterPoint = this->screenToCast(point, viewer);
            this->_caster.setFromCamera(casterPoint, camera);
            return this->_caster.ray.clone();
    }
}

auto RaycastManager::setPlanes(js::any camera) {
    {
            this->setBasePoints();
            camera["getWorldDirection"](this->_n.normal);
            this->setEnds(camera);
    }
}

auto RaycastManager::setVectors(js::any camera) {
    {
            this->setVector(this->_tl, this->_tlp, this->_tlp, js::number(1), camera);
            this->setVector(this->_tr, this->_brp, this->_tlp, js::number(1), camera);
            this->setVector(this->_bl, this->_tlp, this->_brp, js::number(1), camera);
            this->setVector(this->_br, this->_brp, this->_brp, js::number(1), camera);
            this->setVector(this->_tln, this->_tlp, this->_tlp, js::number(0), camera);
            this->setVector(this->_brn, this->_brp, this->_brp, js::number(0), camera);
    }
}

auto RaycastManager::newFrustum() {
    {
            return std::make_shared<three::Frustum>(this->_t, this->_b, this->_l, this->_r, this->_f, this->_n);
    }
}

auto RaycastManager::setEnds(js::any camera) {
    {
            this->_n.constant = camera["position"].length()();
            this->_f.normal = this->_n.normal;
            this->_f.constant = js::number::POSITIVE_INFINITY;
    }
}

auto RaycastManager::screenToCast(Point p, js::any element, auto result) {
    {
            const js::any rect = element->getBoundingClientRect();
            const js::number scaleX = (rect->width / element->clientWidth);
            const js::number scaleY = (rect->height / element->clientHeight);
            const js::number x = ((p->x - rect->left) / scaleX);
            const js::number y = ((p->y - rect->top) / scaleY);
            result->x = (((x / element->clientWidth) * js::number(2)) - js::number(1));
            result->y = ((-(y / element->clientHeight) * js::number(2)) + js::number(1));
            return result;
    }
}

auto RaycastManager::setVector(js::any v1, js::any v2, js::any v3, js::number value, js::any camera) {
    {
            v1["set"](v2["x"], v3["y"], value);
            v1["unproject"](camera);
    }
}

auto RaycastManager::setPlane(js::any plane, js::any v1, js::any v2, js::any v3) {
    {
            plane["setFromCoplanarPoints"](v1, v2, v3);
    }
}

auto RaycastManager::setBasePoints() {
    {
            this->setPlane(this->_t, this->_tln, this->_tl, this->_tr);
            this->setPlane(this->_r, this->_brn, this->_tr, this->_br);
            this->setPlane(this->_b, this->_brn, this->_br, this->_bl);
            this->setPlane(this->_l, this->_tln, this->_bl, this->_tl);
    }
}

auto RaycastManager::setupRay(js::typed::Nullable<unknown> ray, js::any message) {
    {
            if (ray) {
                        {
                                        this->_ray.copy(ray);
                                        this->_ray.applyMatrix4(this->_inverseTransform);
                                        message["ray"] = this->_ray;
                        }
            }
    }
}

auto RaycastManager::setupMatrix(js::any object) {
    {
            this->_inverseTransform.copy(object->matrixWorld);
            this->_inverseTransform.invert();
    }
}

auto RaycastManager::getRequest(FragmentsModel model, js::any frustum, std::optional<js::any> ray) {
    {
            auto _temp565 = model;
            const auto object = _temp565["object"];
            const auto box = _temp565["box"];
            const auto modelId = _temp565["modelId"];
            const js::any collidesModel = frustum["intersectsBox"](box);
            if (collidesModel) {
                        {
                                        return this->newCastRequest(object, modelId, ray, frustum);
                        }
            }
            return js::null;
    }
}

auto RaycastManager::getRayAndFrustum(RaycastData data) {
    {
            this->updateCamera(data->camera);
            auto _temp1871 = this->getCorners(data->mouse);
            const auto bottomLeft = _temp1871["bottomLeft"];
            const auto topRight = _temp1871["topRight"];
            const js::any ray = this->screenToCasterPoint(data->mouse, data->dom, data->camera);
            const js::any frustum = this->screenRectToFrustum(bottomLeft, topRight, data->dom, data->camera);
            return []() {
                  js::object obj_temp_1;
                  obj_temp_1.set("ray", ray);
                  obj_temp_1.set("frustum", frustum);
                  return js::any(obj_temp_1);
                }();
    }
}

auto RaycastManager::getFrustum(js::any data) {
    {
            this->updateCamera(data->camera);
            return this->screenRectToFrustum(data->topLeft, data->bottomRight, data->dom, data->camera);
    }
}

auto RaycastManager::getCorners(js::any mouse) {
    {
            const js::any bottomLeft = mouse["clone"]()["subScalar"](this->distance);
            const js::any topRight = mouse["clone"]()["addScalar"](this->distance);
            return []() {
                  js::object obj_temp_2;
                  obj_temp_2.set("bottomLeft", bottomLeft);
                  obj_temp_2.set("topRight", topRight);
                  return js::any(obj_temp_2);
                }();
    }
}

auto RaycastManager::getResult(js::any data) {
    {
            auto _temp3610 = data;
            const auto hit = _temp3610["hit"];
            const auto frustum = _temp3610["frustum"];
            const auto ray = _temp3610["ray"];
            const auto model = _temp3610["model"];
            const Partial result = []() {
                  js::object obj_temp_3;
                  return js::any(obj_temp_3);
                }();
            this->setPoint(model, hit, result);
            this->setNormal(model, hit, result);
            this->setDistance(model, hit, result);
            this->setRayDistance(model, hit, result);
            this->setBasicHitData(model, hit, result, ray, frustum);
            this->setSnapEdge(model, hit, result, "snappedEdgeP1"_S);
            this->setSnapEdge(model, hit, result, "snappedEdgeP2"_S);
            result->facePoints = hit["facePoints"];
            result->faceIndices = hit["faceIndices"];
            return result;
    }
}

auto RaycastManager::updateCamera(js::any camera) {
    {
            camera["updateProjectionMatrix"]();
            camera["updateWorldMatrix"](true, true);
    }
}

auto RaycastManager::newCastRequest(js::any object, js::string modelId, js::typed::Nullable<unknown> ray, js::any frustum) {
    {
            this->setupMatrix(object);
            const js::any request = []() {
                  js::object obj_temp_4;
                  return js::any(obj_temp_4);
                }();
            request["class"] = MultiThreadingRequestClass::RAYCAST;
            request["modelId"] = modelId;
            this->setupRay(ray, request);
            CameraUtils::transform(frustum, this->_inverseTransform, this->_frustum);
            request["frustum"] = this->_frustum;
            return request;
    }
}

auto RaycastManager::setSnapEdge(FragmentsModel model, js::any hit, Partial result, js::any key) {
    {
            if (hit[key]) {
                        {
                                        const std::shared_ptr<three::Vector3> edge = std::make_shared<three::Vector3>();
                                        edge["copy"](hit[key]);
                                        edge["applyMatrix4"](model["object"]["matrixWorld"]);
                                        result->key = edge;
                        }
            } else {
                        {
                                        result->key = js::undefined;
                        }
            }
    }
}

auto RaycastManager::setNormal(FragmentsModel model, js::any hit, Partial result) {
    {
            if (hit["normal"]) {
                        {
                                        const std::shared_ptr<three::Vector3> normal = std::make_shared<three::Vector3>();
                                        normal["copy"](hit["normal"]);
                                        normal["transformDirection"](model["object"]["matrixWorld"]);
                                        normal["normalize"]();
                                        result->normal = normal;
                                        return;
                        }
            }
            result->normal = js::undefined;
    }
}

auto RaycastManager::setDistance(FragmentsModel model, js::any hit, Partial result) {
    {
            const js::any cameraDist = js::Math::sqrt(hit["cameraSquaredDistance"]);
            const js::any modelScale = model["object"]["matrixWorld"]["getMaxScaleOnAxis"]();
            result->distance = (cameraDist * modelScale);
    }
}

auto RaycastManager::setPoint(FragmentsModel model, js::any hit, Partial result) {
    {
            const std::shared_ptr<three::Vector3> point = std::make_shared<three::Vector3>();
            point["copy"](hit["point"]);
            point["applyMatrix4"](model["object"]["matrixWorld"]);
            result->point = point;
    }
}

auto RaycastManager::newRaycastSnapResult(js::any response, js::any frustum, js::any ray, FragmentsModel model) {
    {
            js::array<RaycastResult> results = js::array<js::any>{};
            for (const auto& hit : response["results"]) {
                        {
                                        const js::any result = this->getResult([]() {
                                              js::object obj_temp_5;
                                              obj_temp_5.set("hit", hit);
                                              obj_temp_5.set("frustum", frustum);
                                              obj_temp_5.set("ray", ray);
                                              obj_temp_5.set("model", model);
                                              return js::any(obj_temp_5);
                                            }());
                                        results.push(result);
                        }
            }
            return results;
    }
}

auto RaycastManager::newRectangleCastResponse(js::any response, MeshManager meshes) {
    {
            const RectangleRaycastResult result = []() {
                  js::object obj_temp_6;
                  obj_temp_6.set("localIds", response["localIds"]);
                  obj_temp_6.set("fragments", meshes["list"]["get"](response["modelId"]));
                  return js::any(obj_temp_6);
                }();
            return result;
    }
}

auto RaycastManager::setRayDistance(FragmentsModel model, js::any hit, Partial result) {
    {
            if (hit["raySquaredDistance"] !== js::undefined) {
                        {
                                        const js::any modelScale = model["object"]["matrixWorld"]["getMaxScaleOnAxis"]();
                                        const js::any rayDist = js::Math::sqrt(hit["raySquaredDistance"]);
                                        result->rayDistance = (rayDist * modelScale);
                                        return;
                        }
            }
            result->rayDistance = js::undefined;
    }
}

auto RaycastManager::setBasicHitData(FragmentsModel model, js::any hit, Partial result, js::typed::Nullable<unknown> ray, js::any frustum) {
    {
            result->itemId = hit["itemId"];
            result->localId = hit["localId"];
            result->object = model["object"];
            result->fragments = model;
            result->ray = ray;
            result->frustum = frustum;
            result->representationClass = hit["representationClass"];
            result->snappingClass = hit["snappingClass"];
    }
}
