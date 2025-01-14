#pragma once

#include "entities.hpp"
#include <memory>
#include <unordered_map>

class Manager {
    using objMap = std::unordered_map<std::string, std::shared_ptr<SpaceObj>>;
    objMap objects;

  public:
    template <typename SpaceT> std::shared_ptr<SpaceT> AddObj(const std::string &name, v3f pos) {
        static_assert(std::is_base_of_v<SpaceObj, SpaceT>,
                      "SpaceT must be derived from SpaceObj class");

        if (objects.find(name) != objects.end()) {
            throw std::invalid_argument("Object name duplicate: " + name);
        }

        auto [iter, success] = objects.emplace(name, std::make_shared<SpaceT>(name, pos));
        if (!success) {
            throw std::runtime_error("Failed to emplace");
        }

        return std::static_pointer_cast<SpaceT>(iter->second);
    }

    objMap::iterator GetObj(std::string name) { return objects.find(name); }

    void Update(float delta) {
        for (auto &[name, obj] : objects) {
            obj->Update(delta);
        }
    }

    void Draw(sf::RenderWindow &window, const Camera &from) {
        for (auto &[name, obj] : objects) {
            obj->Draw(window, from);
        }
    }

    void RmObj(std::string name) { objects.erase(name); }
};
