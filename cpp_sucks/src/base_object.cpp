#include <algorithm>
using std::remove_if;

#include "base_object.h"

FClass::FClass() {
    this->name = "";
}

FClass::FClass(const string& name) {
    this->name = name;
}

const string& FClass::Name() const {
    return this->name;
}

void FClass::Update(float deltaMs, FObject& object) {
    for (auto& component: this->components) {
        component->Update(deltaMs, object);
    }
}

void FClass::AddComponent(shared_ptr<IComponent> component) {
    this->components.push_back(component);
}

void FClass::Initialise() {
    // remove fake components
    this->components.erase(
        remove_if(
            this->components.begin(),
            this->components.end(),
            [](const auto& component) { return !component; }
        )
    );

    // sort components by priority
    sort(
        this->components.begin(),
        this->components.end(),
        [](const auto& a, const auto& b) { return a->Priority() < b->Priority(); }
    );
}
