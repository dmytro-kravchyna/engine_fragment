#include "index_generated.h"
#include "profiles.h"

using namespace js;

Profiles::Profiles(Plane plane) {
    {
            this->plane = plane;
    }
}

auto Profiles::add(Edge edge) {
    {
            const js::any matches = this->match(edge);
            if (matches.length() === js::number(0)) {
                        {
                                        const js::any profileId = this->nextProfileID++;
                                        const std::shared_ptr<Profile> profile = std::make_shared<Profile>(this->plane);
                                        profile["add"](edge);
                                        this->list.set(profileId, profile);
                                        return;
                        }
            }
            if (matches.length() === js::number(1)) {
                        {
                                        const js::any profile = this->list.get(matches[js::number(0)]);
                                        profile["add"](edge);
                                        return;
                        }
            }
            if ((matches.length() > js::number(1))) {
                        {
                                        const js::any profile = this->list.get(matches[js::number(0)]);
                                        profile["add"](edge);
                                        const js::any profileToMerge = this->list.get(matches[js::number(1)]);
                                        profile["merge"](profileToMerge);
                                        this->list.delete(matches[js::number(1)]);
                        }
            }
    }
}

auto Profiles::getProfiles() {
    {
            js::typed::Nullable<js::number> biggestProfile = js::null;
            js::number biggestProfileSize = js::number(0);
            for (const auto& js::undefined : this->list) {
                        {
                                        const js::any area = profile["getArea"]();
                                        if ((area > biggestProfileSize)) {
                                                            {
                                                                                    biggestProfileSize = area;
                                                                                    biggestProfile = profileId;
                                                            }
                                        }
                        }
            }
            if (biggestProfile === js::null) {
                        {
                                        return js::null;
                        }
            }
            const js::any profile = this->list.get(biggestProfile).getIndices();
            js::array<js::array<js::number>> holes = js::array<js::any>{};
            for (const auto& js::undefined : this->list) {
                        {
                                        if (profileId === biggestProfile) {
                                                            continue;
                                        }
                                        holes.push(profile["getIndices"]());
                        }
            }
            return []() {
                  js::object obj_temp_0;
                  obj_temp_0.set("profile", profile);
                  obj_temp_0.set("holes", holes);
                  return js::any(obj_temp_0);
                }();
    }
}

auto Profiles::match(Edge edge) {
    {
            js::array<js::number> ids = js::array<js::any>{};
            for (const auto& js::undefined : this->list) {
                        {
                                        if ((profile.match(edge) > js::number(0))) {
                                                            {
                                                                                    ids.push(id);
                                                            }
                                        }
                        }
            }
            return ids;
    }
}
