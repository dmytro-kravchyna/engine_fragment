#include "index_generated.h"
#include "virtual-box-collider.h"

using namespace js;

VirtualBoxCollider::VirtualBoxCollider(VirtualBoxCompressor compressor, js::any data) {
    {
            this->_data = data;
            this->_compressor = compressor;
    }
}

js::array<js::number> VirtualBoxCollider::frustumCollide(js::array<unknown> bounds, js::any frustum, auto fullyIncluded) {
    {
            const js::any planes = this->getFrustumPlanes(frustum, bounds);
            const js::any onCollide = this->getFrustumOnCollide(planes);
            const js::any onIncludes = this->getFrustumOnIncludes(planes);
            const js::any onSeen = this->newDefaultCallback(true);
            return this->collide(onCollide, onIncludes, onSeen, fullyIncluded);
    }
}

js::array<js::number> VirtualBoxCollider::rayCollide(js::array<unknown> bounds, js::any ray) {
    {
            const js::any onCollide = this->getRayOnCollide(ray);
            const js::any onIncludes = this->newDefaultCallback(false);
            const js::any onSeen = this->getRayOnSeen(bounds);
            return this->collide(onCollide, onIncludes, onSeen);
    }
}

auto VirtualBoxCollider::addPoint(bool fullyIncluded, js::array<js::number> result, js::number currentPosition, bool includes) {
    {
            if (!fullyIncluded) {
                        {
                                        result.push(this->getPointData(currentPosition));
                        }
            } else {
                        if (includes) {
                                        {
                                                            result.push(this->getPointData(currentPosition));
                                        }
                        }
            }
    }
}

js::number VirtualBoxCollider::getPointData(js::number position) {
    {
            const js::any point = this->getPoint(position);
            return point["data"];
    }
}

js::any VirtualBoxCollider::getBounds(js::number position) {
    {
            const js::any point = this->getPoint(position);
            return this->_compressor.inflate(point["box"]);
    }
}

bool VirtualBoxCollider::isPoint(js::number position) {
    {
            const js::any point = this->getPoint(position);
            return point["isPoint"];
    }
}

auto VirtualBoxCollider::newDefaultCallback(bool value) {
    {
            return [&](js::any _args) -> auto { return value; };
    }
}

js::number VirtualBoxCollider::groupSize(js::number position) {
    {
            const js::any point = this->getPoint(position);
            return point["size"];
    }
}

auto VirtualBoxCollider::getPoint(js::number position) {
    {
            return this->_data.points[position];
    }
}

auto VirtualBoxCollider::getRayOnSeen(js::array<unknown> bounds) {
    {
            js::any onSeen = this->newDefaultCallback(true);
            const bool boundsExists = (bounds.length() > js::number(0));
            if (boundsExists) {
                        {
                                        onSeen = [&](js::any box) -> auto { return CameraUtils::collides(box, bounds); };
                        }
            }
            return onSeen;
    }
}

auto VirtualBoxCollider::getRayOnCollide(js::any beam) {
    {
            return [&](js::any box) -> auto { return beam["intersectsBox"](box); };
    }
}

js::array<js::number> VirtualBoxCollider::collide(BoxEvent onCollide, BoxEvent onIncludes, BoxEvent onSeen, auto fullyIncluded) {
    {
            const js::any pointAmount = this->_data.points.length();
            js::array<js::number> result = js::array<js::any>{};
            js::number currentPosition = js::number(0);
            const js::any addAllPoints = [&](js::any bound, bool includes) -> auto {
            const js::number finalPosition = (currentPosition + this->groupSize(currentPosition));
            for (; (currentPosition < finalPosition); currentPosition++) {
                        {
                                        const js::any isPoint = this->isPoint(currentPosition);
                                        if ((isPoint && onSeen(bound))) {
                                                            {
                                                                                    if (!fullyIncluded) {
                                                                                                                {
                                                                                                                                                this->savePoint(currentPosition, result);
                                                                                                                }
                                                                                    } else {
                                                                                                                if (includes) {
                                                                                                                                                {
                                                                                                                                                                                    this->savePoint(currentPosition, result);
                                                                                                                                                }
                                                                                                                }
                                                                                    }
                                                            }
                                        }
                        }
            }
            };
            const js::any processCollisions = [&]() -> auto {
            const js::any bound = this->getBounds(currentPosition);
            const js::any includes = onIncludes(bound);
            const js::any isPoint = this->isPoint(currentPosition);
            const js::any collides = (includes || onCollide(bound));
            if (((isPoint && collides) && onSeen(bound))) {
                        {
                                        this->addPoint(fullyIncluded, result, currentPosition, includes);
                        }
            }
            if ((collides || isPoint)) {
                        {
                                        currentPosition++;
                                        if ((includes && !isPoint)) {
                                                            {
                                                                                    addAllPoints(bound, includes);
                                                            }
                                        }
                        }
            } else {
                        {
                                        currentPosition += this->groupSize(currentPosition);
                        }
            }
            };
            while (js::null) {
                        {
                        }
            }
            return result;
    }
}

auto VirtualBoxCollider::getFrustumOnIncludes(js::array<unknown> planes) {
    {
            return [&](js::any box) -> auto { return CameraUtils::isIncluded(box, planes); };
    }
}

auto VirtualBoxCollider::getFrustumOnCollide(js::array<unknown> planes) {
    {
            return [&](js::any box) -> auto { return CameraUtils::collides(box, planes); };
    }
}

auto VirtualBoxCollider::getFrustumPlanes(js::any frustum, js::array<unknown> bounds) {
    {
            js::array<unknown> planes = js::array<js::any>{};
            for (const auto& plane : frustum["planes"]) {
                        {
                                        planes.push(plane);
                        }
            }
            if (bounds) {
                        {
                                        for (const auto& plane : bounds) {
                                                            {
                                                                                    planes.push(plane);
                                                            }
                                        }
                        }
            }
            return planes;
    }
}

auto VirtualBoxCollider::savePoint(js::number position, js::array<js::number> result) {
    {
            const js::any point = this->getPoint(position);
            result.push(point["data"]);
    }
}
