#include "index_generated.h"
#include "view-manager.h"

using namespace js;

auto ViewManager::refreshView(FragmentsModel model, MeshManager meshes) {
    {
            const js::any fov = this->setup(meshes, model);
            const js::any frustum = CameraUtils::transform(this->_tempFrustum, this->_tempMatrix);
            const js::any request = this->newViewRequest(frustum, fov, model);
            co_await model["threads"]["fetch"](request);
    }
}

auto ViewManager::useCamera(js::any camera) {
    {
            const std::shared_ptr<three::Matrix4> projScreenMatrix = std::make_shared<three::Matrix4>();
            this->setCameraPosition(camera);
            this->setCameraFrustum(camera, projScreenMatrix);
            this->setFov(camera);
            this->setOrtho();
    }
}

auto ViewManager::getOrthoSize() {
    {
            js::any orthoSize = this->_updateOrthoSizeEvent();
            if (orthoSize) {
                        {
                                        const js::any modelScale = this->_tempMatrix.getMaxScaleOnAxis();
                                        orthoSize *= modelScale;
                        }
            }
            return orthoSize;
    }
}

auto ViewManager::setup(MeshManager meshes, FragmentsModel model) {
    {
            meshes["requests"]["clean"](model["modelId"]);
            this->_tempMatrix.copy(model["object"]["matrixWorld"]).invert();
            this->_updateCameraPositionEvent(this->_tempVec);
            this->_updateCameraFrustumEvent(this->_tempFrustum);
            const js::any fov = this->_updateFOVEvent();
            return fov;
    }
}

auto ViewManager::newViewRequest(js::any frustum, js::any fov, FragmentsModel model) {
    {
            const js::any view = this->newView(frustum, fov, model);
            const js::any request = []() {
                  js::object obj_temp_0;
                  return js::any(obj_temp_0);
                }();
            request["class"] = MultiThreadingRequestClass::REFRESH_VIEW;
            request["modelId"] = model["modelId"];
            request["cameraFrustum"] = frustum;
            request["view"] = view;
            return request;
    }
}

auto ViewManager::newView(js::any frustum, js::any fov, FragmentsModel model) {
    {
            const js::any view = []() {
                  js::object obj_temp_1;
                  return js::any(obj_temp_1);
                }();
            view["cameraFrustum"] = frustum;
            view["cameraPosition"] = this->_tempVec.applyMatrix4(this->_tempMatrix);
            view["fov"] = fov;
            view["orthogonalDimension"] = this->getOrthoSize();
            view["viewSize"] = js::Math::max(window["innerWidth"], window["innerHeight"]);
            view["graphicThreshold"] = GPU::estimateCapacity();
            view["graphicQuality"] = ((model["graphicsQuality"] * -js::number(1.5)) + js::number(2));
            view["clippingPlanes"] = this->getPlanes();
            view["modelPlacement"] = model["object"]["matrixWorld"];
            return view;
    }
}

auto ViewManager::setOrtho() {
    {
            this->_updateOrthoSizeEvent = [&]() -> auto { return js::undefined; };
    }
}

auto ViewManager::setFov(js::any camera) {
    {
            this->_updateFOVEvent = [&]() -> auto {
            if (js::instanceof_op(camera, "three::PerspectiveCamera")) {
                        {
                                        return camera["fov"];
                        }
            }
            return js::undefined;
            };
    }
}

auto ViewManager::getPlanes() {
    {
            js::array<unknown> planes = js::array<js::any>{};
            const js::any originalPlanes = this->getClippingPlanesEvent();
            for (const auto& plane : originalPlanes) {
                        {
                                        const js::any cloned = plane["clone"]();
                                        cloned["applyMatrix4"](this->_tempMatrix);
                                        planes.push(cloned);
                        }
            }
            return planes;
    }
}

auto ViewManager::setCameraPosition(js::any camera) {
    {
            this->_updateCameraPositionEvent = [&](js::any position) -> auto {
            position["copy"](camera["position"]);
            };
    }
}

auto ViewManager::setCameraFrustum(js::any camera, js::any projScreenMatrix) {
    {
            this->_updateCameraFrustumEvent = [&](js::any frustum) -> auto {
            camera["updateProjectionMatrix"]();
            camera["updateWorldMatrix"](true, true);
            auto _temp7363 = camera;
            const auto projectionMatrix = _temp7363["projectionMatrix"];
            const auto matrixWorldInverse = _temp7363["matrixWorldInverse"];
            projScreenMatrix->multiplyMatrices(projectionMatrix, matrixWorldInverse);
            frustum["setFromProjectionMatrix"](projScreenMatrix);
            };
    }
}
